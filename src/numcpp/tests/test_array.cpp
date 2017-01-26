#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>
#include <numcpp/core.hpp>


using namespace numcpp;


TEST_CASE("numcpp::array basics")
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

    b = arange<float32>(15).reshape(shape);

    CHECK( b.size() == 15 );
    CHECK( b.ndim() == 2 );
    CHECK( b.shape() == shape );

    float32 f = 0.0f;

    for(uint64 i = 0; i < b.shape()[0]; ++i)
    {
        for(uint64 j = 0; j < b.shape()[1]; ++j)
        {
            CHECK( b(i,j) == Approx(f) );

            f += 1.0f;
        }
    }

    CHECK_THROWS( array<float32>({0},   0.0f) );
    CHECK_THROWS( array<float32>({0,5}, 0.0f) );
    CHECK_THROWS( array<float32>({5,0}, 0.0f) );
}


TEST_CASE( "numcpp::array::operator==" )
{
    auto a = array<int>({});
    auto b = array<int>({});
    auto c = a == b;
    auto d = a != b;

    CHECK( c.size() == 0 );
    CHECK( d.size() == 0 );
}


const int & nick(const array<int> & a)
{
    int x = a(0);

    CHECK( x == 1 );

    const int & y = a(5);

    return y;
}


TEST_CASE( "numcpp::array::reshape")
{
    std::vector<uint64> s = {3,4};

    auto a = array<int32>({1,2,3,4,5,6,7,8,9,10,11,12}).reshape(s);

    CHECK( a.ndim() == 2 );
    CHECK( a.shape()[0] == 3 );
    CHECK( a.shape()[1] == 4 );
    CHECK( a.shape() == s );
    CHECK( a(0,0) == 1 );
    CHECK( a(1,1) == 6 );
    CHECK( a(2,2) == 11 );

    CHECK_THROWS( a.reshape({4,4}) );

    s = {1,12};

    a = a.reshape(s);

    CHECK( a.ndim() == 2 );
    CHECK( a.shape()[0] == 1 );
    CHECK( a.shape()[1] == 12 );
    CHECK( a.shape() == s );
    CHECK( a(0,0) == 1 );
    CHECK( a(0,2) == 3 );
    CHECK_THROWS( a(1,1) );
    CHECK_THROWS( a(2,2) );

    s = {12};
    a = a.reshape(s);

    CHECK( a.ndim() == 1 );
    CHECK( a.shape()[0] == 12 );
    CHECK( a.shape() == s );
    CHECK( a(0) == 1 );
    CHECK( a(2) == 3 );
    CHECK_THROWS( a(1,1) );
    CHECK_THROWS( a(2,2) );

    auto y = nick(a);

    CHECK( y == 6 );
}


TEST_CASE( "numcpp::array::slicing 1D")
{
    auto a = arange<int>(10);

    auto b = a(0_s | 10 | 2);

    CHECK( b.ndim() == 1 );
    CHECK( b.size() == 5 );

    CHECK( all(b == array<int>({0,2,4,6,8})) );

    auto c = b(1_s | -1);

    CHECK( c.ndim() == 1 );
    CHECK( c.size() == 3 );
    CHECK( all(c == array<int>({2,4,6})) );

    auto d = a(6_s|3|-2);

    CHECK( d.ndim() == 1 );
    CHECK( d.size() == 2 );
    CHECK( all(d == array<int>({6,4})) );

    missing _;

    auto e = a(_|_|-1);

    CHECK( e.ndim() == 1 );
    CHECK( e.size() == 10 );
    CHECK( all(e == array<int>({9,8,7,6,5,4,3,2,1,0})) );

    e = a(_|_|-2);

    CHECK( e.ndim() == 1 );
    CHECK( e.size() == 5 );
    CHECK( all(e == array<int>({9,7,5,3,1})) );

    auto f = e(1_s | -1 | 2);

    CHECK( f.size() == 2 );
    CHECK( all(f == array<int>({7,3})) );
}


TEST_CASE( "numcpp::array::slicing 2D -> 1D", "[slicing]" )
{
    missing _;

    auto a = array<int>(
        {
            0, 1,  2,  3,
            4, 5,  6,  7,
            8, 9, 10, 11
        }
    ).reshape({3,4});

    auto b = a(2);

    INFO("a = " << a.debug_print() );
    INFO("b = " << b.debug_print() );

    auto gold = array<int>({8,9,10,11});

    auto c = b == gold;

    INFO( "c = " << c.debug_print() );

    INFO( "b = " << b );

    INFO( "c = " << c );

    CHECK( all(b == array<int>({8,9,10,11})) );

    b = a(-2);

    CHECK( all(b == array<int>({4,5,6,7})) );
}


TEST_CASE( "numcpp::array bool operators")
{
    missing _;

    auto a = array<int>({0,1,2,3,4,5,6,7,8,9,10,11}).reshape({3,4});

    auto b = a(2);

    CHECK( all(b == array<int>({8,9,10,11})) );

    b = a(-2);

    CHECK( all(b == array<int>({4,5,6,7})) );

    auto c = array<bool>({0,0,1,0});

    CHECK( any(c) );

    c = array<bool>({0,0,0,0});

    CHECK_FALSE( any(c) );

    c(2) = true;

    CHECK( any(c) );

    bool d = c(2);

    CHECK( d );

    d = c(0);

    CHECK_FALSE( d );

    c = !c;

    CHECK( all(c == array<bool>({1,1,0,1})) );
}


template <class T>
std::ostream & operator<< (std::ostream & out, const std::vector<T> & vec)
{
    out << "[";

    for(const auto & x : vec) out << x << ", ";

    return out << "\b\b ]";
}


TEST_CASE( "numcpp::array::slicing 2D -> 2D", "[slicing]" )
{
    missing _;

    auto a = array<int>(
        {
             0,  1,  2,  3,  4,
             5,  6,  7,  8,  9,
            10, 11, 12, 13, 14,
            15, 16, 17, 18, 19
        }
    ).reshape({4,5});

    SECTION(" slice along rows ")
    {
        auto gold = array<int>(
            {
                 0,  1,  2,  3,  4,
                 5,  6,  7,  8,  9,
                10, 11, 12, 13, 14,
            }
        ).reshape({3,5});

        auto b = a( 0_s | -1);

        CHECK( all(b == gold ) );
    }

    SECTION(" slice along rows ")
    {
        auto b = a( 1_s | -1);

        auto gold = array<int>(
            {
                 5,  6,  7,  8,  9,
                10, 11, 12, 13, 14,
            }
        ).reshape({2,5});

        CHECK( all(b == gold ) );
    }

    SECTION(" slice along columns ")
    {
        auto b = a(_, 1_s | -1);

        auto gold = array<int>(
            {
                 1,  2,  3,
                 6,  7,  8,
                11, 12, 13,
                16, 17, 18
            }
        ).reshape({4,3});

        CHECK( all(b == gold ) );
    }

    SECTION(" slice along both dimensions ")
    {
        auto b = a(1_s | -1, 1_s | -1);

        auto gold = array<int>(
            {
                 6,  7,  8,
                11, 12, 13,
            }
        ).reshape({2,3});

        CHECK( all(b == gold ) );
    }
}


TEST_CASE( "numcpp::array::slicing a slice 2D -> 2D", "[slicing]" )
{
    missing _;

    auto a = arange<int>(100).reshape({10,10});

    auto b = a(1 | _, 1 | _);

    auto shape = b.shape();

    shape = {9,9};

    CHECK( b.shape() == shape );
    CHECK( b(0,0) == 11 );
    CHECK( b(1,1) == 22 );
    CHECK( b(-2,-2) == 88 );
    CHECK( b(-1,-1) == 99 );

    auto c = b( 1_s | -1, 1_s | -1);

    shape = {7,7};

    CHECK( c.shape() == shape );
    CHECK( c(0,0) == 22 );
    CHECK( c(1,1) == 33 );
    CHECK( c(-2,-2) == 77 );
    CHECK( c(-1,-1) == 88 );

    auto d = c( _ | _ | 2, _ | _ | 2);

    shape = {4,4};

    INFO( "c = " << c.print("%2d") );
    INFO( "d = " << d.print("%2d") );

    CHECK( d.shape() == shape );
    CHECK( d(0,0) == 22 );
    CHECK( d(1,1) == 44 );
    CHECK( d(-2,-2) == 66 );
    CHECK( d(-1,-1) == 88 );

}

// :noTabs=true: