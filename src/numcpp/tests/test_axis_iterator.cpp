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

    INFO(" _ | -10 ");
    {
        s = _ | -10;
        a = axis_iterator(10, s);
        gold = {};

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
        std::cout << "---------------------------------------------------\n";
        s = _ | -7 | -6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

}


TEST_CASE( "numcpp::axis_iterator random 2", "[randomly generated test cases]" )
{
    auto s = slice(1,2,3);
    auto a = axis_iterator(1,s);
    auto gold = std::vector<uint64>();

    missing _;

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
/*
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

    INFO(" -2 | _ | 7 ");
    {
        s = -2 | _ | 7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 6 ");
    {
        s = _ | -9 | 6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 4 | -8 ");
    {
        s = -5_s | 4 | -8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 ");
    {
        s = _ | -3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 8 | -8 ");
    {
        s = _ | 8 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 4 | 1 ");
    {
        s = 2_s | 4 | 1;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | 3 ");
    {
        s = 6 | _ | 3;
        a = axis_iterator(10, s);
        gold = {6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 4 ");
    {
        s = 0_s | 4;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -10 ");
    {
        s = -5_s | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 3 | 7 ");
    {
        s = -5_s | 3 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 4 | 7 ");
    {
        s = -10_s | 4 | 7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 7 | -5 ");
    {
        s = 2_s | 7 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -6 | 4 ");
    {
        s = _ | -6 | 4;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -2 | -4 ");
    {
        s = 5_s | -2 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7 | _ | -9 ");
    {
        s = 7 | _ | -9;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -3 | 3 ");
    {
        s = -9_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -2 | 8 ");
    {
        s = 6_s | -2 | 8;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 | -2 ");
    {
        s = -10_s | 6 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 9 | -5 ");
    {
        s = 7_s | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 3 ");
    {
        s = _ | _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | -1 ");
    {
        s = -8 | _ | -1;
        a = axis_iterator(10, s);
        gold = {2, 1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 0 | -2 ");
    {
        s = 6_s | 0 | -2;
        a = axis_iterator(10, s);
        gold = {6, 4, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -2 | 9 ");
    {
        s = -4_s | -2 | 9;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -6 ");
    {
        s = 4_s | 2 | -6;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -10 ");
    {
        s = _ | 9 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -1 | -2 ");
    {
        s = -10_s | -1 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -5 | -1 ");
    {
        s = 5_s | -5 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 2 | 1 ");
    {
        s = -6_s | 2 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | -6 ");
    {
        s = _ | 1 | -6;
        a = axis_iterator(10, s);
        gold = {9, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ ");
    {
        s = 6 | _;
        a = axis_iterator(10, s);
        gold = {6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -7 | -9 ");
    {
        s = -6_s | -7 | -9;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 0 ");
    {
        s = -9_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -5 ");
    {
        s = -7_s | -5;
        a = axis_iterator(10, s);
        gold = {3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ ");
    {
        s = -2 | _;
        a = axis_iterator(10, s);
        gold = {8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -9 ");
    {
        s = _ | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -4 | -7 ");
    {
        s = -5_s | -4 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 4 | -4 ");
    {
        s = 3_s | 4 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -8 | 2 ");
    {
        s = -4_s | -8 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 8 | 2 ");
    {
        s = -1_s | 8 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | -7 ");
    {
        s = -8 | _ | -7;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | -9 ");
    {
        s = 9 | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 ");
    {
        s = _ | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -5 | 1 ");
    {
        s = 6_s | -5 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 3 | -1 ");
    {
        s = 0_s | 3 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 7 | -10 ");
    {
        s = -8_s | 7 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 9 | 2 ");
    {
        s = -5_s | 9 | 2;
        a = axis_iterator(10, s);
        gold = {5, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -1 ");
    {
        s = 0_s | -1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 | -2 ");
    {
        s = _ | -4 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -7 ");
    {
        s = 7_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | 1 ");
    {
        s = 4 | _ | 1;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -10 | 3 ");
    {
        s = 9_s | -10 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 | -7 ");
    {
        s = _ | 4 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -5 | 8 ");
    {
        s = -3_s | -5 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 7 | -8 ");
    {
        s = -10_s | 7 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 | -1 ");
    {
        s = _ | -3 | -1;
        a = axis_iterator(10, s);
        gold = {9, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 3 | -6 ");
    {
        s = 7_s | 3 | -6;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 0 | -7 ");
    {
        s = -2_s | 0 | -7;
        a = axis_iterator(10, s);
        gold = {8, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 0 | -2 ");
    {
        s = -10_s | 0 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 8 | -2 ");
    {
        s = 2_s | 8 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -4 | 8 ");
    {
        s = 6_s | -4 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 1 | -2 ");
    {
        s = 0_s | 1 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ | 3 ");
    {
        s = -2 | _ | 3;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 7 ");
    {
        s = -5_s | 7;
        a = axis_iterator(10, s);
        gold = {5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | -3 ");
    {
        s = 4 | _ | -3;
        a = axis_iterator(10, s);
        gold = {4, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | -7 ");
    {
        s = -10 | _ | -7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -4 | 3 ");
    {
        s = -1_s | -4 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 1 ");
    {
        s = -2_s | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 0 | 3 ");
    {
        s = -7_s | 0 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -6 | -8 ");
    {
        s = 3_s | -6 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -10 | 9 ");
    {
        s = 1_s | -10 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 2 | -4 ");
    {
        s = -2_s | 2 | -4;
        a = axis_iterator(10, s);
        gold = {8, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -1 ");
    {
        s = 2_s | -1;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -6 ");
    {
        s = -8_s | -6;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -8 ");
    {
        s = _ | 9 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 0 | -5 ");
    {
        s = -3_s | 0 | -5;
        a = axis_iterator(10, s);
        gold = {7, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -9 | -1 ");
    {
        s = 9_s | -9 | -1;
        a = axis_iterator(10, s);
        gold = {9, 8, 7, 6, 5, 4, 3, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -10 | 3 ");
    {
        s = 2_s | -10 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 9 | -2 ");
    {
        s = 0_s | 9 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -5 ");
    {
        s = 1_s | -5;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 0 | -3 ");
    {
        s = -9_s | 0 | -3;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ ");
    {
        s = -6 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -3 | 9 ");
    {
        s = -5_s | -3 | 9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -4 ");
    {
        s = _ | 9 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ ");
    {
        s = 9 | _;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -9 ");
    {
        s = 8_s | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ | 4 ");
    {
        s = 3 | _ | 4;
        a = axis_iterator(10, s);
        gold = {3, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -1 | -6 ");
    {
        s = 7_s | -1 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -6 | -10 ");
    {
        s = 7_s | -6 | -10;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ ");
    {
        s = -4 | _;
        a = axis_iterator(10, s);
        gold = {6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ | -7 ");
    {
        s = -6 | _ | -7;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | -7 ");
    {
        s = _ | 7 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 3 | -2 ");
    {
        s = 2_s | 3 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 5 | -8 ");
    {
        s = -5_s | 5 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 2 ");
    {
        s = -5 | _ | 2;
        a = axis_iterator(10, s);
        gold = {5, 7, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 3 ");
    {
        s = _ | _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 9 ");
    {
        s = 0_s | 9;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -2 | -9 ");
    {
        s = 2_s | -2 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 2 | -5 ");
    {
        s = 3_s | 2 | -5;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -3 | 3 ");
    {
        s = -4_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -2 | -1 ");
    {
        s = 6_s | -2 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 9 ");
    {
        s = _ | _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 2 | 3 ");
    {
        s = 0_s | 2 | 3;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ | -4 ");
    {
        s = -9 | _ | -4;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | -3 ");
    {
        s = _ | -10 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 2 | -2 ");
    {
        s = -4_s | 2 | -2;
        a = axis_iterator(10, s);
        gold = {6, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 9 | 7 ");
    {
        s = -8_s | 9 | 7;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | -9 ");
    {
        s = _ | 7 | -9;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 7 | -5 ");
    {
        s = 2_s | 7 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ ");
    {
        s = 4 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -1 ");
    {
        s = 1_s | -1;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -6 | -7 ");
    {
        s = 6_s | -6 | -7;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | -7 ");
    {
        s = 9 | _ | -7;
        a = axis_iterator(10, s);
        gold = {9, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 4 ");
    {
        s = -7_s | 4;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 ");
    {
        s = _ | -8;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -1 | 5 ");
    {
        s = 9_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 4 | 7 ");
    {
        s = -8_s | 4 | 7;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -1 ");
    {
        s = 7_s | -1;
        a = axis_iterator(10, s);
        gold = {7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ ");
    {
        s = -1 | _;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -4 ");
    {
        s = 8_s | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -1 | -4 ");
    {
        s = 6_s | -1 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 2 | -9 ");
    {
        s = 0_s | 2 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -5 ");
    {
        s = _ | -7 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | 7 ");
    {
        s = 5 | _ | 7;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 3 | -4 ");
    {
        s = -8_s | 3 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 5 | -3 ");
    {
        s = 7_s | 5 | -3;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 8 ");
    {
        s = -5 | _ | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | -2 ");
    {
        s = _ | -10 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 0 | -1 ");
    {
        s = -5_s | 0 | -1;
        a = axis_iterator(10, s);
        gold = {5, 4, 3, 2, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -7 | 1 ");
    {
        s = 3_s | -7 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -2 | 2 ");
    {
        s = -3_s | -2 | 2;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 1 | 6 ");
    {
        s = 9_s | 1 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -4 | -9 ");
    {
        s = 0_s | -4 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | 2 ");
    {
        s = _ | 5 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -1 | 5 ");
    {
        s = 1_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {1, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -2 | -7 ");
    {
        s = -10_s | -2 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 1 | -5 ");
    {
        s = -4_s | 1 | -5;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -10 | -5 ");
    {
        s = 4_s | -10 | -5;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -10 | -7 ");
    {
        s = 3_s | -10 | -7;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | 4 ");
    {
        s = -10 | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 3 | -4 ");
    {
        s = 8_s | 3 | -4;
        a = axis_iterator(10, s);
        gold = {8, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 9 ");
    {
        s = -5 | _ | 9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -5 | 3 ");
    {
        s = 1_s | -5 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 4 | -3 ");
    {
        s = -10_s | 4 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 | 1 ");
    {
        s = _ | -3 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 | -1 ");
    {
        s = _ | 2 | -1;
        a = axis_iterator(10, s);
        gold = {9, 8, 7, 6, 5, 4, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 0 ");
    {
        s = 7_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 ");
    {
        s = _ | -3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 | -8 ");
    {
        s = _ | -4 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 0 ");
    {
        s = 4_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 4 | -9 ");
    {
        s = 6_s | 4 | -9;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 5 | -6 ");
    {
        s = -4_s | 5 | -6;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ ");
    {
        s = -7 | _;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 3 | 1 ");
    {
        s = 0_s | 3 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ | -4 ");
    {
        s = -2 | _ | -4;
        a = axis_iterator(10, s);
        gold = {8, 4, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 7 | -4 ");
    {
        s = 1_s | 7 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ ");
    {
        s = -8 | _;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 3 ");
    {
        s = _ | -9 | 3;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 6 | -5 ");
    {
        s = -6_s | 6 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 4 | 3 ");
    {
        s = 7_s | 4 | 3;
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

    INFO(" _ | -2 ");
    {
        s = _ | -2;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -7 ");
    {
        s = 9_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -5 | -1 ");
    {
        s = 9_s | -5 | -1;
        a = axis_iterator(10, s);
        gold = {9, 8, 7, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -3 ");
    {
        s = _ | _ | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -3 | 2 ");
    {
        s = 8_s | -3 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -6 | -2 ");
    {
        s = -4_s | -6 | -2;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 7 | -4 ");
    {
        s = -1_s | 7 | -4;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 4 ");
    {
        s = -8_s | 4;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ ");
    {
        s = 0 | _;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 9 | -5 ");
    {
        s = -9_s | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -4 ");
    {
        s = 4_s | 2 | -4;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 7 | _ | -5 ");
    {
        s = 7 | _ | -5;
        a = axis_iterator(10, s);
        gold = {7, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 ");
    {
        s = _ | 1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 9 | 1 ");
    {
        s = -1_s | 9 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 4 | 5 ");
    {
        s = -1_s | 4 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ | -1 ");
    {
        s = 8 | _ | -1;
        a = axis_iterator(10, s);
        gold = {8, 7, 6, 5, 4, 3, 2, 1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 | 7 ");
    {
        s = -10_s | 6 | 7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 0 | -4 ");
    {
        s = -9_s | 0 | -4;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 6 | -3 ");
    {
        s = -8_s | 6 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | -10 ");
    {
        s = _ | -8 | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ | -10 ");
    {
        s = -1 | _ | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 3 ");
    {
        s = -9_s | 3;
        a = axis_iterator(10, s);
        gold = {1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 8 ");
    {
        s = 0_s | 8;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 3 | -3 ");
    {
        s = 2_s | 3 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ ");
    {
        s = 1 | _;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -4 | -5 ");
    {
        s = -10_s | -4 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 ");
    {
        s = _ | -1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 0 ");
    {
        s = 5_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | 4 ");
    {
        s = 9 | _ | 4;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ ");
    {
        s = 3 | _;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 8 | -6 ");
    {
        s = _ | 8 | -6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 2 | 1 ");
    {
        s = -7_s | 2 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -10 | -7 ");
    {
        s = -9_s | -10 | -7;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 9 | 7 ");
    {
        s = -8_s | 9 | 7;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | -3 ");
    {
        s = _ | -8 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 3 ");
    {
        s = 1_s | 3;
        a = axis_iterator(10, s);
        gold = {1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 5 | -7 ");
    {
        s = -1_s | 5 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ ");
    {
        s = 2 | _;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | -9 ");
    {
        s = _ | 5 | -9;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -6 | -3 ");
    {
        s = -9_s | -6 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 4 ");
    {
        s = -8 | _ | 4;
        a = axis_iterator(10, s);
        gold = {2, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ | 7 ");
    {
        s = 8 | _ | 7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -8 ");
    {
        s = _ | 9 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 ");
    {
        s = -10_s | 6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -8 | 4 ");
    {
        s = 9_s | -8 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 9 | -5 ");
    {
        s = -4_s | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -2 ");
    {
        s = _ | _ | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | -7 ");
    {
        s = _ | 7 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -4 | -8 ");
    {
        s = -5_s | -4 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -10 | -9 ");
    {
        s = -5_s | -10 | -9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 7 | -7 ");
    {
        s = 6_s | 7 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -7 ");
    {
        s = -3 | _ | -7;
        a = axis_iterator(10, s);
        gold = {7, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 9 | -5 ");
    {
        s = -7_s | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 | 7 ");
    {
        s = -10_s | 6 | 7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 9 | 1 ");
    {
        s = -7_s | 9 | 1;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 ");
    {
        s = _ | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -7 | -2 ");
    {
        s = 8_s | -7 | -2;
        a = axis_iterator(10, s);
        gold = {8, 6, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | 1 ");
    {
        s = _ | -2 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 3 | -3 ");
    {
        s = -9_s | 3 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -7 | -10 ");
    {
        s = -2_s | -7 | -10;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | -9 ");
    {
        s = 5 | _ | -9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 8 | -9 ");
    {
        s = -8_s | 8 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ ");
    {
        s = 3 | _;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 ");
    {
        s = _ | -8;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 4 | -3 ");
    {
        s = 3_s | 4 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -10 | -1 ");
    {
        s = 2_s | -10 | -1;
        a = axis_iterator(10, s);
        gold = {2, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 3 | -2 ");
    {
        s = 0_s | 3 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -5 | 3 ");
    {
        s = 1_s | -5 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -3 | -9 ");
    {
        s = -7_s | -3 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 7 | -1 ");
    {
        s = -10_s | 7 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -2 | 5 ");
    {
        s = -8_s | -2 | 5;
        a = axis_iterator(10, s);
        gold = {2, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 1 | -2 ");
    {
        s = 7_s | 1 | -2;
        a = axis_iterator(10, s);
        gold = {7, 5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ | -2 ");
    {
        s = 2 | _ | -2;
        a = axis_iterator(10, s);
        gold = {2, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -6 | 2 ");
    {
        s = -5_s | -6 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 8 | -9 ");
    {
        s = -6_s | 8 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 8 | -3 ");
    {
        s = 4_s | 8 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -5 | 3 ");
    {
        s = -10_s | -5 | 3;
        a = axis_iterator(10, s);
        gold = {0, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -3 | 9 ");
    {
        s = 8_s | -3 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 9 | -8 ");
    {
        s = 3_s | 9 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -9 | -10 ");
    {
        s = -6_s | -9 | -10;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -6 | 8 ");
    {
        s = 3_s | -6 | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -1 | -10 ");
    {
        s = -2_s | -1 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -5 | -2 ");
    {
        s = -7_s | -5 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 3 ");
    {
        s = -8 | _ | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -9 | 7 ");
    {
        s = -8_s | -9 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ ");
    {
        s = 4 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 7 | -6 ");
    {
        s = 6_s | 7 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -6 ");
    {
        s = 0_s | -6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 9 | -6 ");
    {
        s = 7_s | 9 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | -4 ");
    {
        s = 4 | _ | -4;
        a = axis_iterator(10, s);
        gold = {4, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ ");
    {
        s = -9 | _;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 ");
    {
        s = _ | 2;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 8 ");
    {
        s = _ | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 1 | -2 ");
    {
        s = 3_s | 1 | -2;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 ");
    {
        s = _ | 5;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 4 | 1 ");
    {
        s = -8_s | 4 | 1;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 0 ");
    {
        s = -2_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 8 | -1 ");
    {
        s = 2_s | 8 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 2 | 3 ");
    {
        s = 5_s | 2 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 1 | 4 ");
    {
        s = -3_s | 1 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -10 | -1 ");
    {
        s = 8_s | -10 | -1;
        a = axis_iterator(10, s);
        gold = {8, 7, 6, 5, 4, 3, 2, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 5 | 4 ");
    {
        s = -1_s | 5 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -1 | -2 ");
    {
        s = -4_s | -1 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -4 | 8 ");
    {
        s = 1_s | -4 | 8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 2 | -3 ");
    {
        s = 6_s | 2 | -3;
        a = axis_iterator(10, s);
        gold = {6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 1 | -6 ");
    {
        s = -7_s | 1 | -6;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -3 | -6 ");
    {
        s = -5_s | -3 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 | 1 ");
    {
        s = _ | 2 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -3 | 9 ");
    {
        s = 2_s | -3 | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ | 1 ");
    {
        s = -1 | _ | 1;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -4 ");
    {
        s = 4_s | 2 | -4;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | 7 ");
    {
        s = 5 | _ | 7;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 7 | -2 ");
    {
        s = 9_s | 7 | -2;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -1 | 2 ");
    {
        s = -4_s | -1 | 2;
        a = axis_iterator(10, s);
        gold = {6, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -10 | 1 ");
    {
        s = 6_s | -10 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 9 | -10 ");
    {
        s = -4_s | 9 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -8 ");
    {
        s = 1_s | -8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 8 | -1 ");
    {
        s = 2_s | 8 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -9 ");
    {
        s = _ | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -6 ");
    {
        s = -8_s | -6;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -2 | -9 ");
    {
        s = 0_s | -2 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 3 ");
    {
        s = _ | _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 5 ");
    {
        s = 8_s | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -1 | -3 ");
    {
        s = 1_s | -1 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 5 | -10 ");
    {
        s = -3_s | 5 | -10;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 3 ");
    {
        s = -10_s | 3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -3 | 5 ");
    {
        s = -2_s | -3 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -5 | -2 ");
    {
        s = 8_s | -5 | -2;
        a = axis_iterator(10, s);
        gold = {8, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -3 | 9 ");
    {
        s = 2_s | -3 | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | 6 ");
    {
        s = 9 | _ | 6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | 1 ");
    {
        s = _ | -10 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ | -3 ");
    {
        s = -6 | _ | -3;
        a = axis_iterator(10, s);
        gold = {4, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | -5 ");
    {
        s = _ | -8 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | 5 ");
    {
        s = -3 | _ | 5;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 ");
    {
        s = _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 0 | -6 ");
    {
        s = 5_s | 0 | -6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 8 | -5 ");
    {
        s = -8_s | 8 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | -6 ");
    {
        s = _ | -10 | -6;
        a = axis_iterator(10, s);
        gold = {9, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | -9 ");
    {
        s = 4 | _ | -9;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 4 ");
    {
        s = _ | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -7 ");
    {
        s = 6_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ ");
    {
        s = -3 | _;
        a = axis_iterator(10, s);
        gold = {7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ | 7 ");
    {
        s = -1 | _ | 7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 0 | -6 ");
    {
        s = -3_s | 0 | -6;
        a = axis_iterator(10, s);
        gold = {7, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -5 | 8 ");
    {
        s = 5_s | -5 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -9 ");
    {
        s = 9_s | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -1 ");
    {
        s = 5_s | -1;
        a = axis_iterator(10, s);
        gold = {5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 4 | 6 ");
    {
        s = 2_s | 4 | 6;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 2 | -1 ");
    {
        s = -9_s | 2 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | 8 ");
    {
        s = _ | 7 | 8;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -2 | -4 ");
    {
        s = 9_s | -2 | -4;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 0 | -6 ");
    {
        s = 2_s | 0 | -6;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 9 ");
    {
        s = 3_s | 9;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -3 | -9 ");
    {
        s = -2_s | -3 | -9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 4 | -1 ");
    {
        s = 2_s | 4 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -1 | 5 ");
    {
        s = 7_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -10 | -8 ");
    {
        s = -4_s | -10 | -8;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -5 | 2 ");
    {
        s = _ | -5 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | -4 ");
    {
        s = 6 | _ | -4;
        a = axis_iterator(10, s);
        gold = {6, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -3 | -8 ");
    {
        s = 4_s | -3 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -10 ");
    {
        s = 0_s | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 4 | 2 ");
    {
        s = -2_s | 4 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -5 | 6 ");
    {
        s = 1_s | -5 | 6;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 | -5 ");
    {
        s = _ | 0 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 6 | -1 ");
    {
        s = 1_s | 6 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -7 | -5 ");
    {
        s = 3_s | -7 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -9 | 7 ");
    {
        s = -8_s | -9 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -1 ");
    {
        s = 0 | _ | -1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -9 ");
    {
        s = _ | -7 | -9;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -10 | 1 ");
    {
        s = _ | -10 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -9 | 8 ");
    {
        s = 2_s | -9 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 8 ");
    {
        s = _ | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ ");
    {
        s = -6 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -8 | 1 ");
    {
        s = 8_s | -8 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ ");
    {
        s = -8 | _;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -2 | -10 ");
    {
        s = -3_s | -2 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ | -9 ");
    {
        s = -2 | _ | -9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 3 | 2 ");
    {
        s = -2_s | 3 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 3 | 2 ");
    {
        s = 4_s | 3 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -8 | -1 ");
    {
        s = -3_s | -8 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6, 5, 4, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ | 2 ");
    {
        s = 1 | _ | 2;
        a = axis_iterator(10, s);
        gold = {1, 3, 5, 7, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ | -9 ");
    {
        s = -1 | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 5 | 2 ");
    {
        s = -8_s | 5 | 2;
        a = axis_iterator(10, s);
        gold = {2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 5 | -5 ");
    {
        s = 6_s | 5 | -5;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -5 | 9 ");
    {
        s = 2_s | -5 | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 ");
    {
        s = _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 8 | -8 ");
    {
        s = -7_s | 8 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 8 ");
    {
        s = -3_s | 8;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -4 ");
    {
        s = -3 | _ | -4;
        a = axis_iterator(10, s);
        gold = {7, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -2 | 4 ");
    {
        s = 3_s | -2 | 4;
        a = axis_iterator(10, s);
        gold = {3, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -2 | 2 ");
    {
        s = 7_s | -2 | 2;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 5 | 4 ");
    {
        s = 6_s | 5 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 7 ");
    {
        s = -8_s | 7;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -2 | 3 ");
    {
        s = -3_s | -2 | 3;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 5 | -1 ");
    {
        s = 1_s | 5 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -1 | -4 ");
    {
        s = 4_s | -1 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 6 | -10 ");
    {
        s = -4_s | 6 | -10;
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

    INFO(" 8 | _ | -7 ");
    {
        s = 8 | _ | -7;
        a = axis_iterator(10, s);
        gold = {8, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -1 ");
    {
        s = 0 | _ | -1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -3 | -4 ");
    {
        s = -6_s | -3 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -9 | -2 ");
    {
        s = -5_s | -9 | -2;
        a = axis_iterator(10, s);
        gold = {5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -2 ");
    {
        s = -4 | _ | -2;
        a = axis_iterator(10, s);
        gold = {6, 4, 2, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | 9 ");
    {
        s = -10 | _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 6 ");
    {
        s = 9_s | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ ");
    {
        s = 2 | _;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | 8 ");
    {
        s = 5 | _ | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -3 | 8 ");
    {
        s = -5_s | -3 | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -9 | -2 ");
    {
        s = -3_s | -9 | -2;
        a = axis_iterator(10, s);
        gold = {7, 5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 6 ");
    {
        s = -6_s | 6;
        a = axis_iterator(10, s);
        gold = {4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 | -3 ");
    {
        s = _ | 2 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 6 ");
    {
        s = -6_s | 6;
        a = axis_iterator(10, s);
        gold = {4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 7 ");
    {
        s = -6_s | 7;
        a = axis_iterator(10, s);
        gold = {4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 4 ");
    {
        s = 0 | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 3 | -10 ");
    {
        s = -6_s | 3 | -10;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -5 ");
    {
        s = _ | -7 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -9 | 1 ");
    {
        s = 6_s | -9 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 | -5 ");
    {
        s = _ | 0 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -6 | -4 ");
    {
        s = 9_s | -6 | -4;
        a = axis_iterator(10, s);
        gold = {9, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 9 ");
    {
        s = -3_s | 9;
        a = axis_iterator(10, s);
        gold = {7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 3 ");
    {
        s = -9_s | 3;
        a = axis_iterator(10, s);
        gold = {1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 9 | 7 ");
    {
        s = -3_s | 9 | 7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 2 | -10 ");
    {
        s = -2_s | 2 | -10;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -3 | -9 ");
    {
        s = 8_s | -3 | -9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | 6 ");
    {
        s = -3 | _ | 6;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 9 | -5 ");
    {
        s = -2_s | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | 3 ");
    {
        s = _ | -8 | 3;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ ");
    {
        s = -6 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -4 | -6 ");
    {
        s = 5_s | -4 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -1 ");
    {
        s = 2_s | -1;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 | 8 ");
    {
        s = _ | 0 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 ");
    {
        s = _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 | -6 ");
    {
        s = -10_s | 6 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 0 | -4 ");
    {
        s = -7_s | 0 | -4;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 3 | -7 ");
    {
        s = 7_s | 3 | -7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 7 | 8 ");
    {
        s = -3_s | 7 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 7 | 3 ");
    {
        s = -6_s | 7 | 3;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | 8 ");
    {
        s = -3 | _ | 8;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 6 ");
    {
        s = 0 | _ | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | 6 ");
    {
        s = _ | 1 | 6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -1 | -4 ");
    {
        s = -9_s | -1 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | -4 ");
    {
        s = -10 | _ | -4;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -6 | -1 ");
    {
        s = -3_s | -6 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 ");
    {
        s = _ | 1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -7 | 2 ");
    {
        s = 6_s | -7 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -10 | 9 ");
    {
        s = 2_s | -10 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 3 ");
    {
        s = -4_s | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -2 | 9 ");
    {
        s = -1_s | -2 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 5 | -1 ");
    {
        s = 7_s | 5 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 6 | 5 ");
    {
        s = 8_s | 6 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | -10 ");
    {
        s = 9 | _ | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -6 | -10 ");
    {
        s = -1_s | -6 | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 9 | -1 ");
    {
        s = 7_s | 9 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | -10 ");
    {
        s = -8 | _ | -10;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ ");
    {
        s = -4 | _;
        a = axis_iterator(10, s);
        gold = {6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -6 | -8 ");
    {
        s = _ | -6 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 5 ");
    {
        s = 8_s | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -7 ");
    {
        s = -4 | _ | -7;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | 4 ");
    {
        s = _ | 3 | 4;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 5 | -1 ");
    {
        s = -6_s | 5 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 4 | -6 ");
    {
        s = 9_s | 4 | -6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 ");
    {
        s = _ | -4;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -9 | 4 ");
    {
        s = -2_s | -9 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -9 ");
    {
        s = 0_s | -9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -1 ");
    {
        s = 0 | _ | -1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -1 | 2 ");
    {
        s = 8_s | -1 | 2;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 9 | 6 ");
    {
        s = -9_s | 9 | 6;
        a = axis_iterator(10, s);
        gold = {1, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 6 ");
    {
        s = -10_s | 6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -3 | -4 ");
    {
        s = -10_s | -3 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -8 | -6 ");
    {
        s = 0_s | -8 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 5 | -2 ");
    {
        s = 8_s | 5 | -2;
        a = axis_iterator(10, s);
        gold = {8, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 0 | 2 ");
    {
        s = -6_s | 0 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -10 | 2 ");
    {
        s = 3_s | -10 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 3 | 6 ");
    {
        s = -2_s | 3 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -3 ");
    {
        s = 0 | _ | -3;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | 9 ");
    {
        s = _ | 1 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -10 | -3 ");
    {
        s = -1_s | -10 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 3 ");
    {
        s = 2_s | 3;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 ");
    {
        s = _ | 1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -10 | -3 ");
    {
        s = 4_s | -10 | -3;
        a = axis_iterator(10, s);
        gold = {4, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 9 ");
    {
        s = _ | -9 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ | -8 ");
    {
        s = 3 | _ | -8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -4 ");
    {
        s = 3_s | -4;
        a = axis_iterator(10, s);
        gold = {3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -5 ");
    {
        s = 8_s | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 1 | -2 ");
    {
        s = 8_s | 1 | -2;
        a = axis_iterator(10, s);
        gold = {8, 6, 4, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -4 | -1 ");
    {
        s = -5_s | -4 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 6 | 2 ");
    {
        s = -7_s | 6 | 2;
        a = axis_iterator(10, s);
        gold = {3, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 5 | -1 ");
    {
        s = -3_s | 5 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -7 ");
    {
        s = -3_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | -6 ");
    {
        s = -8 | _ | -6;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 4 | -6 ");
    {
        s = -2_s | 4 | -6;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | -5 ");
    {
        s = _ | -8 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -6 | 8 ");
    {
        s = 1_s | -6 | 8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | 9 ");
    {
        s = 4 | _ | 9;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 8 ");
    {
        s = -5 | _ | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 9 | 4 ");
    {
        s = 0_s | 9 | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 2 | 7 ");
    {
        s = -9_s | 2 | 7;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | 4 ");
    {
        s = 6 | _ | 4;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -6 | 5 ");
    {
        s = 0_s | -6 | 5;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -3 ");
    {
        s = 8_s | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ | -5 ");
    {
        s = -9 | _ | -5;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -10 | -4 ");
    {
        s = 1_s | -10 | -4;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ ");
    {
        s = 8 | _;
        a = axis_iterator(10, s);
        gold = {8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 9 | -1 ");
    {
        s = 2_s | 9 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 6 | -10 ");
    {
        s = 4_s | 6 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -10 | -7 ");
    {
        s = -8_s | -10 | -7;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | 4 ");
    {
        s = _ | 3 | 4;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 7 ");
    {
        s = 5_s | 7;
        a = axis_iterator(10, s);
        gold = {5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 6 ");
    {
        s = -8 | _ | 6;
        a = axis_iterator(10, s);
        gold = {2, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 5 | 2 ");
    {
        s = 9_s | 5 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -4 | -8 ");
    {
        s = 2_s | -4 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -5 | -9 ");
    {
        s = 5_s | -5 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 | 6 ");
    {
        s = _ | -3 | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -9 | -3 ");
    {
        s = -1_s | -9 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -6 | -8 ");
    {
        s = 5_s | -6 | -8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 | -8 ");
    {
        s = _ | 0 | -8;
        a = axis_iterator(10, s);
        gold = {9, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 8 ");
    {
        s = 0 | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 3 | -1 ");
    {
        s = 1_s | 3 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ | -3 ");
    {
        s = 3 | _ | -3;
        a = axis_iterator(10, s);
        gold = {3, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -4 | -2 ");
    {
        s = -10_s | -4 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ | -2 ");
    {
        s = 2 | _ | -2;
        a = axis_iterator(10, s);
        gold = {2, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -9 ");
    {
        s = _ | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 9 | -8 ");
    {
        s = -7_s | 9 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 3 ");
    {
        s = -8 | _ | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 0 | 2 ");
    {
        s = 9_s | 0 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 5 ");
    {
        s = 0_s | 5;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -10 ");
    {
        s = -4_s | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -10 | 7 ");
    {
        s = 3_s | -10 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 6 ");
    {
        s = -5_s | 6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 2 | 9 ");
    {
        s = -10_s | 2 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -3 | -9 ");
    {
        s = -6_s | -3 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -2 | 5 ");
    {
        s = 3_s | -2 | 5;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 0 ");
    {
        s = -4_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -9 | -7 ");
    {
        s = 7_s | -9 | -7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -6 ");
    {
        s = 2_s | -6;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -2 | 1 ");
    {
        s = 8_s | -2 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 4 ");
    {
        s = _ | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 2 | 6 ");
    {
        s = 5_s | 2 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 0 | -4 ");
    {
        s = -3_s | 0 | -4;
        a = axis_iterator(10, s);
        gold = {7, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ | -1 ");
    {
        s = 1 | _ | -1;
        a = axis_iterator(10, s);
        gold = {1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -5 | 9 ");
    {
        s = 6_s | -5 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -10 | 4 ");
    {
        s = -9_s | -10 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 6 | -4 ");
    {
        s = -3_s | 6 | -4;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | -8 ");
    {
        s = _ | -9 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -7 | -9 ");
    {
        s = 2_s | -7 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -1 | -4 ");
    {
        s = -9_s | -1 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 1 ");
    {
        s = -8_s | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 4 | -1 ");
    {
        s = 7_s | 4 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 6 | -5 ");
    {
        s = 2_s | 6 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | 6 ");
    {
        s = 4 | _ | 6;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -6 ");
    {
        s = _ | _ | -6;
        a = axis_iterator(10, s);
        gold = {9, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 7 | -10 ");
    {
        s = 1_s | 7 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 1 | 4 ");
    {
        s = 7_s | 1 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -3 | 8 ");
    {
        s = -7_s | -3 | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -6 | 1 ");
    {
        s = 3_s | -6 | 1;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | 6 ");
    {
        s = _ | 5 | 6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 3 | 2 ");
    {
        s = 4_s | 3 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ ");
    {
        s = -7 | _;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -10 | -3 ");
    {
        s = 7_s | -10 | -3;
        a = axis_iterator(10, s);
        gold = {7, 4, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -6 | -5 ");
    {
        s = -4_s | -6 | -5;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -9 ");
    {
        s = 3_s | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -3 | 3 ");
    {
        s = -8_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {2, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 5 | -8 ");
    {
        s = -10_s | 5 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 2 ");
    {
        s = 3_s | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 3 | 6 ");
    {
        s = 8_s | 3 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -7 | -8 ");
    {
        s = -4_s | -7 | -8;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 4 ");
    {
        s = 8_s | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 5 | -2 ");
    {
        s = -9_s | 5 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | 4 ");
    {
        s = 6 | _ | 4;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 1 | 9 ");
    {
        s = -7_s | 1 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -5 | 3 ");
    {
        s = -9_s | -5 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -1 | 5 ");
    {
        s = 7_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -9 | -7 ");
    {
        s = 8_s | -9 | -7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 | -10 ");
    {
        s = _ | -1 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 2 | -5 ");
    {
        s = 5_s | 2 | -5;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -3 | -2 ");
    {
        s = -8_s | -3 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 1 | 2 ");
    {
        s = 6_s | 1 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ ");
    {
        s = 9 | _;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 2 ");
    {
        s = _ | -9 | 2;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 | -6 ");
    {
        s = _ | 4 | -6;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 1 ");
    {
        s = -10_s | 1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | 5 ");
    {
        s = 4_s | 2 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -8 ");
    {
        s = 1_s | -8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 | -2 ");
    {
        s = _ | 4 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -8 | 5 ");
    {
        s = 4_s | -8 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -6 | -7 ");
    {
        s = 3_s | -6 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | 9 ");
    {
        s = _ | 5 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -8 ");
    {
        s = -4_s | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 4 ");
    {
        s = -10_s | 4;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 1 | -1 ");
    {
        s = -6_s | 1 | -1;
        a = axis_iterator(10, s);
        gold = {4, 3, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 7 ");
    {
        s = 5_s | 7;
        a = axis_iterator(10, s);
        gold = {5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | 9 ");
    {
        s = _ | -2 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 7 | -9 ");
    {
        s = -4_s | 7 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -9 ");
    {
        s = -4 | _ | -9;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | 9 ");
    {
        s = _ | 3 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -6 | -1 ");
    {
        s = 9_s | -6 | -1;
        a = axis_iterator(10, s);
        gold = {9, 8, 7, 6, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 | 3 ");
    {
        s = _ | -1 | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -5 | -7 ");
    {
        s = -3_s | -5 | -7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 3 ");
    {
        s = _ | _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 8 | 6 ");
    {
        s = -5_s | 8 | 6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | -3 ");
    {
        s = 5 | _ | -3;
        a = axis_iterator(10, s);
        gold = {5, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | 4 ");
    {
        s = _ | 7 | 4;
        a = axis_iterator(10, s);
        gold = {0, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -9 ");
    {
        s = 2_s | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -8 | 3 ");
    {
        s = -5_s | -8 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -5 ");
    {
        s = _ | -7 | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -10 | 3 ");
    {
        s = -2_s | -10 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -6 | -4 ");
    {
        s = 2_s | -6 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -3 | -8 ");
    {
        s = 5_s | -3 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -8 | -1 ");
    {
        s = -3_s | -8 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6, 5, 4, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -7 | 1 ");
    {
        s = -6_s | -7 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 0 ");
    {
        s = 5_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | -7 ");
    {
        s = _ | 5 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ | -6 ");
    {
        s = 3 | _ | -6;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -9 | 1 ");
    {
        s = 6_s | -9 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -7 ");
    {
        s = _ | _ | -7;
        a = axis_iterator(10, s);
        gold = {9, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 2 | 7 ");
    {
        s = 6_s | 2 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -6 | -10 ");
    {
        s = -7_s | -6 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 6 ");
    {
        s = -5 | _ | 6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 4 | -3 ");
    {
        s = 0_s | 4 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 1 ");
    {
        s = -3_s | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | 2 ");
    {
        s = _ | 5 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -1 | 1 ");
    {
        s = -4_s | -1 | 1;
        a = axis_iterator(10, s);
        gold = {6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -9 | -1 ");
    {
        s = 1_s | -9 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 5 | -9 ");
    {
        s = 2_s | 5 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -10 | 6 ");
    {
        s = 4_s | -10 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -10 | 1 ");
    {
        s = -2_s | -10 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -1 | -3 ");
    {
        s = -7_s | -1 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 4 | -10 ");
    {
        s = 7_s | 4 | -10;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 9 ");
    {
        s = -6_s | 9;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | 3 ");
    {
        s = _ | 9 | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -6 | 4 ");
    {
        s = -9_s | -6 | 4;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -3 | -2 ");
    {
        s = 6_s | -3 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -10 | -1 ");
    {
        s = 0_s | -10 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -9 | 8 ");
    {
        s = -7_s | -9 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 0 | 5 ");
    {
        s = 3_s | 0 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 4 ");
    {
        s = 8_s | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 5 | -1 ");
    {
        s = -5_s | 5 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ ");
    {
        s = -4 | _;
        a = axis_iterator(10, s);
        gold = {6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 7 | -2 ");
    {
        s = 1_s | 7 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 9 | 8 ");
    {
        s = 4_s | 9 | 8;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -2 ");
    {
        s = -3_s | -2;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 6 | -5 ");
    {
        s = -8_s | 6 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 3 | 6 ");
    {
        s = -1_s | 3 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -9 | -5 ");
    {
        s = 4_s | -9 | -5;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -5 | -10 ");
    {
        s = 6_s | -5 | -10;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -5 ");
    {
        s = -4 | _ | -5;
        a = axis_iterator(10, s);
        gold = {6, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 9 ");
    {
        s = -8 | _ | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 ");
    {
        s = _ | 2;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 8 | -7 ");
    {
        s = 3_s | 8 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7 | _ | 9 ");
    {
        s = 7 | _ | 9;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -2 | -9 ");
    {
        s = 8_s | -2 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 7 | -8 ");
    {
        s = 6_s | 7 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -1 ");
    {
        s = _ | 9 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -5 | 1 ");
    {
        s = 6_s | -5 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -7 ");
    {
        s = -3_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 6 ");
    {
        s = 8_s | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ ");
    {
        s = 0 | _;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -10 | -5 ");
    {
        s = 5_s | -10 | -5;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -6 ");
    {
        s = 7_s | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -5 ");
    {
        s = _ | _ | -5;
        a = axis_iterator(10, s);
        gold = {9, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -5 ");
    {
        s = -3_s | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 5 | 6 ");
    {
        s = 7_s | 5 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 1 | 4 ");
    {
        s = 2_s | 1 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | 2 ");
    {
        s = 9 | _ | 2;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | -8 ");
    {
        s = _ | -2 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 5 ");
    {
        s = 2_s | 5;
        a = axis_iterator(10, s);
        gold = {2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 3 | -3 ");
    {
        s = 9_s | 3 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -3 | -4 ");
    {
        s = -9_s | -3 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -5 | 7 ");
    {
        s = -4_s | -5 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 6 | -6 ");
    {
        s = -8_s | 6 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 7 ");
    {
        s = 6_s | 7;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -7 | -10 ");
    {
        s = 2_s | -7 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -1 | -10 ");
    {
        s = -6_s | -1 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -3 | -7 ");
    {
        s = 8_s | -3 | -7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 7 ");
    {
        s = -8 | _ | 7;
        a = axis_iterator(10, s);
        gold = {2, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -5 | -7 ");
    {
        s = -10_s | -5 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | 4 ");
    {
        s = _ | 6 | 4;
        a = axis_iterator(10, s);
        gold = {0, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 9 | -10 ");
    {
        s = 4_s | 9 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 7 | -5 ");
    {
        s = -7_s | 7 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 8 | 6 ");
    {
        s = -2_s | 8 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ | -8 ");
    {
        s = -6 | _ | -8;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 2 | 5 ");
    {
        s = 7_s | 2 | 5;
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

    INFO(" 7 | _ | 6 ");
    {
        s = 7 | _ | 6;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | 8 ");
    {
        s = _ | -8 | 8;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | -4 ");
    {
        s = _ | -2 | -4;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -6 | 9 ");
    {
        s = -1_s | -6 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -4 | 2 ");
    {
        s = 0_s | -4 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 0 | 8 ");
    {
        s = -4_s | 0 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 2 | -4 ");
    {
        s = 3_s | 2 | -4;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -8 ");
    {
        s = _ | _ | -8;
        a = axis_iterator(10, s);
        gold = {9, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 8 ");
    {
        s = _ | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 7 | 3 ");
    {
        s = -9_s | 7 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 8 ");
    {
        s = 2_s | 8;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -6 ");
    {
        s = 0 | _ | -6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 4 ");
    {
        s = _ | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -8 | -7 ");
    {
        s = -10_s | -8 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -6 ");
    {
        s = -4 | _ | -6;
        a = axis_iterator(10, s);
        gold = {6, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -5 ");
    {
        s = -8_s | -5;
        a = axis_iterator(10, s);
        gold = {2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | -8 ");
    {
        s = _ | 6 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 0 | -1 ");
    {
        s = -7_s | 0 | -1;
        a = axis_iterator(10, s);
        gold = {3, 2, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -5 | -4 ");
    {
        s = -8_s | -5 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -5 | -9 ");
    {
        s = 2_s | -5 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | -4 ");
    {
        s = 9 | _ | -4;
        a = axis_iterator(10, s);
        gold = {9, 5, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 9 ");
    {
        s = -2_s | 9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 5 ");
    {
        s = -6_s | 5;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -4 | 2 ");
    {
        s = -10_s | -4 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 2 | -1 ");
    {
        s = -5_s | 2 | -1;
        a = axis_iterator(10, s);
        gold = {5, 4, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 6 | -7 ");
    {
        s = -6_s | 6 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | -10 ");
    {
        s = 4 | _ | -10;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 0 ");
    {
        s = -9_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 3 ");
    {
        s = -8 | _ | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 9 ");
    {
        s = -8 | _ | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 8 ");
    {
        s = _ | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | -8 ");
    {
        s = _ | 6 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -8 | 3 ");
    {
        s = -3_s | -8 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | -7 ");
    {
        s = -4_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7 | _ | 6 ");
    {
        s = 7 | _ | 6;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -5 | 8 ");
    {
        s = -8_s | -5 | 8;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 8 | -8 ");
    {
        s = -9_s | 8 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -9 ");
    {
        s = -3 | _ | -9;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 5 | -2 ");
    {
        s = 4_s | 5 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 3 | -8 ");
    {
        s = -5_s | 3 | -8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -3 | 3 ");
    {
        s = 1_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {1, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -7 | 4 ");
    {
        s = -9_s | -7 | 4;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 ");
    {
        s = _ | -1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 9 ");
    {
        s = 0 | _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 9 ");
    {
        s = -8_s | 9;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ ");
    {
        s = -2 | _;
        a = axis_iterator(10, s);
        gold = {8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 1 | -1 ");
    {
        s = 7_s | 1 | -1;
        a = axis_iterator(10, s);
        gold = {7, 6, 5, 4, 3, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -1 | -2 ");
    {
        s = 4_s | -1 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -8 ");
    {
        s = _ | _ | -8;
        a = axis_iterator(10, s);
        gold = {9, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -9 ");
    {
        s = _ | 9 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 8 | -5 ");
    {
        s = -4_s | 8 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ | 8 ");
    {
        s = -7 | _ | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | 3 ");
    {
        s = _ | 9 | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | 1 ");
    {
        s = _ | 6 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -4 | -6 ");
    {
        s = 1_s | -4 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -1 | 5 ");
    {
        s = -5_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -5 ");
    {
        s = -8_s | -5;
        a = axis_iterator(10, s);
        gold = {2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -7 ");
    {
        s = 5_s | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -2 | 7 ");
    {
        s = 8_s | -2 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 9 ");
    {
        s = _ | _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 4 ");
    {
        s = 3_s | 4;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | -3 ");
    {
        s = _ | 5 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -6 | -8 ");
    {
        s = _ | -6 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -2 ");
    {
        s = _ | _ | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -10 | -7 ");
    {
        s = 7_s | -10 | -7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | -2 ");
    {
        s = _ | 3 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 | 8 ");
    {
        s = _ | -9 | 8;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 5 ");
    {
        s = 1_s | 5;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ | 3 ");
    {
        s = 8 | _ | 3;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 9 | 5 ");
    {
        s = -1_s | 9 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 3 | -8 ");
    {
        s = 9_s | 3 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -5 ");
    {
        s = 9_s | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 9 | 8 ");
    {
        s = -7_s | 9 | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -3 | -1 ");
    {
        s = 2_s | -3 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -6 ");
    {
        s = 9_s | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ | 8 ");
    {
        s = -7 | _ | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 1 | 7 ");
    {
        s = -5_s | 1 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -9 | 8 ");
    {
        s = 7_s | -9 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 9 | 3 ");
    {
        s = 2_s | 9 | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -1 | -4 ");
    {
        s = -10_s | -1 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 6 ");
    {
        s = -9_s | 6;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -8 | 8 ");
    {
        s = 2_s | -8 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 | 5 ");
    {
        s = _ | 4 | 5;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 9 ");
    {
        s = _ | _ | 9;
        a = axis_iterator(10, s);
        gold = {0, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -3 | 2 ");
    {
        s = -5_s | -3 | 2;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 6 ");
    {
        s = -2_s | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -2 | 4 ");
    {
        s = -3_s | -2 | 4;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 0 ");
    {
        s = -3_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | 0 ");
    {
        s = -7_s | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -3 | -2 ");
    {
        s = 0_s | -3 | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ | 6 ");
    {
        s = 8 | _ | 6;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 | -5 ");
    {
        s = _ | 4 | -5;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 8 | 9 ");
    {
        s = -8_s | 8 | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | -9 ");
    {
        s = -5 | _ | -9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -8 ");
    {
        s = 1_s | -8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -3 | -4 ");
    {
        s = -7_s | -3 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -6 ");
    {
        s = -8_s | -6;
        a = axis_iterator(10, s);
        gold = {2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | -1 ");
    {
        s = 5 | _ | -1;
        a = axis_iterator(10, s);
        gold = {5, 4, 3, 2, 1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 4 | -1 ");
    {
        s = -5_s | 4 | -1;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -5 | _ | 4 ");
    {
        s = -5 | _ | 4;
        a = axis_iterator(10, s);
        gold = {5, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -5 | 6 ");
    {
        s = 1_s | -5 | 6;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 8 | -5 ");
    {
        s = -2_s | 8 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -8 | 4 ");
    {
        s = 3_s | -8 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ | -5 ");
    {
        s = 1 | _ | -5;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 5 | 6 ");
    {
        s = _ | 5 | 6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 3 ");
    {
        s = -4_s | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -9 | -10 ");
    {
        s = -6_s | -9 | -10;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 3 | _ | 8 ");
    {
        s = 3 | _ | 8;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | 6 ");
    {
        s = 5 | _ | 6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 6 | -6 ");
    {
        s = 3_s | 6 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -2 | 3 ");
    {
        s = -10_s | -2 | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -1 ");
    {
        s = 5_s | -1;
        a = axis_iterator(10, s);
        gold = {5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 8 | _ | 9 ");
    {
        s = 8 | _ | 9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -10 | 8 ");
    {
        s = -8_s | -10 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -5 | 6 ");
    {
        s = -7_s | -5 | 6;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 8 | 7 ");
    {
        s = -3_s | 8 | 7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -7 ");
    {
        s = 4_s | 2 | -7;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | 8 ");
    {
        s = 9 | _ | 8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ | -9 ");
    {
        s = 2 | _ | -9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | 6 ");
    {
        s = -9_s | 6;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ | -3 ");
    {
        s = -6 | _ | -3;
        a = axis_iterator(10, s);
        gold = {4, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 0 | -4 ");
    {
        s = 9_s | 0 | -4;
        a = axis_iterator(10, s);
        gold = {9, 5, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -1 ");
    {
        s = -7_s | -1;
        a = axis_iterator(10, s);
        gold = {3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -8 | -5 ");
    {
        s = 6_s | -8 | -5;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 4 ");
    {
        s = _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -3 | -8 ");
    {
        s = -9_s | -3 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -4 ");
    {
        s = -8_s | -4;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 2 | _ | -10 ");
    {
        s = 2 | _ | -10;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -10 ");
    {
        s = -3 | _ | -10;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ ");
    {
        s = -2 | _;
        a = axis_iterator(10, s);
        gold = {8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -6 | -4 ");
    {
        s = _ | -6 | -4;
        a = axis_iterator(10, s);
        gold = {9, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 7 | -6 ");
    {
        s = -2_s | 7 | -6;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ | -8 ");
    {
        s = -9 | _ | -8;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 | -2 ");
    {
        s = _ | -4 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | -6 ");
    {
        s = 6 | _ | -6;
        a = axis_iterator(10, s);
        gold = {6, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -3 | -7 ");
    {
        s = -2_s | -3 | -7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | -8 | 2 ");
    {
        s = -3_s | -8 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | -2 ");
    {
        s = _ | 1 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -8 | -5 ");
    {
        s = 5_s | -8 | -5;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -9 | -7 ");
    {
        s = -6_s | -9 | -7;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -8 | 7 ");
    {
        s = 1_s | -8 | 7;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -5 | 6 ");
    {
        s = 5_s | -5 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 3 ");
    {
        s = -8 | _ | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 | -3 ");
    {
        s = _ | -1 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -5 ");
    {
        s = _ | 9 | -5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 7 | 3 ");
    {
        s = -1_s | 7 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -8 | -4 ");
    {
        s = 6_s | -8 | -4;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -4 | -8 ");
    {
        s = 4_s | -4 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -8 ");
    {
        s = 4_s | 2 | -8;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -6 | 4 ");
    {
        s = -1_s | -6 | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 8 ");
    {
        s = -8 | _ | 8;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 8 | 2 ");
    {
        s = 7_s | 8 | 2;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 0 | -10 ");
    {
        s = 3_s | 0 | -10;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 ");
    {
        s = _ | 0;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -4 | 2 ");
    {
        s = 9_s | -4 | 2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | -1 ");
    {
        s = -10 | _ | -1;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -5 | -3 ");
    {
        s = _ | -5 | -3;
        a = axis_iterator(10, s);
        gold = {9, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 2 | -8 ");
    {
        s = 5_s | 2 | -8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -8 ");
    {
        s = -3 | _ | -8;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 4 ");
    {
        s = -4_s | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -2 | 8 ");
    {
        s = 5_s | -2 | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 5 | _ | -6 ");
    {
        s = 5 | _ | -6;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | 6 ");
    {
        s = 1_s | 6;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | 1 | 9 ");
    {
        s = 0_s | 1 | 9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -10 | _ | -6 ");
    {
        s = -10 | _ | -6;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -9 | 6 ");
    {
        s = 4_s | -9 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3_s | 2 | -9 ");
    {
        s = -3_s | 2 | -9;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 5 ");
    {
        s = -4_s | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 7 | 1 ");
    {
        s = 4_s | 7 | 1;
        a = axis_iterator(10, s);
        gold = {4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -2 | -1 ");
    {
        s = 6_s | -2 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | 8 ");
    {
        s = _ | _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 3 | -1 ");
    {
        s = 5_s | 3 | -1;
        a = axis_iterator(10, s);
        gold = {5, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 ");
    {
        s = _ | 6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -2 | _ | 7 ");
    {
        s = -2 | _ | 7;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -3 | 5 ");
    {
        s = -6_s | -3 | 5;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 1 ");
    {
        s = -8_s | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -1 | 3 ");
    {
        s = -8_s | -1 | 3;
        a = axis_iterator(10, s);
        gold = {2, 5, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 0 | -3 ");
    {
        s = -8_s | 0 | -3;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 2 | 3 ");
    {
        s = _ | 2 | 3;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 0 | 7 ");
    {
        s = 4_s | 0 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ ");
    {
        s = -9 | _;
        a = axis_iterator(10, s);
        gold = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 3 ");
    {
        s = 0 | _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 3, 6, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 7 ");
    {
        s = 5_s | 7;
        a = axis_iterator(10, s);
        gold = {5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ ");
    {
        s = 0 | _;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ | 4 ");
    {
        s = 1 | _ | 4;
        a = axis_iterator(10, s);
        gold = {1, 5, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | -2 ");
    {
        s = 6 | _ | -2;
        a = axis_iterator(10, s);
        gold = {6, 4, 2, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -5 | 3 ");
    {
        s = -2_s | -5 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -2 | 5 ");
    {
        s = 0_s | -2 | 5;
        a = axis_iterator(10, s);
        gold = {0, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 2 | 9 ");
    {
        s = -8_s | 2 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ | -2 ");
    {
        s = 9 | _ | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | -3 ");
    {
        s = _ | 7 | -3;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | 5 ");
    {
        s = _ | -8 | 5;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4_s | 5 | -9 ");
    {
        s = -4_s | 5 | -9;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | _ | -9 ");
    {
        s = _ | _ | -9;
        a = axis_iterator(10, s);
        gold = {9, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 0 | 5 ");
    {
        s = -6_s | 0 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | -9 | -4 ");
    {
        s = -6_s | -9 | -4;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -8 ");
    {
        s = 4_s | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 | -8 ");
    {
        s = _ | -4 | -8;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 6 | -1 ");
    {
        s = 8_s | 6 | -1;
        a = axis_iterator(10, s);
        gold = {8, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -2 | -1 ");
    {
        s = -8_s | -2 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 8 ");
    {
        s = -8_s | 8;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | 7 ");
    {
        s = -3 | _ | 7;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 1 | -6 ");
    {
        s = 7_s | 1 | -6;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 6 | 8 ");
    {
        s = 9_s | 6 | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 0 | 1 ");
    {
        s = -2_s | 0 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -9 | -10 ");
    {
        s = 6_s | -9 | -10;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 0 | 3 ");
    {
        s = -2_s | 0 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 ");
    {
        s = _ | -3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -5 | 7 ");
    {
        s = 4_s | -5 | 7;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 1 | 6 ");
    {
        s = -6_s | 1 | 6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6 | _ | 9 ");
    {
        s = -6 | _ | 9;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | 1 ");
    {
        s = _ | -7 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -8 | 1 ");
    {
        s = -10_s | -8 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 9 | _ ");
    {
        s = 9 | _;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 8 ");
    {
        s = _ | 8;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 0 | 5 ");
    {
        s = 8_s | 0 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -1 ");
    {
        s = -8_s | -1;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 1 | 9 ");
    {
        s = -6_s | 1 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1 | _ | -4 ");
    {
        s = -1 | _ | -4;
        a = axis_iterator(10, s);
        gold = {9, 5, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 | -10 ");
    {
        s = _ | -8 | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -4 | -9 ");
    {
        s = 0_s | -4 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -8 | 3 ");
    {
        s = 7_s | -8 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 0 | 9 ");
    {
        s = 7_s | 0 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 7 | -7 ");
    {
        s = 9_s | 7 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -2 | 7 ");
    {
        s = 9_s | -2 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -9 ");
    {
        s = 9_s | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 8 | 5 ");
    {
        s = -1_s | 8 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -6 | -9 ");
    {
        s = 5_s | -6 | -9;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 9 | 4 ");
    {
        s = 5_s | 9 | 4;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -8 | -2 ");
    {
        s = -1_s | -8 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | -6 | 9 ");
    {
        s = -1_s | -6 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | -3 ");
    {
        s = -4 | _ | -3;
        a = axis_iterator(10, s);
        gold = {6, 3, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | -4 ");
    {
        s = _ | 1 | -4;
        a = axis_iterator(10, s);
        gold = {9, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | 8 ");
    {
        s = _ | -7 | 8;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | 4 ");
    {
        s = 8_s | 4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -2 ");
    {
        s = 0_s | -2;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ | -1 ");
    {
        s = -7 | _ | -1;
        a = axis_iterator(10, s);
        gold = {3, 2, 1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 9 | -7 ");
    {
        s = 4_s | 9 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -8 ");
    {
        s = _ | -8;
        a = axis_iterator(10, s);
        gold = {0, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 | -9 ");
    {
        s = _ | 6 | -9;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | -10 ");
    {
        s = _ | 9 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 7 | -9 ");
    {
        s = -6_s | 7 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 6 ");
    {
        s = _ | 6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 9 | 6 ");
    {
        s = _ | 9 | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | 0 | -1 ");
    {
        s = 6_s | 0 | -1;
        a = axis_iterator(10, s);
        gold = {6, 5, 4, 3, 2, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -9 ");
    {
        s = 0_s | -9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 5 | 2 ");
    {
        s = 4_s | 5 | 2;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | 7 ");
    {
        s = 5_s | 7;
        a = axis_iterator(10, s);
        gold = {5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 8 | -10 ");
    {
        s = -5_s | 8 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -1 | -6 ");
    {
        s = 7_s | -1 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -5 | -8 ");
    {
        s = 5_s | -5 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 0_s | -1 | 5 ");
    {
        s = 0_s | -1 | 5;
        a = axis_iterator(10, s);
        gold = {0, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 8 | 7 ");
    {
        s = -2_s | 8 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | -9 | 9 ");
    {
        s = 2_s | -9 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -7 | _ | -4 ");
    {
        s = -7 | _ | -4;
        a = axis_iterator(10, s);
        gold = {3};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -5 | 1 ");
    {
        s = -10_s | -5 | 1;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 8 | -1 ");
    {
        s = 7_s | 8 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 8 | -9 ");
    {
        s = 2_s | 8 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 ");
    {
        s = _ | 3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" 6 | _ | 1 ");
    {
        s = 6 | _ | 1;
        a = axis_iterator(10, s);
        gold = {6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -2 ");
    {
        s = 0 | _ | -2;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | 4 | -1 ");
    {
        s = 3_s | 4 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -4 | -9 ");
    {
        s = 3_s | -4 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 8_s | -2 | 5 ");
    {
        s = 8_s | -2 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 1 | -4 ");
    {
        s = -5_s | 1 | -4;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -6 ");
    {
        s = -10_s | -6;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -3 | -8 ");
    {
        s = -9_s | -3 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -8 | 1 ");
    {
        s = 7_s | -8 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -4 | -9 ");
    {
        s = _ | -4 | -9;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | -6 | 7 ");
    {
        s = 4_s | -6 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | 4 ");
    {
        s = _ | 3 | 4;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | 8 ");
    {
        s = -2_s | 8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 1 | _ | -1 ");
    {
        s = 1 | _ | -1;
        a = axis_iterator(10, s);
        gold = {1, 0};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -5 | -10 ");
    {
        s = 9_s | -5 | -10;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | 4 ");
    {
        s = 0 | _ | 4;
        a = axis_iterator(10, s);
        gold = {0, 4, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -6 | -4 ");
    {
        s = 3_s | -6 | -4;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 ");
    {
        s = _ | 7;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" 0 | _ | -7 ");
    {
        s = 0 | _ | -7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" -4 | _ | 6 ");
    {
        s = -4 | _ | 6;
        a = axis_iterator(10, s);
        gold = {6};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 | -2 ");
    {
        s = _ | -3 | -2;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | -7 | -8 ");
    {
        s = 7_s | -7 | -8;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 7 | -1 ");
    {
        s = 4_s | 7 | -1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 2_s | 4 | -6 ");
    {
        s = 2_s | 4 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -1_s | 2 | 9 ");
    {
        s = -1_s | 2 | 9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 ");
    {
        s = _ | -2;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -4 | -9 ");
    {
        s = -7_s | -4 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ | 3 ");
    {
        s = 4 | _ | 3;
        a = axis_iterator(10, s);
        gold = {4, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -7_s | -3 | 3 ");
    {
        s = -7_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {3, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -9 | _ | 4 ");
    {
        s = -9 | _ | 4;
        a = axis_iterator(10, s);
        gold = {1, 5, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -3 ");
    {
        s = _ | -3;
        a = axis_iterator(10, s);
        gold = {0, 1, 2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -6 | -9 ");
    {
        s = -10_s | -6 | -9;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7_s | 2 | -9 ");
    {
        s = 7_s | 2 | -9;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | 3 | 7 ");
    {
        s = 9_s | 3 | 7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 7 | _ | 8 ");
    {
        s = 7 | _ | 8;
        a = axis_iterator(10, s);
        gold = {7};

        CHECK( a.indices() == gold );
    }

    INFO(" 4 | _ ");
    {
        s = 4 | _;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8, 9};

        CHECK( a.indices() == gold );
    }

    INFO(" 1_s | -4 | -3 ");
    {
        s = 1_s | -4 | -3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -6_s | 9 | 1 ");
    {
        s = -6_s | 9 | 1;
        a = axis_iterator(10, s);
        gold = {4, 5, 6, 7, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | 6 | 8 ");
    {
        s = -5_s | 6 | 8;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -2 ");
    {
        s = -8_s | -2;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" -2_s | -8 | -9 ");
    {
        s = -2_s | -8 | -9;
        a = axis_iterator(10, s);
        gold = {8};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 3 | 7 ");
    {
        s = _ | 3 | 7;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -7 | -2 ");
    {
        s = _ | -7 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -2 | 7 ");
    {
        s = _ | -2 | 7;
        a = axis_iterator(10, s);
        gold = {0, 7};

        CHECK( a.indices() == gold );
    }

    INFO(" 6_s | -4 | 3 ");
    {
        s = 6_s | -4 | 3;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -5 | 5 ");
    {
        s = -9_s | -5 | 5;
        a = axis_iterator(10, s);
        gold = {1};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -9 | 1 ");
    {
        s = -5_s | -9 | 1;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 3_s | -4 | -6 ");
    {
        s = 3_s | -4 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -5_s | -3 | 3 ");
    {
        s = -5_s | -3 | 3;
        a = axis_iterator(10, s);
        gold = {5};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -9 ");
    {
        s = _ | -9;
        a = axis_iterator(10, s);
        gold = {0};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | -1 | -7 ");
    {
        s = _ | -1 | -7;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -3 | _ | -6 ");
    {
        s = -3 | _ | -6;
        a = axis_iterator(10, s);
        gold = {7, 1};

        CHECK( a.indices() == gold );
    }

    INFO(" 9_s | -2 ");
    {
        s = 9_s | -2;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 4_s | 2 | -3 ");
    {
        s = 4_s | 2 | -3;
        a = axis_iterator(10, s);
        gold = {4};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 0 | 5 ");
    {
        s = _ | 0 | 5;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 8 | 6 ");
    {
        s = _ | 8 | 6;
        a = axis_iterator(10, s);
        gold = {0, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | 5 | -6 ");
    {
        s = -8_s | 5 | -6;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" 5_s | -4 | -10 ");
    {
        s = 5_s | -4 | -10;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8_s | -3 ");
    {
        s = -8_s | -3;
        a = axis_iterator(10, s);
        gold = {2, 3, 4, 5, 6};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | 3 | 2 ");
    {
        s = -10_s | 3 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 7 | -7 ");
    {
        s = _ | 7 | -7;
        a = axis_iterator(10, s);
        gold = {9};

        CHECK( a.indices() == gold );
    }

    INFO(" _ | 1 | -2 ");
    {
        s = _ | 1 | -2;
        a = axis_iterator(10, s);
        gold = {9, 7, 5, 3};

        CHECK( a.indices() == gold );
    }

    INFO(" -10_s | -1 | 2 ");
    {
        s = -10_s | -1 | 2;
        a = axis_iterator(10, s);
        gold = {0, 2, 4, 6, 8};

        CHECK( a.indices() == gold );
    }

    INFO(" -9_s | -3 | -8 ");
    {
        s = -9_s | -3 | -8;
        a = axis_iterator(10, s);
        gold = {};

        CHECK( a.indices() == gold );
    }

    INFO(" -8 | _ | 9 ");
    {
        s = -8 | _ | 9;
        a = axis_iterator(10, s);
        gold = {2};

        CHECK( a.indices() == gold );
    }
*/
}

// :mode=c++:noTabs=true: