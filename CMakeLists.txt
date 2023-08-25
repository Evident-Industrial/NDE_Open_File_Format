cmake_minimum_required(VERSION 3.12)
project(nde-file-format)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "14")
    message(FATAL_ERROR "Insufficient msvc version")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "10")
    message(FATAL_ERROR "Insufficient clang version")
  endif()
endif()

set(HDF5_DIR "${CMAKE_BINARY_DIR}/hdf5")

include(ExternalProject)

ExternalProject_add(HDF5
  SOURCE_DIR ${HDF5_DIR}
  URL https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.14/hdf5-1.14.1/src/hdf5-1.14.1-2.tar.gz
  UPDATE_COMMAND ""
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=${BUILD_TYPE}
    -DHDF5_BUILD_CPP_LIB:BOOL=OFF
    -DHDF5_ENABLE_Z_LIB_SUPPORT:BOOL=OFF
    -DBUILD_SHARED_LIBS:BOOL=OFF
    -DHDF5_BUILD_TOOLS:BOOL=OFF
    -DHDF5_BUILD_EXAMPLES:BOOL=OFF
    -DBUILD_TESTING:BOOL=OFF
    -DBUILD_STATIC:BOOL=OFF
    -DCMAKE_INSTALL_PREFIX:PATH=${HDF5_DIR}
)

ExternalProject_Add(rapidjson_external
  PREFIX ${RAPIDJSON_DIR}
  GIT_REPOSITORY https://github.com/Tencent/rapidjson.git
  GIT_TAG master  # Use the desired branch or tag here
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""    
  INSTALL_COMMAND "" 
)

ExternalProject_Get_Property(rapidjson_external source_dir)
set(RAPIDJSON_INCLUDE_DIRS ${source_dir}/include)

include_directories(.)

find_package(ZLIB)

if(NOT ZLIB_FOUND)
    message(STATUS "Zlib not found. Download ZLIB to finish build: https://gnuwin32.sourceforge.net/packages/zlib.htm")
endif()

if (WIN32)
  if(EXISTS ${HDF5_DIR}/lib/libhdf5_cpp.lib)
    set(LIBRARIES
    "${HDF5_DIR}/lib/libhdf5.lib"
    ZLIB::ZLIB)
  else() 
    set(LIBRARIES
    "${HDF5_DIR}/lib/libhdf5_D.lib"
    ZLIB::ZLIB)
  endif()
else()
  set(LIBRARIES
    "${HDF5_DIR}/lib/libhdf5.a"
    ZLIB::ZLIB 
    dl)
endif()

set(HDF5_INCLUDE_DIRS "${HDF5_DIR}/include")

include_directories(${HDF5_INCLUDE_DIRS} ${RAPIDJSON_INCLUDE_DIRS})
link_libraries(${LIBRARIES})

add_executable("create-file" examples/create-file/main.cpp)
add_dependencies("create-file" HDF5)

add_executable("read-ascan" examples/read-ascan/main.cpp)
add_dependencies("read-ascan" HDF5)

add_executable("read-setup" examples/read-setup/main.cpp)
add_dependencies("read-setup" HDF5)

add_executable("write-ascan" examples/write-ascan/main.cpp)
add_dependencies("write-ascan" HDF5)
