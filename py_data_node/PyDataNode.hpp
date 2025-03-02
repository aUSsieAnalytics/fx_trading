#include "DataNode.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/iostream.h>
#include <memory>
#include <iostream>

namespace py = pybind11;


// Trampoline class for overriding in Python
template<typename ClassName, typename T>
class PyDataNode : public DataNode<ClassName, T> {
public:
    using Base::Base; // Inherit constructors
};

PYBIND11_MODULE(example, m) {
    py::class_<Base, PyBase, std::shared_ptr<Base>>(m, "Base")
        .def(py::init<>()) // This allows Python subclasses to call the base constructor
        .def_static("create", &Base::create);

    // Ensure Python subclassing works
    m.attr("__metaclass__") = py::type::of<py::class_<Base, PyBase, std::shared_ptr<Base>>>();
}
