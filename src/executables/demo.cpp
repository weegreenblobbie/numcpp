#include <iostream>
#include <numcpp/numcpp.hpp>

using std::cout;

using namespace numcpp;

int main()
{

    cout << arange<int32>(10, 30, 5) << "\n";

    // array([ 10, 15, 20, 25 ], int32)

    cout << arange<float32>(0, 2, 0.3).print("%.1f") << "\n";

    return 0;

}