#include <pybind11/pybind11.h>
#include <pybind11/iostream.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
//#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <complex>
#include <functional>
#include <tuple>
#include <vector>
#include "../tpsa/include/da.h"
#include "../include/complex.h"

namespace py=pybind11;
using namespace pybind11::literals;

PYBIND11_MAKE_OPAQUE(DAVector);
PYBIND11_MAKE_OPAQUE(std::vector<DAVector>);
PYBIND11_MAKE_OPAQUE(std::vector<std::complex<DAVector>>);
PYBIND11_MAKE_OPAQUE(std::complex<DAVector>);

Base& get_base() {return da;}

PYBIND11_MODULE(tpsa, m) {
    m.doc() = "TPSA/DA lib";

    py::class_<std::complex<DAVector>>(m, "CD")
//        .def(py::init([](){return std::complex<DAVector>(0,0);}),py::return_value_policy::reference)
        .def(py::init<>(),py::return_value_policy::reference)
//        .def("complex", ([](std::complex<DAVector>& v, DAVector &r, DAVector &i){get_real(v)=r; get_imag(v)=i;}), py::return_value_policy::reference)
        .def("real", [](std::complex<DAVector> &v){return get_real(v);}, py::return_value_policy::reference)
        .def("real", [](std::complex<DAVector> &v, DAVector &r){get_real(v)=r;}, py::return_value_policy::reference)
        .def("imag", [](std::complex<DAVector> &v){return get_imag(v);}, py::return_value_policy::reference)
        .def("imag", [](std::complex<DAVector> &v, DAVector &i){get_imag(v)=i;}, py::return_value_policy::reference)
        .def("print", [](std::complex<DAVector> &v){std::cout<<v;})
        .def(py::self += double())
        .def(py::self += int())
        .def(py::self += py::self)
        .def(py::self -= double())
        .def(py::self -= int())
        .def(py::self -= py::self)
        .def(py::self *= double())
        .def(py::self *= int())
        .def(py::self *= py::self)
        .def(py::self /= double())
        .def(py::self /= int())
        .def(py::self /= py::self)
        .def(py::self + py::self)
        .def(double() + py::self)
        .def(py::self + double())
        .def(py::self - py::self)
        .def(double() - py::self)
        .def(py::self - double())
        .def(py::self * py::self)
        .def(double() * py::self)
        .def(py::self * double())
        .def(py::self / py::self)
        .def(double() / py::self)
        .def(py::self / double())
        .def(+ py::self)
        .def(- py::self);

    py::bind_vector<std::vector<std::complex<DAVector>>>(m, "CDVectorList");
    py::bind_vector<std::vector<DAVector>>(m, "DAVectorList");

//    py::class_<std::vector<std::complex<DAVector>>>(m, "CDVectorList")
//        .def(py::init<>(), py::return_value_policy::reference)
//        .def("assign", ([](std::vector<std::complex<DAVector>> &v, int n){std::complex<DAVector> x(0*da[0],0*da[0]); for(int i=0; i<n; ++i) v.push_back(x); }), py::return_value_policy::reference)
//        .def("clear", &std::vector<std::complex<DAVector>>::clear, py::return_value_policy::reference)
//        .def("pop_back", &std::vector<std::complex<DAVector>>::pop_back, py::return_value_policy::reference)
//        .def("push_back", (void (std::vector<std::complex<DAVector>>::*)(const std::complex<DAVector> &)) &std::vector<std::complex<DAVector>>::push_back, py::return_value_policy::reference)
//        .def("__len__", [](const std::vector<std::complex<DAVector>> &v){return v.size();})
//        .def("__getitem__", [](const std::vector<std::complex<DAVector>> &v, int i){if (i<0 || i>=v.size()) throw py::index_error(); return v[i];}, py::return_value_policy::reference)
//        .def("__setitem__", [](std::vector<std::complex<DAVector>> &v, int i, std::complex<DAVector> &x){if (i<0 || i>=v.size()) throw py::index_error(); v[i]=x;}, py::return_value_policy::reference)
//        .def("__iter__", [](std::vector<std::complex<DAVector>> &v) {
//             return py::make_iterator(v.begin(), v.end());
//             }, py::keep_alive<0,1>()); /* keep vector alive while iterator is used */


//    py::class_<std::vector<DAVector>>(m, "DAVectorList")
//        .def(py::init<>(), py::return_value_policy::reference)
//        .def("assign", ([](std::vector<DAVector> &v, int n){for(int i=0; i<n; ++i) v.push_back(0); }), py::return_value_policy::reference)
////        .def("assign", ([](std::vector<DAVector> &v, int n){DAVector x=0; for(int i=0; i<n; ++i) v.push_back(x); }), py::return_value_policy::reference)
//        .def("clear", &std::vector<DAVector>::clear, py::return_value_policy::reference)
//        .def("pop_back", &std::vector<DAVector>::pop_back, py::return_value_policy::reference)
//        .def("push_back", (void (std::vector<DAVector>::*)(const DAVector &)) &std::vector<DAVector>::push_back, py::return_value_policy::reference)
//        .def("__len__", [](const std::vector<DAVector> &v){return v.size();})
//        .def("__getitem__", [](const std::vector<DAVector> &v, int i){if (i<0 || i>=v.size()) throw py::index_error(); return v[i];}, py::return_value_policy::reference)
//        .def("__setitem__", [](std::vector<DAVector> &v, int i, DAVector &x){if (i<0 || i>=v.size()) throw py::index_error(); v[i]=x;}, py::return_value_policy::reference)
//        .def("__iter__", [](std::vector<DAVector> &v) {
//             return py::make_iterator(v.begin(), v.end());
//             }, py::keep_alive<0,1>()); /* keep vector alive while iterator is used */

    py::class_<DAVector>(m, "DAVector")
        .def(py::init<>())
        .def(py::init<const DAVector&>())
        .def(py::init<double>())
        .def("print", &DAVector::print)
        .def("con", &DAVector::con)
        .def("length", &DAVector::length)
        .def("n_element", &DAVector::n_element)
        .def("element", (double (DAVector::*)(int)) &DAVector::element, "i"_a)
        .def("index_element", [](const DAVector& v, unsigned int idx){std::vector<unsigned int> c; double elem; v.element(idx, c, elem);
            return std::make_tuple(c,elem);}, "idx"_a)
        .def("element", (double (DAVector::*)(std::vector<int>)) &DAVector::element, "idx"_a)
        .def("set_element", (void (DAVector::*)(std::vector<int>, double)) &DAVector::set_element, "idx"_a, "elem"_a, py::return_value_policy::reference)
        .def("reset", &DAVector::reset, py::return_value_policy::reference)
        .def("reset_const", &DAVector::reset_const, "x"_a, py::return_value_policy::reference)
        .def("clean", (void (DAVector::*)()) &DAVector::clean)
        .def("clean", (void (DAVector::*)(double)) &DAVector::clean, "eps"_a)
        .def("norm", &DAVector::norm)
        .def("weighted_norm", &DAVector::weighted_norm, "w"_a)
        .def("iszero", [](DAVector& v){return v.iszero();})
        .def("iszero", [](DAVector& v, double eps){return v.iszero(eps);}, "eps"_a)
        .def_static("dim", &DAVector::dim)
        .def_static("order", &DAVector::order)
        .def_static("full_length", &DAVector::full_length)
        .def(py::self += double())
        .def(py::self += int())
        .def(py::self += py::self)
        .def(py::self -= double())
        .def(py::self -= int())
        .def(py::self -= py::self)
        .def(py::self *= double())
        .def(py::self *= int())
        .def(py::self *= py::self)
        .def(py::self /= double())
        .def(py::self /= int())
        .def(py::self /= py::self)
        .def(py::self + py::self)
        .def(double() + py::self)
        .def(py::self + double())
        .def(py::self - py::self)
        .def(double() - py::self)
        .def(py::self - double())
        .def(py::self * py::self)
        .def(double() * py::self)
        .def(py::self * double())
        .def(py::self / py::self)
        .def(double() / py::self)
        .def(py::self / double())
        .def(+ py::self)
        .def(- py::self);

    py::class_<Base>(m, "Base")
        .def(py::init<>())
        .def("set_base", (void (Base::*)()) &Base::set_base)
        .def("set_base", (void (Base::*)(const unsigned int)) &Base::set_base, "n"_a)
        .def("__getitem__", &Base::operator[], "i"_a, py::return_value_policy::reference);

//    m.def("base", [](){return da;});
    m.def("base", &get_base, py::return_value_policy::reference);
    m.def("assign", [](){return DAVector(0);});
    m.def("assign", [](int n){std::vector<DAVector> v(n); return v;});
    m.def("assign_cd", [](int n){std::vector<std::complex<DAVector>> v(n); return v;});
    m.def("complex", [](DAVector &r, DAVector &i){return std::complex<DAVector>(r,i);});
    m.def("da_eps", [](){return DAVector::eps;});
    m.def("da_set_eps", &da_set_eps, "Set the cut-off value for DA vectors.", "eps"_a);
    m.def("da_init", &da_init, "Initialize the DA environment.", "da_order"_a, "da_dim"_a, "num_da_vectors"_a, "bool"_a=true);
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
    m.def("da_set_eps", &da_set_eps);
    m.def("da_der", (void (*)(const DAVector&, unsigned int, DAVector&)) &da_der, "da_vector"_a, "base_id"_a, "da_vector_der"_a);
    m.def("da_int", (void (*)(const DAVector&, unsigned int, DAVector&)) &da_int, "da_vector"_a, "base_id"_a, "da_vector_int"_a);
    m.def("da_der", (DAVector (*)(const DAVector&, unsigned int)) &da_der, "da_vector"_a, "base_id"_a);
    m.def("da_int", (DAVector (*)(const DAVector&, unsigned int))  &da_int, "da_vector"_a, "base_id"_a);
    m.def("da_substitute_const", &da_substitute_const, "iv"_a, "base_id"_a, "x"_a, "ov"_a);
    m.def("da_substitute_const", [](const DAVector iv, unsigned int idx, double x){DAVector ov; da_substitute_const(iv, idx, x, ov); return ov;});
    m.def("da_substitute", (void (*)(const DAVector&, unsigned int, const DAVector&, DAVector&)) &da_substitute, "iv"_a,
          "base_id"_a, "v"_a, "ov"_a);
    m.def("da_substitute", [](const DAVector iv, unsigned int idx, const DAVector v){DAVector ov; da_substitute(iv, idx, v, ov); return ov;});
    m.def("da_substitute", (void (*)(const DAVector&, std::vector<unsigned int>&, std::vector<DAVector>&, DAVector&)) &da_substitute,
          "iv"_a, "based_id"_a, "v"_a, "ov"_a);
    m.def("da_substitute", [](const DAVector iv, std::vector<unsigned int>& idx, std::vector<DAVector>& v){DAVector ov; da_substitute(iv, idx, v, ov); return ov;});
    m.def("da_substitute", (void (*)(std::vector<DAVector>&, std::vector<unsigned int>&, std::vector<DAVector>&, std::vector<DAVector>&))
          &da_substitute, "iv"_a, "base_id"_a, "v"_a, "ov"_a);
    m.def("da_composition", (void (*)(std::vector<DAVector>&, std::vector<DAVector>&, std::vector<DAVector>&)) &da_composition, "iv"_a,
          "v"_a, "ov"_a);
    m.def("da_composition", [](std::vector<DAVector>& ivecs, std::vector<double>& v){std::vector<double> o(ivecs.size()); da_composition(ivecs, v, o); return o;});
    m.def("da_composition", [](std::vector<DAVector>& ivecs, std::vector<std::complex<double>>& v) {std::vector<std::complex<double>> o(ivecs.size());
           da_composition(ivecs, v, o); return o; });
    m.def("cd_composition", (void (*)(std::vector<DAVector>&, std::vector<std::complex<DAVector>>&,
                                      std::vector<std::complex<DAVector>>&)) &cd_composition, "ivecs"_a, "v"_a, "ovecs"_a, py::return_value_policy::reference);
    m.def("cd_composition", (void (*)(std::vector<std::complex<DAVector>>&, std::vector<std::complex<DAVector>>&,
                                      std::vector<std::complex<DAVector>>&)) &cd_composition, "ivecs"_a, "v"_a, "ovecs"_a, py::return_value_policy::reference);
    m.def("cd_composition", (void (*)(std::vector<std::complex<DAVector>>&, std::vector<DAVector>&,
                                      std::vector<std::complex<DAVector>>&)) &cd_composition, "ivecs"_a, "v"_a, "ovecs"_a, py::return_value_policy::reference);
    m.def("inv_map", &inv_map, "ivecs"_a, "dim"_a, "ovecs"_a);
    m.def("print",[](DAVector& vec) {
          py::scoped_ostream_redirect stream(std::cout);
          vec.print();
    });
    m.def("print",[](std::complex<DAVector>& vec) {
          py::scoped_ostream_redirect stream(std::cout);
          std::cout<<vec;
    });
}
