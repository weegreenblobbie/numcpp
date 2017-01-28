#include <catch/catch.hpp> // https://github.com/philsquared/Catch


#include <numcpp/core.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::any")
{
    auto a = array<bool>({0,0,0,0});

    CHECK_FALSE( any(a) );

    a(1) = true;

    CHECK( any(a) );

    a.reshape({2,2});

    CHECK( any(a) );

    a(0,1) = false;

    CHECK_FALSE( any(a) );

    a(0, 1) = true;

    missing _;

    a = a(_,1);

    INFO( "a = " << a );
    CHECK( any(a) );
}


TEST_CASE( "numcpp::arange")
{
    auto a = arange<int>(5);

    CHECK( a(0)  == 0 );
    CHECK( a(-1) == 4 );

    a = arange<int>(5,5);

    CHECK( a.size() == 0 );
}

// :mode=c++:noTabs=true: