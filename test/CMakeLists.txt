message(STATUS "Building unit tests...")
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

include_directories(
   ${CMAKE_CURRENT_LIST_DIR}/../Catch2/single_include
   ${CMAKE_CURRENT_LIST_DIR}/../include
   PUBLIC /opt/boost/boost_1_70_0/include/
   )

add_library(test_main ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

enable_testing()

# Listing test srcs
set(main, main.cpp)

file(GLOB srcs RELATIVE ${CMAKE_CURRENT_LIST_DIR} *.cpp)
foreach(src ${srcs})
  get_filename_component(test_name ${src} NAME_WE)
  message(${test_name})
  add_executable(${test_name} main ${src})
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

