#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/slice.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::slice", "[constructor]" )
{
    auto s = slice(16);

    REQUIRE( s.start() == 16 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == false );
    REQUIRE( s.step_valid()  == false );

    s = slice(16, 32);

    REQUIRE( s.start() == 16 );
    REQUIRE( s.stop()  == 32 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = slice(16, 32, 2);

    REQUIRE( s.start() == 16 );
    REQUIRE( s.stop()  == 32 );
    REQUIRE( s.step()  == 2 );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );

    s = slice(-5);

    REQUIRE( s.start() == -5 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == false );
    REQUIRE( s.step_valid()  == false );

    s = slice(6-1,-1,-1);

    REQUIRE( s.start() == 5 );
    REQUIRE( s.stop()  == -1 );
    REQUIRE( s.step()  == -1 );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators", "[positive slice expressions]" )
{
    slice s = 1_s;

    REQUIRE( s.start() == 1 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == false );
    REQUIRE( s.step_valid()  == false );

    s = 1_s | 5;

    REQUIRE( s.start() == 1 );
    REQUIRE( s.stop()  == 5 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = 2_s | 10 | 3;

    REQUIRE( s.start() == 2 );
    REQUIRE( s.stop()  == 10 );
    REQUIRE( s.step()  == 3 );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );

    s = slice(5) | 10;

    REQUIRE( s.start() == 5 );
    REQUIRE( s.stop()  == 10 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = slice(25) | 50 | 3;

    REQUIRE( s.start() == 25 );
    REQUIRE( s.stop()  == 50 );
    REQUIRE( s.step()  == 3 );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 2", "[negative slice expressions]" )
{
    slice s = -5_s;

    REQUIRE( s.start() == -5 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == false );
    REQUIRE( s.step_valid()  == false );

    s = -6_s | 5;

    REQUIRE( s.start() == -6 );
    REQUIRE( s.stop()  == 5 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = -6_s | -1;

    REQUIRE( s.start() == -6 );
    REQUIRE( s.stop()  == -1 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = slice(-6) | -1 | 3;

    REQUIRE( s.start() == -6 );
    REQUIRE( s.stop()  == -1 );
    REQUIRE( s.step()  == 3  );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 3", "[common numpy patterns]" )
{
    // a very common things to do in numpy

    slice x0 = 50;

    slice s = x0 + 100;

    REQUIRE( s.start() == 150 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == false );
    REQUIRE( s.step_valid()  == false );

    s = x0 | x0 + 100;

    REQUIRE( s.start() == 50 );
    REQUIRE( s.stop()  == 150 );
    REQUIRE( s.start_valid() == true  );
    REQUIRE( s.stop_valid()  == true  );
    REQUIRE( s.step_valid()  == false );

    s = x0 | x0 + 100 | 5;

    REQUIRE( s.start() == 50  );
    REQUIRE( s.stop()  == 150 );
    REQUIRE( s.step()  == 5   );
    REQUIRE( s.start_valid() == true );
    REQUIRE( s.stop_valid()  == true );
    REQUIRE( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 4", "[using missing]" )
{
    missing _;

    SECTION(" 5: ")
    {
        slice s = 5 | _;

        REQUIRE( s.start() == 5  );
        REQUIRE( s.start_valid() == true  );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == false );
    }

    SECTION(" -5: ")
    {
        slice s = -5 | _;

        REQUIRE( s.start() == -5  );
        REQUIRE( s.start_valid() == true  );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == false );
    }

    SECTION(" :5 ")
    {
        slice s = _ | 5;

        REQUIRE( s.stop() == 5  );
        REQUIRE( s.start_valid() == false );
        REQUIRE( s.stop_valid()  == true  );
        REQUIRE( s.step_valid()  == false );
    }

    SECTION(" :-5 ")
    {
        slice s = _ | -5;

        REQUIRE( s.stop() == -5  );
        REQUIRE( s.start_valid() == false );
        REQUIRE( s.stop_valid()  == true  );
        REQUIRE( s.step_valid()  == false );
    }

    SECTION(" ::2 ")
    {
        slice s = _ | _ | 2;

        REQUIRE( s.step() == 2  );
        REQUIRE( s.start_valid() == false );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == true  );
    }

    SECTION(" ::-2 ")
    {
        slice s = _ | _ | -2;

        REQUIRE( s.step() == -2  );
        REQUIRE( s.start_valid() == false );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == true  );
    }

    SECTION(" 6::2 ")
    {
        slice s = 6 | _ | 2;

        REQUIRE( s.start() == 6 );
        REQUIRE( s.step() == 2 );
        REQUIRE( s.start_valid() == true );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == true  );
    }

    SECTION(" -6::-2 ")
    {
        slice s = -6 | _ | -2;

        REQUIRE( s.start() == -6 );
        REQUIRE( s.step() == -2 );
        REQUIRE( s.start_valid() == true );
        REQUIRE( s.stop_valid()  == false );
        REQUIRE( s.step_valid()  == true  );
    }
}

// :mode=c++:noTabs=true: