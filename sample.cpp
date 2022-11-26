#include <pybind11/numpy.h>
#include "minfft/minfft.h"
namespace py = pybind11;

static py::array_t<std::complex<double>> fft(py::array_t<std::complex<double>> x) {
    // check ndim
    if (x.request().ndim != 1){
        throw std::runtime_error("ndim should be 1");
    }
    
    // get fft size
    int N = static_cast<int>(x.request().shape[0]);
    
    // make aux data
    minfft_aux *a = ::minfft_mkaux_dft_1d(N);
    if(a == nullptr){
        throw std::runtime_error("shape[0] should be a power of two");
    }

    // allocate return value
    py::array_t<std::complex<double>> y(x.request().shape);

    // execute fft
    ::minfft_dft(
        static_cast<minfft_cmpl*>(x.request().ptr),
        static_cast<minfft_cmpl*>(y.request().ptr),
        a);

    // free aux data
    ::minfft_free_aux(a);

    return y;
}

PYBIND11_MODULE(pybind11_test, m){
    m.def("fft", &fft);
}
