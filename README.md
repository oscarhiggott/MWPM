# PyMatching

![Continuous Integration](https://github.com/oscarhiggott/PyMatching/workflows/ci/badge.svg)
[![codecov](https://codecov.io/gh/oscarhiggott/PyMatching/branch/master/graph/badge.svg)](https://codecov.io/gh/oscarhiggott/PyMatching)
[![docs](https://readthedocs.org/projects/pymatching/badge/?version=latest&style=plastic)](https://readthedocs.org/projects/pymatching/builds/)
[![PyPI version](https://badge.fury.io/py/PyMatching.svg)](https://badge.fury.io/py/PyMatching)
[![Unitary Fund](https://img.shields.io/badge/Supported%20By-UNITARY%20FUND-brightgreen.svg?style=for-the-badge)](http://unitary.fund)

PyMatching is a fast Python/C++ library for decoding quantum error correcting codes (QECC) using the Minimum Weight
Perfect Matching (MWPM) decoder. PyMatching can decode codes for which each error generates a pair of syndrome defects (
or only a single defect at a boundary). Codes that satisfy these properties include two-dimensional topological codes
such as the [toric code](https://en.wikipedia.org/wiki/Toric_code),
the [surface code](https://arxiv.org/abs/quant-ph/0110143) and [2D hyperbolic codes](https://arxiv.org/abs/1506.04029),
amongst others. PyMatching can also be used as a subroutine to decode other codes, such as the 3D toric code and
the [color code](https://arxiv.org/abs/1905.07393). PyMatching can handle boundaries, measurement errors and weighted
edges in the matching graph. Since the core algorithms are written in C++, PyMatching is much faster than a pure Python
NetworkX implementation.

Documentation for PyMatching can be found at: [pymatching.readthedocs.io](https://pymatching.readthedocs.io/en/stable/)

## Installation

PyMatching can be downloaded and installed from [PyPI](https://pypi.org/project/PyMatching/) with the command:

```
pip install pymatching
```

This is the recommended way to install PyMatching since pip will fetch the pre-compiled binaries, rather than building
the C++ extension from source on your machine. Note that PyMatching requires Python 3.

If instead you would like to install PyMatching from source, clone the repository (using the `--recursive` flag to
include the lib/pybind11 submodule) and then use `pip` to install:

```
git clone --recursive https://github.com/oscarhiggott/PyMatching.git
pip install -e ./PyMatching
```

The installation may take a few minutes since the C++ extension has to be compiled. If you'd also like to run the tests,
first install [pytest](https://docs.pytest.org/en/stable/), and then run:

```
pytest ./PyMatching/tests ./PyMatching/src
```

## Usage

In order to decode a parity check matrix `H` (a `scipy.sparse` matrix) with syndrome vector `z` (a bitstring which is a
numpy array of dtype int), first construct the `Matching` object after importing it:

```
from pymatching import Matching
m = Matching(H)
```

Now to decode, simply run:

```
c = m.decode(z)
```

which outputs a bitstring `c`, which is a numpy array of ints corresponding to the minimum-weight correction. Note that
the `m` by `n` parity check matrix `H` should correspond to the Z (or X) stabilisers of a CSS code with `n` qubits, `m`
Z (or X) stabilisers, and with either one or two non-zero entries per column.

To decode instead in the presence of measurement errors, each stabiliser measurement is repeated `L` times, and decoding
then takes place over a 3D matching graph (see Section IV B of [this paper](https://arxiv.org/abs/quant-ph/0110143)),
which can be constructed directly from the check matrix `H` using:

```
m = Matching(H, repetitions=L)
```

and then decoded from an `m` by `L` numpy array syndrome `z` using:

```
c = m.decode(z)
```

Instead of using a check matrix, the Matching object can also be constructed using
the [`Matching.add_edge`](https://pymatching.readthedocs.io/en/stable/api.html#pymatching.matching.Matching.add_edge)
method or by loading from a NetworkX graph. PyMatching supports arbitrary graphs, including weighted edges and boundary
nodes.

PyMatching can be used with [Stim](https://github.com/quantumlib/Stim) for circuit-level simulations of quantum error
correction protocols. Stim is a powerful tool that can automatically construct matching graphs just from the definition
of the annotated stabiliser circuit used for stabiliser measurements. Stim can also be used to sample from the
stabiliser measurement circuits. The
Stim ["getting started" notebook](https://github.com/quantumlib/Stim/blob/main/doc/getting_started.ipynb) contains an
example that uses Stim and PyMatching to estimate the circuit-level threshold of a quantum error correcting code.

For more details on how to use PyMatching,
see [the documentation](https://pymatching.readthedocs.io/en/stable/usage.html).