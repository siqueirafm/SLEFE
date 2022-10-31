# SLEFE

A library to build subdividable linear efficient function enclosures.

## Introduction  

TBD

## Contents

The code is organized as follows:  

* bin            - empty subdirectory where the application `slefe-app` is stored after the build.
* doc            - subdirectory where `doxygen` documentation is stored.
* include        - empty subdirectory where the header files are stored after the build.
* lib            - empty subdirectory where the binary library files are stored after the build.
* plots          - subdirectory where PDF files of plots of basis functions of degree 2 to 9 and their *slefes* are stored.
* src            - subdirectory where the source code of the demo, library, and unit tests are stored.
* tst            - empty subdirectory where the application `slefe-tst` is stored after the build.
* LICENSE.md     - license file for the library.  
* README.md      - this file.  
* CMakeLists.txt - input to the `cmake` build system.


## Installation  

You need `cmake` 3.15 or higher and a C++ compiler that supports C++ 17 to build
the library and the application demo. If you enable the build of unit tests, then
`cmake` will try to download and install the *GTest* library automatically from
[here](https://github.com/google/googletest/). Both options have successfully been
built with `cmake` version 3.22.1 on Linux (Ubuntu 22.04 LTS with GNU g++ 11.2.0),
Windows 10 (MS Visual Studio 17), and macOS Monterrey version 12.6 (clang version
14.0.0).

To build and install the library, follow the steps below:

1. Download or clone the code, and then enter the directory `SLEFE`
2. Run `cmake -S . -B build`
3. Run `cmake --build build --config Release`
4. Run `cmake --install build --prefix` [ *full path to your `SLEFE` directory* ]

If all goes well, then you should see the application `slefe-app` (or `slefe-app.exe`
on Windows) in subdirectory `bin` and the library `libslefe.a` (or `slefe.lib` on
Windows) in subdirectory `lib`. If you want to build the unit tests, then execute
the steps above with the following change to step 2:

+ Run `cmake -S . -B build -D BUILD_UNIT_TESTS=ON`

If all goes well, then you should see the application `slefe-tst` (or `slefe-tst.exe`
on Windows) in subdirectory `tst`.

Likewise, if you want to build `doxygen` documentation files, then execute the
steps above with the following change to step 2:

+ Run `cmake -S . -B build -D BUILD_DOC=ON`

Documentation is generated only if `cmake` can find `doxygen` in your system. If
this is the case and the build succeeds, then the documentation files are placed
in subdirectory `doc`.

You should combine the two changes if you wish to build both the unit tests and
the documentation files:

+ Run `cmake -S . -B build -D BUILD_UNIT_TESTS=ON -D BUILD_DOC=ON`

##  References

1. Lutterkort, D.,
   [Envelopes for Nonlinear Geometry][1],
   PhD thesis, Purdue University, May 2000.

2. Lutterkort, D. and Peters, J.,
   [Linear envelopes for uniform B-spline curves][2],
   Curves and Surface Fitting, Saint-Malo, France, July 1-7, 1999, p. 239-246.

3. Lutterkort, D. and Peters, J.,
   [Optimized refinable enclosures of multivariate polynomial pieces][3],
   CAGD, 18(9), 2001, p. 851-863.

4. Wu, X. and Peters, J.,
   [On the Optimality of Piecewise Linear Max-norm Enclosures based on Slefes][4],
   Curves and Surface Design, Saint-Malo, France, 2002, p. 335-344.

[1]: https://www.cise.ufl.edu/research/SurfLab/papers/99envthesis.pdf
[2]: https://www.cise.ufl.edu/research/SurfLab/papers/stmalo.ps
[3]: https://doi.org/10.1016/S0167-8396(01)00067-X
[4]: https://www.cise.ufl.edu/research/SurfLab/papers/02stmaloSlefe.ps.gz

##  Last Update

October 29, 2022

## Contact

If you run into trouble compiling or using the library, please email me at:

<mfsiqueira@gmail.com>

Have fun!

Marcelo Siqueira
