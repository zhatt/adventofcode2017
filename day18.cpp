/*
--- Day 18: Duet ---
You discover a tablet containing some strange assembly code labeled simply
"Duet". Rather than bother the sound card with it, you decide to run the
code yourself. Unfortunately, you don't see any documentation, so you're
left to figure out what the instructions mean on your own.

It seems like the assembly is meant to operate on a set of registers that
are each named with a single letter and that can each hold a single
integer. You suppose each register should start with a value of 0.

There aren't that many instructions, so it shouldn't be hard to figure out
what they do. Here's what you determine:

  - snd X plays a sound with a frequency equal to the value of X.
  - set X Y sets register X to the value of Y.
  - add X Y increases register X by the value of Y.
  - mul X Y sets register X to the result of multiplying the value
    contained in register X by the value of Y.
  - mod X Y sets register X to the remainder of dividing the value
    contained in register X by the value of Y (that is, it sets X to the
    result of X modulo Y).
  - rcv X recovers the frequency of the last sound played, but only when
    the value of X is not zero. (If it is zero, the command does nothing.)
  - jgz X Y jumps with an offset of the value of Y, but only if the value
    of X is greater than zero. (An offset of 2 skips the next instruction,
    an offset of -1 jumps to the previous instruction, and so on.)

Many of the instructions can take either a register (a single letter) or a
number. The value of a register is the integer it contains; the value of a
number is that number.

After each jump instruction, the program continues with the instruction to
which the jump jumped. After any other instruction, the program continues
with the next instruction. Continuing (or jumping) off either end of the
program terminates it.

For example:

set a 1
add a 2
mul a a
mod a 5
snd a
set a 0
rcv a
jgz a -1
set a 1
jgz a -2

  - The first four instructions set a to 1, add 2 to it, square it, and
    then set it to itself modulo 5, resulting in a value of 4.
  - Then, a sound with frequency 4 (the value of a) is played.
  - After that, a is set to 0, causing the subsequent rcv and jgz
    instructions to both be skipped (rcv because a is 0, and jgz because a
    is not greater than 0).
  - Finally, a is set to 1, causing the next jgz instruction to activate,
    jumping back two instructions to another jump, which jumps again to
    the rcv, which ultimately triggers the recover operation.

At the time the recover operation is executed, the frequency of the last
sound played is 4.

What is the value of the recovered frequency (the value of the most
recently played sound) the first time a rcv instruction is executed with a
non-zero value?

--- Part Two ---

As you congratulate yourself for a job well done, you notice that the
documentation has been on the back of the tablet this entire time. While
you actually got most of the instructions correct, there are a few key
differences. This assembly code isn't about sound at all - it's meant to be
run twice at the same time.

Each running copy of the program has its own set of registers and follows
the code independently - in fact, the programs don't even necessarily run
at the same speed. To coordinate, they use the send (snd) and receive (rcv)
instructions:

  - snd X sends the value of X to the other program. These values wait in
    a queue until that program is ready to receive them. Each program has
    its own message queue, so a program can never receive a message it
    sent.

  - rcv X receives the next value and stores it in register X. If no
    values are in the queue, the program waits for a value to be sent to
    it. Programs do not continue to the next instruction until they have
    received a value. Values are received in the order they are sent.

Each program also has its own program ID (one 0 and the other 1); the
register p should begin with this value.

For example:

snd 1
snd 2
snd p
rcv a
rcv b
rcv c
rcv d

Both programs begin by sending three values to the other. Program 0 sends
1, 2, 0; program 1 sends 1, 2, 1. Then, each program receives a value (both
1) and stores it in a, receives another value (both 2) and stores it in b,
and then each receives the program ID of the other program (program 0
receives 1; program 1 receives 0) and stores it in c. Each program now sees
a different value in its own copy of register c.

Finally, both programs try to rcv a fourth time, but no data is waiting for
either of them, and they reach a deadlock. When this happens, both programs
terminate.

It should be noted that it would be equally valid for the programs to run
at different speeds; for example, program 0 might have sent all three
values and then stopped at the first rcv before program 1 executed even its
first instruction.

Once both of your programs have terminated (regardless of what caused them
to do so), how many times did program 1 send a value?
*/

#include <cassert>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "main.h"

using namespace std;

class Machine;

struct MachineState {
    const unsigned id;
    unsigned pc = 0;
    unsigned frequency;
    unsigned sndCount;
    bool waiting;
    bool waitForMessages;
    bool recovered;
    map<string,int64_t> registers;
    list<int64_t>& sendQ;
    list<int64_t>& receiveQ;

    MachineState( unsigned idnum, list<int64_t>& sq, list<int64_t>& rq, bool wait ) :
        id( idnum ),
        pc( 0 ),
        frequency( 0 ),
        sndCount( 0 ),
        waiting( false ),
        waitForMessages( wait ),
        recovered( false ),
        sendQ( sq ),
        receiveQ( rq )
        {}
};

class Instruction {
    unsigned numReg_;
    string xregim_;
    string yregim_;

    public:
    Instruction() :
                 numReg_( 0 ) {}

    Instruction( string x ) :
                 numReg_( 1 ), xregim_( x ) {}

    Instruction( string x, string y ) :
                 numReg_( 2 ), xregim_( x ), yregim_( y ) {}

    virtual void execute( MachineState& machine ) = 0;

    private:
    int64_t val( const string& v, const map<string,int64_t>& registers ) {
        istringstream parser( v );
        int value;

        if ( parser >> value ) {
            return value;
        } else {
            auto iter = registers.find( v );
            if ( iter != registers.end() ) {
                return iter->second;
            } else {
                return 0;
            }
        }
    }

    public:
    int64_t xval( const map<string,int64_t>& registers ) {
        assert( numReg_ >= 1 );
        return val( xregim_, registers );
    }
    

    int64_t yval( const map<string,int64_t>& registers ) {
        assert( numReg_ >= 2 );
        return val( yregim_, registers );
    }

    string xregName() {
        assert( numReg_ >= 1 );
        return xregim_;
    }
};


class Machine {
    MachineState state_;
    vector<Instruction*> program_;

public:
    Machine ( unsigned id, list<int64_t>& sendQ, list<int64_t>& receiveQ,
              bool wait ) :
        state_( id, sendQ, receiveQ, wait ) {
            state_.registers["p"] = id;
        }

    void addInstruction( Instruction* instruction ) {
        program_.push_back( instruction );
    }

    bool recovered() { return state_.recovered; }

    void execute() {
        assert( program_.size() > state_.pc );
        program_[ state_.pc ]->execute( state_ );
    }

    unsigned frequency() {
        return state_.frequency;
    }

    bool waiting() {
        return state_.waiting;
    }

    unsigned sndCount() {
        return state_.sndCount;
    }

    unsigned pc() {
        return state_.pc;
    }
};

class Add : public Instruction {
    public:
    Add( string x, string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] += yval( state.registers );
        state.pc ++;
    }
};

class Jgz : public Instruction {
    public:
    Jgz( string x, string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        if ( xval( state.registers ) > 0 ) {
            state.pc += yval( state.registers );
        } else {
            state.pc ++;
        }
    }
};

class Mod : public Instruction {
    public:
    Mod( string x, string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] %= yval( state.registers );
        state.pc ++;
    }
};

class Mul : public Instruction {
    public:
    Mul( string x, string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] *= yval( state.registers );
        state.pc ++;
    }
};

class Set : public Instruction {
    public:
    Set( string x, string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] = yval( state.registers );
        state.pc ++;
    }
};

class Rcv : public Instruction {
    public:
    Rcv( string x ) : Instruction( x ) {}

    virtual void execute( MachineState& state ) override {
        // In part 1 the argument is a source.  Check its value.
        if ( xval( state.registers ) ) {
            state.recovered = true;
        }
        if ( state.receiveQ.size() ) {
            int64_t message = state.receiveQ.front();
            state.registers[ xregName() ] = message;
            state.receiveQ.pop_front();
            state.waiting = false;
            state.pc ++;
        } else {
            if ( state.waitForMessages ) {
                state.waiting = true;
            } else {
                state.pc++;
            }
        }
    }
};

class Snd : public Instruction {
    public:
    Snd( string x ) : Instruction( x ) {}

    virtual void execute( MachineState& state ) override {
        int64_t message = xval( state.registers );
        state.frequency = message;
        state.sendQ.push_back( message );
        state.sndCount++;
        state.pc++;
    }
};

class Dmp : public Instruction {
    ostream& os_;
    public:
    Dmp( ostream& os ) : Instruction(), os_(os) {}

    virtual void execute( MachineState& state ) override {
        os_ << state.id << ":pc=" << state.pc << "\n";

        for ( const auto& val : state.registers ) {
            os_ << state.id << ":" << val.first << "=" << val.second << "\n";
        }

        state.pc ++;
    }
};

int mainfunc( istream& is, ostream& os, Part part ) {

    list<int64_t> q01, q10;
    Machine machine0( 0, q01, q10, part == Part::PART1 ? false : true );
    Machine machine1( 1, q10, q01, true );

    string line;
    while ( getline( is, line ) ) {
        istringstream parser( line );

        string cmd;
        string val1, val2;

        parser >> cmd;
        parser >> val1;
        parser >> val2;

        if ( cmd == "snd" ) {
            machine0.addInstruction( new Snd( val1 ) );
            machine1.addInstruction( new Snd( val1 ) );
        } else if ( cmd == "set" ) {
            machine0.addInstruction( new Set( val1, val2 ) );
            machine1.addInstruction( new Set( val1, val2 ) );
        } else if ( cmd == "add" ) {
            machine0.addInstruction( new Add( val1, val2 ) );
            machine1.addInstruction( new Add( val1, val2 ) );
        } else if ( cmd == "mul" ) {
            machine0.addInstruction( new Mul( val1, val2 ) );
            machine1.addInstruction( new Mul( val1, val2 ) );
        } else if ( cmd == "mod" ) {
            machine0.addInstruction( new Mod( val1, val2 ) );
            machine1.addInstruction( new Mod( val1, val2 ) );
        } else if ( cmd == "rcv" ) {
            machine0.addInstruction( new Rcv( val1 ) );
            machine1.addInstruction( new Rcv( val1 ) );
        } else if ( cmd == "jgz" ) {
            machine0.addInstruction( new Jgz( val1, val2 ) );
            machine1.addInstruction( new Jgz( val1, val2 ) );
        } else if ( cmd == "dmp" ) {
            machine0.addInstruction( new Dmp( os ) );
            machine1.addInstruction( new Dmp( os ) );
        } else {
            assert( !"Unknown instruction" );
        }
    }


    if ( part == Part::PART1 ) {
        while( ! machine0.recovered() ) {
            machine0.execute();
        }

        os << machine0.frequency() << endl;

    } else {
        while( ! ( machine0.waiting() && machine1.waiting() ) ) {
            machine0.execute();
            machine1.execute();
        }

        os << machine1.sndCount() << endl;
    }

    return 0;
}
