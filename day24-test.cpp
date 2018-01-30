
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "day24.h"
#include "main.h"

using namespace std;

class Day24Test : public ::testing::Test{};

TEST( Day24Test, ComponentConstruct ) {
    Component c1;
    Component c2{ 23, 34 };
    Component c3{ 123, 1 };

    ostringstream s1;
    s1 << c1;

    ostringstream s2;
    s2 << c2;

    ostringstream s3;
    s3 << c3;

    EXPECT_EQ( "0/0", s1.str() );
    EXPECT_EQ( "23/34", s2.str() );
    EXPECT_EQ( "123/1", s3.str() );
}

TEST( Day24Test, ComponentSetConstruct ) {
    ComponentSet set1;
    ComponentSet set2;
    ComponentSet set3;
    ComponentSet set4{ {2, 3}, {2, 1}, {2, 5} };

    set2.insert( { 1, 2 } );

    set3.insert( {10, 20} );
    set3.insert( {8, 8} );
    set3.insert( {15, 23} );

    ostringstream s1;
    s1 << set1;

    ostringstream s2;
    s2 << set2;

    ostringstream s3;
    s3 << set3;

    ostringstream s4;
    s4 << set4;

    EXPECT_EQ( "", s1.str() );
    EXPECT_EQ( "1/2\n", s2.str() );
    EXPECT_EQ( "8/8\n10/20\n15/23\n", s3.str() );
    EXPECT_EQ( "2/1\n2/3\n2/5\n", s4.str() );
}

TEST( Day24Test, ComponentSetCopyStrength1 ) {
    ComponentSet set1{
        {5, 3},
        {53, 5},
        {2, 7},
        {8, 7}
    };

    ComponentSet set2;

    set1.getCompatible( 5, set2 );

    ostringstream s2;
    s2 << set2;

    EXPECT_EQ( "5/3\n53/5\n", s2.str() );
}

TEST( Day24Test, ComponentSetCopyStrength2 ) {
    ComponentSet set1{
        {5, 3},
        {53, 5},
        {2, 7},
        {8, 7}
    };

    ComponentSet set2;

    set1.getCompatible( 50, set2 );

    ostringstream s2;
    s2 << set2;

    EXPECT_EQ( "", s2.str() );
}

TEST( Day24Test, PuzzleInputPart1 ) {
    ifstream is( "day24.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "1868\n", os.str() );
}

TEST( Day24Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "0/2\n";
    is << "2/2\n";
    is << "2/3\n";
    is << "3/4\n";
    is << "3/5\n";
    is << "0/1\n";
    is << "10/1\n";
    is << "9/10\n";

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "31\n", os.str() );
}

TEST( Day24Test, PuzzleInputPart2 ) {
    ifstream is( "day24.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1841\n", os.str() );
}

TEST( Day24Test, Description2_1 ) {
    stringstream is;
    ostringstream os;

    is << "0/2\n";
    is << "2/2\n";
    is << "2/3\n";
    is << "3/4\n";
    is << "3/5\n";
    is << "0/1\n";
    is << "10/1\n";
    is << "9/10\n";

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "19\n", os.str() );
}

