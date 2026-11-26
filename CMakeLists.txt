cmake_minimum_required(VERSION 3.25)

project(MxuSlidesWindows
    VERSION 0.1.0
    DESCRIPTION "MxU Slides for Windows — C++20 / Qt 6"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(MXU_BUILD_TESTS "Build unit tests" OFF)
option(MXU_ENABLE_NDI "Enable NDI sender (requires NDI SDK)" OFF)
option(MXU_ENABLE_DECKLINK "Enable DeckLink output (requires Blackmagic SDK)" OFF)

if(MSVC)
    add_compile_options(/W4 /permissive- /utf-8 /EHsc /Zc:__cplusplus)
    add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN UNICODE)
else()
    add_compile_options(-Wall -Wextra)
endif()

if(MXU_ENABLE_NDI)
    add_compile_definitions(MXU_HAS_NDI_SDK=1)
endif()
if(MXU_ENABLE_DECKLINK)
    add_compile_definitions(MXU_HAS_DECKLINK_SDK=1)
endif()

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core Gui Qml Quick QuickControls2 Network WebSockets Svg Multimedia QuickDialogs2
)
qt_standard_project_setup(REQUIRES 6.5)

qt_add_library(mxu_core STATIC
    src/core/generated/Models.h
    src/core/generated/Models.cpp
    src/core/Document.h
    src/core/Document.cpp
    src/core/ShowDocument.h
    src/core/ShowDocument.cpp
    src/core/SceneModel.h
    src/core/SceneModel.cpp
)
target_include_directories(mxu_core PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mxu_core PUBLIC Qt6::Core Qt6::Gui)

qt_add_library(mxu_shell STATIC
    src/app/Models.h
    src/app/Models.cpp
    src/app/AppController.h
    src/app/AppController.cpp
    src/api/LocalApiServer.h
    src/api/LocalApiServer.cpp
    src/app/MediaService.h
    src/app/MediaService.cpp
    src/app/AudioService.h
    src/app/AudioService.cpp
    src/app/OutputManager.h
    src/app/OutputManager.cpp
    src/api/OutputBackends.h
    src/api/OutputBackends.cpp
    src/app/AutomationService.h
    src/app/AutomationService.cpp
    src/app/NotesService.h
    src/app/NotesService.cpp
)
target_include_directories(mxu_shell PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mxu_shell PUBLIC
    mxu_core
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Network Qt6::WebSockets Qt6::Svg Qt6::Multimedia
)

qt_add_resources(MXU_RESOURCES resources.qrc)
qt_add_executable(mxu-slides WIN32
    src/main.cpp
    ${MXU_RESOURCES}
)
target_include_directories(mxu-slides PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mxu-slides PRIVATE
    mxu_shell
    Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::Svg Qt6::QuickDialogs2
)
set_target_properties(mxu-slides PROPERTIES
    OUTPUT_NAME "MxuSlides"
    WIN32_EXECUTABLE ON
)

if(MXU_BUILD_TESTS)
    enable_testing()
    find_package(Qt6 REQUIRED COMPONENTS Test)
    add_subdirectory(tests)
endif()
