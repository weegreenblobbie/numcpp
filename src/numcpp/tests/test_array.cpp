#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>

#include <iostream>

using namespace numcpp;


TEST_CASE( "numcpp::array", "[constructor]" )
{
    auto a = array<>();

    REQUIRE( a.size() == 0 );
    REQUIRE( a.ndim() == 0 );
    REQUIRE( a.shape().empty() == true );

    std::vector<uint64> shape = {3};

    a = array<float32>(shape, 3.14f);

    shape = {3, 5};

    a = array<float32>(shape, 0.0f);

    REQUIRE( a.shape() == shape );
    REQUIRE( a.size() == 15 );
    REQUIRE( a.ndim() == 2 );

    a(1,3) = 26;

    float32 f = 0;

    for(int m = 0; m < 3; ++m)
    {
        for(int n = 0; n < 5; ++n)
        {
            a(m, n) = f;
            f += 1.0f;
        }
    }
}
