
#include <gtest/gtest.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "machine.h"

using namespace std;

class MachineTest : public ::testing::Test {
    protected:

    /*
     * Simplified mainfunc similar to day 18 part 2.
     */
    void mainfunc( istream& is, ostream& os ) {

        const Program program( is, os );
        list<int64_t> q;

        Machine machine( registersId0, q, q, program );

        while( ! machine.waiting() ) {
            machine.execute();
        }
    }
};

TEST_F( MachineTest, Dmp ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=0\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, SetIm ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 1\n";
    is << "set b 2\n";
    is << "set p 3\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "3:pc=3\n";
    r << "3:a=1\n";
    r << "3:b=2\n";
    r << "3:p=3\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Set ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 1\n";
    is << "set b a\n";
    is << "set c 2\n";
    is << "set d c\n";
    is << "set c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=2\n";
    r << "0:d=2\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, SetNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -1\n";
    is << "set b -2\n";
    is << "set c a\n";
    is << "set d b\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=-1\n";
    r << "0:b=-2\n";
    r << "0:c=-1\n";
    r << "0:d=-2\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Add ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "add a 1\n";
    is << "add b a\n";
    is << "add c 2\n";
    is << "add d c\n";
    is << "add d a\n";
    is << "add d 8\n";
    is << "add c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=7\n";
    r << "0:a=1\n";
    r << "0:b=1\n";
    r << "0:c=4\n";
    r << "0:d=11\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, AddNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "add a 1\n";
    is << "add b -4\n";
    is << "add a b\n";
    is << "add b 4\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=-3\n";
    r << "0:b=0\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Sub ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "sub a 1\n"; // a = -1
    is << "sub b a\n"; // b = 1
    is << "sub c 2\n"; // c = -2
    is << "sub d c\n"; // d = 2
    is << "sub d a\n"; // d = 3
    is << "sub d 8\n"; // d = -5
    is << "sub c c\n"; // c = 0
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=7\n";
    r << "0:a=-1\n";
    r << "0:b=1\n";
    r << "0:c=0\n";
    r << "0:d=-5\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, SubNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "sub a 1\n";  // a = -1
    is << "sub b -4\n"; // b = 4
    is << "sub a b\n";  // a = -5
    is << "sub b 4\n";  // b = 0
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=-5\n";
    r << "0:b=0\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Mul ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 2\n";
    is << "set b 3\n";
    is << "set c 3\n";
    is << "set d 1\n";
    is << "mul a 5\n";
    is << "mul b a\n";
    is << "mul d a\n";
    is << "mul d a\n";
    is << "mul d 8\n";
    is << "mul c 3\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=10\n";
    r << "0:a=10\n";
    r << "0:b=30\n";
    r << "0:c=9\n";
    r << "0:d=800\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, MulNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -2\n";
    is << "set b 3\n";
    is << "set c -3\n";
    is << "mul a 5\n";
    is << "mul b -2\n";
    is << "mul c c\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:a=-10\n";
    r << "0:b=-6\n";
    r << "0:c=9\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Mod ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 20\n";
    is << "set b 30\n";
    is << "mod a 5\n";
    is << "mod b 8\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=0\n";
    r << "0:b=6\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, ModNeg ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a -20\n";
    is << "set b -30\n";
    is << "set c -30\n";
    is << "mod a 5\n";
    is << "mod b 8\n";
    is << "mod c -8\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:a=0\n";
    r << "0:b=-6\n";
    r << "0:c=-6\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, SndRcv1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "snd 20\n";
    is << "snd 30\n";
    is << "snd 40\n";
    is << "rcv x\n";
    is << "rcv y\n";
    is << "rcv z\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=6\n";
    r << "0:p=0\n";
    r << "0:x=20\n";
    r << "0:y=30\n";
    r << "0:z=40\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jgz1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=2\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jgz2 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 2\n";
    is << "add a 1\n";
    is << "jgz 1 1\n";
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=4\n";
    r << "0:a=1\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jgz3_negoffset ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "jgz 1 4\n";
    is << "dmp\n";
    is << "rcv x\n";
    is << "jgz 1 1\n";
    is << "add a 5\n";
    is << "jgz 1 -4\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=1\n";
    r << "0:a=5\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz1 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 0\n";
    is << "jnz 1 2\n";  // taken
    is << "add a 1\n";
    is << "jnz 1 2\n";  // taken
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=0\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz2 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 0\n";
    is << "jnz 0 2\n";  // taken
    is << "add a 1\n";
    is << "jnz 0 2\n";  // taken
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=2\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz3 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 0\n";
    is << "add a 1\n";
    is << "set b a\n";
    is << "sub b 10\n";
    is << "jnz b -3\n"; // taken 10 times
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=10\n";
    r << "0:b=0\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

TEST_F( MachineTest, Jnz4 ) {
    stringstream is;
    stringstream r;
    ostringstream os;

    is << "set a 0\n";
    is << "set b 2\n";
    is << "jnz 1 b\n";
    is << "add a 1\n";
    is << "add a 1\n";
    is << "dmp\n";
    is << "rcv x\n";

    r << "0:pc=5\n";
    r << "0:a=1\n";
    r << "0:b=2\n";
    r << "0:p=0\n";

    mainfunc( is, os );

    EXPECT_EQ( r.str(), os.str() );
}

