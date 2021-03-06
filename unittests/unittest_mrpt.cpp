
#include "shmfw/variable.h"
#include "shmfw/objects/mrpt.h"
#include "shmfw/serialization/mrpt.h"
#include "shmfw/serialization/io_file.h"
#include <mrpt/utils/bits.h>
#include "gtest/gtest.h"
#include <time.h>

namespace {
  
// The fixture for testing class Foo.
class MrptTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if its body
    // is empty.

    MrptTest()
        : shmSegmentName_ ( "ShmTestSegment" )
        , shmSegmentSize_ ( 65536 ) {
	srand ( time ( NULL ) );
        // You can do set-up work for each test here.
    }

    virtual ~MrptTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    std::string shmSegmentName_;
    int shmSegmentSize_;
    double rand_01() {
        return ( double ) rand() / RAND_MAX;
    }
    double randf ( double fmin, double fmax ) {
        return rand_01() * ( fmax - fmin ) + fmin;
    }
    double randAngle() {
        return rand_01() * 2 * M_PI - M_PI;
    }
    double randf() {
        return randf ( -10, 10 );
    }
};

TEST_F ( MrptTest, MrptInShm_Point2D ) {

    using namespace mrpt::poses;
    using namespace mrpt::utils;
    ShmFw::HandlerPtr shmHdl = ShmFw::Handler::create ( shmSegmentName_, shmSegmentSize_ );
    ShmFw::Var<CPoint3D> l ( "L",shmHdl );
    ShmFw::Var<CPose2D> r ( "R",shmHdl );
    ShmFw::Var<CPose3D> c ( "C",shmHdl );

    *l = CPoint3D ( 0,4,2 );
    *r = CPose2D ( 2,1, DEG2RAD ( 45.0f ) );
    *c = CPose3D ( 0.5f,0.5f,1.5f , DEG2RAD ( -90.0f ), DEG2RAD ( 0 ), DEG2RAD ( -90.0f ) );
    
    ShmFw::Var<CPoint3D> l2 ( "L",shmHdl );
    ShmFw::Var<CPose2D> r2 ( "R",shmHdl );
    ShmFw::Var<CPose3D> c2 ( "C",shmHdl );

    CPoint3D L(0,4,2);
    CPose2D R( 2,1, DEG2RAD ( 45.0f ) );
    CPose3D C( 0.5f,0.5f,1.5f ,DEG2RAD ( -90.0f ), DEG2RAD ( 0 ), DEG2RAD ( -90.0f ));
    
    EXPECT_EQ ( l2, L );
    EXPECT_EQ ( r2, R );
    EXPECT_EQ ( c2, C );
    
    shmHdl->removeSegment();
}

TEST_F ( MrptTest, Assignment_Point2D ) {

    ShmFw::Point2D a ( rand(), rand() );
    ShmFw::Point2D b ( a );
    EXPECT_EQ ( a, b );
    mrpt::poses::CPoint2D c;
    c << a;
    EXPECT_TRUE ( b == c );
    EXPECT_TRUE ( c == b );
    mrpt::poses::CPoint2D d ( rand(), rand() );
    EXPECT_FALSE ( b == d );
    EXPECT_FALSE ( d == b );
    b << d;
    EXPECT_TRUE ( b == d );
    EXPECT_TRUE ( d == b );
}

TEST_F ( MrptTest, Assignment_Point3D ) {

    ShmFw::Point a ( rand(), rand() , rand() );
    ShmFw::Point b ( a );
    EXPECT_EQ ( a, b );
    mrpt::poses::CPoint3D c;
    c << a;
    EXPECT_TRUE ( b == c );
    EXPECT_TRUE ( c == b );
    mrpt::poses::CPoint3D d ( rand(), rand(), rand() );
    EXPECT_FALSE ( b == d );
    EXPECT_FALSE ( d == b );
    b << d;
    EXPECT_TRUE ( b == d );
    EXPECT_TRUE ( d == b );
}

TEST_F ( MrptTest, Assignment_Pose2D ) {

    double angle = randAngle();
    ShmFw::Pose2D a ( rand(), rand() , angle );
    ShmFw::Pose2D b ( a );
    EXPECT_EQ ( a, b );
    mrpt::poses::CPose2D c;
    c << a;
    EXPECT_TRUE ( b == c );
    EXPECT_TRUE ( c == b );
    angle = randAngle();
    mrpt::poses::CPose2D d ( rand(), rand(), angle );
    EXPECT_FALSE ( b == d );
    EXPECT_FALSE ( d == b );
    b << d;
    EXPECT_TRUE ( b == d );
    EXPECT_TRUE ( d == b );
    
}

TEST_F ( MrptTest, Assignment_Pose3D ) {

    double roll = randAngle();
    double pitch = randAngle();
    double yaw = randAngle();
    mrpt::poses::CPose3D a( rand(), rand(), rand() , yaw, pitch, roll );
    ShmFw::Pose b;
    b << a;
    mrpt::poses::CPose3D c;
    c << b;
    ShmFw::Pose d;
    d << c;
    // std::cout << b << std::endl << d << std::endl;
    EXPECT_EQ ( true, b.equal ( d, 0.1f ) ) << "Should be equal";
}

TEST_F ( MrptTest, serializeCPose2D ) {
    std::string filename ( "/tmp/CPose2D.xml" );
    mrpt::poses::CPose2D a(rand(),rand(), randAngle()), b;
    ShmFw::write(filename, a);
    ShmFw::read (filename, b);
    EXPECT_EQ ( a, b );
}

TEST_F ( MrptTest, serializeCPoint2D ) {
    std::string filename ( "/tmp/CPoint2D.xml" );
    mrpt::poses::CPoint2D a(rand(),rand()), b;
    ShmFw::write(filename, a);
    ShmFw::read (filename, b);
    EXPECT_EQ ( a, b );
}
TEST_F ( MrptTest, serializeCPoint3D ) {
    std::string filename ( "/tmp/CPoint3D.xml" );
    mrpt::poses::CPoint3D a(rand(),rand(),rand()), b;
    ShmFw::write(filename, a);
    ShmFw::read (filename, b);
    EXPECT_EQ ( a, b );
}


}  // namespace



int main ( int argc, char **argv ) {
    srand ( time ( NULL ) );
    ::testing::InitGoogleTest ( &argc, argv );
    return RUN_ALL_TESTS();
}

