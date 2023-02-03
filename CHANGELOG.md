# Version 2.2.0

This is a major change to the underlying code to remove the deprecated `pdal::PipelineExecutor` and replace it with `pdal::PipelineManager`.

This version also introduces the following non-breaking changes to the ABI:

- Addition of the following method to allow the consuming app to tell if a pipeline is streamable:

```
bool PDALPipelineIsStreamable(PDALPipelinePtr pipeline)
```

- Addition of the following method to allow the consuming application to run a pipeline in streaming mode. If the pipeline is non-streamable it will be silently run in standard mode:

```
bool PDALExecutePipelineAsStream(PDALPipelinePtr pipeline)
```


# Version 2.1.1

Changes to allow compilation with PDAL 2.4.0

- remove gitsha.h that has been removed from PDAL
- remove the mixed c / cpp calls in the tests

# Version 2.1.0

This version adds

- Access to face data in PDAL using the `GetMeshSize` and `getAllTriangles` methods,
- Updates the sample C# P/Invoke scripts to add the Mesh functions and remove depedencies on Unity. Asdded .csproj files and improved some signatures
- added more examples to readme.

# Version 2.0.0

This was the first version released through conda.
