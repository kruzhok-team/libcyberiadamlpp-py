cmake_minimum_required(VERSION 3.16)

project(cyberiadamlpp-python VERSION 1.0.8)

find_package(cyberiadaml REQUIRED)
find_package(cyberiadamlpp REQUIRED)

if(NOT cyberiadamlpp_FOUND)
  message(FATAL_ERROR "Cannot find libcyberiadamlpp C++ library")
endif()

if(WIN32 AND NOT CMAKE_CROSSCOMPILING)
  # Python 3.8+ loads the DLLs of an extension module from its own folder, not
  # from PATH, so the module the tests import gets them beside it: the library
  # DLLs of the prefix (cyberiadaml and cyberiadamlpp in bin, htgeom.dll in lib,
  # which $<TARGET_RUNTIME_DLLS> cannot report) and what libcyberiadaml needs
  # there: libxml2 with zlib and iconv, the PCRE2 POSIX wrapper of its regular
  # expressions (the vcpkg bin, else the bin beside the import libraries it links)
  get_filename_component(CYB_PREFIX_LIB "${cyberiadaml_LIBRARY}" ABSOLUTE)
  file(GLOB CYB_DEPENDENCY_DLLS "${CYB_PREFIX_LIB}/*.dll" "${CYB_PREFIX_LIB}/../bin/*.dll")
  set(CYB_XML_BINS)
  if(DEFINED VCPKG_INSTALLED_DIR AND DEFINED VCPKG_TARGET_TRIPLET)
    list(APPEND CYB_XML_BINS "${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/bin")
  endif()
  get_target_property(CYB_ML_LINKS cyberiadaml INTERFACE_LINK_LIBRARIES)
  foreach(item IN LISTS CYB_ML_LINKS)
    if(item MATCHES "\\.lib$" AND NOT item MATCHES "/debug/" AND EXISTS "${item}")
      get_filename_component(lib_dir "${item}" DIRECTORY)
      list(APPEND CYB_XML_BINS "${lib_dir}/../bin")
    endif()
  endforeach()
  list(REMOVE_DUPLICATES CYB_XML_BINS)
  foreach(name libxml2 zlib1 iconv-2 charset-1 liblzma pcre2-posix pcre2-8)
    foreach(dir IN LISTS CYB_XML_BINS)
      if(EXISTS "${dir}/${name}.dll")
        list(APPEND CYB_DEPENDENCY_DLLS "${dir}/${name}.dll")
        break()
      endif()
    endforeach()
  endforeach()
  if(NOT CYB_DEPENDENCY_DLLS)
    message(WARNING "No library DLLs found near ${CYB_PREFIX_LIB}; copy cyberiadaml.dll, "
                    "cyberiadamlpp.dll, htgeom.dll, libxml2.dll and pcre2-posix.dll next to "
                    "the module manually")
  endif()
endif()

# Development.Module (the leaner target for extension modules) needs CMake 3.18;
# on older CMake (Ubuntu 20.04 ships 3.16) fall back to the full Development
if(CMAKE_VERSION VERSION_LESS 3.18)
  find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
else()
  find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)
endif()
find_package(pybind11 CONFIG REQUIRED)

if(NOT pybind11_FOUND)
  message(FATAL_ERROR "Cannot find pybind11 library")
endif()

if(NOT Python3_FOUND)
  message(FATAL_ERROR "Cannot find python3")
endif()

set (PYTHON_EXECUTABLE ${Python3_EXECUTABLE})

string(REPLACE "." ";" pybind11_VERSION_list "${pybind11_VERSION}")
list(GET pybind11_VERSION_list 0 PYBIND_MAJOR_VERSION)
list(GET pybind11_VERSION_list 1 PYBIND_MINOR_VERSION)

add_compile_definitions(
  PYBIND_MAJOR_VERSION=${PYBIND_MAJOR_VERSION}
  PYBIND_MINOR_VERSION=${PYBIND_MINOR_VERSION}
  CYBERIADA_ML_PY_LIB_VERSION="${PROJECT_VERSION}"
)

add_compile_definitions($<$<CONFIG:Debug>:__DEBUG__>)

if(MSVC)
  # the pybind11 bindings exceed the default section limit of an object file
  # (pybind11_add_module adds /bigobj, this module is a plain library)
  add_compile_options(/W4 /bigobj)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CyberiadaML MODULE cyberiadamlpp-py.cpp)
set_target_properties(CyberiadaML PROPERTIES PREFIX "")
if(WIN32)
  # python imports the extension modules by the .pyd suffix only
  set_target_properties(CyberiadaML PROPERTIES SUFFIX ".pyd")
endif()
# the Debian layout (dist-packages): a package installs the module into
# /usr/lib/python3/dist-packages, not the /usr/local site dir CMake reports
# for python 3.10+
if(Python3_SITELIB MATCHES "dist-packages")
  set(_python_dest lib/python3/dist-packages)
else()
  set(_python_dest "${Python3_SITELIB}")
endif()
set(PYTHON_INSTALL_DIR "${_python_dest}" CACHE PATH "the install directory of the CyberiadaML module")
install(TARGETS CyberiadaML DESTINATION ${PYTHON_INSTALL_DIR})

# user-facing docs shipped in the package
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md
              ${CMAKE_CURRENT_SOURCE_DIR}/README.md
              ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
        DESTINATION share/doc/python3-libcyberiadamlpp)

# the machine-readable (DEP-5) copyright, where the Debian policy wants it
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/debian-copyright
        DESTINATION share/doc/python3-libcyberiadamlpp RENAME copyright)

# the tests import the module from their own directory
add_custom_command(TARGET CyberiadaML
  POST_BUILD
  COMMAND "${CMAKE_COMMAND}" -E copy_if_different
          "$<TARGET_FILE:CyberiadaML>"
          "${PROJECT_BINARY_DIR}/tests/"
  )
if(WIN32 AND CMAKE_VERSION VERSION_GREATER_EQUAL 3.21)
  add_custom_command(TARGET CyberiadaML
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_RUNTIME_DLLS:CyberiadaML>"
            "${PROJECT_BINARY_DIR}/tests/"
    COMMAND_EXPAND_LISTS
    )
endif()
if(CYB_DEPENDENCY_DLLS)
  add_custom_command(TARGET CyberiadaML
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            ${CYB_DEPENDENCY_DLLS}
            "$<TARGET_FILE_DIR:CyberiadaML>"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            ${CYB_DEPENDENCY_DLLS}
            "${PROJECT_BINARY_DIR}/tests/"
    COMMAND_EXPAND_LISTS
    )
endif()

target_include_directories(CyberiadaML PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Python3_INCLUDE_DIRS}
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
  file(COPY "${f}" DESTINATION "${PROJECT_BINARY_DIR}/tests/")
endforeach()

file(COPY "${PROJECT_SOURCE_DIR}/run-tests.sh" DESTINATION "${PROJECT_BINARY_DIR}")


enable_testing()

option(MEMCHECK "Run the tests under valgrind memcheck" OFF)
if(MEMCHECK)
  find_program(VALGRIND valgrind REQUIRED)
  set(MEMCHECK_COMMAND "${VALGRIND} --tool=memcheck -s --leak-check=full --error-exitcode=1")
endif()

file(GLOB test_scripts "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.py")
foreach(script_path ${test_scripts})
  get_filename_component(script_name "${script_path}" NAME)
  get_filename_component(test_name "${script_path}" NAME_WE)
  # the script path is relative to the build directory: the tests
  # resolve their input/output files and print the paths via sys.argv[0]
  string(SUBSTRING "${test_name}" 0 2 test_num)
  set(test_args "-DBINARY=tests/${script_name}" "-DPYTHON=${Python3_EXECUTABLE}")
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/${script_name}-input.graphml" OR
      EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_num}-output.txt")
    list(APPEND test_args "-DCAPTURE=1")
  endif()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_num}-output.txt")
    list(APPEND test_args "-DPATTERN_TXT=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_num}-output.txt")
  endif()
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_num}-output.graphml")
    list(APPEND test_args "-DPATTERN_GRAPHML=${CMAKE_CURRENT_SOURCE_DIR}/tests/${test_num}-output.graphml")
  endif()
  if(MEMCHECK)
    list(APPEND test_args "-DMEMCHECK=${MEMCHECK_COMMAND}")
  endif()
  add_test(NAME "${test_name}"
    COMMAND ${CMAKE_COMMAND} ${test_args} -P "${CMAKE_CURRENT_SOURCE_DIR}/tests/runtest.cmake")
  set_tests_properties("${test_name}" PROPERTIES
    WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    ENVIRONMENT "LD_LIBRARY_PATH=$ENV{LD_LIBRARY_PATH}")
endforeach()

# optional per-release suffix (e.g. ubuntu2404) for the package version, so the
# distro-dependent binding .deb is distinguishable across Ubuntu releases
set(DISTRO_TAG "" CACHE STRING "distribution suffix appended to the package version")
configure_file ("${PROJECT_SOURCE_DIR}/CyberiadaMLPyPackOptions.cmake.in"
                "${PROJECT_BINARY_DIR}/CyberiadaMLPyPackOptions.cmake"
                @ONLY)
set (CPACK_PROJECT_CONFIG_FILE
     "${PROJECT_BINARY_DIR}/CyberiadaMLPyPackOptions.cmake")

include(CPack)
