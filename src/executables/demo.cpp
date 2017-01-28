#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;

using namespace numcpp;

int main()
{
    auto b = arange<int>(20).reshape({5,4});

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

    return 0;

}