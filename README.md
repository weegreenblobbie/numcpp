numcpp
======

A C++ array object that tries to match the expressiveness of numpy.


Why another array library in C++?
=================================

This project is meant to exercise my my template and operator overloading skills.  The goal
is to achive expressions very close to Python & NumPy.

Examples
========

```python
>>> import numpy as np

>>> a = np.arange(15).reshape(3, 5)
>>> a
array([[ 0,  1,  2,  3,  4],
       [ 5,  6,  7,  8,  9],
       [10, 11, 12, 13, 14]])
>>> a.shape
(3, 5)
>>> a.ndim
2
>>> a.dtype.name
'int64'
>>> a.itemsize
8
>>> a.size
15
```

```c++
#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;

using namespace numcpp;

auto a = arange<int64>(15).reshape({3,5});

cout
    << a.print("%2d")          << "\n"
    << "shape = " << a.shape() << "\n"
    << "ndim  = " << a.ndim()  << "\n"
    << "size  = " << a.size()  << "\n";
/*
array([
    [  0,  1,  2,  3,  4 ],
    [  5,  6,  7,  8,  9 ],
    [ 10, 11, 12, 13, 14 ],
], int64)
shape = (3, 5, )
ndim  = 2
size  = 15
*/
```

```python
>>> c = np.array(
    [ [1,2], [3,4] ], dtype = complex)
>>> c
array([[ 1.+0.j,  2.+0.j],
       [ 3.+0.j,  4.+0.j]])
```

```c++
auto c1 = array<complex64>(
    {1,2,3,4}
).reshape({2,2});

auto c2 = array<complex64>(
    { {1,2}, {3,4} }
);

cout
    << c1.print("%.1f") << "\n"
    << "\n"
    << c2.print("%.1f") << "\n";

/*

array([
    [ 1.0+0.0j, 2.0+0.0j ],
    [ 3.0+0.0j, 4.0+0.0j ],
], complex64)

array([ 1.0+2.0j, 3.0+4.0j ], complex64)

*/
```

```python
>>> np.zeros( (3,4) )
array([[ 0.,  0.,  0.,  0.],
       [ 0.,  0.,  0.,  0.],
       [ 0.,  0.,  0.,  0.]])

>>> np.ones( (2,3,4), dtype=np.int16 )
array([[[ 1, 1, 1, 1],
        [ 1, 1, 1, 1],
        [ 1, 1, 1, 1]],
       [[ 1, 1, 1, 1],
        [ 1, 1, 1, 1],
        [ 1, 1, 1, 1]]], dtype=int16)

# uninitialized, output may vary
>>> np.empty( (2,3) )
array([[  3.73603959e-262,   6.02658058e-154,   6.55490914e-260],
       [  5.30498948e-313,   3.14673309e-307,   1.00000000e+000]])
```

```c++
cout << zeros<float32>({3,4}).print("%.1f") << "\n";

/*
array([
    [ 0.0, 0.0, 0.0, 0.0 ],
    [ 0.0, 0.0, 0.0, 0.0 ],
    [ 0.0, 0.0, 0.0, 0.0 ],
], float32)
*/

// 3D not yet implemented (2017-01-27)
cout << ones<int16>({2,3}) << "\n";

/*
array([
    [ 1, 1, 1 ],
    [ 1, 1, 1 ],
], int16)
*/

// uninitialized array not supported (yet?)
```

```python
>>> np.arange( 10, 30, 5 )

array([10, 15, 20, 25])

>>> np.arange( 0, 2, 0.3 )

array([ 0. ,  0.3,  0.6,
    0.9,  1.2,  1.5,  1.8])
```

```c++

cout << arange<int32>(10, 30, 5) << "\n";

// array([ 10, 15, 20, 25 ], int32)

cout << arange<float32>(0, 2, 0.3).print("%.1f") << "\n";

// array([ 0.0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8 ], float32)
```

How to build unittests
======================

`scons --test`


How to get unittest code coverage
=================================

`scons --coverage`

Then open the file `coverage/index.html` with a webrowser.
