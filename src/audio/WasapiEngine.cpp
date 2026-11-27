#include "WasapiEngine.h"

#ifdef Q_OS_WIN
#define NOMINMAX
#include <windows.h>
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <avrt.h>
#include <objbase.h>
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "avrt.lib")

namespace {
class WasapiContext
{
public:
    IMMDeviceEnumerator* enumerator = nullptr;
    IMMDevice* device = nullptr;
    IAudioClient* client = nullptr;
    IAudioRenderClient* render = nullptr;
    HANDLE event = nullptr;
    HANDLE thread = nullptr;
    volatile bool running = false;
    UINT32 bufferFrames = 480;
    void* engine = nullptr;
};
}
#endif

namespace mxu::audio {

WasapiRenderEngine::WasapiRenderEngine(QObject* parent)
    : QObject(parent)
{
}

WasapiRenderEngine::~WasapiRenderEngine()
{
    stop();
}

bool WasapiRenderEngine::available() const
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

bool WasapiRenderEngine::start()
{
#ifdef Q_OS_WIN
    if (m_active)
        return true;
    auto* context = new WasapiContext();
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr) && hr != RPC_E_CHANGED_MODE) {
        emit errorOccurred(QStringLiteral(u"COM initialization failed"));
        delete context;
        return false;
    }
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
                          __uuidof(IMMDeviceEnumerator),
                          reinterpret_cast<void**>(&context->enumerator));
    if (FAILED(hr)) {
        emit errorOccurred(QStringLiteral(u"Cannot create device enumerator"));
        delete context;
        return false;
    }
    hr = context->enumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &context->device);
    if (FAILED(hr)) {
        emit errorOccurred(QStringLiteral(u"No default render device"));
        context->enumerator->Release();
        delete context;
        return false;
    }
    hr = context->device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr,
                                   reinterpret_cast<void**>(&context->client));
    if (FAILED(hr)) {
        emit errorOccurred(QStringLiteral(u"Cannot activate audio client"));
        context->device->Release();
        context->enumerator->Release();
        delete context;
        return false;
    }

    WAVEFORMATEX format{};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 2;
    format.nSamplesPerSec = 48000;
    format.wBitsPerSample = 16;
    format.nBlockAlign = static_cast<WORD>(format.nChannels * format.wBitsPerSample / 8);
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
    format.cbSize = 0;

    REFERENCE_TIME requested = 10000; // 10 ms
    hr = context->client->Initialize(AUDCLNT_SHAREMODE_SHARED,
                                     AUDCLNT_STREAMFLAGS_EVENTCALLBACK | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM
                                         | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY,
                                     requested, 0, &format, nullptr);
    if (FAILED(hr)) {
        emit errorOccurred(QStringLiteral(u"IAudioClient::Initialize failed"));
        context->client->Release();
        context->device->Release();
        context->enumerator->Release();
        delete context;
        return false;
    }
    context->client->GetBufferSize(&context->bufferFrames);
    context->client->GetService(__uuidof(IAudioRenderClient),
                                reinterpret_cast<void**>(&context->render));
    context->event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    context->client->SetEventHandle(context->event);

    context->engine = this;
    m_sampleRate = static_cast<int>(format.nSamplesPerSec);
    m_bufferFrames = static_cast<int>(context->bufferFrames);
    m_context = context;
    context->running = true;
    context->client->Start();
    m_active = true;
    emit changed();

    // Render loop: wait for the WASAPI event, fill the buffer from the callback.
    // The lambda owns the context and releases it on exit.
    context->thread = CreateThread(nullptr, 0, [](LPVOID parameter) -> DWORD {
        auto* ctx = static_cast<WasapiContext*>(parameter);
        const DWORD priority = AvSetMmThreadCharacteristicsW(L"Pro Audio", nullptr);
        while (ctx->running) {
            WaitForSingleObject(ctx->event, INFINITE);
            UINT32 padding = 0;
            ctx->client->GetCurrentPadding(&padding);
            const UINT32 frames = ctx->bufferFrames - padding;
            if (frames == 0)
                continue;
            BYTE* data = nullptr;
            if (FAILED(ctx->render->GetBuffer(frames, &data)))
                continue;
            auto* engine = static_cast<WasapiRenderEngine*>(ctx->engine);
            const QVector<float> rendered = engine->renderFrames(static_cast<int>(frames));
            auto* samples = reinterpret_cast<short*>(data);
            for (UINT32 i = 0; i < frames * 2; ++i) {
                const float value = rendered.size() > static_cast<qsizetype>(i)
                                        ? rendered.at(static_cast<qsizetype>(i)) : 0.0f;
                samples[i] = static_cast<short>(qBound(-1.0f, value, 1.0f) * 32767.0f);
            }
            ctx->render->ReleaseBuffer(frames, 0);
        }
        if (priority)
            AvRevertMmThreadCharacteristics(priority);
        return 0;
    }, context, 0, nullptr);
    return true;
#else
    emit errorOccurred(QStringLiteral(u"WASAPI is available on Windows only"));
    return false;
#endif
}

void WasapiRenderEngine::stop()
{
#ifdef Q_OS_WIN
    if (!m_context || !m_active)
        return;
    auto* context = static_cast<WasapiContext*>(m_context);
    context->running = false;
    if (context->thread) {
        SetEvent(context->event);
        WaitForSingleObject(context->thread, 2000);
        CloseHandle(context->thread);
    }
    context->client->Stop();
    if (context->render) context->render->Release();
    if (context->event) CloseHandle(context->event);
    context->client->Release();
    context->device->Release();
    context->enumerator->Release();
    delete context;
    m_context = nullptr;
    m_active = false;
    emit changed();
#else
    if (m_active) {
        m_active = false;
        emit changed();
    }
#endif
}

QVector<float> WasapiRenderEngine::renderFrames(int frames)
{
    if (m_callback && frames > 0)
        return m_callback(frames);
    return QVector<float>(frames * 2, 0.0f);
}

} // namespace mxu::audio
