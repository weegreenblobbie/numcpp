#include <catch/catch.hpp> // https://github.com/philsquared/Catch

#include <numcpp/slice.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::slice", "[constructor]" )
{
    auto s = slice(16);

    INFO( "s = " << s );

    CHECK( s.start() == 16 );
    CHECK( s.stop() == 17 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == false );

    s = slice(16, 32);

    INFO( "s = " << s );

    CHECK( s.start() == 16 );
    CHECK( s.stop()  == 32 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );


    s = slice(16, 32, 2);

    CHECK( s.start() == 16 );
    CHECK( s.stop()  == 32 );
    CHECK( s.step()  == 2 );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );


    s = slice(-5);

    CHECK( s.start() == -5 );
    CHECK( s.stop() == -4 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );


    s = slice(6-1,-1,-1);

    CHECK( s.start() == 5 );
    CHECK( s.stop()  == -1 );
    CHECK( s.step()  == -1 );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );


    s = slice(-16);

    CHECK( s.start() == -16 );
    CHECK( s.stop() == -15 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == false );


    s = slice(-16, -32);

    CHECK( s.start() == -16 );
    CHECK( s.stop()  == -32 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );


    s = slice(-16, -32, -2);

    CHECK( s.start() == -16 );
    CHECK( s.stop()  == -32 );
    CHECK( s.step()  == -2 );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators", "[positive slice expressions]" )
{
    slice s = 8_s;

    CHECK( s.start() == 8 );
    CHECK( s.stop() == 9 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == false );

    s = 1_s | 5;

    CHECK( s.start() == 1 );
    CHECK( s.stop()  == 5 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );

    s = 2_s | 10 | 3;

    CHECK( s.start() == 2 );
    CHECK( s.stop()  == 10 );
    CHECK( s.step()  == 3 );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );

    s = slice(5) | 10;

    CHECK( s.start() == 5 );
    CHECK( s.stop()  == 10 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );

    s = slice(25) | 50 | 3;

    CHECK( s.start() == 25 );
    CHECK( s.stop()  == 50 );
    CHECK( s.step()  == 3 );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 2", "[negative slice expressions]" )
{
    slice s = -5_s;

    CHECK( s.start() == -5 );
    CHECK( s.stop() == -4 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == false );

    s = -6_s | 5;

    CHECK( s.start() == -6 );
    CHECK( s.stop()  == 5 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );

    s = -6_s | -1;

    CHECK( s.start() == -6 );
    CHECK( s.stop()  == -1 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );

    s = slice(-6) | -1 | 3;

    CHECK( s.start() == -6 );
    CHECK( s.stop()  == -1 );
    CHECK( s.step()  == 3  );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 3", "[common numpy patterns]" )
{
    // a very common things to do in numpy

    slice x0 = 50;

    slice s = x0 + 100;

    CHECK( s.start() == 150 );
    CHECK( s.stop() == 151 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == false );

    s = x0 | x0 + 100;

    CHECK( s.start() == 50 );
    CHECK( s.stop()  == 150 );
    CHECK( s.start_valid() == true  );
    CHECK( s.stop_valid()  == true  );
    CHECK( s.step_valid()  == false );

    s = x0 | x0 + 100 | 5;

    CHECK( s.start() == 50  );
    CHECK( s.stop()  == 150 );
    CHECK( s.step()  == 5   );
    CHECK( s.start_valid() == true );
    CHECK( s.stop_valid()  == true );
    CHECK( s.step_valid()  == true );
}


TEST_CASE( "numcpp::slice::operators 4", "[using missing]" )
{
    missing _;

    SECTION(" 5: ")
    {
        slice s = 5 | _;

        CHECK( s.start() == 5  );
        CHECK( s.start_valid() == true  );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == false );
    }

    SECTION(" -5: ")
    {
        slice s = -5 | _;

        INFO( "s = " << s );

        CHECK( s.start() == -5  );
        CHECK( s.start_valid() == true  );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == false );
    }

    SECTION(" :5 ")
    {
        slice s = _ | 5;

        INFO( "s = " << s );

        CHECK( s.stop() == 5  );
        CHECK( s.step() == 1  );
        CHECK( s.start_valid() == false );
        CHECK( s.stop_valid()  == true  );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" :-5 ")
    {
        slice s = _ | -5;

        CHECK( s.stop() == -5  );
        CHECK( s.step() == 1  );
        CHECK( s.start_valid() == false );
        CHECK( s.stop_valid()  == true  );
        CHECK( s.step_valid()  == true );
    }

    SECTION(" ::2 ")
    {
        slice s = _ | _ | 2;

        CHECK( s.step() == 2  );
        CHECK( s.start_valid() == false );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" ::-2 ")
    {
        slice s = _ | _ | -2;

        CHECK( s.step() == -2  );
        CHECK( s.start_valid() == false );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" 6::2 ")
    {
        slice s = 6 | _ | 2;

        CHECK( s.start() == 6 );
        CHECK( s.step() == 2 );
        CHECK( s.start_valid() == true );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" -6::2 ")
    {
        slice s = -6 | _ | 2;

        CHECK( s.start() == -6 );
        CHECK( s.step() == 2 );
        CHECK( s.start_valid() == true );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" 6::-2 ")
    {
        slice s = 6 | _ | -2;

        CHECK( s.start() == 6 );
        CHECK( s.step() == -2 );
        CHECK( s.start_valid() == true );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }

    SECTION(" -6::-2 ")
    {
        slice s = -6 | _ | -2;

        CHECK( s.start() == -6 );
        CHECK( s.step() == -2 );
        CHECK( s.start_valid() == true );
        CHECK( s.stop_valid()  == false );
        CHECK( s.step_valid()  == true  );
    }
}

// :mode=c++:noTabs=true: