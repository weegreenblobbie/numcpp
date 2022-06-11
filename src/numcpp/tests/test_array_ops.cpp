#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/array.hpp>
#include <numcpp/core.hpp>
#include <numcpp/testing.hpp>


using namespace numcpp;


TEST_CASE("numcpp::array::operator-()")
{
    auto a = arange<int32>(-3,4);

    auto b = -a;

    INFO( "b = " << b );

    CHECK( all(b == array<int32>({3, 2, 1, 0, -1, -2, -3})) );
}


TEST_CASE("numcpp::array::operator~()")
{
    auto a = arange(-3,4);

    auto b = ~a;

    INFO( "b = " << b );

    CHECK( all(b == array<int32>({2, 1, 0, -1, -2, -3, -4})) );
}


TEST_CASE("numcpp::array::operator!()")
{
    auto a = array<bool>({0,1,1,0});

    auto b = !a;

    CHECK( all(b == array<bool>({1,0,0,1})) );
}


TEST_CASE("numcpp::array::operator+=()")
{
    missing _;

    auto a = zeros<int>({3,3,3});

    a(_,_,0) += 1;
    a(_,1,_) += 2;
    a(2,_,_) += 3;

    auto gold = array<int>(
    {
        1, 0, 0,
        3, 2, 2,
        1, 0, 0,

        1, 0, 0,
        3, 2, 2,
        1, 0, 0,

        4, 3, 3,
        6, 5, 5,
        4, 3, 3,
    }
    ).reshape({3,3,3});

    INFO( "a = " << a );

    CHECK( all(a == gold) );

    auto b = a * 2;
    auto c = 2 * a;

    gold = array<int>(
    {
         2,  0,  0,
         6,  4,  4,
         2,  0,  0,

         2,  0,  0,
         6,  4,  4,
         2,  0,  0,

         8,  6,  6,
        12, 10, 10,
         8,  6,  6,
    }
    ).reshape({3,3,3});

    CHECK( all(b == gold) );
    CHECK( all(c == gold) );
}


TEST_CASE("numcpp::array::operator+=() + slice")
{
    missing _;

    auto aa = zeros<int>({3,3,4});

    auto a = aa(_,_,_|_|2);

    a(_,_,0) += 1;
    a(_,1,_) += 2;
    a(2,_,_) += 3;

    auto gold = array<int>(
    {
        1, 0,
        3, 2,
        1, 0,

        1, 0,
        3, 2,
        1, 0,

        4, 3,
        6, 5,
        4, 3,
    }
    ).reshape({3,3,2});

    INFO( "a = " << a );

    CHECK( all(a == gold) );

    auto b = a * 2;
    auto c = 2 * a;

    gold = array<int>(
    {
         2,  0,
         6,  4,
         2,  0,

         2,  0,
         6,  4,
         2,  0,

         8,  6,
        12, 10,
         8,  6,
    }
    ).reshape({3,3,2});

    CHECK( all(b == gold) );
    CHECK( all(c == gold) );

    auto d = b + c;

    CHECK( all(d == 2 * b) );
    CHECK( all(d == 2 * c) );
    CHECK( all(d / 2 == c) );

    d -= b;

    CHECK( all(d == c) );
}


TEST_CASE("numcpp::array::abs()")
{
    auto a = arange<int>(-5, 5);

    auto gold = array<int>({5,4,3,2,1,0,1,2,3,4});

    a.abs();

    INFO( "a = " << a );

    CHECK( all(a == gold) );

    auto b = arange<float32>(-5, 5);

    b.abs();

    auto gf = gold.astype<float32>();

    INFO( "b = " << b.print("%.1f") );

    CHECK_NOTHROW( assert_allclose(b, gf, 1e-7f) );

    auto c = arange<int>(9).reshape({3,3}).astype<float32>();
    gf = arange<float32>(9).reshape({3,3});

    INFO( "c = " << c.print("%.1f") );

    CHECK_NOTHROW( assert_allclose(c, gf, 1e-7f) );

    auto d = arange<int>(27).reshape({3,3,3}).astype<float32>();
    gf = arange<float32>(27).reshape({3,3,3});

    INFO( "d = " << d.print("%.1f") );
    INFO( "gf = " << gf.print("%.1f") );

    CHECK_NOTHROW( assert_allclose(d, gf, 1e-7f) );
}


TEST_CASE("numcpp::array<complex64>::abs()")
{
    auto a = array<complex64>({
        { 5.0f, -5.0f},
        { 4.0f, -4.0f},
        { 3.0f, -3.0f},
        { 2.0f, -2.0f},
        { 1.0f, -1.0f},
        { 0.0f,  0.0f},
        {-1.0f,  1.0f},
        {-2.0f,  2.0f},
        {-3.0f,  3.0f},
        {-4.0f,  4.0f},
        {-5.0f,  5.0f},
    });

    const auto gold = array<float32>({
        7.071068, 5.656854, 4.242640, 2.828427, 1.414214, 0.000000,
        1.414214, 2.828427, 4.242640, 5.656854, 7.071068,
    });

    auto data = abs(a);

    INFO( "gold = " << gold.print("%f") );
    INFO( "data = " << data.print("%f") );

    CHECK_NOTHROW( assert_allclose(data, gold, 1e-6f) );
}


// :noTabs=true: