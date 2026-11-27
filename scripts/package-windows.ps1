param(
    [string]$QtPath = $env:CMAKE_PREFIX_PATH,
    [string]$Configuration = "Release"
)

if (-not $QtPath) {
    Write-Error "Set CMAKE_PREFIX_PATH or pass -QtPath (e.g. C:\Qt\6.12.0\msvc2022_64)"
    exit 1
}

cmake -S . -B build -G "Visual Studio 17 2022" -A x64 `
    -DCMAKE_PREFIX_PATH="$QtPath" -DMXU_BUILD_TESTS=ON
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

cmake --build build --config $Configuration --parallel
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

ctest --test-dir build -C $Configuration --output-on-failure
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

$stage = "build/package/MxuSlides"
New-Item -ItemType Directory -Force -Path $stage | Out-Null
Copy-Item "build/$Configuration/MxuSlides.exe" $stage
Copy-Item "build/$Configuration/"*.dll $stage -ErrorAction SilentlyContinue
Compress-Archive -Path $stage -DestinationPath "build/MxuSlides-Windows.zip" -Force
Write-Host "Package: build/MxuSlides-Windows.zip"
