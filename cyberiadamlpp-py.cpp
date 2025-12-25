/* -----------------------------------------------------------------------------
 * The Python binding for Cyberiada GraphML C++ library 
 *
 * The Python-C++ binding library implementation
 *
 * Copyright (C) 2025 Alexey Fedoseev <aleksey@fedoseev.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see https://www.gnu.org/licenses/
 *
 * ----------------------------------------------------------------------------- */

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

/* Replace the macro names for older versions of pybind11 */
#if defined(PYBIND_MAJOR_VERSION) and PYBIND_MAJOR_VERSION >= 2
  #if defined(PYBIND_MINOR_VERSION) and PYBIND_MINOR_VERSION < 5
    #define PYBIND11_OVERRIDE      PYBIND11_OVERLOAD
    #define PYBIND11_OVERRIDE_PURE PYBIND11_OVERLOAD_PURE
  #endif
#else
  #error Unsupported pybind11 version
#endif

#include <cyberiada/cyberiadamlpp.h>

namespace py = pybind11;
namespace cy = Cyberiada;

PYBIND11_MAKE_OPAQUE(std::vector<cy::ID>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Point>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::CommentSubject>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::Element*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Element*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::ElementType>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::Vertex*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Vertex*>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::State*>);;
PYBIND11_MAKE_OPAQUE(std::vector<cy::State*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Action>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::Comment*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Comment*>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::Transition*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::Transition*>);
PYBIND11_MAKE_OPAQUE(std::vector<const cy::StateMachine*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::StateMachine*>);
PYBIND11_MAKE_OPAQUE(std::vector<cy::SMIsomorphismFlagsResult>);
PYBIND11_MAKE_OPAQUE(std::vector<std::pair<cy::String, cy::String>>);

class PyElement: public cy::Element {
public:
	using cy::Element::Element;
	
	/*PyElement(cy::Element* parent, cy::ElementType type, const cy::ID& id):
		cy::Element(parent, type, id) {}
	PyElement(cy::Element* parent, cy::ElementType type, const cy::ID& id, const cy::Name& name):
		cy::Element(parent, type, id, name) {}
	PyElement(const cy::Element& e):
	cy::Element(e) {}*/

	void set_name(const cy::Name& name) override {
		PYBIND11_OVERRIDE(void, cy::Element, set_name, name);
    }
	bool has_children() const override {
		PYBIND11_OVERRIDE(bool, cy::Element, has_children, );
	}
	size_t children_count() const override {
		PYBIND11_OVERRIDE(size_t, cy::Element, children_count,);
	}
	size_t elements_count() const override {
		PYBIND11_OVERRIDE(size_t, cy::Element, elements_count,);
	}
	bool has_geometry() const override {
		PYBIND11_OVERRIDE_PURE(bool, cy::Element, has_geometry,);
	}
	bool has_point_geometry() const override {
		PYBIND11_OVERRIDE_PURE(bool, cy::Element, has_point_geometry,);
	}
	bool has_rect_geometry() const override {
		PYBIND11_OVERRIDE_PURE(bool, cy::Element, has_rect_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE_PURE(cy::Rect, cy::Element, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE_PURE(void, cy::Element, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE_PURE(void, cy::Element, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE_PURE(cy::Element*, cy::Element, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::Element, dump, os);
	}
};

class PyComment: public cy::Comment {
public:
	using cy::Comment::Comment;

	bool has_children() const override {
		PYBIND11_OVERRIDE(bool, cy::Comment, has_children,);
	}
	bool has_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Comment, has_geometry,);
	}
	bool has_point_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Comment, has_point_geometry,);
	}
	bool has_rect_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Comment, has_rect_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::Comment, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Comment, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Comment, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::Comment, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::Comment, dump, os);
	}
};

class PyVertex: public cy::Vertex {
public:
	using cy::Vertex::Vertex;

	bool has_children() const override {
		PYBIND11_OVERRIDE(bool, cy::Vertex, has_children, );
	}
	bool has_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Vertex, has_geometry,);
	}
	bool has_point_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Vertex, has_point_geometry,);
	}
	bool has_rect_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Vertex, has_rect_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::Vertex, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Vertex, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Vertex, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE_PURE(cy::Element*, cy::Vertex, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::Vertex, dump, os);
	}
};

class PyPseudostate: public cy::Pseudostate {
public:
	using cy::Pseudostate::Pseudostate;

	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE_PURE(cy::Element*, cy::Pseudostate, copy, parent);
	}
};

class PyInitialPseudostate: public cy::InitialPseudostate {
public:
	using cy::InitialPseudostate::InitialPseudostate;

	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::InitialPseudostate, copy, parent);
	}
};

class PyTerminatePseudostate: public cy::TerminatePseudostate {
public:
	using cy::TerminatePseudostate::TerminatePseudostate;

	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::TerminatePseudostate, copy, parent);
	}
};

class PyFinalState: public cy::FinalState {
public:
	using cy::FinalState::FinalState;

	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::FinalState, copy, parent);
	}
};

class PyChoicePseudostate: public cy::ChoicePseudostate {
public:
	using cy::ChoicePseudostate::ChoicePseudostate;

	bool has_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ChoicePseudostate, has_geometry,);
	}
	bool has_point_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ChoicePseudostate, has_point_geometry,);
	}
	bool has_rect_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ChoicePseudostate, has_rect_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::ChoicePseudostate, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE(void, cy::ChoicePseudostate, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE(void, cy::ChoicePseudostate, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::ChoicePseudostate, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::ChoicePseudostate, dump, os);
	}
};

class PyElementCollection: public cy::ElementCollection {
public:
	using cy::ElementCollection::ElementCollection;

	bool has_children() const override {
		PYBIND11_OVERRIDE(bool, cy::ElementCollection, has_children, );
	}
	size_t children_count() const override {
		PYBIND11_OVERRIDE(size_t, cy::ElementCollection, children_count,);
	}
	size_t elements_count() const override {
		PYBIND11_OVERRIDE(size_t, cy::ElementCollection, elements_count,);
	}
	bool has_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ElementCollection, has_geometry,);
	}
	bool has_point_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ElementCollection, has_point_geometry,);
	}
	bool has_rect_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::ElementCollection, has_rect_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::ElementCollection, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE(void, cy::ElementCollection, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE(void, cy::ElementCollection, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE_PURE(cy::Element*, cy::ElementCollection, copy, parent);
	}
	void add_element(cy::Element* e) {
		PYBIND11_OVERRIDE(void, cy::ElementCollection, add_element, e);
	}
	void remove_element(const cy::ID& id) {
		PYBIND11_OVERRIDE(void, cy::ElementCollection, remove_element, id);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::ElementCollection, dump, os);
	}
};

class PyState: public cy::State {
public:
	using cy::State::State;

	void add_element(cy::Element* e) {
		PYBIND11_OVERRIDE(void, cy::State, add_element, e);
	}
	void remove_element(const cy::ID& id) {
		PYBIND11_OVERRIDE(void, cy::State, remove_element, id);
	}	
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::State, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::State, dump, os);
	}
};

class PyTransition: public cy::Transition {
public:
	using cy::Transition::Transition;

	bool has_geometry() const override {
		PYBIND11_OVERRIDE(bool, cy::Transition, has_geometry,);
	}
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::Transition, get_bound_rect, d);
	}
	void clean_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Transition, clean_geometry,);
	}
	void round_geometry() override {
		PYBIND11_OVERRIDE(void, cy::Transition, round_geometry,);
	}
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE_PURE(cy::Element*, cy::Transition, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::Transition, dump, os);
	}
};

class PyStateMachine: public cy::StateMachine {
public:
	PyStateMachine(cy::Element* parent, const cy::ID& id, const cy::Name& name = "",
				   const cy::Rect& r = cy::Rect()): cy::StateMachine(parent, id, name, r) {}
	PyStateMachine(const cy::StateMachine& sm): cy::StateMachine(sm) {}

	
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::StateMachine, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::StateMachine, dump, os);
	}
};

class PyDocument: public cy::Document {
public:
	PyDocument(cy::DocumentGeometryFormat format = cy::geometryFormatNone): cy::Document(format) {}
	PyDocument(const cy::Document& d): cy::Document(d) {} 
	
	cy::Rect get_bound_rect(const cy::Document& d) const override {
		PYBIND11_OVERRIDE(cy::Rect, cy::Document, get_bound_rect, d);
	}
	void set_name(const cy::Name& name) override {
		PYBIND11_OVERRIDE(void, cy::Document, set_name, name);
    }	
	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::Document, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::Document, dump, os);
	}
};

class PyLocalDocument: public cy::LocalDocument {
public:
	PyLocalDocument(): cy::LocalDocument() {}
	PyLocalDocument(const cy::Document& d, const cy::String& path, cy::DocumentFormat f = cy::formatCyberiada10):
		cy::LocalDocument(d, path, f) {}
	PyLocalDocument(const cy::LocalDocument& ld): cy::LocalDocument(ld) {}

	cy::Element* copy(cy::Element* parent) const override {
		PYBIND11_OVERRIDE(cy::Element*, cy::LocalDocument, copy, parent);
	}
protected:
	std::ostream& dump(std::ostream& os) const override {
		PYBIND11_OVERRIDE(std::ostream&, cy::LocalDocument, dump, os);
	}
};

static std::unique_ptr<cy::Polyline> polyline_from_list(const py::list& points)
{
	std::vector<cy::Point> v;
	for (size_t i = 0; i < points.size(); i++) {
		v.push_back(points[i].cast<cy::Point>());
	}
	return std::make_unique<cy::Polyline>(v);
}

PYBIND11_MODULE(CyberiadaML, m) {
    m.doc() = "Cyberiada GraphML C++ Library Binding"; // optional module docstring

	py::enum_<cy::ElementType>(m, "ElementType")
		.value("elementRoot", cy::ElementType::elementRoot)
		.value("elementSM", cy::ElementType::elementSM)
		.value("elementSimpleState", cy::ElementType::elementSimpleState)
		.value("elementCompositeState", cy::ElementType::elementCompositeState)
		.value("elementComment", cy::ElementType::elementComment)
		.value("elementFormalComment", cy::ElementType::elementFormalComment)
		.value("elementInitial", cy::ElementType::elementInitial)
		.value("elementFinal", cy::ElementType::elementFinal)
		.value("elementChoice", cy::ElementType::elementChoice)
		.value("elementTerminate", cy::ElementType::elementTerminate)
		.value("elementTransition", cy::ElementType::elementTransition)
		.export_values();

	py::enum_<cy::TransitionType>(m, "TransitionType")
		.value("transitionExternal", cy::TransitionType::transitionExternal)
		.value("transitionLocal", cy::TransitionType::transitionLocal)
		.export_values();
	
	m.attr("QUALIFIED_NAME_SEPARATOR") = cy::String(cy::QUALIFIED_NAME_SEPARATOR);
	
	py::enum_<cy::DocumentFormat>(m, "DocumentFormat")
		.value("formatCyberiada10", cy::DocumentFormat::formatCyberiada10) 
		.value("formatLegacyYED", cy::DocumentFormat::formatLegacyYED) 
		.value("formatDetect", cy::DocumentFormat::formatDetect)
		.export_values();

	py::enum_<cy::DocumentGeometryFormat>(m, "DocumentGeometryFormat")
		.value("geometryFormatNone", cy::DocumentGeometryFormat::geometryFormatNone)
		.value("geometryFormatLegacyYED", cy::DocumentGeometryFormat::geometryFormatLegacyYED)
		.value("geometryFormatCyberiada10", cy::DocumentGeometryFormat::geometryFormatCyberiada10)
		.value("geometryFormatQt", cy::DocumentGeometryFormat::geometryFormatQt)
		.export_values();

	py::class_<cy::Point>(m, "Point")
		.def(py::init<>())
		.def(py::init<float, float>())
		.def_readwrite("valid", &cy::Point::valid)
		.def_readwrite("x", &cy::Point::x)
		.def_readwrite("y", &cy::Point::y)
		.def("__repr__", &cy::Point::to_str);

	py::class_<cy::Rect>(m, "Rect")
		.def(py::init<>())
		.def(py::init<float, float, float, float>())
		.def(py::self == py::self)
		.def(py::self != py::self)
		.def_readwrite("valid", &cy::Rect::valid)
		.def_readwrite("x", &cy::Rect::x)
		.def_readwrite("y", &cy::Rect::y)
		.def_readwrite("x", &cy::Rect::width)
		.def_readwrite("y", &cy::Rect::height)
		.def("__repr__", &cy::Rect::to_str);

	py::class_<cy::Polyline>(m, "Polyline")
		.def(py::init<>())
		.def(py::init(&polyline_from_list))
		.def(py::init<const std::vector<cy::Point>&>(), py::arg("points"))
		.def("append", [](cy::Polyline& pl, const cy::Point& p){
						   pl.push_back(p);
					   })
		.def("__getitem__", [](const cy::Polyline &pl, size_t i) {
								if (i >= pl.size()) {
									throw py::index_error();
								}
								return pl[i];
							})
		.def("__setitem__", [](cy::Polyline &pl, size_t i, const cy::Point& p) {
								if (i >= pl.size()) {
									throw py::index_error();
								}
								pl[i] = p;
							})
		.def("__iter__", [](const cy::Polyline &pl) {
							 return py::make_iterator(pl.begin(), pl.end());
						 },
			 py::keep_alive<0, 1>())
		.def("__len__", &cy::Polyline::size)		
		.def("__repr__", &cy::Polyline::to_str);

	py::class_<cy::Element, PyElement>(m, "Element")
		.def("clean_geometry", &cy::Element::clean_geometry)
		.def("copy", &cy::Element::copy, py::return_value_policy::copy)
		.def("get_bound_rect", &cy::Element::get_bound_rect)
		.def("get_children_count", &cy::Element::children_count)
		.def("get_elements_count", &cy::Element::elements_count)
		.def("get_id", &cy::Element::get_id)
		.def("get_index", &cy::Element::index)
		.def("get_formal_name", &cy::Element::get_name)
		.def("get_name", &cy::Element::get_name)
		.def("get_parent", static_cast<const cy::Element* (cy::Element::*)() const>(&cy::Element::get_parent),
			 py::return_value_policy::reference)
		.def("get_parent", static_cast<cy::Element* (cy::Element::*)()>(&cy::Element::get_parent),
			 py::return_value_policy::reference)
		.def("get_qualified_name", &cy::Element::qualified_name)
		.def("get_full_qualified_name", &cy::Element::full_qualified_name)
		.def("get_type", &cy::Element::get_type)
		.def("has_children", &cy::Element::has_children)
		.def("has_geometry", &cy::Element::has_geometry)
		.def("has_formal_name", &cy::Element::has_name)
		.def("has_name", &cy::Element::has_formal_name)
		.def("has_qualified_name", &cy::Element::has_qualified_name)
		.def("is_root", &cy::Element::is_root)
		.def("round_geometry", &cy::Element::round_geometry)
		.def("set_name", &cy::Element::set_name)
		.def("__repr__", &cy::Element::dump_to_str);

	py::enum_<cy::CommentSubjectType>(m, "CommentSubjectType")
		.value("commentSubjectElement", cy::CommentSubjectType::commentSubjectElement) 
		.value("commentSubjectName", cy::CommentSubjectType::commentSubjectName) 
		.value("commentSubjectData", cy::CommentSubjectType::commentSubjectData)
		.export_values();
	
	py::class_<cy::CommentSubject>(m, "CommentSubject")
		.def(py::init<const cy::ID&, cy::Element*, const cy::Point&, const cy::Point&, const cy::Polyline&>(),
			 py::arg("id"), py::arg("element"),
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline())
		.def(py::init<const cy::ID&, cy::Element*, cy::CommentSubjectType, const cy::String&,
			 const cy::Point&, const cy::Point&, const cy::Polyline&>(),
			 py::arg("id"), py::arg("element"), py::arg("type"), py::arg("fragment"), 
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline())
		.def("clean_geometry", &cy::CommentSubject::clean_geometry)
		.def("get_bound_rect", &cy::CommentSubject::get_bound_rect)
		.def("get_element", static_cast<const cy::Element* (cy::CommentSubject::*)() const>(&cy::CommentSubject::get_element),
			 py::return_value_policy::reference)
		.def("get_element", static_cast<cy::Element* (cy::CommentSubject::*)()>(&cy::CommentSubject::get_element),
			 py::return_value_policy::reference)
		.def("get_fragment", &cy::CommentSubject::get_fragment)
		.def("get_geometry_polyline", &cy::CommentSubject::get_geometry_polyline,
			 py::return_value_policy::reference)
		.def("get_geometry_source_point", &cy::CommentSubject::get_geometry_source_point,
			 py::return_value_policy::reference)
		.def("get_geometry_target_point", &cy::CommentSubject::get_geometry_source_point,
			 py::return_value_policy::reference)
		.def("get_id", &cy::CommentSubject::get_id)
		.def("get_type", &cy::CommentSubject::get_type)
		.def("has_fragment", &cy::CommentSubject::has_fragment)
		.def("has_geometry", &cy::CommentSubject::has_geometry)
		.def("has_geometry_polyline", &cy::CommentSubject::has_polyline)		
		.def("has_geometry_source_point", &cy::CommentSubject::has_geometry_source_point)
		.def("has_geometry_target_point", &cy::CommentSubject::has_geometry_source_point)
		.def("round_geometry", &cy::CommentSubject::round_geometry)
		.def("__repr__", &cy::CommentSubject::to_str);

	py::class_<cy::Comment, cy::Element, PyComment>(m, "Comment")
		.def(py::init<cy::Element*, const cy::ID&, const cy::String&, bool, const cy::String&,
			 const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("id"), py::arg("body"), py::arg("human_readable") = true, py::arg("markup") = cy::String(),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def(py::init<cy::Element*, const cy::ID&, const cy::String&, const cy::String&, bool, const cy::String&,
			 const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("id"), py::arg("body"), py::arg("name"), py::arg("human_readable") = true,
			 py::arg("markup") = cy::String(),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def("add_subject", &cy::Comment::add_subject, py::return_value_policy::reference)
		.def("clean_geometry", &cy::Comment::clean_geometry)
		.def("copy", &cy::Comment::copy, py::return_value_policy::copy)
		.def("get_body", &cy::Comment::get_body)
		.def("get_bound_rect", &cy::Comment::get_bound_rect, py::return_value_policy::reference)
		.def("get_color", &cy::Comment::get_color)
		.def("get_geometry_rect", &cy::Comment::get_geometry_rect)
		.def("get_markup", &cy::Comment::get_color)
		.def("get_subjects", &cy::Comment::get_subjects, py::return_value_policy::reference)
		.def("has_body", &cy::Comment::has_body)
		.def("has_children", &cy::Comment::has_children)
		.def("has_color", &cy::Comment::has_color)
		.def("has_geometry", &cy::Comment::has_geometry)
		.def("has_markup", &cy::Comment::has_color)
		.def("has_subjects", &cy::Comment::has_subjects)
		.def("is_human_readable", &cy::Comment::is_human_readable)
		.def("is_machine_readable", &cy::Comment::is_machine_readable)
		.def("remove_subject", &cy::Comment::remove_subject)
		.def("round_geometry", &cy::Comment::round_geometry)
		.def("set_body", &cy::Comment::set_body);

	py::class_<cy::Vertex, cy::Element, PyVertex>(m, "Vertex")
		.def("clean_geometry", &cy::Vertex::clean_geometry)
		.def("copy", &cy::Vertex::copy, py::return_value_policy::copy)
		.def("get_bound_rect", &cy::Vertex::get_bound_rect)
		.def("get_geometry_point", &cy::Vertex::get_geometry_point, py::return_value_policy::reference)
		.def("has_children", &cy::Vertex::has_children)
		.def("has_geometry", &cy::Vertex::has_geometry)
		.def("round_geometry", &cy::Vertex::round_geometry);
	
	py::class_<cy::Pseudostate, cy::Vertex, PyPseudostate>(m, "Pseidostate");

	py::class_<cy::InitialPseudostate, cy::Pseudostate, PyInitialPseudostate>(m, "Initial")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point())
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point())
		.def("copy", &cy::InitialPseudostate::copy, py::return_value_policy::copy);

	py::class_<cy::ChoicePseudostate, cy::Pseudostate, PyChoicePseudostate>(m, "Choice")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("id"), py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name") = cy::String(), py::arg("rect") = cy::Rect(),
			 py::arg("color") = cy::Color())
		.def("clean_geometry", &cy::ChoicePseudostate::clean_geometry)
		.def("copy", &cy::ChoicePseudostate::copy, py::return_value_policy::copy)
		.def("get_bound_rect", &cy::ChoicePseudostate::get_bound_rect)
		.def("get_color", &cy::ChoicePseudostate::get_color)
		.def("get_geometry_rect", &cy::ChoicePseudostate::get_geometry_rect, py::return_value_policy::reference)
		.def("has_color", &cy::ChoicePseudostate::has_color)
		.def("has_geometry", &cy::ChoicePseudostate::has_geometry)
		.def("round_geometry", &cy::ChoicePseudostate::round_geometry);

	py::class_<cy::TerminatePseudostate, cy::Pseudostate, PyTerminatePseudostate>(m, "Terminate")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point())
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point())
		.def("copy", &cy::TerminatePseudostate::copy, py::return_value_policy::copy);

	py::class_<cy::FinalState, cy::Vertex, PyFinalState>(m, "Final")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point())
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Point&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point())
		.def("copy", &cy::FinalState::copy, py::return_value_policy::copy);

	py::enum_<cy::ActionType>(m, "ActionType")
		.value("actionTransition", cy::ActionType::actionTransition) 
		.value("actionEntry", cy::ActionType::actionEntry) 
		.value("actionExit", cy::ActionType::actionExit)
		.export_values();
	
	py::class_<cy::Action>(m, "Action")
		.def(py::init<cy::ActionType, const cy::Behavior&>(), py::arg("type"), py::arg("behavior") = cy::Behavior())
		.def(py::init<const cy::Event&, const cy::Guard&, const cy::Behavior&>(),
			 py::arg("trigger") = cy::Event(), py::arg("guard") = cy::Guard(), py::arg("behavior") = cy::Behavior())
		.def("is_empty_transition", &cy::Action::is_empty_transition)
		.def("get_type", &cy::Action::get_type)
		.def("has_trigger", &cy::Action::has_trigger)
		.def("get_trigger", &cy::Action::get_trigger)
		.def("has_guard", &cy::Action::has_guard)
		.def("get_guard", &cy::Action::get_guard)
		.def("has_behavior", &cy::Action::has_behavior)
		.def("get_behavior", &cy::Action::get_behavior)
		.def("__repr__", &cy::Action::to_str);
	
	m.attr("adiffArguments") = py::int_(static_cast<int>(cy::ActionDiff::adiffArguments));
	m.attr("adiffOrder") = py::int_(static_cast<int>(cy::ActionDiff::adiffOrder));
	m.attr("adiffActions") = py::int_(static_cast<int>(cy::ActionDiff::adiffActions));
	m.attr("adiffTypes") = py::int_(static_cast<int>(cy::ActionDiff::adiffTypes));
	m.attr("adiffGuards") = py::int_(static_cast<int>(cy::ActionDiff::adiffGuards));
	m.attr("adiffNumber") = py::int_(static_cast<int>(cy::ActionDiff::adiffNumber));
	
	py::class_<cy::ElementCollection, cy::Element, PyElementCollection>(m, "ElementCollection")
		.def(py::init<cy::Element*, cy::ElementType, const cy::ID&, const cy::Name&, const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("type"), py::arg("id"), py::arg("name"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def("add_element", &cy::ElementCollection::add_element)
		.def("add_first_element", &cy::ElementCollection::add_first_element)
		.def("children_count", &cy::ElementCollection::children_count)
		.def("clean_geometry", &cy::ElementCollection::clean_geometry)
		.def("clear", &cy::ElementCollection::clear)
		.def("copy", &cy::ElementCollection::copy, py::return_value_policy::copy)
		.def("element_index", &cy::ElementCollection::element_index)
		.def("elements_count", &cy::ElementCollection::elements_count)
		.def("first_element",
			 static_cast<const cy::Element* (cy::ElementCollection::*)() const>(&cy::ElementCollection::first_element),
             py::return_value_policy::reference)
		.def("first_element",
			 static_cast<cy::Element* (cy::ElementCollection::*)()>(&cy::ElementCollection::first_element),
             py::return_value_policy::reference)
		.def("find_element_by_id",
			 static_cast<const cy::Element* (cy::ElementCollection::*)(const cy::ID&) const>(&cy::ElementCollection::find_element_by_id),
             py::return_value_policy::reference)
		.def("find_element_by_id",
			 static_cast<cy::Element* (cy::ElementCollection::*)(const cy::ID&)>(&cy::ElementCollection::find_element_by_id),
             py::return_value_policy::reference)
		.def("find_elements_by_type",
			 static_cast<cy::ConstElementList (cy::ElementCollection::*)(cy::ElementType) const>(&cy::ElementCollection::find_elements_by_type))
		.def("find_elements_by_type",
			 static_cast<cy::ElementList (cy::ElementCollection::*)(cy::ElementType)>(&cy::ElementCollection::find_elements_by_type))
		.def("find_elements_by_types",
			 static_cast<cy::ConstElementList (cy::ElementCollection::*)(const cy::ElementTypes&)
			 const>(&cy::ElementCollection::find_elements_by_types))
		.def("find_elements_by_types",
			 static_cast<cy::ElementList (cy::ElementCollection::*)(const cy::ElementTypes&)>(&cy::ElementCollection::find_elements_by_types))
		.def("find_elements_by_types", [](const cy::ElementCollection &collection, const py::list& types) {
										   	std::vector<cy::ElementType> v;
											for (size_t i = 0; i < types.size(); i++) {
												v.push_back(types[i].cast<cy::ElementType>());
											}
											return collection.find_elements_by_types(v);
									   })
		.def("find_elements_by_types", [](cy::ElementCollection &collection, const py::list& types) {
										   	std::vector<cy::ElementType> v;
											for (size_t i = 0; i < types.size(); i++) {
												v.push_back(types[i].cast<cy::ElementType>());
											}
											return collection.find_elements_by_types(v);
									   })
		.def("get_bound_rect", &cy::ElementCollection::get_bound_rect)
		.def("get_children",
			 static_cast<cy::ConstElementList (cy::ElementCollection::*)() const>(&cy::ElementCollection::get_children))
		.def("get_children",
			 static_cast<const cy::ElementList& (cy::ElementCollection::*)()>(&cy::ElementCollection::get_children),
			 py::return_value_policy::reference)
		.def("get_color", &cy::ElementCollection::get_color)
		.def("get_element",
			 static_cast<const cy::Element* (cy::ElementCollection::*)(int) const>(&cy::ElementCollection::get_element),
			 py::return_value_policy::reference)
		.def("get_element",
			 static_cast<cy::Element* (cy::ElementCollection::*)(int)>(&cy::ElementCollection::get_element),
			 py::return_value_policy::reference)
		.def("get_geometry_rect", &cy::ElementCollection::get_geometry_rect, py::return_value_policy::reference)
		.def("get_vertexes",
			 static_cast<std::vector<const cy::Vertex*> (cy::ElementCollection::*)() const>(&cy::ElementCollection::get_vertexes))
		.def("get_vertexes",
			 static_cast<std::vector<cy::Vertex*> (cy::ElementCollection::*)()>(&cy::ElementCollection::get_vertexes))
		.def("get_qualified_name", &cy::ElementCollection::qualified_name)
		.def("has_children", &cy::ElementCollection::has_children)
		.def("has_color", &cy::ElementCollection::has_color)
		.def("has_geometry", &cy::ElementCollection::has_geometry)
		.def("has_initial", &cy::ElementCollection::has_initial)
		.def("has_qualified_name", &cy::ElementCollection::has_qualified_name)
		.def("remove_element", &cy::ElementCollection::remove_element)
		.def("round_geometry", &cy::ElementCollection::round_geometry);

	py::class_<cy::State, cy::ElementCollection, PyState>(m, "State")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Rect&, const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("rect") = cy::Rect(),
			 py::arg("region_rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def("add_action", &cy::State::add_action)
		.def("add_element", &cy::State::add_element)
		.def("copy", &cy::State::copy, py::return_value_policy::copy)
		.def("get_actions", static_cast<const std::vector<cy::Action>& (cy::State::*)() const>(&cy::State::get_actions))
		.def("get_actions", static_cast<std::vector<cy::Action>& (cy::State::*)()>(&cy::State::get_actions))
		.def("get_region_geometry_rect", &cy::State::get_region_geometry_rect)
		.def("get_substates", static_cast<std::vector<const cy::State*> (cy::State::*)() const>(&cy::State::get_substates))
		.def("get_substates", static_cast<std::vector<cy::State*> (cy::State::*)()>(&cy::State::get_substates))
		.def("has_actions", &cy::State::has_actions)
		.def("is_collapsed", &cy::State::is_collapsed)
		.def("is_composite_state", &cy::State::is_composite_state)
		.def("is_simple_state", &cy::State::is_simple_state)
		.def("set_collapsed", &cy::State::set_collapsed)
		.def("remove_element", &cy::State::add_element)
		.def("compare_actions", &cy::State::compare_actions);

	py::class_<cy::Transition, cy::Element, PyTransition>(m, "Transition")
		.def(py::init<cy::Element*, cy::TransitionType, const cy::ID&, const cy::ID&, const cy::ID&, const cy::Action&,
			 const cy::Polyline&, const cy::Point&, const cy::Point&, const cy::Point&, const cy::Rect&, const cy::Color&>(),
			 py::arg("parent"), py::arg("ttype"), py::arg("id"), py::arg("source"), py::arg("target"), py::arg("action"),
			 py::arg("polyline") = cy::Polyline(), py::arg("sp") = cy::Point(), py::arg("tp") = cy::Point(),
			 py::arg("label_point") = cy::Point(), py::arg("label_rect") = cy::Rect(), py::arg("color") = cy::Color())
		.def("copy", &cy::Transition::copy, py::return_value_policy::copy)
		.def("get_action", static_cast<const cy::Action& (cy::Transition::*)() const>(&cy::Transition::get_action),
			 py::return_value_policy::reference)
		.def("get_action", static_cast<cy::Action& (cy::Transition::*)()>(&cy::Transition::get_action),
			 py::return_value_policy::reference)
		.def("get_bound_rect", &cy::Transition::get_bound_rect, py::return_value_policy::reference)
		.def("get_color", &cy::Transition::get_color)
		.def("get_geometry_label_point", &cy::Transition::get_label_point, py::return_value_policy::reference)
		.def("get_geometry_label_rect", &cy::Transition::get_label_rect, py::return_value_policy::reference)
		.def("get_geometry_polyline", &cy::Transition::get_geometry_polyline, py::return_value_policy::reference)
		.def("get_geometry_source_point", &cy::Transition::get_source_point, py::return_value_policy::reference)
		.def("get_geometry_target_point", &cy::Transition::get_target_point, py::return_value_policy::reference)
		.def("get_source_element_id", &cy::Transition::source_element_id)
		.def("get_target_element_id", &cy::Transition::target_element_id)
		.def("get_transition_type", &cy::Transition::get_transition_type)
		.def("has_action", &cy::Transition::has_action)
		.def("has_color", &cy::Transition::has_color)
		.def("has_geometry", &cy::Transition::has_geometry)
		.def("has_geometry_label_point", &cy::Transition::has_geometry_label_point)
		.def("has_geometry_label_rect", &cy::Transition::has_geometry_label_rect)
		.def("has_geometry_polyline", &cy::Transition::has_polyline)
		.def("has_geometry_source_point", &cy::Transition::has_geometry_source_point)
		.def("has_geometry_target_point", &cy::Transition::has_geometry_target_point)
		.def("round_geometry", &cy::Transition::round_geometry)
		.def("compare_actions", &cy::Transition::compare_actions);

	m.attr("smiIdentical") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiIdentical));
	m.attr("smiEqual") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiEqual));
	m.attr("smiIsomorphic") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiIsomorphic));
	m.attr("smiDiffStates") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiDiffStates));
	m.attr("smiDiffInitial") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiDiffInitial));
	m.attr("smiDiffEdges") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismTypes::smiDiffEdges));

	m.attr("smiNodeDiffFlagID") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagID));
	m.attr("smiNodeDiffFlagType") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagType));
	m.attr("smiNodeDiffFlagTitle") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagTitle));
	m.attr("smiNodeDiffFlagActions") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagActions));
	m.attr("smiNodeDiffFlagSMLink") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagSMLink));
	m.attr("smiNodeDiffFlagChildren") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagChildren));
	m.attr("smiNodeDiffFlagEdges") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiNodeDiffFlagEdges));
	m.attr("smiEdgeDiffFlagID") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiEdgeDiffFlagID));
	m.attr("smiEdgeDiffFlagAction") = py::int_(static_cast<unsigned int>(cy::SMIsomorphismFlags::smiEdgeDiffFlagAction));

	py::class_<cy::StateMachine, cy::ElementCollection, PyStateMachine>(m, "StateMachine")
		.def(py::init<cy::Element*, const cy::ID&, const cy::Name&, const cy::Rect&>(),
			 py::arg("parent"), py::arg("id"), py::arg("name") = cy::Name(""), py::arg("rect") = cy::Rect())
		.def(py::init<const cy::StateMachine&>())
		.def("check_isomorphism", &cy::StateMachine::check_isomorphism, py::arg("sm"),
			 py::arg("ignore_comments") = true, py::arg("require_initial") = false)
		.def("check_isomorphism", [](const cy::StateMachine &sm1, const cy::StateMachine &sm2,
									 bool ignore_comments, bool require_initial, py::str& new_initial,
									 py::list& diff_nodes1, py::list& diff_nodes2, py::list& diff_nodes_flags) {

									  cy::ID _new_initial; 
									  std::vector<cy::ID> _diff_nodes1, _diff_nodes2;
									  std::vector<cy::SMIsomorphismFlagsResult> _diff_nodes_flags;

									  cy::SMIsomorphismResult r = sm1.check_isomorphism_details(sm2, ignore_comments, require_initial,
																								&_new_initial,
																								&_diff_nodes1,
																								&_diff_nodes2,
																								&_diff_nodes_flags,
																								NULL,
																								NULL,
																								NULL,
																								NULL,
																								NULL,
																								NULL);
									  new_initial = std::string(_new_initial);
									  for (size_t i = 0; i < _diff_nodes1.size(); i++) {
										  diff_nodes1.append(std::string(_diff_nodes1[i]));
									  }
									  for (size_t i = 0; i < _diff_nodes2.size(); i++) {
										  diff_nodes2.append(std::string(_diff_nodes2[i]));
									  }
									  for (size_t i = 0; i < _diff_nodes_flags.size(); i++) {
										  diff_nodes_flags.append(static_cast<unsigned int>(_diff_nodes_flags[i]));
									  }
									  return r;									  
								  })
		.def("check_isomorphism", [](const cy::StateMachine &sm1, const cy::StateMachine &sm2,
									 bool ignore_comments, bool require_initial, py::str& new_initial,
									 py::list& diff_nodes1, py::list& diff_nodes2, py::list& diff_nodes_flags,
									 py::list& new_nodes, py::list& missing_nodes,
									 py::list& diff_edges1, py::list& diff_edges2,
									 py::list& diff_edges_flags, py::list& new_edges, py::list& missing_edges) {

									  cy::ID _new_initial; 
									  std::vector<cy::ID> _diff_nodes1, _diff_nodes2, _new_nodes, _missing_nodes,
										  _diff_edges1, _diff_edges2, _new_edges, _missing_edges;
									  std::vector<cy::SMIsomorphismFlagsResult> _diff_nodes_flags, _diff_edges_flags;

									  cy::SMIsomorphismResult r = sm1.check_isomorphism_details(sm2, ignore_comments, require_initial,
																								&_new_initial,
																								&_diff_nodes1,
																								&_diff_nodes2,
																								&_diff_nodes_flags,
																								&_new_nodes,
																								&_missing_nodes,
																								&_diff_edges1,
																								&_diff_edges2,
																								&_diff_edges_flags,
																								&_new_edges,
																								&_missing_edges);
									  new_initial = std::string(_new_initial);
									  for (size_t i = 0; i < _diff_nodes1.size(); i++) {
										  diff_nodes1.append(std::string(_diff_nodes1[i]));
									  }
									  for (size_t i = 0; i < _diff_nodes2.size(); i++) {
										  diff_nodes2.append(std::string(_diff_nodes2[i]));
									  }
									  for (size_t i = 0; i < _diff_nodes_flags.size(); i++) {
										  diff_nodes_flags.append(static_cast<unsigned int>(_diff_nodes_flags[i]));
									  }
									  for (size_t i = 0; i < _new_nodes.size(); i++) {
										  new_nodes.append(std::string(_new_nodes[i]));
									  }
									  for (size_t i = 0; i < _missing_nodes.size(); i++) {
										  missing_nodes.append(std::string(_missing_nodes[i]));
									  }
									  for (size_t i = 0; i < _diff_edges1.size(); i++) {
										  diff_edges1.append(std::string(_diff_edges1[i]));
									  }
									  for (size_t i = 0; i < _diff_edges2.size(); i++) {
										  diff_edges2.append(std::string(_diff_edges2[i]));
									  }
									  for (size_t i = 0; i < _diff_edges_flags.size(); i++) {
										  diff_edges_flags.append(static_cast<unsigned int>(_diff_edges_flags[i]));
									  }
									  for (size_t i = 0; i < _new_edges.size(); i++) {
										  new_edges.append(std::string(_new_edges[i]));
									  }
									  for (size_t i = 0; i < _missing_edges.size(); i++) {
										  missing_edges.append(std::string(_missing_edges[i]));
									  }
									  return r;
								  })
		.def("copy", &cy::StateMachine::copy, py::return_value_policy::copy)
		.def("get_comments", static_cast<std::vector<const cy::Comment*> (cy::StateMachine::*)() const>(&cy::StateMachine::get_comments))
		.def("get_comments", static_cast<std::vector<cy::Comment*> (cy::StateMachine::*)()>(&cy::StateMachine::get_comments))
		.def("get_transitions", static_cast<std::vector<const cy::Transition*> (cy::StateMachine::*)() const>(&cy::StateMachine::get_transitions))
		.def("get_transitions", static_cast<std::vector<cy::Transition*> (cy::StateMachine::*)()>(&cy::StateMachine::get_transitions));

	py::class_<cy::DocumentMetainformation>(m, "DocumentMetainformation")
		.def(py::init<>())
		.def_readwrite("standard_version", &cy::DocumentMetainformation::standard_version)
		.def_readwrite("strings", &cy::DocumentMetainformation::strings)
		.def("get_string", &cy::DocumentMetainformation::get_string)
		.def("set_string", &cy::DocumentMetainformation::set_string)
		.def_readwrite("transition_order_flag", &cy::DocumentMetainformation::transition_order_flag)
		.def_readwrite("event_propagation_flag", &cy::DocumentMetainformation::event_propagation_flag);

	py::class_<cy::Document, cy::ElementCollection, PyDocument>(m, "Document")
        .def(py::init<cy::DocumentGeometryFormat>(), py::arg("format") = cy::DocumentGeometryFormat::geometryFormatNone)
        .def(py::init<const cy::Document&>())
		.def("add_comment_to_element", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*, const cy::ID&,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element),
			 py::arg("comment"), py::arg("element"), py::arg("id"), py::arg("source") = cy::Point(), py::arg("target") = cy::Point(),
			 py::arg("polyline") = cy::Polyline(), py::return_value_policy::reference)
		.def("add_comment_to_element", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element),
			 py::arg("comment"), py::arg("element"), py::arg("source") = cy::Point(), py::arg("target") = cy::Point(),
			 py::arg("polyline") = cy::Polyline(), py::return_value_policy::reference)
		.def("add_comment_to_element_body", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*, const cy::String&, const cy::ID&,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element_body),
			 py::arg("comment"), py::arg("element"), py::arg("fragment"), py::arg("id"),
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline(),
			 py::return_value_policy::reference)
		.def("add_comment_to_element_body", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*, const cy::String&,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element_body),
			 py::arg("comment"), py::arg("element"), py::arg("fragment"),
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline(),
			 py::return_value_policy::reference)
		.def("add_comment_to_element_name", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*, const cy::String&, const cy::ID&,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element_name),
			 py::arg("comment"), py::arg("element"), py::arg("fragment"), py::arg("id"),
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline(),
			 py::return_value_policy::reference)
		.def("add_comment_to_element_name", static_cast<const cy::CommentSubject&
			 (cy::Document::*)(cy::Comment*, cy::Element*, const cy::String&,
							   const cy::Point&, const cy::Point&, const cy::Polyline&)>(&cy::Document::add_comment_to_element_name),
			 py::arg("comment"), py::arg("element"), py::arg("fragment"),
			 py::arg("source") = cy::Point(), py::arg("target") = cy::Point(), py::arg("polyline") = cy::Polyline(),
			 py::return_value_policy::reference)
		.def("clean_geometry", &cy::Document::clean_geometry)
		.def("convert_geometry", &cy::Document::convert_geometry)
		.def("copy", &cy::Document::copy, py::return_value_policy::copy)
		.def("decode", &cy::Document::decode,
			 py::arg("buffer"), py::arg("format"), py::arg("format_str"), py::arg("gf") = cy::geometryFormatQt,
			 py::arg("reconstruct") = false, py::arg("reconstruct_sm") = false, py::arg("skip_empty_actions") = false,
			 py::arg("simplify_ids") = false)
		.def("encode", &cy::Document::encode, py::arg("buffer"), py::arg("f") = cy::formatCyberiada10, py::arg("round") = false)
		.def("get_bound_rect", static_cast<cy::Rect (cy::Document::*)() const>(&cy::Document::get_bound_rect))
		.def("get_bound_rect", static_cast<cy::Rect (cy::Document::*)(const cy::Document&) const>(&cy::Document::get_bound_rect))
		.def("get_geometry_format", &cy::Document::get_geometry_format)
		.def("get_meta", static_cast<const cy::DocumentMetainformation& (cy::Document::*)() const>(&cy::Document::meta),
			 py::return_value_policy::reference)
		.def("get_meta", static_cast<cy::DocumentMetainformation& (cy::Document::*)()>(&cy::Document::meta),
			 py::return_value_policy::reference)
		.def("get_parent_sm", static_cast<const cy::StateMachine* (cy::Document::*)(const cy::Element*) const>(&cy::Document::get_parent_sm),
			 py::return_value_policy::reference)
		.def("get_parent_sm", static_cast<cy::StateMachine* (cy::Document::*)(const cy::Element*)>(&cy::Document::get_parent_sm),
			 py::return_value_policy::reference)
		.def("get_state_machines", static_cast<std::vector<const cy::StateMachine*> (cy::Document::*)() const>(&cy::Document::get_state_machines))
		.def("get_state_machines", static_cast<std::vector<cy::StateMachine*> (cy::Document::*)()>(&cy::Document::get_state_machines))
		.def("has_geometry", &cy::Document::has_geometry)
		.def("new_choice", static_cast<cy::ChoicePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Name&, const cy::Rect&, const cy::Color&)>(&cy::Document::new_choice),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_choice", static_cast<cy::ChoicePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::Name&, const cy::Rect&, const cy::Color&)>(&cy::Document::new_choice),
			 py::arg("parent"), py::arg("name"), py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_choice", static_cast<cy::ChoicePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::Rect&, const cy::Color&)>(&cy::Document::new_choice),
			 py::arg("parent"), py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::String&, const cy::String&,
							   const cy::Rect&, const cy::Color&, const cy::String& )>(&cy::Document::new_comment),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::String&, const cy::Rect&, const cy::Color&,
							   const cy::String& )>(&cy::Document::new_comment),
			 py::arg("parent"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::String&, const cy::String&, const cy::Rect&, const cy::Color&,
							  const cy::String& )>(&cy::Document::new_comment),
			 py::arg("parent"), py::arg("name"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_final", static_cast<cy::FinalState*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Name&, const cy::Point&)>(&cy::Document::new_final),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_final", static_cast<cy::FinalState*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Point&)>(&cy::Document::new_final),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_final", static_cast<cy::FinalState*
			 (cy::Document::*)(cy::ElementCollection*, const cy::Point&)>(&cy::Document::new_final),
			 py::arg("parent"), py::arg("point") = cy::Point(),			 
			 py::return_value_policy::reference)
		.def("new_formal_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::String&, const cy::String&, const cy::Rect&, const cy::Color&,
							   const cy::String& )>(&cy::Document::new_formal_comment),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_formal_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::String&, const cy::Rect&, const cy::Color&,
							   const cy::String& )>(&cy::Document::new_formal_comment),
			 py::arg("parent"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_formal_comment", static_cast<cy::Comment*
			 (cy::Document::*)(cy::ElementCollection*, const cy::String&, const cy::String&, const cy::Rect&, const cy::Color&,
							   const cy::String& )>(&cy::Document::new_formal_comment),
			 py::arg("parent"), py::arg("name"), py::arg("body"),
			 py::arg("rect") = cy::Rect(), py::arg("color") = cy::Color(), py::arg("markup") = cy::String(),
			 py::return_value_policy::reference)
		.def("new_initial", static_cast<cy::InitialPseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Name&, const cy::Point&)>(&cy::Document::new_initial),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_initial", static_cast<cy::InitialPseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Point&)>(&cy::Document::new_initial),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_initial", static_cast<cy::InitialPseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::Point&)>(&cy::Document::new_initial),
			 py::arg("parent"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_state", static_cast<cy::State*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::String&, const cy::Action&,
							   const cy::Rect&, const cy::Rect&, const cy::Color&)>(&cy::Document::new_state),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("action") = cy::Action(),
			 py::arg("rect") = cy::Rect(), py::arg("region_rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_state", static_cast<cy::State*
			 (cy::Document::*)(cy::ElementCollection*, const cy::String&, const cy::Action&,
							   const cy::Rect&, const cy::Rect&, const cy::Color&)>(&cy::Document::new_state),
			 py::arg("parent"), py::arg("name"), py::arg("action") = cy::Action(),
			 py::arg("rect") = cy::Rect(), py::arg("region_rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_state_machine", static_cast<cy::StateMachine*
			 (cy::Document::*)(const cy::ID&, const cy::String&, const cy::Rect&)>(&cy::Document::new_state_machine),
			 py::arg("id"), py::arg("sm_name"), py::arg("rect") = cy::Rect(), py::return_value_policy::reference)
		.def("new_state_machine", static_cast<cy::StateMachine*
			 (cy::Document::*)(const cy::String&, const cy::Rect&)>(&cy::Document::new_state_machine),
			 py::arg("sm_name"), py::arg("rect") = cy::Rect(),
			 py::return_value_policy::reference)
		.def("new_terminate", static_cast<cy::TerminatePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Name&, const cy::Point&)>(&cy::Document::new_terminate),
			 py::arg("parent"), py::arg("id"), py::arg("name"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_terminate", static_cast<cy::TerminatePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::ID&, const cy::Point&)>(&cy::Document::new_terminate),
			 py::arg("parent"), py::arg("id"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_terminate", static_cast<cy::TerminatePseudostate*
			 (cy::Document::*)(cy::ElementCollection*, const cy::Point&)>(&cy::Document::new_terminate),
			 py::arg("parent"), py::arg("point") = cy::Point(),
			 py::return_value_policy::reference)
		.def("new_transition", static_cast<cy::Transition*
			 (cy::Document::*)(cy::StateMachine*, cy::TransitionType, const cy::ID&, cy::Element*, cy::Element*, const cy::Action&,
							   const cy::Polyline&, const cy::Point&, const cy::Point&, const cy::Point&, const cy::Rect&,
							   const cy::Color&)>(&cy::Document::new_transition),
			 py::arg("parent"), py::arg("ttype"), py::arg("id"), py::arg("source"), py::arg("target"), py::arg("action"),
			 py::arg("polyline") = cy::Polyline(), py::arg("sp") = cy::Point(), py::arg("tp") = cy::Point(),
			 py::arg("label_point") = cy::Point(), py::arg("label_rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("new_transition", static_cast<cy::Transition*
			 (cy::Document::*)(cy::StateMachine*, cy::TransitionType, cy::Element*, cy::Element*, const cy::Action&,
							   const cy::Polyline&, const cy::Point&, const cy::Point&, const cy::Point&, const cy::Rect&,
							   const cy::Color&)>(&cy::Document::new_transition),
			 py::arg("parent"), py::arg("ttype"), py::arg("source"), py::arg("target"), py::arg("action"),
			 py::arg("polyline") = cy::Polyline(), py::arg("sp") = cy::Point(), py::arg("tp") = cy::Point(),
			 py::arg("label_point") = cy::Point(), py::arg("label_rect") = cy::Rect(), py::arg("color") = cy::Color(),
			 py::return_value_policy::reference)
		.def("reconstruct_geometry", &cy::Document::reconstruct_geometry)
		.def("set_name", &cy::Document::set_name)
        .def("reset", &cy::Document::reset, "Reset the document", py::arg("format") = cy::DocumentGeometryFormat::geometryFormatNone);

	py::class_<cy::LocalDocument, cy::Document, PyLocalDocument>(m, "LocalDocument")
		.def(py::init<>())
		.def(py::init<const cy::Document&, const cy::String&>())
		.def(py::init<const cy::Document&, const cy::String&, cy::DocumentFormat>())
        .def(py::init<const cy::LocalDocument&>())
		.def("copy", &cy::LocalDocument::copy, py::return_value_policy::copy)
		.def("get_file_format", &cy::LocalDocument::get_file_format)
		.def("get_file_format_str", &cy::LocalDocument::get_file_format_str)
		.def("get_file_path", &cy::LocalDocument::get_file_path)
		.def("open", &cy::LocalDocument::open,
			 py::arg("path"), py::arg("f") = cy::formatDetect, py::arg("gf") = cy::geometryFormatQt,
			 py::arg("reconstruct") = false, py::arg("reconstruct_sm") = false, py::arg("skip_empty_actions") = false,
			 py::arg("simplify_ids") = false)
		.def("reset", &cy::LocalDocument::reset)
		.def("save", &cy::LocalDocument::save, "Save the previously opened document", py::arg("round") = false)
		.def("save_as", &cy::LocalDocument::save_as,
			 py::arg("path"), py::arg("f") = cy::formatDetect, py::arg("round") = false);

/*	py::class_<cy::Exception>(m, "Exception")
		.def("str", &cy::Exception::str)
		.def("__repr__", &cy::Exception::str);
	py::class_<cy::FormatException, cy::Exception>(m, "FormatException");
	py::class_<cy::XMLException, cy::FormatException>(m, "XMLException");
	py::class_<cy::CybMLException, cy::FormatException>(m, "CybMLException");
	py::class_<cy::ActionException, cy::CybMLException>(m, "ActionException");
	py::class_<cy::MetainformationException, cy::FormatException>(m, "MetainfoException");
	py::class_<cy::ParametersException, cy::Exception>(m, "ParametersException");
	py::class_<cy::NotFoundException, cy::ParametersException>(m, "NotFoundException");
	py::class_<cy::AssertException, cy::Exception>(m, "AssertException");
	py::class_<cy::NotImplementedException, cy::Exception>(m, "NotImplementedException");*/

	py::bind_vector<std::vector<cy::CommentSubject>>(m, "ContentSubjectList");
	py::bind_vector<std::vector<const cy::Element*>>(m, "ConstElementRefList");
	py::bind_vector<std::vector<cy::Element*>>(m, "ElementRefList");
	py::bind_vector<std::vector<cy::ElementType>>(m, "ElementTypeList");
	py::bind_vector<std::vector<const cy::Vertex*>>(m, "ConstVertexRefList");
	py::bind_vector<std::vector<cy::Vertex*>>(m, "VertexRefList");
	py::bind_vector<std::vector<const cy::State*>>(m, "ConstStateRefList");
	py::bind_vector<std::vector<cy::State*>>(m, "StateRefList");
	py::bind_vector<std::vector<cy::Action>>(m, "ActionList");
	py::bind_vector<std::vector<const cy::Comment*>>(m, "ConstCommentRefList");
	py::bind_vector<std::vector<cy::Comment*>>(m, "CommentRefList");
	py::bind_vector<std::vector<const cy::Transition*>>(m, "ConstTransitionRefList");
	py::bind_vector<std::vector<cy::Transition*>>(m, "TransitionRefList");
	py::bind_vector<std::vector<const cy::StateMachine*>>(m, "ConstStateMachinesRefList");
	py::bind_vector<std::vector<cy::StateMachine*>>(m, "StateMachinesRefList");
	
	py::register_exception<cy::Exception>(m, "Exception");
	py::register_exception<cy::FileException>(m, "FileException");
	py::register_exception<cy::FormatException>(m, "FormatException");
	py::register_exception<cy::XMLException>(m, "XMLException");
	py::register_exception<cy::CybMLException>(m, "CybMLException");
	py::register_exception<cy::ActionException>(m, "ActionException");
	py::register_exception<cy::MetainformationException>(m, "MetainfoException");
	py::register_exception<cy::ParametersException>(m, "ParametersException");
	py::register_exception<cy::NotFoundException>(m, "NotFoundException");
	py::register_exception<cy::AssertException>(m, "AssertException");
	py::register_exception<cy::NotImplementedException>(m, "NotImplementedException");

}
