# FindFFmpeg — minimal finder for avcodec/avformat/avutil/swscale.
# Provides FFmpeg_FOUND and imported targets FFmpeg::<component>.

find_path(FFMPEG_INCLUDE_DIR
    NAMES libavcodec/avcodec.h
    HINTS ENV FFMPEG_ROOT
    PATH_SUFFIXES include
)
find_path(FFMPEG_SWSCALE_INCLUDE_DIR
    NAMES libswscale/swscale.h
    HINTS ENV FFMPEG_ROOT
    PATH_SUFFIXES include
)

set(_ffmpeg_components avcodec avformat avutil swscale)
set(FFmpeg_FOUND TRUE)
set(FFMPEG_LIBRARIES "")

foreach(_comp IN LISTS _ffmpeg_components)
    find_library(FFMPEG_${_comp}_LIBRARY
        NAMES ${_comp}
        HINTS ENV FFMPEG_ROOT
        PATH_SUFFIXES lib lib64
    )
    if(NOT FFMPEG_${_comp}_LIBRARY)
        set(FFmpeg_FOUND FALSE)
    else()
        list(APPEND FFMPEG_LIBRARIES ${FFMPEG_${_comp}_LIBRARY})
        if(NOT TARGET FFmpeg::${_comp})
            add_library(FFmpeg::${_comp} UNKNOWN IMPORTED)
            set_target_properties(FFmpeg::${_comp} PROPERTIES
                IMPORTED_LOCATION "${FFMPEG_${_comp}_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${FFMPEG_INCLUDE_DIR};${FFMPEG_SWSCALE_INCLUDE_DIR}"
            )
        endif()
    endif()
endforeach()

if(NOT FFMPEG_INCLUDE_DIR OR NOT FFMPEG_SWSCALE_INCLUDE_DIR)
    set(FFmpeg_FOUND FALSE)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FFmpeg
    REQUIRED_VARS FFMPEG_INCLUDE_DIR FFMPEG_SWSCALE_INCLUDE_DIR FFMPEG_LIBRARIES
)
