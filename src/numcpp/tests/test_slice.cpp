#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/slice.hpp>

using namespace numcpp;


TEST_CASE( "numcpp::slice", "[constructor]" )
{
    auto s = slice();

    REQUIRE( s.i0() == 0 );
    REQUIRE( s.i1() == 1 );
    REQUIRE( s.step() == 1 );

    s = slice(16);

    REQUIRE( s.i0() == 16 );
    REQUIRE( s.i1() == 17 );
    REQUIRE( s.step() == 1 );

    s = slice(16, 32);

    REQUIRE( s.i0() == 16 );
    REQUIRE( s.i1() == 32 );
    REQUIRE( s.step() == 1 );

    s = slice(16, 32, 2);

    REQUIRE( s.i0() == 16 );
    REQUIRE( s.i1() == 32 );
    REQUIRE( s.step() == 2 );

    s = slice(-5);

    REQUIRE( s.i0() == -5 );
    REQUIRE( s.i1() == -4 );
    REQUIRE( s.step() == 1 );

    s = slice(6-1,-1,-1);

    REQUIRE( s.i0() == 5 );
    REQUIRE( s.i1() == -1 );
    REQUIRE( s.step() == -1 );
}


TEST_CASE( "numcpp::slice::operators", "[positive slice expressions]" )
{
    slice s = 1_s;

    REQUIRE( s.i0() == 1 );
    REQUIRE( s.i1() == 2 );
    REQUIRE( s.step() == 1 );

    s = 1_s | 5;

    REQUIRE( s.i0() == 1 );
    REQUIRE( s.i1() == 5 );
    REQUIRE( s.step() == 1 );

    s = 2_s | 10 | 3;

    REQUIRE( s.i0() == 2 );
    REQUIRE( s.i1() == 10 );
    REQUIRE( s.step() == 3 );

    s = slice(5) | 10;

    REQUIRE( s.i0() == 5 );
    REQUIRE( s.i1() == 10 );
    REQUIRE( s.step() == 1 );

    s = slice(25) | 50 | 3;

    REQUIRE( s.i0() == 25 );
    REQUIRE( s.i1() == 50 );
    REQUIRE( s.step() == 3 );
}


TEST_CASE( "numcpp::slice::operators 2", "[negative slice expressions]" )
{
    slice s = -5_s;

    REQUIRE( s.i0() == -5 );
    REQUIRE( s.i1() == -4 );
    REQUIRE( s.step() == 1 );

    s = -6_s | 5;

    REQUIRE( s.i0() == -6 );
    REQUIRE( s.i1() == 5 );
    REQUIRE( s.step() == 1 );

    s = -6_s | -1;

    REQUIRE( s.i0() == -6 );
    REQUIRE( s.i1() == -1 );
    REQUIRE( s.step() == 1 );

    s = slice(-6) | -1 | 3;

    REQUIRE( s.i0() == -6 );
    REQUIRE( s.i1() == -1 );
    REQUIRE( s.step() == 3 );
}


TEST_CASE( "numcpp::slice::operators 3", "[common numpy patterns]" )
{
    // a very common things to do in numpy

    slice x0 = 50;

    slice s = x0 + 100;

    REQUIRE( s.i0() == 150 );
    REQUIRE( s.i1() == 151 );
    REQUIRE( s.step() == 1 );

    s = x0 | x0 + 100;

    REQUIRE( s.i0() == 50 );
    REQUIRE( s.i1() == 150 );
    REQUIRE( s.step() == 1 );

    s = x0 | x0 + 100 | 5;

    REQUIRE( s.i0() == 50 );
    REQUIRE( s.i1() == 150 );
    REQUIRE( s.step() == 5 );
}
