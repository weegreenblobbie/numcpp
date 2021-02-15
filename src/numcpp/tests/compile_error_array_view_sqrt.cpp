#include <numcpp/array.hpp>
#include <numcpp/array_view.hpp>

using namespace numcpp;

missing _;

void foo()
{
    const auto a = array<int>({1,2,3,4,5});

    array_view<int> ca = a(0|_);

    ca.sqrt();
}


// :noTabs=true:
