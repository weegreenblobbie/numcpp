#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>
#include <numcpp/core.hpp>


using namespace numcpp;


TEST_CASE("numcpp::array::operator-()")
{
    auto a = arange<int32>(-3,4);

    auto b = -a;

    INFO( "b = " << b );

    CHECK( all(b == array<int32>({3, 2, 1, 0, -1, -2, -3})) );
}


TEST_CASE("numcpp::array::operator~()")
{
    auto a = arange(-3,4);

    auto b = ~a;

    INFO( "b = " << b );

    CHECK( all(b == array<int32>({2, 1, 0, -1, -2, -3, -4})) );
}


TEST_CASE("numcpp::array::operator!()")
{
    auto a = array<bool>({0,1,1,0});

    auto b = !a;

    CHECK( all(b == array<bool>({1,0,0,1})) );
}




// :noTabs=true: