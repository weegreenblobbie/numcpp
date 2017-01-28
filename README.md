numcpp
======

A C++ array object that tries to match the expressiveness of numpy.


Why another array library in C++?
=================================

This project is meant to exercise my my template and operator overloading skills.  The goal
is to achive expressions very close to Python + NumPy.

<table>
    <tr>
        <th>Python + NumPy</th>
        <th>C++ + numcpp</th>
    </tr>

    <tr>
    <td>
         <pre lang="python"><code>
>>> import numpy as np
>>> a = np.arange(15).reshape(3, 5)
>>> a
array([[ 0,  1,  2,  3,  4],
       [ 5,  6,  7,  8,  9],
       [10, 11, 12, 13, 14]])
>>> a.shape
(3, 5)
         </pre></code>
    </td>
    <td>
        <pre lang="c++"><code>
#include <iostream>
using std::cout;
#include <numcpp/numcpp.hpp>
namespace np = numcpp;
auto a = np::arange<int>(15).reshape({3,5});
cout << a.print("%2d") << "\n";
        </pre></code><pre><code>
array([
    [  0,  1,  2,  3,  4 ],
    [  5,  6,  7,  8,  9 ],
    [ 10, 11, 12, 13, 14 ],
], int32)
        </pre></code>
    </td>
</table>


How to build unittests
======================

`scons --test`


How to get unittest code coverage
=================================

`scons --coverage`

Then open the file `coverage/index.html` with a webrowser.
