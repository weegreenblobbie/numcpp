#include <catch/catch.hpp> // https://github.com/philsquared/Catch


#include <numcpp/axis_iterator.hpp>


using namespace numcpp;


TEST_CASE( "numcpp::axis_iterator", "[directed tests]" )
{
    auto s = slice(1,2,3);
    auto a = axis_iterator(1,s);
    auto gold = std::vector<uint64>();

    INFO(" a ");
    {
        s = slice(4);
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" a:b ");
    {
        s = slice(4, 8);
        a = axis_iterator(10, s);
        gold = {4,5,6,7};

        CHECK( a.indices() == gold );
    }

    INFO(" a:b:c ");
    {
        s = slice(4, 8, 2);
        a = axis_iterator(10, s);
        gold = {4,6};

        CHECK( a.indices() == gold );
    }

    INFO(" -a ");
    {
        s = slice(-4);
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" invalid a:-1:-1 ");
    {
        s = slice(6-1,-1,-1);
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" invalid -a:-b ");
    {
        s = slice(-4,-8);
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -a:-b:-c ");
    {
        s = slice(-4,-8, -2);
        a = axis_iterator(10, s);
        gold = {6, 4};

        CHECK( a.indices() == gold );
    }

    missing _;

    INFO(" :-4 ");
    {
        s = _ | -4;
        a = axis_iterator(10, s);
        gold = {0,1,2,3,4,5};

        CHECK( a.indices() == gold );
    }

    INFO(" ::2 ");
    {
        s = _ | _ | 2;
        a = axis_iterator(10, s);
        gold = {0,2,4,6,8};

        CHECK( a.indices() == gold );
    }

    INFO(" ::-2 ");
    {
        s = _ | _ | -2;
        a = axis_iterator(10, s);
        gold = {9,7,5,3,1};

        CHECK( a.indices() == gold );
    }

    INFO(" 4::2 ");
    {
        s = 4 | _ | 2;
        a = axis_iterator(10, s);
        gold = {4,6,8};

        CHECK( a.indices() == gold );
    }

    INFO(" -4::2 ");
    {
        s = -4 | _ | 2;
        a = axis_iterator(10, s);
        gold = {6,8};

        CHECK( a.indices() == gold );
    }

    INFO(" 4::-2 ");
    {
        s = 4 | _ | -2;
        a = axis_iterator(10, s);
        gold = {4,2,0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4::-2 ");
    {
        s = -4 | _ | -2;
        a = axis_iterator(10, s);
        gold = {6,4,2,0};

        CHECK( a.indices() == gold );
    }

    INFO(" :-10 ");
    {
        s = _ | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6:3-1 ");
    {
        s = 6_s | 3 | -1;
        a = axis_iterator(10, s);
        gold = {6, 5, 4};

        CHECK( a.indices() == gold );
    }

}


TEST_CASE( "numcpp::axis_iterator random", "[randomly generated test cases]" )
{
    auto s = slice(1,2,3);
    auto a = axis_iterator(1,s);
    auto gold = std::vector<uint64>();

    missing _;

    INFO(" _ | -1 | 7 ");
    {
        s = _ | -1 | 7;
        a = axis_iterator(10, s);
        gold = {0, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ | -3 ");
    {
        s = -7 | _ | -3;
        a = axis_iterator(10, s);
        gold = {3, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | 4 ");
    {
        s = _ | 6 | 4;
        a = axis_iterator(10, s);
        gold = {0, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -1 ");
    {
        s = _ | _ | -1;
        a = axis_iterator(10, s);
        gold = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 5 | -7 ");
    {
        s = -1_s | 5 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | -10 ");
    {
        s = _ | -2 | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -6 ");
    {
        s = _ | -7 | -6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 6 ");
    {
        s = _ | -9 | 6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -10 | 3 ");
    {
        s = 2_s | -10 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 7 | -6 ");
    {
        s = 3_s | 7 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | -4 ");
    {
        s = _ | -10 | -4;
        a = axis_iterator(10, s);
        gold = {9, 5, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 3 | 9 ");
    {
        s = -4_s | 3 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 6 | -5 ");
    {
        s = 7_s | 6 | -5;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -6 ");
    {
        s = 4_s | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -5 | 7 ");
    {
        s = 9_s | -5 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 5 ");
    {
        s = 1_s | 5;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -9 | 3 ");
    {
        s = -8_s | -9 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ ");
    {
        s = -1 | _;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 7 | 6 ");
    {
        s = -6_s | 7 | 6;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | 7 ");
    {
        s = 4_s | 2 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -2 | 2 ");
    {
        s = 5_s | -2 | 2;
        a = axis_iterator(10, s);
        gold = {5, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -2 | -10 ");
    {
        s = 8_s | -2 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 9 | -4 ");
    {
        s = -5_s | 9 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 6 | -4 ");
    {
        s = 0_s | 6 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 6 ");
    {
        s = _ | _ | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ | -2 ");
    {
        s = -9 | _ | -2;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 4 | 2 ");
    {
        s = 5_s | 4 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 9 | -8 ");
    {
        s = 4_s | 9 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 9 | -4 ");
    {
        s = 4_s | 9 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 6 ");
    {
        s = -7_s | 6;
        a = axis_iterator(10, s);
        gold = {3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 6 ");
    {
        s = _ | _ | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 4 | 3 ");
    {
        s = -9_s | 4 | 3;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }
}

// :mode=c++:noTabs=true: