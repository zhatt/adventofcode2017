
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "day21.h"
#include "main.h"

using namespace std;

class Day21Test : public ::testing::Test{};

TEST_F( Day21Test, PuzzleInputPart1 ) {
    ifstream is( "day21.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART1 );

    EXPECT_EQ( "139\n", os.str() );
}

TEST_F( Day21Test, Description1_1 ) {
    stringstream is;
    ostringstream os;

    is << "../.# => ##./#../...\n";
    is << ".#./..#/### => #..#/..../..../#..#\n";

    simulate( is, os, Part::PART1, 2 );

    EXPECT_EQ( "12\n", os.str() );
}

TEST_F( Day21Test, Simple1_1 ) {
    stringstream is;
    ostringstream os;

    is << "#./.. => #../.../...\n";
    is << "../.. => .../.../...\n";
    is << ".#./..#/### => #.../..../..../....\n";
    is << "#../.../... => #.../..../..../....\n";
    is << ".../.../... => #.../..../..../....\n";

    simulate( is, os, Part::PART1, 5 );

    EXPECT_EQ( "9\n", os.str() );
}

TEST_F( Day21Test, PuzzleInputPart2 ) {
    ifstream is( "day21.input" );
    ostringstream os;

    mainfunc( is, os, Part::PART2 );

    EXPECT_EQ( "1857134\n", os.str() );
}

TEST( Pixels, Construct ) {
    Pixels p1 { "." };
    EXPECT_EQ( ".", p1.getString() );
    EXPECT_EQ( 1, p1.size() );

    Pixels p2 { "../.." };
    EXPECT_EQ( "../..", p2.getString() );
    EXPECT_EQ( 2, p2.size() );

    Pixels p3 { ".../.../..." };
    EXPECT_EQ( ".../.../...", p3.getString() );
    EXPECT_EQ( 3, p3.size() );

    Pixels p4 { "..../..../..../...." };
    EXPECT_EQ( "..../..../..../....", p4.getString() );
    EXPECT_EQ( 4, p4.size() );

    Pixels p5 { ".#../...#/..../#..." };
    EXPECT_EQ( ".#../...#/..../#...", p5.getString() );
    EXPECT_EQ( 4, p5.size() );
}

TEST( Pixels, Bad ) {
    EXPECT_THROW( Pixels p { "" }, std::invalid_argument );
    EXPECT_THROW( Pixels p { ".//." }, std::invalid_argument );
    EXPECT_THROW( Pixels p { ".../...../..../...."},
                  std::invalid_argument );
}

TEST( Pixels, MirrorHoriz ) {
    Pixels p1 { "a" };
    p1.mirrorHoriz();
    EXPECT_EQ( "a", p1.getString() );

    Pixels p2 { "ab/cd" };
    p2.mirrorHoriz();
    EXPECT_EQ( "cd/ab", p2.getString() );

    Pixels p3 { "abc/def/ghi" };
    p3.mirrorHoriz();
    EXPECT_EQ( "ghi/def/abc", p3.getString() );

    Pixels p4 { "abcd/efgh/ijkl/mnop" };
    p4.mirrorHoriz();
    EXPECT_EQ( "mnop/ijkl/efgh/abcd", p4.getString() );

    Pixels p5 { "abcde/fghij/klmno/pqrst/uvwxy" };
    p5.mirrorHoriz();
    EXPECT_EQ( "uvwxy/pqrst/klmno/fghij/abcde", p5.getString() );
}

TEST( Pixels, MirrorVert ) {
    Pixels p1 { "a" };
    p1.mirrorVert();
    EXPECT_EQ( "a", p1.getString() );

    Pixels p2 { "ab/cd" };
    p2.mirrorVert();
    EXPECT_EQ( "ba/dc", p2.getString() );

    Pixels p3 { "abc/def/ghi" };
    p3.mirrorVert();
    EXPECT_EQ( "cba/fed/ihg", p3.getString() );

    Pixels p4 { "abce/efgh/ijkl/mnop" };
    p4.mirrorVert();
    EXPECT_EQ(   "ecba/hgfe/lkji/ponm", p4.getString() );

    Pixels p5 { "abcde/fghij/klmno/pqrst/uvwxy" };
    p5.mirrorVert();
    EXPECT_EQ( "edcba/jihgf/onmlk/tsrqp/yxwvu", p5.getString() );
}

TEST( Pixels, RotateCCW ) {
    Pixels p1 { "a" };
    p1.rotateCCW();
    EXPECT_EQ( "a", p1.getString() );

    Pixels p2 { "ab/cd" };
    p2.rotateCCW();
    EXPECT_EQ( "bd/ac", p2.getString() );

    Pixels p3 { "abc/def/ghi" };
    p3.rotateCCW();
    EXPECT_EQ( "cfi/beh/adg", p3.getString() );

    Pixels p4 { "abcd/efgh/ijkl/mnop" };
    p4.rotateCCW();
    EXPECT_EQ( "dhlp/cgko/bfjn/aeim", p4.getString() );

    Pixels p5 { "abcde/fghij/klmno/pqrst/uvwxy" };
    p5.rotateCCW();
    EXPECT_EQ( "ejoty/dinsx/chmrw/bglqv/afkpu", p5.getString() );
}

TEST( Pixels, GetSubPixels ) {
    Pixels p4 { "abcd/efgh/ijkl/mnop" };

    Pixels ul( p4.getSubPixels( 0, 0, 2 ) );
    Pixels ur( p4.getSubPixels( 2, 0, 2 ) );
    Pixels ll( p4.getSubPixels( 0, 2, 2 ) );
    Pixels lr( p4.getSubPixels( 2, 2, 2 ) );

    EXPECT_EQ( "ab/ef", ul.getString() );
    EXPECT_EQ( "cd/gh", ur.getString() );
    EXPECT_EQ( "ij/mn", ll.getString() );
    EXPECT_EQ( "kl/op", lr.getString() );
}

TEST( Pixels, NumOnPixels ) {
    Pixels p5 { ".#../...#/..../#..." };
    EXPECT_EQ( 3, p5.numMatching( '#' ) );
}

TEST( Pixels, getRowString ) {
    Pixels p1 { "a" };
    EXPECT_EQ( "a", p1.getRowString( 0 ) );

    Pixels p2 { "ab/cd" };
    EXPECT_EQ( "ab", p2.getRowString( 0 ) );
    EXPECT_EQ( "cd", p2.getRowString( 1 ) );

    Pixels p3 { "abc/def/ghi" };
    EXPECT_EQ( "abc", p3.getRowString( 0 ) );
    EXPECT_EQ( "def", p3.getRowString( 1 ) );
    EXPECT_EQ( "ghi", p3.getRowString( 2 ) );

    Pixels p4 { "abcd/efgh/ijkl/mnop" };
    EXPECT_EQ( "abcd", p4.getRowString( 0 ) );
    EXPECT_EQ( "efgh", p4.getRowString( 1 ) );
    EXPECT_EQ( "ijkl", p4.getRowString( 2 ) );
    EXPECT_EQ( "mnop", p4.getRowString( 3 ) );

    Pixels p5 { "abcde/fghij/klmno/pqrst/uvwxy" };
    EXPECT_EQ( "abcde", p5.getRowString( 0 ) );
    EXPECT_EQ( "fghij", p5.getRowString( 1 ) );
    EXPECT_EQ( "klmno", p5.getRowString( 2 ) );
    EXPECT_EQ( "pqrst", p5.getRowString( 3 ) );
    EXPECT_EQ( "uvwxy", p5.getRowString( 4 ) );
}

TEST( Picture, print ) {

    {
    Picture pic{ { "a" } };
    stringstream s;
    s << pic;
    EXPECT_EQ( "a\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|a|\n", sd.str() );
    }

    {
    Picture pic{ { "ab/cd" } };
    stringstream s;
    s << pic;
    EXPECT_EQ( "ab\ncd\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|ab|\n|cd|\n", sd.str() );
    }

    {
    Picture pic{ { "abc/def/ghi" } };
    stringstream s;
    s << pic;
    EXPECT_EQ( "abc\ndef\nghi\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|abc|\n|def|\n|ghi|\n", sd.str() );
    }

    {
    Picture pic{ { "abcd/efgh/ijkl/mnop" } };
    stringstream s;
    s << pic;
    EXPECT_EQ( "abcd\nefgh\nijkl\nmnop\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|abcd|\n|efgh|\n|ijkl|\n|mnop|\n", sd.str() );
    }

    {
    Picture pic{ { "a" } };
    pic.resize( 2 );

    auto iter = pic.begin();
    iter->push_back( { "b" } );

    ++iter;
    iter->push_back( { "c" } );
    iter->push_back( { "d" } );

    stringstream s;
    s << pic;
    EXPECT_EQ( "ab\ncd\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|a|b|\n|c|d|\n", sd.str() );
    }

    {
    Picture pic{ { "ab/ef" } };
    pic.resize( 2 );

    auto iter = pic.begin();
    iter->push_back( { "cd/gh" } );

    ++iter;
    iter->push_back( { "ij/mn" } );
    iter->push_back( { "kl/op" } );

    stringstream s;
    s << pic;
    EXPECT_EQ( "abcd\nefgh\nijkl\nmnop\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|ab|cd|\n|ef|gh|\n|ij|kl|\n|mn|op|\n", sd.str() );
    }

    {
    Picture pic{ { "ab/gh" } };
    pic.resize( 3 );

    auto iter = pic.begin();
    iter->push_back( { "cd/ij" } );
    iter->push_back( { "ef/kl" } );

    ++iter;
    iter->push_back( { "mn/st" } );
    iter->push_back( { "op/uv" } );
    iter->push_back( { "qr/wx" } );

    ++iter;
    iter->push_back( { "yz/ef" } );
    iter->push_back( { "ab/gh" } );
    iter->push_back( { "cd/ij" } );

    stringstream s;
    s << pic;
    EXPECT_EQ( "abcdef\nghijkl\nmnopqr\nstuvwx\nyzabcd\nefghij\n", s.str() );
    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|ab|cd|ef|\n|gh|ij|kl|\n|mn|op|qr|\n|st|uv|wx|\n|yz|ab|cd|\n|ef|gh|ij|\n", sd.str() );
    }
}

TEST( Picture, Flatten ) {
    {
    Picture pic{ { "ab/gh" } };
    pic.resize( 3 );

    auto iter = pic.begin();
    iter->push_back( { "cd/ij" } );
    iter->push_back( { "ef/kl" } );

    ++iter;
    iter->push_back( { "mn/st" } );
    iter->push_back( { "op/uv" } );
    iter->push_back( { "qr/wx" } );

    ++iter;
    iter->push_back( { "yz/ef" } );
    iter->push_back( { "ab/gh" } );
    iter->push_back( { "cd/ij" } );

    pic.flatten();

    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|abcdef|\n|ghijkl|\n|mnopqr|\n|stuvwx|\n|yzabcd|\n|efghij|\n", sd.str() );
    }
}

TEST( Picture, Reduce2x2 ) {
    {
    Picture pic{ { "abcdef/ghijkl/mnopqr/stuvwx/yzabcd/efghij" } };

    pic.flatten();
    pic.reduce();

    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|ab|cd|ef|\n|gh|ij|kl|\n|mn|op|qr|\n|st|uv|wx|\n|yz|ab|cd|\n|ef|gh|ij|\n", sd.str() );
    }
}

TEST( Picture, Reduce3x3 ) {
    {
    Picture pic{ { "abcdefghi/"
                   "jklmnopqr/"
                   "stuvwxyza/"
                   "bcdefghij/"
                   "klmnopqrs/"
                   "tuvwxyzab/"
                   "cdefghijk/"
                   "lmnopqrst/"
                   "uvwxyzabc" } };

    pic.flatten();
    pic.reduce();

    stringstream sd;
    pic.print( sd, "|" );
    EXPECT_EQ( "|abc|def|ghi|\n"
               "|jkl|mno|pqr|\n"
               "|stu|vwx|yza|\n"
               "|bcd|efg|hij|\n"
               "|klm|nop|qrs|\n"
               "|tuv|wxy|zab|\n"
               "|cde|fgh|ijk|\n"
               "|lmn|opq|rst|\n"
               "|uvw|xyz|abc|\n", sd.str() );
    }
}
