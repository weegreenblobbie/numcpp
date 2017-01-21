#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::array", "[constructor]" )
{
    auto a = array<int32>({1,2,3,4});

    CHECK( a.size() == 4 );
    CHECK( a.ndim() == 1 );
    CHECK( a.shape() == std::vector<uint64>({4}) );
    CHECK( a(0) == 1 );
    CHECK( a(1) == 2 );
    CHECK( a(2) == 3 );
    CHECK( a(3) == 4 );

    auto b = array<float32>({1}, 0.0f);

    CHECK( b.size() == 1 );
    CHECK( b.ndim() == 1 );
    CHECK( b.shape()[0] == 1 );
    CHECK( b(0) == Approx(0.0f) );

    std::vector<uint64> shape = {3};

    b = array<float32>(shape, 3.14f);

    CHECK( b.size() == 3 );
    CHECK( b.ndim() == 1 );
    CHECK( b.shape() == shape );
    CHECK( b(0) == Approx(3.14f) );
    CHECK( b(1) == Approx(3.14f) );
    CHECK( b(2) == Approx(3.14f) );

    shape = {3, 5};

    b = array<float32>(shape, 1.0f);

    CHECK( b.size() == 15 );
    CHECK( b.ndim() == 2 );
    CHECK( b.shape() == shape );

//~    for(uint64 i = 0; i < a.shape()[0]; ++i)
//~    {
//~        for(uint64 j = 0; j < a.shape()[0]; ++j)
//~        {
//~            CHECK( b(i,j) == Approx(1.0f) );
//~        }
//~    }

    CHECK_THROWS( array<float32>({0},   0.0f) );
    CHECK_THROWS( array<float32>({0,5}, 0.0f) );
    CHECK_THROWS( array<float32>({5,0}, 0.0f) );
}


TEST_CASE( "numcpp::array::operator==" )
{
    auto a = array<int>({});
    auto b = array<int>({});

    CHECK( a == b );
}


const int & nick(const array<int> & a)
{
    int x = a(0);

    CHECK( x == 1 );

    const int & y = a(5);

    return y;
}
//~
//~
//~    TEST_CASE( "numcpp::array::reshape", "[constructor]" )
//~    {
//~        std::vector<uint64> s = {3,4};
//~
//~        auto a = array<int32>({1,2,3,4,5,6,7,8,9,10,11,12}).reshape(s);
//~
//~        CHECK( a.ndim() == 2 );
//~        CHECK( a.shape()[0] == 3 );
//~        CHECK( a.shape()[1] == 4 );
//~        CHECK( a.shape() == s );
//~    //~    CHECK( a(0,0) == 1 );
//~    //~    CHECK( a(1,1) == 6 );
//~    //~    CHECK( a(2,2) == 11 );
//~
//~    //~    CHECK_THROWS( a.reshape({4,4}) );
//~
//~        s = {1,12};
//~
//~        a = a.reshape(s);
//~
//~        CHECK( a.ndim() == 2 );
//~        CHECK( a.shape()[0] == 1 );
//~        CHECK( a.shape()[1] == 12 );
//~        CHECK( a.shape() == s );
//~    //~    CHECK( a(0,0) == 1 );
//~    //~    CHECK( a(0,2) == 3 );
//~    //~    CHECK_THROWS( a(1,1) );
//~    //~    CHECK_THROWS( a(2,2) );
//~
//~        s = {12};
//~        a = a.reshape(s);
//~
//~        CHECK( a.ndim() == 1 );
//~        CHECK( a.shape()[0] == 12 );
//~        CHECK( a.shape() == s );
//~        CHECK( a(0) == 1 );
//~        CHECK( a(2) == 3 );
//~    //~    CHECK_THROWS( a(1,1) );
//~    //~    CHECK_THROWS( a(2,2) );
//~
//~        auto y = nick(a);
//~
//~        CHECK( y == 6 );
//~    }
//~
//~
//~    TEST_CASE( "numcpp::array::slicing 1D", "[slicing]" )
//~    {
//~        auto a = array<int>({0,1,2,3,4,5,6,7,8,9,10,11});
//~
//~        auto b = a(0_s | 10 | 2);
//~
//~        CHECK( b.ndim() == 1 );
//~        CHECK( b.shape()[0] == 5 );
//~        CHECK( b(0) == 0 );
//~        CHECK( b(1) == 2 );
//~        CHECK( b(2) == 4 );
//~        CHECK( b(3) == 6 );
//~        CHECK( b(4) == 8 );
//~
//~        auto c = b(1_s | -1);
//~
//~        CHECK( c.ndim() == 1 );
//~        CHECK( c.shape()[0] == 3 );
//~        CHECK( c(0) == 2 );
//~        CHECK( c(1) == 4 );
//~        CHECK( c(2) == 6 );
//~
//~        auto d = a(6_s|3|-2);
//~
//~        CHECK( d.ndim() == 1 );
//~        CHECK( d.shape()[0] == 2 );
//~        CHECK( d(0) == 6 );
//~        CHECK( d(1) == 4 );
//~    }
//~
//~
//~
//~    TEST_CASE( "numcpp::array::slicing 2D -> 1D", "[slicing]" )
//~    {
//~        missing _;
//~
//~        auto a = array<int>({0,1,2,3,4,5,6,7,8,9,10,11}).reshape({3,4});
//~
//~        auto b = a(2);
//~
//~        CHECK( b.ndim() == 1 );
//~        CHECK( b.shape()[0] == 4 );
//~        CHECK( b(0) == 8 );
//~        CHECK( b(1) == 9 );
//~        CHECK( b(2) == 10 );
//~        CHECK( b(3) == 11 );
//~
//~        b = a(-2);
//~
//~        CHECK( b.ndim() == 1 );
//~        CHECK( b.shape()[0] == 4 );
//~        CHECK( b(0) == 4 );
//~        CHECK( b(1) == 5 );
//~        CHECK( b(2) == 6 );
//~        CHECK( b(3) == 7 );
//~    }