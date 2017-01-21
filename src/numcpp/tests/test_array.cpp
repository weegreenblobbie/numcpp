#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::array", "[constructor]" )
{
    CHECK_THROWS( array<int32>({}) );

    auto ai = array<int32>({1,2,3,4});

    CHECK( ai.size() == 4 );
    CHECK( ai.ndim() == 1 );
    CHECK( ai.shape() == std::vector<uint64>({4}) );
    CHECK( ai(0) == 1 );
    CHECK( ai(1) == 2 );
    CHECK( ai(2) == 3 );
    CHECK( ai(3) == 4 );

    auto a = array<float32>({1}, 0.0f);

    CHECK( a.size() == 1 );
    CHECK( a.ndim() == 1 );
    CHECK( a.shape()[0] == 1 );
    CHECK( a(0) == Approx(0.0f) );

    std::vector<uint64> shape = {3};

    a = array<float32>(shape, 3.14f);

    CHECK( a.size() == 3 );
    CHECK( a.ndim() == 1 );
    CHECK( a.shape() == shape );
    CHECK( a(0) == Approx(3.14f) );
    CHECK( a(1) == Approx(3.14f) );
    CHECK( a(2) == Approx(3.14f) );

    shape = {3, 5};

    a = array<float32>(shape, 1.0f);

    CHECK( a.size() == 15 );
    CHECK( a.ndim() == 2 );
    CHECK( a.shape() == shape );

//~    for(uint64 i = 0; i < a.shape()[0]; ++i)
//~    {
//~        for(uint64 j = 0; j < a.shape()[0]; ++j)
//~        {
//~            CHECK( a(i,j) == Approx(1.0f) );
//~        }
//~    }

    CHECK_THROWS( array<float32>({0},   0.0f) );
    CHECK_THROWS( array<float32>({0,5}, 0.0f) );
    CHECK_THROWS( array<float32>({5,0}, 0.0f) );
}


const int & nick(const array<int> & a)
{
    int x = a(0);

    std::cout << "x = " << x << "\n";

    const int & y = a(5);

    return y;
}


TEST_CASE( "numcpp::array::reshape", "[constructor]" )
{
    std::vector<uint64> s = {3,4};

    auto a = array<int32>({1,2,3,4,5,6,7,8,9,10,11,12}).reshape(s);

    WARN("a = " << a.debug_print() );

    CHECK( a.ndim() == 2 );
    CHECK( a.shape()[0] == 3 );
    CHECK( a.shape()[1] == 4 );
    CHECK( a.shape() == s );
//~    CHECK( a(0,0) == 1 );
//~    CHECK( a(1,1) == 6 );
//~    CHECK( a(2,2) == 11 );

//~    CHECK_THROWS( a.reshape({4,4}) );

    s = {1,12};

    a = a.reshape(s);

//~    WARN("a = " << a.debug_print() );

    CHECK( a.ndim() == 2 );
    CHECK( a.shape()[0] == 1 );
    CHECK( a.shape()[1] == 12 );
    CHECK( a.shape() == s );
//~    CHECK( a(0,0) == 1 );
//~    CHECK( a(0,2) == 3 );
//~    CHECK_THROWS( a(1,1) );
//~    CHECK_THROWS( a(2,2) );

    s = {12};
    a = a.reshape(s);

//~    WARN("a = " << a.debug_print() );

    CHECK( a.ndim() == 1 );
    CHECK( a.shape()[0] == 12 );
    CHECK( a.shape() == s );
    CHECK( a(0) == 1 );
    CHECK( a(2) == 3 );
//~    CHECK_THROWS( a(1,1) );
//~    CHECK_THROWS( a(2,2) );

    auto y = nick(a);

    std::cout << "nick(a) = " << y << "\n";
}


TEST_CASE( "numcpp::array::slicing 1D", "[slicing]" )
{
    auto a = array<int>({0,1,2,3,4,5,6,7,8,9,10,11});

    auto b = a(0_s | 10 | 2);

    WARN("b = " << b << "\n");

    CHECK( b.ndim() == 1 );
    CHECK( b.shape()[0] == 5 );
    CHECK( b(0) == 0 );
    CHECK( b(1) == 2 );
    CHECK( b(2) == 4 );
    CHECK( b(3) == 6 );
    CHECK( b(4) == 8 );

    WARN("b = " << b.debug_print() );

    auto c = b(1_s | -1);

    WARN("c = " << c << "\n");

    CHECK( c.ndim() == 1 );
    CHECK( c.shape()[0] == 3 );
    CHECK( c(0) == 2 );
    CHECK( c(1) == 4 );
    CHECK( c(2) == 6 );
}