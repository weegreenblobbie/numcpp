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


TEST_CASE( "numcpp::min(array)")
{
    auto a = arange<int>(5, 20);

    CHECK( min(a) == 5 );

    a = arange<int>(20-1, 10-1, -1).reshape({2,5});

    CHECK( min(a) == 10 );

    a = arange<int>(3*5*7 + 10 -1, 10 -1, -1).reshape({3,5,7});

    CHECK( min(a) == 10 );
}


TEST_CASE( "numcpp::min(array,axis)")
{
    auto a = arange<int>(5, 20);

    CHECK( min(a, 0) == 5 );

    CHECK_THROWS( min(a, 1) );

    a = arange<int>(20-1, 10-1, -1).reshape({2,5});

    auto gold = array<int>({14, 13, 12, 11, 10});

    CHECK( all(min(a,0) == gold) );

    gold = array<int>({15, 10});

    CHECK( all(min(a, 1) == gold) );

    CHECK_THROWS( min(a, 2) );

    a = arange<int>(3*5*7 + 10 -1, 10 -1, -1).reshape({3,5,7});

    gold = array<int>(
        {
            44, 43, 42, 41, 40, 39, 38,
            37, 36, 35, 34, 33, 32, 31,
            30, 29, 28, 27, 26, 25, 24,
            23, 22, 21, 20, 19, 18, 17,
            16, 15, 14, 13, 12, 11, 10,
        }
    ).reshape({5,7});

    CHECK( all(min(a,0) == gold) );

    gold = array<int>(
        {
            86,  85,  84,  83,  82,  81,  80,
            51,  50,  49,  48,  47,  46,  45,
            16,  15,  14,  13,  12,  11,  10,
        }
    ).reshape({3,7});

    CHECK( all(min(a,1) == gold) );

    gold = array<int>(
        {
            108, 101,  94,  87,  80,
             73,  66,  59,  52,  45,
             38,  31,  24,  17,  10,
        }
    ).reshape({3,5});

    CHECK( all(min(a,2) == gold) );

    CHECK_THROWS( min(a,3) );
}


TEST_CASE( "numcpp::max(array)")
{
    auto a = arange<int>(5, 20);

    CHECK( max(a) == 19 );

    a = arange<int>(20-1, 10-1, -1).reshape({2,5});

    CHECK( max(a) == 19 );

    a = arange<int>(3*5*7 + 10 -1, 10 -1, -1).reshape({3,5,7});

    CHECK( max(a) == 114 );
}


TEST_CASE( "numcpp::max(array,axis)")
{
    auto a = arange<int>(5, 20);

    CHECK( max(a, 0) == 19 );

    CHECK_THROWS( max(a, 1) );

    a = arange<int>(20-1, 10-1, -1).reshape({2,5});

    auto gold = array<int>({19, 18, 17, 16, 15});

    CHECK( all(max(a,0) == gold) );

    gold = array<int>({19, 14});

    CHECK( all(max(a, 1) == gold) );

    CHECK_THROWS( max(a, 2) );

    a = arange<int>(3*5*7 + 10 -1, 10 -1, -1).reshape({3,5,7});

    gold = array<int>(
        {
            114, 113, 112, 111, 110, 109, 108,
            107, 106, 105, 104, 103, 102, 101,
            100,  99,  98,  97,  96,  95,  94,
             93,  92,  91,  90,  89,  88,  87,
             86,  85,  84,  83,  82,  81,  80,
        }
    ).reshape({5,7});

    CHECK( all(max(a,0) == gold) );

    gold = array<int>(
        {
            114, 113, 112, 111, 110, 109, 108,
             79,  78,  77,  76,  75,  74,  73,
             44,  43,  42,  41,  40,  39,  38,
        }
    ).reshape({3,7});

    CHECK( all(max(a,1) == gold) );

    gold = array<int>(
        {
            114, 107, 100,  93,  86,
             79,  72,  65,  58,  51,
             44,  37,  30,  23,  16,
        }
    ).reshape({3,5});

    CHECK( all(max(a,2) == gold) );

    CHECK_THROWS( max(a,3) );
}


TEST_CASE( "array::operator>" )
{
    auto a = array<int>(
        {
            9, 8, 8, 2, 2,
            3, 5, 6, 0, 2,
        }
    ).reshape({2,5});

    auto b = array<int>(
        {
            0, 2, 5, 5, 7,
            2, 3, 4, 1, 4,
        }
    ).reshape({2,5});

    auto gold = array<bool>(
        {
            1, 1, 1, 0, 0,
            1, 1, 1, 0, 0,
        }
    ).reshape({2,5});

    INFO( "a > b = " << (a > b) );

    CHECK( all(a > b == gold) );
}


// :mode=c++:noTabs=true: