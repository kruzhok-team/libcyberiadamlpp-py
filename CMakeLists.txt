cmake_minimum_required(VERSION 3.21)

project(cyberiadamlpp-python VERSION 1.0)

set(cyberiadaml_DIR /usr/lib/cmake)
find_package(cyberiadaml REQUIRED)
set(cyberiadamlpp_DIR /usr/lib/cmake)
find_package(cyberiadamlpp REQUIRED)

if(!cyberiadamlpp_FOUND)
  message(FATAL_ERROR "Cannot find libcyberiadamlpp C++ library")
endif()

set (PYTHON_EXECUTABLE "/usr/bin/python3")
find_package(pybind11 CONFIG REQUIRED)

if(!pybind11_FOUND)
  message(FATAL_ERROR "Cannot find pybind11 library")
endif()

string(REPLACE "." ";" pybind11_VERSION_list "${pybind11_VERSION}")
list(GET pybind11_VERSION_list 0 PYBIND_MAJOR_VERSION)
list(GET pybind11_VERSION_list 1 PYBIND_MINOR_VERSION)

add_compile_definitions(
  PYBIND_MAJOR_VERSION=${PYBIND_MAJOR_VERSION}
  PYBIND_MINOR_VERSION=${PYBIND_MINOR_VERSION}
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D__DEBUG__")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CyberiadaML MODULE cyberiadamlpp-py.cpp)
set_target_properties(CyberiadaML PROPERTIES PREFIX "")

if (WIN32)
  add_custom_command(TARGET CyberiadaML
    POST_BUILD
    COMMAND copy "$<TARGET_FILE:CyberiadaML>" "${PROJECT_BINARY_DIR}/tests/"
  )
else()
  add_custom_command(TARGET CyberiadaML
    POST_BUILD
    COMMAND ln -sf "$<TARGET_FILE:CyberiadaML>" "${PROJECT_BINARY_DIR}/tests/"
  )
endif()

target_include_directories(CyberiadaML PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${cyberiadaml_INCLUDE_DIRS}
  ${cyberiadamlpp_INCLUDE_DIRS}
)

target_link_directories(CyberiadaML PUBLIC
  ${cyberiadaml_LIBRARY}
  ${cyberiadamlpp_LIBRARY}
)

target_link_libraries(CyberiadaML PUBLIC
  pybind11::module
  ${pybind11_LIBRARIES}
  ${cyberiadaml_LIBRARIES}
  ${cyberiadamlpp_LIBRARIES}
)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/tests/")

file(GLOB test_files
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py"
"${CMAKE_CURRENT_SOURCE_DIR}/tests/*.graphml"
  "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.txt"
  )
foreach(f ${test_files})
  get_filename_component(fname "${f}" NAME)
  file(COPY_FILE
    "${f}"
    "${PROJECT_BINARY_DIR}/tests/${fname}"
    ONLY_IF_DIFFERENT)  
endforeach()

file(COPY_FILE
  ${PROJECT_SOURCE_DIR}/run-tests.sh
  ${PROJECT_BINARY_DIR}/run-tests.sh ONLY_IF_DIFFERENT)
