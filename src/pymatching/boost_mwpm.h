#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "weighted_stabiliser_graph.h"

namespace py = pybind11;

py::array_t<std::uint8_t> BoostDecodeMatchNeighbourhood(WeightedStabiliserGraph& sg, const py::array_t<int>& defects, int num_neighbours);
py::array_t<std::uint8_t> BoostDecode(IStabiliserGraph& sg, const py::array_t<int>& defects);