# Convhull_3d

A header only C implementation of the 3-D quickhull algorithm for building Convex Hulls. The implementation was designed to also work for challenging cases, such as spherical arrangements with nearly-uniformly distributed vertices, where it performs similarly to the MatLab 'convhull' function. The code is also C++ compiler safe.

![](images/sph_tdesigns.png)

## Getting Started

To use this 3-D convexhull implementation in a '.c' or '.cpp' file , simply add the following:

```c
#define CONVHULL_3D_ENABLE
#include "convhull_3d.h"
```

Then specify the vertices, which can be optionally extracted from an '.obj' file using the following code:

```c
ch_vertex* vertices = NULL;
int nVertices;
extractVerticesFromObjFile(OBJ_FILE_NAME, &vertices, &nVertices);
```

Where 'OBJ_FILE_NAME' is the '.obj' file path (without the extention).

The convexhull may then be built and subsequently exported using this code:
```c
int* out_faces = NULL;
int nFaces;
convhull_3d_build(vertices, nVertices, &out_faces, &nFaces);
convhull_3d_export_obj(vertices, nVertices, out_faces, nFaces, 1, OUTPUT_OBJ_FILE_NAME);
```

Where 'OUTPUT_OBJ_FILE_NAME' is the output '.obj' file path (without the extention).

### Additional options

By default, the algorithm uses double floating point precision to build the hull, but it still exports the results in floating point precision. However, one may configure it to use single precision to build the hull (which is less accurate but quicker) by adding the following:
```c
#define CONVHULL_3D_USE_FLOAT_PRECISION /* (optional) */
#define CONVHULL_3D_ENABLE
#include "convhull_3d.h"
```

Also, if your project has CBLAS linked, then you can speed up the matrix multiplications by adding:
```c
#define CONVHULL_3D_USE_CBLAS /* (optional) */
#define CONVHULL_3D_USE_FLOAT_PRECISION /* (optional) */
#define CONVHULL_3D_ENABLE
#include "convhull_3d.h"
```

## Test

This repository contains files: 'test/test_convhull_3d.c' and 'test/test_script.m'. The former can be used to generate Convex Hulls of the '.obj' files in 'test/obj_files', which can be subsequently verified in MatLab using the latter file.

![](images/teapot_matlab.png)

## Examples

The 'test/test_convhull_3d.c' file may also serve as example usage of the convhull_3d implementation. The following images are depictions of the generated .obj files, using Tim Maxwell's OBJ Viewer:

![](images/teapot.png)
![](images/violin_case.png)
![](images/sandal.png)

## License

The code is distributed under the MIT license, but contains code that was originally written for MatLab by George Papazafeiropoulos (c) 2014; which was distributed under the BSD (2-clause) license and can be found [here](https://se.mathworks.com/matlabcentral/fileexchange/48509-computational-geometry-toolbox?focused=3851286&tab=function).

## Contact

If you have any questions, or spot any bugs, please email: leo.mccormack@aalto.fi
