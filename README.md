numcpp
======

A C++ array object that tries to match the expressiveness of numpy.


Why another array library in C++?
=================================

This project is meant to exercise my my template and operator overloading skills.  The goal
is to achive expressions very close to Python+NumPy.


How to get unittest code coverage
=================================

To produced an html coverage report do:

    scons --coverage
    # ...
    chrome coverage/index.html

