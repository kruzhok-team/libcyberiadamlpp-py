# libcyberiadamlpp-py project changelog

## Version 1.1.0 (unreleased)

Added:
- `Document.arrange_geometry`: the layout anew, seeded by the existing
  geometry - its bands, order, directions and minimum sizes (libcyberiadamlpp
  1.1);
- `DocumentMetainformation.regions_stored` / `set_regions_stored`: the meta
  parameter `regionGeometry/ stored` (libcyberiadamlpp 1.1, test 74);
- the routing of the layout: `LayoutRouting` (`layoutRoutingPolyline`, the
  default, or `layoutRoutingOrthogonal`), the optional `routing` argument of
  `Document.reconstruct_geometry`, `update_geometry` and `arrange_geometry`
  (libcyberiadamlpp 1.1, test 73);
- the EXT-FA extension: `FAException` for a finite automaton document
  (`type/ fa`) breaking the EXT-FA rules on any load or save; `Document.is_fa`,
  `get_input_alphabet` / `get_output_alphabet` and their `has_` forms; the
  package requires the 1.1 C/C++ libraries.
- `Comment.update_subject_geometry`, `Comment.update_subject` and
  `Document.update_comment_subject`: a comment subject changed in place (libcyberiadamlpp
  1.0.9); the package requires the 1.0.9 C/C++ libraries and libhtreegeom 1.3.

## Version 1.0.8

Added:
- `formatLapki`: the Lapki IDE dialect of Cyberiada 1.0 written for lapki-client and
  lapki-compiler.
- `Document.update_geometry`: the geometry update keeping the drawn elements
  (libhtgeom 1.2); the package requires the 1.0.8 C/C++ libraries and libhtreegeom 1.2.
- `State.set_actions` (from any iterable of actions), `State.clear_actions` and
  `State.remove_action`.
- the tests of the transition colour without geometry and of the wide labels
  inside the reconstructed machine border.

Changed:
- the tests follow the Arena and Lapki documents detected as Cyberiada, the
  non-strict Lapki repairs and the document name cleared by the reset.

Fixed:
- Windows build issues

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

