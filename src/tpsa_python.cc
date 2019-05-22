#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <functional>
#include <tuple>
#include <vector>
#include "../tpsa/include/da.h"

namespace py=pybind11;
using namespace pybind11::literals;
using std::vector;

PYBIND11_MODULE(tpsa, m) {
    m.doc() = "TPSA/DA lib";

    py::class_<DAVector>(m, "DAVector")
        .def(py::init<>())
        .def(py::init<const DAVector&>())
        .def(py::init<double>())
        .def("print", &DAVector::print)
        .def("con", &DAVector::con)
        .def("length", &DAVector::length)
        .def("n_element", &DAVector::n_element)
        .def("element", (double (DAVector::*)(int)) &DAVector::element, "i"_a)
        .def("index_element", [](const DAVector& v, unsigned int idx){vector<unsigned int> c; double elem; v.element(idx, c, elem);
            return std::make_tuple(c,elem);}, "idx"_a)
        .def("element", (double (DAVector::*)(vector<int>)) &DAVector::element, "idx"_a)
        .def("set_element", (void (DAVector::*)(vector<int>, double)) &DAVector::set_element, "idx"_a, "elem"_a)
        .def("reset", &DAVector::reset)
        .def("reset_const", &DAVector::reset_const, "x"_a)
        .def("clean", &DAVector::clean, "eps"_a)
        .def_static("dim", &DAVector::dim)
        .def_static("order", &DAVector::order)
        .def_static("full_length", &DAVector::full_length)
        .def(py::self += float())
        .def(py::self += int())
        .def(py::self += py::self)
        .def(py::self -= float())
        .def(py::self -= int())
        .def(py::self -= py::self)
        .def(py::self *= float())
        .def(py::self *= int())
        .def(py::self *= py::self)
        .def(py::self /= float())
        .def(py::self /= int())
        .def(py::self /= py::self)
        .def(py::self + py::self)
        .def(float() + py::self)
        .def(py::self + float())
        .def(py::self - py::self)
        .def(float() - py::self)
        .def(py::self - float())
        .def(py::self * py::self)
        .def(float() * py::self)
        .def(py::self * float())
        .def(py::self / py::self)
        .def(float() / py::self)
        .def(py::self / float())
        .def(+ py::self)
        .def(- py::self);

    py::class_<Base>(m, "Base")
        .def(py::init<>())
        .def("set_base", (void (Base::*)()) &Base::set_base)
        .def("set_base", (void (Base::*)(const unsigned int)) &Base::set_base, "n"_a)
        .def("__getitem__", &Base::operator[], "i"_a);

    m.def("base", [](){return da;});
    m.def("da_init", &da_init, "Initialize the DA environment.", "da_order"_a, "da_dim"_a, "num_da_vectors"_a);
    m.def("da_clear", &da_clear, "Destroy the DA environment");
    m.def("sqrt", (DAVector (*)(const DAVector&)) &sqrt, "da_vector"_a);
    m.def("exp", (DAVector (*)(const DAVector&)) &exp, "da_vector"_a);
    m.def("log", (DAVector (*)(const DAVector&)) &log, "da_vector"_a);
    m.def("sin", (DAVector (*)(const DAVector&)) &sin, "da_vector"_a);
    m.def("cos", (DAVector (*)(const DAVector&)) &cos, "da_vector"_a);
    m.def("tan", (DAVector (*)(const DAVector&)) &tan, "da_vector"_a);
    m.def("asin", (DAVector (*)(const DAVector&)) &asin, "da_vector"_a);
    m.def("acos", (DAVector (*)(const DAVector&)) &acos, "da_vector"_a);
    m.def("atan", (DAVector (*)(const DAVector&)) &atan, "da_vector"_a);
    m.def("sinh", (DAVector (*)(const DAVector&)) &sinh, "da_vector"_a);
    m.def("cosh", (DAVector (*)(const DAVector&)) &cosh, "da_vector"_a);
    m.def("tanh", (DAVector (*)(const DAVector&)) &tanh, "da_vector"_a);
    m.def("abs", (double (*)(const DAVector&)) &abs, "da_vector"_a);
    m.def("erf", (DAVector (*)(const DAVector&)) &erf, "da_vector"_a);
    m.def("pow", (DAVector (*)(const DAVector&, const int)) &pow, "da_vector"_a, "order"_a);
    m.def("pow", (DAVector (*)(const DAVector&, const double)) &pow, "da_vector"_a, "order"_a);
    m.def("da_count", &da_count);
    m.def("da_remain", &da_remain);
    m.def("da_full_length", &da_full_length);
    m.def("da_der", (void (*)(const DAVector&, unsigned int, DAVector&)) &da_der, "da_vector"_a, "base_id"_a, "da_vector_der"_a);
    m.def("da_int", (void (*)(const DAVector&, unsigned int, DAVector&)) &da_int, "da_vector"_a, "base_id"_a, "da_vector_int"_a);
    m.def("da_der", (DAVector (*)(const DAVector&, unsigned int)) &da_der, "da_vector"_a, "base_id"_a);
    m.def("da_int", (DAVector (*)(const DAVector&, unsigned int))  &da_int, "da_vector"_a, "base_id"_a);
    m.def("da_subscribe_const", &da_subscribe_const, "iv"_a, "base_id"_a, "x"_a, "ov"_a);
    m.def("da_subscribe", (void (*)(const DAVector&, unsigned int, const DAVector&, DAVector&)) &da_subscribe, "iv"_a,
          "base_id"_a, "v"_a, "ov"_a);
    m.def("da_subscribe", (void (*)(const DAVector&, vector<unsigned int>&, vector<DAVector>&, DAVector&)) &da_subscribe,
          "iv"_a, "based_id"_a, "v"_a, "ov"_a);
    m.def("da_subscribe", (void (*)(vector<DAVector>&, vector<unsigned int>&, vector<DAVector>&, vector<DAVector>&))
          &da_subscribe, "iv"_a, "base_id"_a, "v"_a, "ov"_a);
    m.def("da_composition", (void (*)(vector<DAVector>&, vector<DAVector>&, vector<DAVector>&)) &da_composition, "iv"_a,
          "v"_a, "ov"_a);
    m.def("da_composition", (void (*)(vector<DAVector>&, vector<double>&, vector<double>&)) &da_composition, "iv"_a,
          "v"_a, "ov"_a);
    m.def("inv_map", &inv_map, "ivecs"_a, "dim"_a, "ovecs"_a);
}
