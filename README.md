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
    <td align="left" valign="top">
         <pre lang="python">
>>> import numpy as np
>>> a = np.arange(15).reshape(3, 5)
>>> a
array([[ 0,  1,  2,  3,  4],
       [ 5,  6,  7,  8,  9],
       [10, 11, 12, 13, 14]])
>>> a.shape
(3, 5)
         </pre>
    </td>
    <td align="left" valign="top">
    <!--
#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;
using namespace numcpp; // bring in a few output operator<<

namespace np = numcpp;

auto a = np::arange<int>(15).reshape({3,5});

cout << a.print("%2d") << "\n" << "a.shape = " << a.shape() << "\n";

array([
    [  0,  1,  2,  3,  4 ],
    [  5,  6,  7,  8,  9 ],
    [ 10, 11, 12, 13, 14 ],
], int32)
a.shape = (3, 5, )

    -->
        <pre lang="c++">
#include &lt;iostream&gt;
#include &lt;numcpp/numcpp.hpp&gt;

using std::cout;
using namespace numcpp; // bring in a few output operator&lt;&lt;

namespace np = numcpp;

auto a = np::arange&lt;int&gt;(15).reshape({3,5});

cout &lt;&lt; a.print(&quot;%2d&quot;) &lt;&lt; &quot;\n&quot; &lt;&lt; &quot;a.shape = &quot; &lt;&lt; a.shape() &lt;&lt; &quot;\n&quot;;

array([
    [  0,  1,  2,  3,  4 ],
    [  5,  6,  7,  8,  9 ],
    [ 10, 11, 12, 13, 14 ],
], int32)
a.shape = (3, 5, )
        </pre>
    </td>
</table>


How to build unittests
======================

`scons --test`


How to get unittest code coverage
=================================

`scons --coverage`

Then open the file `coverage/index.html` with a webrowser.
