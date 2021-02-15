#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>
#include <numcpp/core.hpp>

using namespace numcpp;

namespace numcpp
{
// Instantiate array of many types to get code coverage.

template class array<bool>;
template class array<int8>;
template class array<int16>;
template class array<int32>;
template class array<int64>;
template class array<uint8>;
template class array<uint16>;
template class array<uint32>;
template class array<uint64>;
template class array<float>;
template class array<double>;
//~template class array<complex64>;
//~template class array<complex128>;

template class array_view<bool>;
template class array_view<int8>;
template class array_view<int16>;
template class array_view<int32>;
template class array_view<int64>;
template class array_view<uint8>;
template class array_view<uint16>;
template class array_view<uint32>;
template class array_view<uint64>;
template class array_view<float>;
template class array_view<double>;
//~template class array<complex64>;
//~template class array<complex128>;





}



TEST_CASE("numcpp::array basics")
{


    auto a = array<int32>({1,2,3,4});

    shape_t shape = {4};

    CHECK( a.size() == 4 );
    CHECK( a.ndim() == 1 );
    CHECK( a.shape() == shape );
    CHECK( a(0) == 1 );
    CHECK( a(1) == 2 );
    CHECK( a(2) == 3 );
    CHECK( a(3) == 4 );

    shape = {1};

    auto b = array<float32>(shape, 0.0f);

    CHECK( b.size() == 1 );
    CHECK( b.ndim() == 1 );
    CHECK( b.shape() == shape );
    CHECK( b(0) == Approx(0.0f) );

    shape = {3};

    b = array<float32>(shape, 3.14f);

    CHECK( b.size() == 3 );
    CHECK( b.ndim() == 1 );
    CHECK( b.shape() == shape );
    CHECK( b(0) == Approx(3.14f) );
    CHECK( b(1) == Approx(3.14f) );
    CHECK( b(2) == Approx(3.14f) );

    shape = {3, 5};

    b = arange<float32>(15).reshape(shape);

    INFO( "b = " << b.print("%.2f") );
    CHECK( b.size() == 15 );
    CHECK( b.ndim() == 2 );
    CHECK( b.shape() == shape );

    float32 f = 0.0f;

    for(std::size_t m = 0; m < b.shape()[0]; ++m)
    {
        for(std::size_t n = 0; n < b.shape()[1]; ++n)
        {
            CHECK( b(m,n) == Approx(f) );

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


TEST_CASE( "numcpp::array::reshape")
{
    shape_t s = {3,4};

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

    CHECK( all(b == array<int>({8,9,10,11})) );

    b = a(-2);

    CHECK( all(b == array<int>({4,5,6,7})) );
}

TEST_CASE( "numcpp::array bool operators")
{
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


TEST_CASE( "numcpp::array::slicing 2D -> 2D", "[slicing]" )
{
    missing _;

    auto a = array<int>(
        {
             0,  1,  2,  3,  4,
             5,  6,  7,  8,  9,
            10, 11, 12, 13, 14,
            15, 16, 17, 18, 19,
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

        CHECK( all(b == gold) );

        auto c = b(_);

        CHECK( all(c == gold) );
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
                16, 17, 18,
            }
        ).reshape({4,3});

        INFO( "b = " << b.debug_print() );
        INFO( "b = " << b.print("%2d") );

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

    CHECK( d.shape() == shape );
    CHECK( d(0,0) == 22 );
    CHECK( d(1,1) == 44 );
    CHECK( d(-2,-2) == 66 );
    CHECK( d(-1,-1) == 88 );

    auto e = d(_|_|-2, _|_|-2);

    INFO( "d = " << d );
    INFO( "e = " << e );

    shape = {2,2};

    CHECK( e.shape() == shape );
    CHECK( all(e == array<int>({88,84,48,44}).reshape(shape)) );
}


TEST_CASE( "numcpp::array 1D element access" )
{
    auto a = arange<int>(10);

    a(1) = 99;

    CHECK( all(a == array<int>({0,99,2,3,4,5,6,7,8,9})) );

    a(-2) = 99;

    CHECK( all(a == array<int>({0,99,2,3,4,5,6,7,99,9})) );

    missing _;

    auto b = a(1|_|2);

    CHECK( all(b == array<int>({99,3,5,7,9})) );

    b(3) = 99;

    CHECK( all(b == array<int>({99,3,5,99,9})) );

    b = b(_|_|-1);

    b(1) = 88;

    CHECK( all(b == array<int>({9,88,5,3,99})) );

    b = b(_|_|2);

    b(1) = 77;

    CHECK( all(b == array<int>({9,77,99})) );

    a = arange<int>(10);

    a(_|_|2) = 99;

    CHECK( all(a == array<int>({99,1,99,3,99,5,99,7,99,9})) );

    a(_|_|-2) = 88;

    CHECK( all(a == array<int>({99,88,99,88,99,88,99,88,99,88})) );
}


TEST_CASE( "numcpp::array truth value throws" )
{
    auto a = array<bool>({1,0,1,0});

    using Catch::Matchers::Contains;
    const auto single_val_error = "converting to single value from array!";
    const auto ambiguous_error =
        "The truth value of an array with more than one "
        "element is ambiguous. Use numcpp::any() or numcpp::all().";

    CHECK_THROWS_WITH(bool b = a, Contains(ambiguous_error));

    auto b = array<int>({1,0,1,0});

    CHECK_THROWS_WITH(int c = b, Contains(single_val_error));
    CHECK_THROWS_WITH(const int & c = b, Contains(single_val_error));

    // Conversion to bool from array with size > 1 is an error.

    auto d = array<bool>({0, 0});

    CHECK_THROWS_WITH(bool e = d, Contains(ambiguous_error));

    SECTION(" convertion to bool from array_view<R> with size > 1 is an error ")
    {
        using Catch::Matchers::Contains;

        // Construct a array_view<bool>.
        const auto f = array<bool>({0, 1});
        missing _;
        auto g = f(_);

        CHECK_THROWS_WITH(bool h = g, Contains(ambiguous_error));

        // Convertion to single value should work.
        bool i = g(0);
        bool j = g(1);
        CHECK_FALSE( i );
        CHECK( j );

        // Construct a array_view<int>.
        const auto k = array<int>({26, 42});
        auto l = k(_);

        CHECK_THROWS_WITH(bool m = l, Contains(single_val_error));

        // Convertion to single value should work.
        int n = l(0);
        int o = l(1);
        CHECK( n == 26 );
        CHECK( o == 42 );
    }
}


TEST_CASE( "numcpp::array::operator!" )
{
    missing _;

    auto a = array<bool>(
        {
            0, 1, 1, 1, 1,
            1, 0, 1, 1, 1,
            1, 1, 0, 1, 0,
            1, 1, 1, 0, 1,
        }
    ).reshape({4,5});

    auto gold = array<bool>(
        {
            1, 0, 0, 0, 0,
            0, 1, 0, 0, 0,
            0, 0, 1, 0, 1,
            0, 0, 0, 1, 0,
        }
    ).reshape({4,5});

    CHECK( all(gold == !a) );

    a = a(1_s|-1, _|_|2);

    gold = array<bool>(
        {
            0, 0, 0,
            0, 1, 1,
        }
    ).reshape({2,3});

    CHECK( all(gold == !a) );

    a = array<bool>({0,1,0,0,1,1,0,0,0});

    a = a(_|_|2);

    gold = array<bool>({1,1,0,1,1});

    CHECK( all(gold == !a) );


    SECTION( "!a with 2 strides, sliced to a single row" )
    {
        a = array<bool>(
            {
                0, 1, 1, 1, 1,
                1, 0, 1, 1, 1,
                1, 1, 0, 1, 0,
                1, 1, 1, 0, 1,
            }
        ).reshape({4,5});

        auto b = a(_|_|2, _|_|2);

        gold = array<bool>(
            {
                0, 1, 1,
                1, 0, 0,
            }
        ).reshape({2,3});

        CHECK( all(b == gold) );

        INFO( "b = " << b );

        b = b(1);

        INFO( "b(1) = " << b );

        gold = array<bool>({1,0,0});

        CHECK( all(b == gold) );

        INFO( "!b(1) = " << !b );

        gold = array<bool>(
            {
                0, 1, 1,
            }
        ).reshape({3});

        CHECK( all(gold == !b) );
    }
}


TEST_CASE( "numcpp::array 2D element access" )
{
    missing _;

    auto a = arange<int>(20).reshape({4,5});

    a(1) = 99;
    a(_,1) = 88;

    auto gold = array<int>(
        {
              0, 88,  2,  3,  4,
             99, 88, 99, 99, 99,
             10, 88, 12, 13, 14,
             15, 88, 17, 18, 19,
        }
    ).reshape({4,5});

    CHECK( all(a == gold) );

    a(2, 2_s | 4) = 77;

    gold = array<int>(
        {
              0, 88,  2,  3,  4,
             99, 88, 99, 99, 99,
             10, 88, 77, 77, 14,
             15, 88, 17, 18, 19,
        }
    ).reshape({4,5});

    CHECK( all(a == gold) );

    auto mask = a(1_s|-1, 1_s|-1) == 99;

    auto gg = array<bool>(
        {
            0, 1, 1,
            0, 0, 0,
        }
    ).reshape({2,3});

    CHECK( all(mask == gg) );

    a(1 | _, 3) = 22;

    gold = array<int>(
        {
              0, 88,  2,  3,  4,
             99, 88, 99, 22, 99,
             10, 88, 77, 22, 14,
             15, 88, 17, 22, 19,
        }
    ).reshape({4,5});

    CHECK( all(a == gold) );

    a(2, _|_|2) = 44;

    gold = array<int>(
        {
              0, 88,  2,  3,  4,
             99, 88, 99, 22, 99,
             44, 88, 44, 22, 44,
             15, 88, 17, 22, 19,
        }
    ).reshape({4,5});

    INFO( "a = " << a.print("%2d") );
    CHECK( all(a == gold) );

    auto b = a == 88;

    auto g = array<bool>(
        {
             0, 1, 0, 0, 0,
             0, 1, 0, 0, 0,
             0, 1, 0, 0, 0,
             0, 1, 0, 0, 0,
        }
    ).reshape({4,5});

    INFO( "b = " << b );
    CHECK( all(b == g) );

    a = arange<int>(16).reshape({4,4});

    a(_|_|2, _|_|-2) = 99;

    gold = array<int>(
        {
            0, 99,  2, 99,
            4,  5,  6,  7,
            8, 99, 10, 99,
           12, 13, 14, 15,
        }
    ).reshape({4,4});

    CHECK( all(a == gold) );

    a = 300;

    gold = array<int>(
        {
           300, 300, 300, 300,
           300, 300, 300, 300,
           300, 300, 300, 300,
           300, 300, 300, 300,
        }
    ).reshape({4,4});

    CHECK( all(a == gold) );

    a(1_s|3,1_s|3) = 0;

    gold = array<int>(
        {
           300, 300, 300, 300,
           300,   0,   0, 300,
           300,   0,   0, 300,
           300, 300, 300, 300,
        }
    ).reshape({4,4});

    CHECK( all(a == gold) );

    // deep copy
    auto c = array<int>(a);

    c(1_s|3,1_s|3) = 300;

    CHECK( all(a == gold) );

    gold = array<int>(
        {
           300, 300, 300, 300,
           300, 300, 300, 300,
           300, 300, 300, 300,
           300, 300, 300, 300,
        }
    ).reshape({4,4});

    CHECK( all(c == gold) );

    a = arange<int>(2*3*5).reshape({2,3,5});

    a(_,_,-2) = 300;

    gold = array<int>(
        {
             0,   1,   2, 300,   4,
             5,   6,   7, 300,   9,
            10,  11,  12, 300,  14,

            15,  16,  17, 300,  19,
            20,  21,  22, 300,  24,
            25,  26,  27, 300,  29,
        }
    ).reshape({2,3,5});

    CHECK( all(a == gold) );

    a = 26;

    gold = 26 * ones<int>({2,3,5});

    CHECK( all(a == gold) );

    a(_,_|-1,_) = 0;

    gold = array<int>(
        {
             0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,
            26, 26, 26, 26, 26,

             0,  0,  0,  0,  0,
             0,  0,  0,  0,  0,
            26, 26, 26, 26, 26,
        }
    ).reshape({2,3,5});

    CHECK( all(a == gold) );
}


TEST_CASE( "numcpp::array 3D element access" )
{
    missing _;

    auto a = arange<int>(3*5*7).reshape({3,5,7});

    INFO( "a = " << a.print("%3d") );

    CHECK( a(0,1,2) == 9  );
    CHECK( a(1,2,3) == 52 );
    CHECK( a(2,3,4) == 95 );

    auto b = a(0,_|3,_|3);

    CHECK_THROWS( b(0,0,0) );

    auto gold = array<int>(
        {
             0,  1,  2,
             7,  8,  9,
            14, 15, 16,
        }
    ).reshape({3,3});

    CHECK( all( b == gold) );

    b = a(_|3, 0, _|3);

    gold = array<int>(
        {
             0,  1,  2,
            35, 36, 37,
            70, 71, 72,
        }
    ).reshape({3,3});

    CHECK( all( b == gold) );

    b = a(_|3, _|3, 0);

    gold = array<int>(
        {
             0,  7, 14,
            35, 42, 49,
            70, 77, 84,
        }
    ).reshape({3,3});

    CHECK( all( b == gold) );

    b = a(1);

    gold = array<int>(
        {
            35, 36, 37, 38, 39, 40, 41,
            42, 43, 44, 45, 46, 47, 48,
            49, 50, 51, 52, 53, 54, 55,
            56, 57, 58, 59, 60, 61, 62,
            63, 64, 65, 66, 67, 68, 69,
        }
    ).reshape({5,7});

    CHECK( all( b == gold) );

    b = a(2, 0_s|2);

    gold = array<int>(
        {
            70, 71, 72, 73, 74, 75, 76,
            77, 78, 79, 80, 81, 82, 83,
        }
    ).reshape({2,7});

    CHECK( all( b == gold) );

    b = a(2, 0_s|2, 2_s|2+3);

    gold = array<int>(
        {
            72, 73, 74,
            79, 80, 81,
        }
    ).reshape({2,3});

    CHECK( all( b == gold) );

    b = a(1, 3, 2_s|2+3);

    gold = array<int>({58, 59, 60});

    CHECK( all( b == gold) );

    b = a(1, 1_s|1+2, 3);

    gold = array<int>({45, 52});

    CHECK( all( b == gold) );
}


TEST_CASE( "numcpp::array 3D element access with strides" )
{
    missing _;

    auto a = arange<int>(3*5*7).reshape({3,5,7});

    a = a(_|_|-1,_|_|2,_|_|-3);

    INFO( "a = " << a.print("%3d") );

    auto gold = array<int>(
        {
             76,  73,  70,
             90,  87,  84,
            104, 101,  98,

             41,  38,  35,
             55,  52,  49,
             69,  66,  63,

              6,   3,   0,
             20,  17,  14,
             34,  31,  28,
        }
    ).reshape({3,3,3});

    CHECK( all(a == gold) );

    auto b = a(_|2, _|_|2, -1);

    gold = array<int>(
        {
            70, 98,
            35, 63,
        }
    ).reshape({2,2});

    INFO( "b = " << b );

    CHECK( all(b == gold) );
}


TEST_CASE( "numcpp::array::transpose" )
{
    missing _;

    auto a = arange<int>(15);

    auto gold = arange<int>(15);

    CHECK( all(a.T() == gold) );

    auto b = a(_|_|2);

    b.reshape({2,4});

    INFO( "b = " << b.print("%2d") );

    gold = array<int>(
        {
            0,  2,  4,  6,
            8, 10, 12, 14,
        }
    ).reshape({2,4});

    CHECK( all(b == gold) );

    a.reshape({3,5});

    gold = array<int>(
        {
            0, 5, 10,
            1, 6, 11,
            2, 7, 12,
            3, 8, 13,
            4, 9, 14,
        }
    ).reshape({5,3});

    CHECK( all(a.T() == gold) );

    gold = array<int>(
        {
             0,  5, 10,  1,  6,
            11,  2,  7, 12,  3,
             8, 13,  4,  9, 14,
        }
    ).reshape({3, 5});

    CHECK( all(a.T().reshape({3,5}) == gold) );

    a = a(_, _|_|2);

    gold = array<int>(
        {
            0, 5, 10,
            2, 7, 12,
            4, 9, 14,
        }
    ).reshape({3,3});

    CHECK( all(a.T() == gold) );

    a = arange<int>(3*5*7).reshape({3,5,7});

    gold = array<int>(
        {
             0,  35,  70,
             7,  42,  77,
            14,  49,  84,
            21,  56,  91,
            28,  63,  98,

             1,  36,  71,
             8,  43,  78,
            15,  50,  85,
            22,  57,  92,
            29,  64,  99,

             2,  37,  72,
             9,  44,  79,
            16,  51,  86,
            23,  58,  93,
            30,  65, 100,

             3,  38,  73,
            10,  45,  80,
            17,  52,  87,
            24,  59,  94,
            31,  66, 101,

             4,  39,  74,
            11,  46,  81,
            18,  53,  88,
            25,  60,  95,
            32,  67, 102,

             5,  40,  75,
            12,  47,  82,
            19,  54,  89,
            26,  61,  96,
            33,  68, 103,

             6,  41,  76,
            13,  48,  83,
            20,  55,  90,
            27,  62,  97,
            34,  69, 104,
        }
    ).reshape({7,5,3});

    CHECK( all(a.T() == gold) );

    b = a.T();

    gold = arange<int>(3*5*7).reshape({3,5,7});

    CHECK( all(b.T() == gold) );

    b = a(_,3|_, _|_|-2);

    gold = array<int>(
        {
            27,  62,  97,
            34,  69, 104,

            25,  60,  95,
            32,  67, 102,

            23,  58,  93,
            30,  65, 100,

            21,  56,  91,
            28,  63,  98,
        }
    ).reshape({4,2,3});

    CHECK( all(b.T() == gold) );

    auto c = b.T().reshape({2,12});

    gold = array<int>(
        {
            27,  62,  97,  34,  69, 104,  25,  60,  95,  32,  67, 102,
            23,  58,  93,  30,  65, 100,  21,  56,  91,  28,  63,  98,
        }
    ).reshape({2,12});
}


// :noTabs=true:
