cmake_minimum_required(VERSION 2.8)

project(simple)

FILE(
  GLOB SOURCE_FILES
  src/audio/*.h
  src/audio/*.c
src/filesystem/*.h
src/filesystem/*.c
src/graphics/*.h
src/graphics/*.c
src/image/*.h
src/image/*.c
src/luaapi/*.h
src/luaapi/*.c
src/math/*.h
src/math/*.c
src/timer/*.h
src/timer/*.c
src/*.c
src/*.h
)

set(love_package "love")
set(love_creator "Muresan Vlad")
set(love_copyright "Copyright (c) 2015, ${love_creator}.")

include_directories(src/3rdparty/stb)

add_executable(
  love
  ${SOURCE_FILES}
  src/3rdparty/stb
  )

#freetype
add_subdirectory(src/3rdparty/freetype)
set(FREETYPE_INCLUDE_DIR src/3rdparty/freetype/include)
set(FREETYPE_LIBRARIES freetype)
include_directories(src/3rdparty/freetype/include)

if(APPLE)
  target_link_libraries(love ${FREETYPE_LIBRARIES})
endif()

if(UNIX)
  target_link_libraries(love dl ${FREETYPE_LIBRARIES})
endif()

IF(WIN32)
  FIND_PACKAGE(OpenGL REQUIRED)

  LINK_DIRECTORIES("$ENV{DXSDK_DIR}/Lib/$ENV{PROCESSOR_ARCHITECTURE}")
  SET(SDL_BUILDING_LIBRARY ON)
  SET(USE_NETWORKING FALSE)

  IF(SSE2_TRUE)
    SET(SSE_FLAG /arch:SSE2)
  ELSEIF(SSE_TRUE)
    SET(SSE_FLAG /arch:SSE)
  ENDIF()

  SET(flag_var "/MD")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /EHsc /nologo /GR /FC /DWIN32 /D_MBCS")
  SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /Z7 /W4 /Od /MDd /D_DEBUG /D__Debug__")
  SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /W1 /O2 /Ot /MD /DNDEBUG /fp:fast ${SSE_FLAG}")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /EHsc /nologo /GR /FC /DWIN32 /D_MBCS")
  SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Z7 /W4 /Od /MDd /D_DEBUG /D__Debug__")
  SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W1 /O2 /Ot /MD /DNDEBUG /fp:fast ${SSE_FLAG}")


  SET(FREETYPE_LIBRARY "freetype")
  SET(OPENAL_LIBRARY "OpenAL32")
ENDIF(WIN32)

if(WIN32)
  target_link_libraries(love ws2_32.lib ${FREETYPE_LIBRARIES})
endif()
