numcpp
======

A C++ array object that tries to match the expressiveness of numpy.

Why another array library in C++?
=================================

This project is meant to exercise my my template and operator overloading skills.  The goal
is to achive expressions very close to Python+NumPy.



How to get unittest code coverage
=================================

I will make this a scons tool but for now here's a recipe:

    # reset counters
    lcov --base-directory . --directory . --zerocounters -q

    # execute tests
    src/executables/unittests

    # collect info
    lcov --base-directory . --directory . -c -o unittests.info

    # remove data from system code
    lcov --remove unittests.info "/usr*" -o unittests.info

    # remove data from external code
    lcov --remove unittests.info "external/*" -o unittests.info

    # generate html report

    genhtml -o unittest_coverage -t "unittest coverage" --num-spaces 4 unittests.info
