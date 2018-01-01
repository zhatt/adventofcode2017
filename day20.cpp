/*
--- Day 20: Particle Swarm ---

Suddenly, the GPU contacts you, asking for help. Someone has asked it to
simulate too many particles, and it won't be able to finish them all in
time to render the next frame at this rate.

It transmits to you a buffer (your puzzle input) listing each particle in
order (starting with particle 0, then particle 1, particle 2, and so on).
For each particle, it provides the X, Y, and Z coordinates for the
particle's position (p), velocity (v), and acceleration (a), each in the
format <X,Y,Z>.

Each tick, all particles are updated simultaneously. A particle's
properties are updated in the following order:

  - Increase the X velocity by the X acceleration.
  - Increase the Y velocity by the Y acceleration.
  - Increase the Z velocity by the Z acceleration.
  - Increase the X position by the X velocity.
  - Increase the Y position by the Y velocity.
  - Increase the Z position by the Z velocity.

Because of seemingly tenuous rationale involving z-buffering, the GPU would
like to know which particle will stay closest to position <0,0,0> in the
long term. Measure this using the Manhattan distance, which in this
situation is simply the sum of the absolute values of a particle's X, Y,
and Z position.

For example, suppose you are only given two particles, both of which stay
entirely on the X-axis (for simplicity). Drawing the current states of
particles 0 and 1 (in that order) with an adjacent a number line and
diagram of current X positions (marked in parenthesis), the following would
take place:

p=< 3,0,0>, v=< 2,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 4,0,0>, v=< 0,0,0>, a=<-2,0,0>                         (0)(1)

p=< 4,0,0>, v=< 1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=< 2,0,0>, v=<-2,0,0>, a=<-2,0,0>                      (1)   (0)

p=< 4,0,0>, v=< 0,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-2,0,0>, v=<-4,0,0>, a=<-2,0,0>          (1)               (0)

p=< 3,0,0>, v=<-1,0,0>, a=<-1,0,0>    -4 -3 -2 -1  0  1  2  3  4
p=<-8,0,0>, v=<-6,0,0>, a=<-2,0,0>                         (0)   

At this point, particle 1 will never be closer to <0,0,0> than particle 0,
and so, in the long run, particle 0 will stay closest.

Which particle will stay closest to position <0,0,0> in the long term?

--- Part Two ---

To simplify the problem further, the GPU would like to remove any particles
that collide. Particles collide if their positions ever exactly match.
Because particles are updated simultaneously, more than two particles can
collide at the same time and place. Once particles collide, they are
removed and cannot collide with anything else after that tick.

For example:

p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>    (0)   (1)   (2)            (3)
p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=<-3,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=<-2,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=<-1,0,0>, v=< 1,0,0>, a=< 0,0,0>             (0)(1)(2)      (3)   
p=< 2,0,0>, v=<-1,0,0>, a=< 0,0,0>

p=< 0,0,0>, v=< 3,0,0>, a=< 0,0,0>    
p=< 0,0,0>, v=< 2,0,0>, a=< 0,0,0>    -6 -5 -4 -3 -2 -1  0  1  2  3
p=< 0,0,0>, v=< 1,0,0>, a=< 0,0,0>                       X (3)      
p=< 1,0,0>, v=<-1,0,0>, a=< 0,0,0>

------destroyed by collision------    
------destroyed by collision------    -6 -5 -4 -3 -2 -1  0  1  2  3
------destroyed by collision------                      (3)         
p=< 0,0,0>, v=<-1,0,0>, a=< 0,0,0>

In this example, particles 0, 1, and 2 are simultaneously destroyed at
the time and place marked X. On the next tick, particle 3 passes through
unharmed.

How many particles are left after all collisions are resolved?
*/

#include <algorithm>
#include <cassert>
#include <climits>
#include <iostream>
#include <list>
#include <sstream>

#include "main.h"

using namespace std;

class XYZ {
    int x_, y_, z_;

    friend ostream& operator<<( ostream& os, const XYZ& xyz );

    public:
    XYZ ( int x, int y, int z ) :
        x_( x ), y_( y ), z_( z ) {}

    int magnitude() const {
        long sum = abs(x_) + abs(y_) + abs(z_);

        if ( sum > INT_MAX ) {
            return INT_MAX;
        } else {
            return sum;
        }
    }

    bool operator==( const XYZ& other ) const {
        return x_ == other.x_ && y_ == other.y_ && z_ == other.z_;
    }

    XYZ& operator+=( const XYZ& other ) {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }

    static XYZ maxFactory() {
        return XYZ( INT_MAX, INT_MAX, INT_MAX );
    }

    static bool compare( const XYZ& a, const XYZ& b ) {
        if ( a.x_ < b.x_ ) return true;
        if ( a.x_ > b.x_ ) return false;
        // x ==
        if ( a.y_ < b.y_ ) return true;
        if ( a.y_ > b.y_ ) return false;
        // y == (and x == )
        if ( a.z_ < b.z_ ) return true;
        return false;
    }
};

ostream& operator<<( ostream& os, const XYZ& xyz ) {
    return os << "<" << xyz.x_ << "," << xyz.y_ << "," << xyz.z_ << ">";
}

class Particle {
    XYZ position_;
    XYZ velocity_;
    XYZ acceleration_;

    friend ostream& operator<<( ostream& os, const Particle& p );

    public:
    Particle ( XYZ p, XYZ v, XYZ a ) :
        position_( p ), velocity_( v ), acceleration_( a ) {}

    void step() {
        velocity_ += acceleration_;
        position_ += velocity_;
    }

    static bool comparePosition( const Particle& a, const Particle& b ) {
        return XYZ::compare( a.position_, b.position_ );
    }

    static bool comparePositionMagnitude( const Particle& a, const Particle& b ) {
        return a.position_.magnitude() < b.position_.magnitude();
    }

    static bool compareVelocityMagnitude( const Particle& a, const Particle& b ) {
        return a.velocity_.magnitude() < b.velocity_.magnitude();
    }

    static bool compareAccelerationMagnitude( const Particle& a, const Particle& b ) {
        return a.acceleration_.magnitude() < b.acceleration_.magnitude();
    }

    static bool equalPosition( const Particle& a, const Particle& b ) {
        return a.position_ == b.position_;
    }
};

ostream& operator<<( ostream& os, const Particle& p ) {
    return os << "p=" << p.position_ << "[" << p.position_.magnitude() << "], "
              << "v=" << p.velocity_ << "[" << p.velocity_.magnitude() << "], "
              << "a=" << p.acceleration_ << "[" << p.acceleration_.magnitude() << "]";
}

class ParticleList {
    list<Particle> particles_;
    unsigned initialMinimumAccelerationParticleNumber_ = 0;

    friend ostream& operator<<( ostream& os, const ParticleList& p );

    public:
    void load( istream& is ) {
        XYZ minimumAcceleration = XYZ::maxFactory();

        string line;

        unsigned particleNumber = 0;
        while ( getline( is, line ) ) {
            istringstream parser( line );

            int px, py, pz;
            parser.ignore( 100, '<' );  // p-<
            parser >> px;
            parser.ignore( 100, ',' );
            parser >> py;
            parser.ignore( 100, ',' );
            parser >> pz;
            assert( parser );

            int vx, vy, vz;
            parser.ignore( 100, '<' );  // v-<
            parser >> vx;
            parser.ignore( 100, ',' );
            parser >> vy;
            parser.ignore( 100, ',' );
            parser >> vz;
            assert( parser );

            int ax, ay, az;
            parser.ignore( 100, '<' );  // a-<
            parser >> ax;
            parser.ignore( 100, ',' );
            parser >> ay;
            parser.ignore( 100, ',' );
            parser >> az;
            assert( parser );

            XYZ newPosition( px, py, pz );
            XYZ newVelocity( vx, vy, vz );
            XYZ newAccel( ax, ay, az );

            particles_.push_back( Particle { newPosition, newVelocity, newAccel } );

            if ( newAccel.magnitude() < minimumAcceleration.magnitude() ) {
                minimumAcceleration = newAccel;
                initialMinimumAccelerationParticleNumber_ = particleNumber;
            } 

            particleNumber++;
        }
    }

    size_t initialMinimumAccelerationParticleNumber() {
        return initialMinimumAccelerationParticleNumber_;
    }

    size_t size() {
        return particles_.size();
    }

    void clean() {
        particles_.sort( Particle::comparePosition );
        auto begin = particles_.begin();
        while ( true ) {
            begin = adjacent_find( begin, particles_.end(),
                                   Particle::equalPosition );
            if ( begin == particles_.end() ) break;

            auto current = begin++;
            while ( begin != particles_.end() && 
                    Particle::equalPosition( *current, *begin ) ) {
                particles_.erase( begin++ );
            }
            particles_.erase( current );
        }
    }

    void next() {
        // Update positions.
        for ( auto& p : particles_ ) {
            p.step();
        }
    }

    bool isDone() {
        particles_.sort( Particle::comparePositionMagnitude );

        bool velocitysAreSorted = is_sorted(
            particles_.begin(),
            particles_.end(),
            Particle::compareVelocityMagnitude
        );

        if ( ! velocitysAreSorted ) return false;

        bool accelerationsAreSorted = is_sorted(
            particles_.begin(),
            particles_.end(),
            Particle::compareAccelerationMagnitude
        );

        if ( ! accelerationsAreSorted ) return false;

        return true;
    }
};

ostream& operator<<( ostream& os, const ParticleList& p ) {
    for ( const auto& p : p.particles_ ) {
        os << p << endl;
    }
    return os;
}

int mainfunc( istream& is, ostream& os, Part part ) {

    ParticleList particles;
    particles.load( is );

    // Remove particles at the same position.  Given input doesn't have any
    // particles in the same position but a different one could.
    particles.clean();

    while( true ) {
        // Update particles to next position.
        particles.next();

        // Remove particles at the same position.
        particles.clean();

        if ( particles.isDone() ) {
            break;
        }
    }

    if ( part == Part::PART1 ) {
        os << particles.initialMinimumAccelerationParticleNumber() << endl;

    } else {
        size_t finalNumberOfParticles = particles.size();
        os << finalNumberOfParticles << endl;
    }

    return 0;
}

