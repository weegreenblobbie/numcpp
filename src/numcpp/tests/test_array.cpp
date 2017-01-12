#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>

#include <iostream>

using namespace numcpp;


TEST_CASE( "numcpp::array", "[constructor]" )
{
    auto a = array<>();

    REQUIRE( a.size() == 0 );

    a = array<float32>({3, 5}, 3.13f);

    REQUIRE( a.size() == 15 );

    float32 f = 0;

    for(int m = 0; m < 3; ++m)
    {
        for(int n = 0; n < 5; ++n)
        {
            a(m, n) = f;
            f += 1.0f;
        }
    }

    f = 0;

    for(int m = 0; m < 3; ++m)
    {
        for(int n = 0; n < 5; ++n)
        {
            std::cout << "a[" << m << "," << n << "] = " << a(m,n) << "\n";

            REQUIRE( Approx(f) == a(m, n) );
            f += 1.0f;
        }
    }

}