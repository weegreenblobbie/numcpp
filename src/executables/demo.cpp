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
    auto b = arange<int>(20).reshape({5,4});

    cout << b.shape() << "\n";

    cout << b.print("%2d") << "\n";

    cout << b(2,3) << "\n";

    cout << b(0_s|5, 1) << "\n";

    missing _;

    cout << b(_, 1) << "\n";

    cout << b(1_s|3, 1) << "\n";

    cout << b(-1) << "\n";

    cout << b(_|_|-1, _|_|-2).print("%2d") << "\n";

    auto c = b(1_s|-1, 1_s|-1);

    c = -1000;

    cout << b.print("%5d") << "\n";

    cout << ones<int16>({2,3,4}) << "\n";

//~    const int size = 1000;
//~    const int iterations = 1000;

//~    auto a = arange<int>(size*size).reshape({size,size});

//~    // start timer

//~    using namespace numcpp::milliseconds;

//~    auto t0 = now();

//~    for(int i = 0; i < iterations; ++i)
//~    {
//~        a = i;
//~    }

//~    auto t1 = now();

//~    cout << "took " << (t1 - t0) << " ms\n";

    return 0;
}