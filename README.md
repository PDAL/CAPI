pdal-c: PDAL C API
==================

[//]: # (@cond Hide build status from Doxygen)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/OSX%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/Linux%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/Windows%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)

[![Anaconda-Server Badge](https://anaconda.org/conda-forge/pdal-c/badges/version.svg)](https://anaconda.org/conda-forge/pdal-c)

[//]: # (@endcond)

# Basics

*pdal-c* is a C API for the Point Data Abstraction Library ([PDAL](https://pdal.io))
and is compatible with PDAL 1.7 and later.

*pdal-c* is released under the [BSD 3-clause license](LICENSE.md).

# Documentation

[API Documentation](https://pdal.io/CAPI/doxygen/html/index.html)

# Installation

The library can be installed as a package on Windows, Mac and Linux using Conda.

```
conda install -c conda-forge pdal-c
```

The conda package includes a tool called `test_pdalc`. Run this to confirm that the API configuration is correct and to report on the version of PDAL that the API is connected to.

## Dependencies

The library is dependent on PDAL and has currently been tested up to v2.2.0.

# Usage

An example of the use of the API is given in the `csharp` folder which contains an integration to PDAL in C#.

NOTE - these scripts are provided for information only as examples and are not supported in any way!

# For Developers

## Build on Windows

The library can be built on Windows using the following command - which assumes that you are in a conda environment that has the conda-forge `pdal` package loaded:

```
cd CAPI
make.bat
```

## Build on Linux and Mac

The library can be built on Linux and Mac using the following command - which assumes that you are in a conda environment that has the conda-forge `pdal` package loaded:

```
cd CAPI
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCONDA_BUILD=OFF .
make
make install
```

## Code Style

This project enforces the PDAL code styles, which can checked as follows :

- On Windows - as per `astylerc`
- On Linux by running `./check_all.bash`
