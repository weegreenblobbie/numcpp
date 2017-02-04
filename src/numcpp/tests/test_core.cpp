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


TEST_CASE( "numcpp::sum(array)")
{
    auto a = arange<int>(5);

    CHECK( a(0)  == 0 );
    CHECK( a(-1) == 4 );

    CHECK( sum(a) == 10 );

    a = arange<int>(10).reshape({2,5});

    CHECK( sum(a) == 45 );

    a = arange<int>(3*5*7).reshape({3,5,7});

    CHECK( sum(a) == 5460 );
}


TEST_CASE( "numcpp::sum(array,axis)")
{
    auto a = arange<int>(5);

    CHECK( sum(a, 0) == 10 );

    CHECK_THROWS( sum(a, 1) );

    a = arange<int>(10).reshape({2,5});

    auto gold = array<int>({5, 7, 9, 11, 13});

    CHECK( all(sum(a,0) == gold) );

    gold = array<int>({10, 35});

    CHECK( all(sum(a, 1) == gold) );

    CHECK_THROWS( sum(a, 2) );

    a = arange<int>(3*5*7).reshape({3,5,7});

    gold = array<int>(
        {
            105, 108, 111, 114, 117, 120, 123,
            126, 129, 132, 135, 138, 141, 144,
            147, 150, 153, 156, 159, 162, 165,
            168, 171, 174, 177, 180, 183, 186,
            189, 192, 195, 198, 201, 204, 207,
        }
    ).reshape({5,7});

    CHECK( all(sum(a,0) == gold) );

    gold = array<int>(
        {
             70,  75,  80,  85,  90,  95, 100,
            245, 250, 255, 260, 265, 270, 275,
            420, 425, 430, 435, 440, 445, 450,
        }
    ).reshape({3,7});

    CHECK( all(sum(a,1) == gold) );

    gold = array<int>(
        {
             21,  70, 119, 168, 217,
            266, 315, 364, 413, 462,
            511, 560, 609, 658, 707,
        }
    ).reshape({3,5});

    CHECK( all(sum(a,2) == gold) );

    CHECK_THROWS( sum(a,3) );
}

// :mode=c++:noTabs=true: