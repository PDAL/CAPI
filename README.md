pdal-c: PDAL C API
==================

[//]: # (@cond Hide build status from Doxygen)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/OSX%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/Linux%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)
[![Actions Status](https://github.com/PDAL/CAPI/workflows/Windows%20Build%20Test/badge.svg)](https://github.com/PDAL/CAPI/actions)

[![Anaconda-Server Badge](https://anaconda.org/conda-forge/pdal-c/badges/version.svg)](https://anaconda.org/conda-forge/pdal-c)
[![openupm](https://img.shields.io/npm/v/com.virgis.pdal?label=openupm&registry_uri=https://package.openupm.com)](https://openupm.com/packages/com.virgis.pdal/)

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

This interface is suitable for use with C# and with Unity.

There is a [Unity Package Manager (UPM) package for PDAL](https://openupm.com/packages/com.virgis.pdal/) based on this library.

## Dependencies

The library is dependent on PDAL and has currently been tested up to v2.2.0.

# Usage

An example of the use of the API is given in the `csharp` folder which contains an integration to PDAL in C#.

NOTE - these scripts are provided for information only as examples and are not supported in any way!

## Example C# Program

``` c#
using System;
using System.Collections.Generic;
using Pdal;
using Newtonsoft.Json;
using g3;

namespace pdal_mesh
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            Config pdal = new Config();
            Console.WriteLine(pdal.Version);

            List<object> pipe = new List<object>();
            pipe.Add(".../CAPI/tests/data/las/1.2-with-color.las");
            pipe.Add(new
            {
                type = "filters.splitter",
                length = 1000
            });
            pipe.Add(new
            {
                type = "filters.delaunay"
            });

            string json = JsonConvert.SerializeObject(pipe.ToArray());

            Pipeline pl = new Pipeline(json);

            long count = pl.Execute();

            Console.WriteLine($"Point Count is {count}");

            using (PointViewIterator views = pl.Views) {
                views.Reset();

                while (views.HasNext())
                {
                    PointView view = views.Next;
                    if (view != null)
                    {
                        Console.WriteLine($"Point Count is {view.Size}");
                        Console.WriteLine($"Triangle Count is {view.MeshSize}");

                        BpcData pc = view.GetBakedPointCloud();

                        DMesh3 mesh = view.getMesh();

                    }
                }
            }
        }
    }
}
```

This takes a LAS file, splits the file into tiles and then creates a Delaunay Triangulation (i.e. Mesh) for each one.

This code uses the sample bindings as-is and has a dependency on [Geometry3Sharp](https://github.com/gradientspace/geometry3Sharp) only.

Note that `BcpData` is a custom data structure that holds the Point Cloud in a form suitable to create a [Baked PointCloud](https://medium.com/realities-io/point-cloud-rendering-7bd83c6220c8) suitable for rendering as a VFX graph in Unity. This is an efficient way to display point cloud data in VR and I have used it successfully with point clouds of 10 million points. 

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

Setting `-DBUILD_SHARED_LIBS=OFF` enables the generation of a static (`.a`) library. 

## Code Style

This project enforces the PDAL code styles, which can checked as follows :

- On Windows - as per `astylerc`
- On Linux by running `./check_all.bash`
