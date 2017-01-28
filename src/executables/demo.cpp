#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;

using namespace numcpp;

int main()
{

    auto a = arange<int>(10);

    cout << a << "\n";

    // array([ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 ], int32)

    cout << a(2) << "\n";

    cout << a(2_s|5) << "\n";

    missing _;

    a(_|6|2) = -1000;

    cout << a << "\n";

    //

    cout << a(_|_|-1) << "\n";


    return 0;

}