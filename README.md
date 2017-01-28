numcpp
======

A C++ array object that tries to match the expressiveness of numpy.


How to build unittests
======================

`scons --test`


How to get unittest code coverage
=================================

`scons --coverage`

Then open the file `coverage/index.html` with a webrowser.


Examples
========

Creating arrays
---------------

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

// init the real parts only
auto c = array<complex64>({1,2,3,4}).reshape({2,2});

cout << c.print("%.1f") << "\n";
/*
array([
    [ 1.0+0.0j, 2.0+0.0j ],
    [ 3.0+0.0j, 4.0+0.0j ],
], complex64)
*/

// init both the real & imag parts
auto c2 = array<complex64>( { {1,2}, {3,4} } );

cout << c2.print("%.1f") << "\n"
// array([ 1.0+2.0j, 3.0+4.0j ], complex64)
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

array([ 0. ,  0.3,  0.6,  0.9,  1.2,  1.5,  1.8])
```

```c++

cout << arange<int32>(10, 30, 5) << "\n";
// array([ 10, 15, 20, 25 ], int32)

cout << arange<float32>(0, 2, 0.3).print("%.1f") << "\n";
// array([ 0.0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8 ], float32)
```

Slicing
-------

```python
>>> a = np.arange(10)
>>> a
array([  0,  1,  2,  3,  4,  5,  6,  7,  8,  9 ])

>>> a[2]
2

>>> a[2:5]
array([ 2, 3, 4])

>>> a[:6:2] = -1000
>>> a
array([-1000,     1, -1000,     3, -1000,     5,     6,     7,     8,     9])

>>> a[ : :-1]
array([    9,     8,     7,     6,     5, -1000,     3, -1000,     1, -1000])
```

```c++
auto a = arange<int>(10);

cout << a << "\n";
// array([ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], int32)

cout << a(2) << "\n";
// 2

cout << a(2_s|5) << "\n";     // _s is a literal operator to start a slice
// array([ 2, 3, 4 ], int32)

missing _;  // a helper object that represent missing args to slice expressions

a(_|6|2) = -1000;

cout << a << "\n";
// array([ -1000, 1, -1000, 3, -1000, 5, 6, 7, 8, 9 ], int32)

cout << a(_|_|-1) << "\n";
// array([ 9, 8, 7, 6, 5, -1000, 3, -1000, 1, -1000 ], int32)
```

```python

>>> b = np.arange(20).reshape(5,4)
array([[ 0,  1,  2,  3],
       [ 4,  5,  6,  7],
       [ 8,  9, 10, 11],
       [12, 13, 14, 15],
       [16, 17, 18, 19]])

>> b[2,3]
11

>>> b[0:5, 1]
array([ 1,  5,  9, 13, 17])

>>> b[:, 1]
array([ 1,  5,  9, 13, 17])

>>> b[1:3, 1]
array([5, 9])

>>> b[-1]
array([16, 17, 18, 19])

>>> b[::-1, ::-2]
array([[19, 17],
       [15, 13],
       [11,  9],
       [ 7,  5],
       [ 3,  1]])

>>> c = b[1:-1, 1:-1]
>>> c[:] = -99
>>> b
array([[  0,   1,   2,   3],
       [  4, -99, -99,   7],
       [  8, -99, -99,  11],
       [ 12, -99, -99,  15],
       [ 16,  17,  18,  19]])

```

```c++
    auto b = arange<int>(20).reshape({5,4});

    cout << b.print("%2d") << "\n";
    /*
    array([
        [  0,  1,  2,  3 ],
        [  4,  5,  6,  7 ],
        [  8,  9, 10, 11 ],
        [ 12, 13, 14, 15 ],
        [ 16, 17, 18, 19 ],
    ], int32)
    */

    cout << b(2,3) << "\n";
    // 11

    cout << b(0_s|5, 1) << "\n";
    // array([ 1, 5, 9, 13, 17 ], int32)

    missing _;

    cout << b(_, 1) << "\n";
    // array([ 1, 5, 9, 13, 17 ], int32)

    cout << b(1_s|3, 1) << "\n";
    // array([ 5, 9 ], int32)

    cout << b(-1) << "\n";
    // array([ 16, 17, 18, 19 ], int32)

    cout << b(_|_|-1, _|_|-2).print("%2d") << "\n";
    /*
    array([
        [ 19, 17 ],
        [ 15, 13 ],
        [ 11,  9 ],
        [  7,  5 ],
        [  3,  1 ],
    ], int32)
    */

    auto c = b(1_s|-1, 1_s|-1);

    c = -99;

    cout << b.print("%3d") << "\n";
    /*
    array([
        [   0,   1,   2,   3 ],
        [   4, -99, -99,   7 ],
        [   8, -99, -99,  11 ],
        [  12, -99, -99,  15 ],
        [  16,  17,  18,  19 ],
    ], int32)
    */
```