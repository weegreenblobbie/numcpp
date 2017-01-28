numcpp
======

A C++ array object that tries to match the expressiveness of numpy.


Why another array library in C++?
=================================

This project is meant to exercise my my template and operator overloading skills.  The goal
is to achive expressions very close to Python & NumPy.

<table>
    <tr>
        <th>Python &amp; NumPy</th>
        <th>C++ &amp; numcpp</th>
    </tr>

    <!---------------------------- ROW 1 ------------------------------------------>
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
>>> a.ndim
2
>>> a.dtype.name
'int64'
>>> a.itemsize
8
>>> a.size
15
         </pre>
    </td>
    <td align="left" valign="top">
    <!--
#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;

using namespace numcpp;

auto a = arange<int64>(15).reshape({3,5});

{
cout
    << a.print("%2d")          << "\n"
    << "shape = " << a.shape() << "\n"
    << "ndim  = " << a.ndim()  << "\n"
    << "size  = " << a.size()  << "\n";
}

array([
    [  0,  1,  2,  3,  4 ],
    [  5,  6,  7,  8,  9 ],
    [ 10, 11, 12, 13, 14 ],
], int64)
shape = (3, 5, )
ndim  = 2
size  = 15

    -->
        <pre lang="c++">
#include &lt;iostream&gt;
#include &lt;numcpp/numcpp.hpp&gt;

using std::cout;

using namespace numcpp;

auto a = arange&lt;int64&gt;(15).reshape({3,5});

cout
    &lt;&lt; a.print(&quot;%2d&quot;)          &lt;&lt; &quot;\n&quot;
    &lt;&lt; &quot;shape = &quot; &lt;&lt; a.shape() &lt;&lt; &quot;\n&quot;
    &lt;&lt; &quot;ndim  = &quot; &lt;&lt; a.ndim()  &lt;&lt; &quot;\n&quot;
    &lt;&lt; &quot;size  = &quot; &lt;&lt; a.size()  &lt;&lt; &quot;\n&quot;;

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
        </pre>
    </td>
    </tr>

    <!---------------------------- ROW 2 ------------------------------------------>
    <tr>
    <td align="left" valign="top">
         <pre lang="python">
>>> c = np.array(
    [ [1,2], [3,4] ], dtype = complex)
>>> c
array([[ 1.+0.j,  2.+0.j],
       [ 3.+0.j,  4.+0.j]])
         </pre>
    </td>
    <td align="left" valign="top">
    <!--
auto c1 = array<complex64>(
    {1,2,3,4}
).reshape({2,2});

auto c2 = array<complex64>(
    { {1,2}, {3,4} }
);

{
cout
    << c1.print("%.1f") << "\n"
    << "\n"
    << c2.print("%.1f") << "\n";
}

/*

array([
    [ 1.0+0.0j, 2.0+0.0j ],
    [ 3.0+0.0j, 4.0+0.0j ],
], complex64)

array([ 1.0+2.0j, 3.0+4.0j ], complex64)

*/
    -->
        <pre lang="c++">
auto c1 = array&lt;complex64&gt;(
    {1,2,3,4}
).reshape({2,2});

auto c2 = array&lt;complex64&gt;(
    { {1,2}, {3,4} }
);

cout
    &lt;&lt; c1.print(&quot;%.1f&quot;) &lt;&lt; &quot;\n&quot;
    &lt;&lt; &quot;\n&quot;
    &lt;&lt; c2.print(&quot;%.1f&quot;) &lt;&lt; &quot;\n&quot;;

/*

array([
    [ 1.0+0.0j, 2.0+0.0j ],
    [ 3.0+0.0j, 4.0+0.0j ],
], complex64)

array([ 1.0+2.0j, 3.0+4.0j ], complex64)

*/
        </pre>
    </td>
    </tr>



    <!---------------------------- ROW 3 ------------------------------------------>
    <tr>
    <td align="left" valign="top">
         <pre lang="python">
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
         </pre>
    </td>
    <td align="left" valign="top">
    <!--
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
    -->
        <pre lang="c++">
cout &lt;&lt; zeros&lt;float32&gt;({3,4}).print(&quot;%.1f&quot;) &lt;&lt; &quot;\n&quot;;
/*
array([
    [ 0.0, 0.0, 0.0, 0.0 ],
    [ 0.0, 0.0, 0.0, 0.0 ],
    [ 0.0, 0.0, 0.0, 0.0 ],
], float32)
*/
// 3D not yet implemented (2017-01-27)
cout &lt;&lt; ones&lt;int16&gt;({2,3}) &lt;&lt; &quot;\n&quot;;
/*
array([
    [ 1, 1, 1 ],
    [ 1, 1, 1 ],
], int16)
*/
// uninitialized array not supported (yet?)
        </pre>
    </td>
    </tr>

</table>


How to build unittests
======================

`scons --test`


How to get unittest code coverage
=================================

`scons --coverage`

Then open the file `coverage/index.html` with a webrowser.
