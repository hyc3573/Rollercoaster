set(CMAKE_SYSTEM_NAME Windows)
set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc-posix)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++-posix)
set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)
set(CMAKE_MAKE_PROGRAM "/usr/bin/make")

set(CMAKE_INCLUDE_DIR "/usr/x86_64-w64-mingw32/include")
include_directories(/usr/x86_64-w64-mingw32/include)
set(CMAKE_LIBRARY_DIR /usr/x86_64-w64-mingw32/lib)

set(CMAKE_FIND_LIBRARY_SUFFIXES "-s.a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_compile_options(-Wa,-mbig-obj)
