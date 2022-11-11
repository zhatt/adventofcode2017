/*
 * Machine for day 18 and 23.
*/

#include <cassert>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Machine;
typedef std::map<std::string,int64_t> Registers;

struct MachineState {
    unsigned pc = 0;
    unsigned frequency;
    unsigned sndCount;
    bool waiting;
    bool waitForMessages;
    bool recovered;
    Registers registers;
    std::list<int64_t>& sendQ;
    std::list<int64_t>& receiveQ;

    MachineState( const Registers& registers, std::list<int64_t>& sq,
                  std::list<int64_t>& rq, bool wait ) :
        pc( 0 ),
        frequency( 0 ),
        sndCount( 0 ),
        waiting( false ),
        waitForMessages( wait ),
        recovered( false ),
        registers( registers ),
        sendQ( sq ),
        receiveQ( rq )
        {}

    void dump( std::ostream& os ) const {

        unsigned id = 0;
        const auto iter = registers.find( "p" );
        if ( iter != registers.end() ) {
            id = iter->second;
        }

        os << id << ":pc=" << this->pc << "\n";

        for ( const auto& val : this->registers ) {
            os << id << ":" << val.first << "=" << val.second << "\n";
        }
    }
};

// Day 18 uses register p as ID register.
const Registers registersId0 { { "p", 0 } };
const Registers registersId1 { { "p", 1 } };
// Day 23 uses register a as debug enable register.
const Registers registersDebugOn  { { "a", 0 } };
const Registers registersDebugOff { { "a", 1 } };

class Instruction {
    unsigned numReg_;
    std::string xregim_;
    std::string yregim_;

    public:
    Instruction() :
                 numReg_( 0 ) {}

    Instruction( std::string x ) :
                 numReg_( 1 ), xregim_( x ) {}

    Instruction(  std::string x, std::string y ) :
                 numReg_( 2 ), xregim_( x ), yregim_( y ) {}

    virtual ~Instruction() = default;

    virtual void execute( MachineState& machine ) = 0;

    private:
    int64_t val( const std::string& v,
                 const std::map<std::string,int64_t>& registers ) {
        std::istringstream parser( v );
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
    int64_t xval( const std::map<std::string,int64_t>& registers ) {
        assert( numReg_ >= 1 );
        return val( xregim_, registers );
    }

    int64_t yval( const std::map<std::string,int64_t>& registers ) {
        assert( numReg_ >= 2 );
        return val( yregim_, registers );
    }

    std::string xregName() {
        assert( numReg_ >= 1 );
        return xregim_;
    }
};


class Add : public Instruction {
    public:
    Add( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] += yval( state.registers );
        state.pc ++;
    }
};

class Sub : public Instruction {
    public:
    Sub( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] -= yval( state.registers );
        state.pc ++;
    }
};

class Jgz : public Instruction {
    public:
    Jgz( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        if ( xval( state.registers ) > 0 ) {
            state.pc += yval( state.registers );
        } else {
            state.pc ++;
        }
    }
};

class Jnz : public Instruction {
    public:
    Jnz( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        if ( xval( state.registers ) != 0 ) {
            state.pc += yval( state.registers );
        } else {
            state.pc ++;
        }
    }
};

class Mod : public Instruction {
    public:
    Mod( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] %= yval( state.registers );
        state.pc ++;
    }
};

class Mul : public Instruction {
    public:
    Mul( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] *= yval( state.registers );
        state.pc ++;
        count ++;
    }

    static unsigned getCount() { return count; }

    private:
    static unsigned count;
};

unsigned Mul::count;

class Set : public Instruction {
    public:
    Set( std::string x, std::string y ) : Instruction( x, y ) {}

    virtual void execute( MachineState& state ) override {
        state.registers[ xregName() ] = yval( state.registers );
        state.pc ++;
    }
};

class Rcv : public Instruction {
    public:
    Rcv( std::string x ) : Instruction( x ) {}

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
    Snd( std::string x ) : Instruction( x ) {}

    virtual void execute( MachineState& state ) override {
        int64_t message = xval( state.registers );
        state.frequency = message;
        state.sendQ.push_back( message );
        state.sndCount++;
        state.pc++;
    }
};

class Dmp : public Instruction {
    std::ostream& os_;
    public:
    Dmp( std::ostream& os ) : Instruction(), os_(os) {}

    virtual void execute( MachineState& state ) override {

        state.dump( os_ );

        state.pc ++;
    }
};

struct Program : std::vector<Instruction*> {

    Program( std::istream& is, std::ostream& os ) {
        std::string line;
        while ( getline( is, line ) ) {
            std::istringstream parser( line );

            std::string cmd;
            std::string val1, val2;

            parser >> cmd;
            parser >> val1;
            parser >> val2;

            if ( cmd == "snd" ) {
                push_back( new Snd( val1 ) );
            } else if ( cmd == "set" ) {
                push_back( new Set( val1, val2 ) );
            } else if ( cmd == "add" ) {
                push_back( new Add( val1, val2 ) );
            } else if ( cmd == "sub" ) {
                push_back( new Sub( val1, val2 ) );
            } else if ( cmd == "mul" ) {
                push_back( new Mul( val1, val2 ) );
            } else if ( cmd == "mod" ) {
                push_back( new Mod( val1, val2 ) );
            } else if ( cmd == "rcv" ) {
                push_back( new Rcv( val1 ) );
            } else if ( cmd == "jgz" ) {
                push_back( new Jgz( val1, val2 ) );
            } else if ( cmd == "jnz" ) {
                push_back( new Jnz( val1, val2 ) );
            } else if ( cmd == "dmp" ) {
                push_back( new Dmp( os ) );
            } else {
                assert( !"Unknown instruction" );
            }
        }
    }

};

class Machine {
    MachineState state_;
    const std::vector<Instruction*>& program_;

public:
    Machine ( const Registers& initialRegisters, std::list<int64_t>& sendQ,
              std::list<int64_t>& receiveQ,
              const Program& program,
              bool wait=true ) :
        state_( initialRegisters, sendQ, receiveQ, wait ),
        program_( program ) {}

    bool recovered() { return state_.recovered; }

    bool pastEnd() { return state_.pc >= program_.size(); }

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

    int64_t getReg( const std::string& reg ) {
        // FIXME create register.
        return state_.registers[ reg ];
    }

    void dump( std::ostream& os ) const {
        return state_.dump( os );
    }
};

