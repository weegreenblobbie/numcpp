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

void nick(const array<int> & a)
{
    int x = a(0);
}


TEST_CASE( "numcpp::array::reshape", "[constructor]" )
{
    std::vector<uint64> s = {3,4};

    auto a = array<int32>({1,2,3,4,5,6,7,8,9,10,11,12}).reshape(s);

//~    WARN("a = " << a.debug_print() );

    CHECK( a.ndim() == 2 );
    CHECK( a.shape()[0] == 3 );
    CHECK( a.shape()[1] == 4 );
    CHECK( a.shape() == s );
//~    CHECK( a(0,0) == 1 );
//~    CHECK( a(1,1) == 6 );
//~    CHECK( a(2,2) == 11 );

    CHECK_THROWS( a.reshape({4,4}) );

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

    nick(a);

    std::cout << "a(0) = " << a(0) << "\n";

}





