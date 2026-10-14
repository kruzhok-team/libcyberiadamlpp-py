# libcyberiadamlpp-py project changelog

## Version 1.0.9 (unreleased)

Changed:
- the tests follow the Arena and Lapki documents detected as Cyberiada.

## Version 1.0.8

Added:
- `Document.update_geometry`: the geometry update keeping the drawn elements
  (libhtgeom 1.2); the package requires the 1.0.8 C/C++ libraries and libhtreegeom 1.2.
- `State.set_actions` (from any iterable of actions), `State.clear_actions` and
  `State.remove_action`.
- the tests of the transition colour without geometry and of the wide labels
  inside the reconstructed machine border.

## Version 1.0.7

Changed:
- the full geometry reconstruction follows the libhtgeom 1.1 layered layout.

Fixed:
- minor fixes.

## Version 1.0.6

The version compatible with `libcyberiadamlpp` 1.0.6 and the CyberiadaML-GraphML 1.0
(PNST_1044-2025) standard.

Added:
- the missing library API: the event propagation, the mutation and the isomorphism details;
- the export options and the yEd dialects on saving;
- the declared geometry format of the document;
- the strict standard checks and the metainformation parameter enums;
- the ctest-based test suite.

Fixed:
- the pybind11 3.x support;
- the misbound methods and the pseudostate class name;
- minor fixes.

## Version 1.0

Stable version of the Python binding library for the `libcyberiadamlpp` project.

Known issues:
- limited standard API based on the C++ library.

