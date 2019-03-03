#include <iostream>
#include <numcpp/numcpp.hpp>
#include <chrono>

using std::cout;


namespace numcpp
{
    auto now()
    {
        return std::chrono::high_resolution_clock().now();
    }

    namespace milliseconds
    {
        auto operator-(
            const std::chrono::time_point<std::chrono::high_resolution_clock> & lhs,
            const std::chrono::time_point<std::chrono::high_resolution_clock> & rhs)
        {
            using std::chrono::operator-;

            return std::chrono::duration_cast<std::chrono::milliseconds>(lhs - rhs).count();
        }
    }
}

using namespace numcpp;



int main()
{
    const int size = 1000;
    const int iterations = 1000;

    auto a = arange<int>(size*size).reshape({size,size});

    // start timer

    using namespace numcpp::milliseconds;

    auto t0 = now();

    for(int i = 0; i < iterations; ++i)
    {
        a += i;
    }

    auto t1 = now();

    cout << "took " << (t1 - t0) << " ms\n";

    return 0;
}