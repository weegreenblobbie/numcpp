#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/testing.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::assert_all_close", "rtol" )
{
    auto a = array<int>({1,2,3});
    auto gold = array<int>({1,2,3}) + 1;

    INFO( "a    = " << a );
    INFO( "gold = " << gold );

    CHECK_NOTHROW( assert_allclose(a, gold, 2) );

    using Catch::Matchers::Contains;

    CHECK_THROWS_WITH(
        assert_allclose(a, gold, 0),
        Contains("arrays are not close, 3 value(s) out of tolerance")
    );

    CHECK_THROWS_WITH(
        assert_allclose(a, gold, 0, "My custom error message"),
        Contains("My custom error message")
    );

    auto b = arange<int>(4).reshape({2,2});

    INFO( "b = " << b );
    INFO( "a.shape = " << a.shape() );
    INFO( "b.shape = " << b.shape() );

    CHECK_THROWS_WITH(
        assert_allclose(a, b, 0),
        Contains("(shapes (3), (2, 2) mismatch)")
    );



}


// :mode=c++:noTabs=true: