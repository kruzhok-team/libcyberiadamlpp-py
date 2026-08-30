# The Python 3 binding for the Cyberida State Machine Library

The Python 3 binding for the [C++ library for processing
CyberiadaML](https://github.com/kruzhok-team/libcyberiadamlpp/) - the
version of GraphML for storing state machine graphs used by the
Cyberiada Project, the Berloga Project games and the Orbita Simulator.

This is the Python 3 interface for the libcyberiadamlpp C++ library.

The code is distributed under the Lesser GNU Public License (version 3), the documentation -- under
the GNU Free Documentation License (version 1.3).

## Requirements

* libcyberiadamlpp (version 1.0+, and its dependencies)
* cmake (version 3.21+)
* pybind11
* python3 (version 3.8+)

## Installation

Create `build` directory: `mkdir build && cd build`

Run `cmake ..` to build the library binaries and the test program.

Run `make install` to install the library.

Run `cpack -G DEB` to build the Debian package: `python3-libcyberiadamlpp`
with the Python module.

Use CMake parameters to change the build type / installation prefix / etc.

## Testing

The tests are run by CTest. From the `build` directory:

`cmake .. && make && ctest`

Use `ctest -R <regexp>` to filter the tests.

The wrapper script builds the library and runs the tests in one step
(from the `build` directory): `run-tests.sh`. The optional argument of
the script is a regular expression to filter the tests.

If the libcyberiadaml / libcyberiadamlpp libraries are installed into a
non-standard prefix, set `LD_LIBRARY_PATH` accordingly before running
`cmake` - the test environment captures it at configure time.
