cmake_minimum_required(VERSION 3.14)
project(pokedex)
set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

ExternalProject_Add(lyra
  GIT_REPOSITORY https://github.com/bfgroup/Lyra
  TIMEOUT 10
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON)

ExternalProject_Get_Property(lyra source_dir)

link_directories(${binary_dir})
include_directories(${source_dir}/include)

ExternalProject_Add(restclient-cpp
  GIT_REPOSITORY https://github.com/mrtazz/restclient-cpp/
  TIMEOUT 10
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON)

ExternalProject_Get_Property(restclient-cpp source_dir)
ExternalProject_Get_Property(restclient-cpp binary_dir)

include_directories(${source_dir}/include)
include_directories(${binary_dir}/include)
link_directories(${binary_dir})

ExternalProject_Add(json11_lib
  GIT_REPOSITORY https://github.com/dropbox/json11/
  TIMEOUT 10
  INSTALL_COMMAND ""
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON)

ExternalProject_Get_Property(json11_lib source_dir)
ExternalProject_Get_Property(json11_lib binary_dir)
include_directories(${source_dir})
link_directories(${binary_dir})

add_executable(pokedex main.cpp pokemon.cc)
add_dependencies(pokedex lyra restclient-cpp json11_lib)
target_link_libraries(pokedex -lrestclient-cpp -ljson11)