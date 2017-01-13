#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>

#include <iostream>

using namespace numcpp;


TEST_CASE( "numcpp::array", "[constructor]" )
{
    REQUIRE_THROWS( array<int32>({}) );

    auto ai = array<int32>({1,2,3,4});

    REQUIRE( ai.size() == 4 );
    REQUIRE( ai.ndim() == 1 );
    REQUIRE( ai.shape() == std::vector<uint64>({4}) );
    REQUIRE( ai(0) == 1 );
    REQUIRE( ai(1) == 2 );
    REQUIRE( ai(2) == 3 );
    REQUIRE( ai(3) == 4 );

    auto a = array<float32>({1}, 0.0f);

    REQUIRE( a.size() == 1 );
    REQUIRE( a.ndim() == 1 );
    REQUIRE( a.shape()[0] == 1 );
    REQUIRE( a(0) == Approx(0.0f) );

    std::vector<uint64> shape = {3};

    a = array<float32>(shape, 3.14f);

    REQUIRE( a.size() == 3 );
    REQUIRE( a.ndim() == 1 );
    REQUIRE( a.shape() == shape );
    REQUIRE( a(0) == Approx(3.14f) );
    REQUIRE( a(1) == Approx(3.14f) );
    REQUIRE( a(2) == Approx(3.14f) );

    shape = {3, 5};

    a = array<float32>(shape, 1.0f);

    REQUIRE( a.size() == 15 );
    REQUIRE( a.ndim() == 2 );
    REQUIRE( a.shape() == shape );

    for(uint64 i = 0; i < a.shape()[0]; ++i)
    {
        for(uint64 j = 0; j < a.shape()[0]; ++j)
        {
            REQUIRE( a(i,j) == Approx(1.0f) );
        }
    }

    REQUIRE_THROWS( array<float32>({0},   0.0f) );
    REQUIRE_THROWS( array<float32>({0,5}, 0.0f) );
    REQUIRE_THROWS( array<float32>({5,0}, 0.0f) );
}
