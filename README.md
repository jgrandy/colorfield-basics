## Colorfield Basics: C++ Numeric and Simulation Library


### Description

Colorfield Basics is a C++ library I wrote from 1995-2001, including support for matrix algebra and certain numerical simulations. I started the project in the SCS PhD program at Carnegie Mellon, and developed it further as part of a startup called Colorfield Digital Media. Basics shipped with two products, Xproof and Insight, but I wouldn't say the library was ever completed. It certainly wouldn't have met Boost standards for library design.

I'm posting it to github as sort of a historical artifact and because it includes a few interesting techniques that I hadn't seen in other C++ libraries. (I've been away from the C++ world for a few years so they may well be familiar by now.) Please treat it as a source of ideas and inspiration rather than anything project-worthy.

The library makes really extensive use of template meta-programming. At the time I was first writing it there were not many C++ numerics libraries, and very few that made extensive use of template meta-programming to drive performance. I remember being proud of the fact that a dense matrix multiply from my library was only a few instructions longer than a hand-written version.

To my mind the whole point of writing a template matrix library is to make it  possible to write matrix algorithms (everything from a simple AXPY operation to a Runge-Kutta solver) with little concern for scalar type, matrix storage layout (dense or sparse) or whether the inputs are statically or dynamically dimensioned. The matrix class in Colorfield Basics uses template arguments to control both dimensions and storage but doesn't parameterize scalar type. I chose not to include scalar type as a template argument because including it required everything to be a template, which compounded complexity quite a bit. I settled on one type - `double` - and moved on.

Control of both dynamic and static dimensions in a single template argument is a bit tricky because a single template argument can be either a type or a value, but not both. My solution involved turning small integers into types through a small template class called `cindex`. This allowed `size_t` to be intermixed with, e.g. `cindex<3>`. With this technique I could express a 3x3 matrix using `cindex<3>` for width and height, or a 1xn column vector using `cindex<1>` for width and `size_t` for height. With appropriate use of traits it is possible to statically check dimensional compatibility of matrices and to do other compile-time dimensional computations.

Later in the development of the library I became interested in doing compile-time composition of vector functions. I began the library because I was studying physically-based modelling under Andy Witkin in the CMU SCS graphics lab, and as part of that we wrote a lot of solvers that did nonlinear constrained optimization. These solvers require evaluation of both a vector function's value and its derivative. Others in Andy's lab had written libraries that did runtime composition of vector functions, but I wanted to try compile-time composition. The result worked pretty well, but there were wrappers required that couldn't be entirely hidden from the user so I'm not sure I would call the design a success. It is a good example of how to navigate a tricky template design problem, though.

For me this library represents the results of commitment to a fairly radical design approach - extensive use of template meta-programming. I can admire the principled stance taken by my younger self, but I'm not as interested in working through all the difficult (and obscure) challenges with compiling complex templated programs, so I don't see myself picking this code up and improving it. If you get inspired please do let me know, though!


### Features

* Matrices and vectors with basic operations (comparison, copy, assignment, multiplication (axpy)

* Vector function with function composition and derivative calculations

* Linear solvers: LU Decomposition, Cholesky, Conjugate Gradient

* Nonlinear solvers: Euler, Runge-Kutta

* A library for working with systems of geometric objects (points, lines, etc). Useful for particle simulations and the like, but not developed enough for 2D or 3D solid-body simulation.

* A library for doing nonlinear constrained simulation over geometric systems.

* Compiles with Xcode 5 using clang 4 with libc++ and C++11 turned on. It probably compiles (with some work) on other modern C++ compilers, but I haven't tried.


### Missing or Mis- Features

* One oddity of the library is that it doesn't include sparse matrix support. I originally wrote sparse matrix code, but it didn't survive a design iteration and I didn't need it for what I was doing so it never got coded.

* The automated tests are really sparse, in places just verification that a particular template specialization properly compiles.

* Several automated tests actually fail.

* Since the library was originally written in the late 1990s it doesn't use any improvements in the C++ language since that time. I was impressed that so much of my code made the transition from pre-TR1 Boost to modern libc++; the only major change I had to make was to add `typename` to a bunch of qualified types.


### Project Status

This project was set aside in 2001, and a small amount of work was done in late 2013 to get it to compile and pass the automated tests. I don't currently have plans to do further work with it. There are probably many C++ based numerics libraries now, so if I were to start another project I would certainly look at them before picking this code base myself.


### Credits and Acknowledgements

The code here was entirely written by me. Several algorithms were adapted from standard sources, credit given in the sources.

Thanks to Andy Witkin and David Baraff for sparking my interest in physically-based modeling.