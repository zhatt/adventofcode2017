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
*/

#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "main.h"

using namespace std;

class nullbuf : public std::streambuf
{
public:
  int overflow(int c) { return c; }
};

nullbuf null_buffer;
std::ostream trace(&null_buffer);


class Machine;

struct MachineState {
    unsigned pc = 0;
    unsigned frequency;
    bool recovered;
    map<string,int64_t> registers;

    MachineState() :
        pc( 0 ),
        frequency( 0 ),
        recovered( false)
        {}
};

class Instruction {
    string dreg_;
    string sregim_;

    public:
    Instruction( string dreg, string sregim ) :
                 dreg_( dreg ), sregim_( sregim ) {}

    virtual void execute( MachineState& machine ) = 0;

    string dreg() { return dreg_; }

    int64_t rval( const map<string,int64_t>& registers ) {
        istringstream parser( sregim_ );
        int value;

        if ( parser >> value ) {
            return value;
        } else {
            auto iter = registers.find( sregim_ );
            if ( iter != registers.end() ) {
                return iter->second;
            } else {
                return 0;
            }
        }
    }
};


class Machine {
    MachineState state_;
    vector<Instruction*> program_;

public:

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
};

class Add : public Instruction {
    public:
    Add( string dreg, string sregim ) : Instruction( dreg, sregim ) {}

    virtual void execute( MachineState& state ) override {
        long int result = state.registers[ dreg() ] + rval( state.registers );
        trace << "Add: " << result << endl;
        state.registers[ dreg() ] += rval( state.registers );
        state.pc ++;
    }
};

class Jgz : public Instruction {
    public:
    Jgz( string dreg, string sregim ) : Instruction( dreg, sregim ) {}

    virtual void execute( MachineState& state ) override {
        if ( state.registers[ dreg() ] > 0 ) {
            trace << "Jump:" << rval( state.registers ) << endl;
            state.pc += rval( state.registers );
        } else {
            state.pc ++;
        }
    }
};

class Mod : public Instruction {
    public:
    Mod( string dreg, string sregim ) : Instruction( dreg, sregim ) {}

    virtual void execute( MachineState& state ) override {
        long int result = state.registers[ dreg() ] % rval( state.registers );
        trace << "Mod: " << result << endl;

        state.registers[ dreg() ] %= rval( state.registers );
        state.pc ++;
    }
};

class Mul : public Instruction {
    public:
    Mul( string dreg, string sregim ) : Instruction( dreg, sregim ) {}

    virtual void execute( MachineState& state ) override {
        long int result = state.registers[ dreg() ] * rval( state.registers );
        trace << "Mul: " << result << endl;

        state.registers[ dreg() ] *= rval( state.registers );
        state.pc ++;
    }
};

class Set : public Instruction {
    public:
    Set( string dreg, string sregim ) : Instruction( dreg, sregim ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ dreg() ] = rval( state.registers );
        state.pc ++;
    }
};

class Rcv : public Instruction {
    public:
    Rcv( string sregim ) : Instruction( "", sregim ) {}

    virtual void execute( MachineState& state ) override {
        trace << "Recover:" << rval( state.registers ) << " " << state.frequency << endl;

        if ( rval( state.registers ) ) {
            state.recovered = true;
        }
        state.pc ++;
    }
};

class Snd : public Instruction {
    public:
    Snd( string sregim ) : Instruction( "", sregim ) {}

    virtual void execute( MachineState& state ) override {
        trace << "Play:" << rval( state.registers ) << endl;
        state.frequency = rval( state.registers );
        state.pc++;
    }
};


int mainfunc( istream& is, ostream& os, Part part ) {

    Machine machine;

    string line;
    while ( getline( is, line ) ) {
        istringstream parser( line );

        string cmd;
        string val1, val2;

        parser >> cmd;
        parser >> val1;
        parser >> val2;

        if ( cmd == "snd" ) {
            machine.addInstruction( new Snd( val1 ) );
        } else if ( cmd == "set" ) {
            machine.addInstruction( new Set( val1, val2 ) );
        } else if ( cmd == "add" ) {
            machine.addInstruction( new Add( val1, val2 ) );
        } else if ( cmd == "mul" ) {
            machine.addInstruction( new Mul( val1, val2 ) );
        } else if ( cmd == "mod" ) {
            machine.addInstruction( new Mod( val1, val2 ) );
        } else if ( cmd == "rcv" ) {
            machine.addInstruction( new Rcv( val1 ) );
        } else if ( cmd == "jgz" ) {
            machine.addInstruction( new Jgz( val1, val2 ) );
        } else {
            assert( !"Unknown instruction" );
        }
    }

    while( ! machine.recovered() ) {
        machine.execute();
    }

    os << machine.frequency() << endl;

    return 0;
}
