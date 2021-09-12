#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "datatypes.h"
#include "functions.h"

TEST_CASE("Tuple Test"){
    SUBCASE("Bare Tuple"){
        Tuple t(4.3, -4.2, 3.1, 1.0);
        CHECK(t.x == doctest::Approx(4.3));
        CHECK(t.y == doctest::Approx(-4.2));
        CHECK(t.z == doctest::Approx(3.1));
        CHECK(t.w == doctest::Approx(1.0));
        CHECK(t.is_vector == false);
    }
    SUBCASE("Tuple Factories"){
        Tuple p = Point(4, -4, 3);
        Tuple v = Vector(4, -4, 3);
        Tuple c = Color(0.5, 0.5, 0.3);
        CHECK(equal(p, Tuple(4, -4, 3, 1)));
        CHECK(equal(v, Tuple(4, -4, 3, 0)));
        CHECK(equal(c, Tuple(0.5, 0.5, 0.3, 0.0)));
    }
    SUBCASE("Arithmetic Operations"){
        Tuple a(3, -2, 5, 1);
        Tuple b(-2, 3, 1, 0);
        Tuple p1 = Point(3, 2, 1);
        Tuple p2 = Point(5, 6, 7);
        Tuple v1 = Vector(3, 2, 1);
        Tuple v2 = Vector(5, 6, 7);
        Tuple zero = Vector(0, 0, 0);
        Tuple v3 = Vector(1, -2, 3);
        CHECK(equal(a+b, Tuple(1, 1, 6, 1)));
        CHECK(equal(p1-p2, Vector(-2, -4, -6)));
        CHECK(equal(p1-v2, Point(-2, -4, -6)));
        CHECK(equal(v1-v2, Vector(-2, -4, -6)));
        CHECK(equal(zero - v3, Vector(-1, 2, -3)));
        CHECK(equal(-v2, Vector(-5, -6, -7)));
        CHECK(equal(v1*5.0, Vector(15, 10, 5)));
        CHECK(equal(v1/2.0, Vector(1.5, 1.0, 0.5)));

        CHECK(equal(Vector(1, 2, 3).norm(),
                    Vector(1.0 / std::sqrt(14), 2.0 / std::sqrt(14), 3.0 / std::sqrt(14))));
    }
    SUBCASE("Member functions"){
        CHECK(Vector(0, 1, 0).len() == doctest::Approx(1.0));
        CHECK(Vector(0, 0, 1).len() == doctest::Approx(1.0));
        CHECK(Vector(1, 2, 3).len() == doctest::Approx(std::sqrt(14)));
        CHECK(Vector(-1, -2, -3).len() == doctest::Approx(std::sqrt(14)));

        CHECK(Vector(1, 2, 3).dot(Vector(2, 3, 4)) == doctest::Approx(20));
        CHECK(equal(Vector(1, 2, 3).cross(Vector(2, 3, 4)), Vector(-1, 2, -1)));
        CHECK(equal(Vector(2, 3, 4).cross(Vector(1, 2, 3)), Vector(1, -2, 1)));
    }
    SUBCASE("Color tests"){
        Tuple c1 = Color(0.9, 0.6, 0.75);
        Tuple c2 = Color(0.7, 0.1, 0.25);
        CHECK(equal(c1+c2, Color(1.6, 0.7, 1.0)));
        CHECK(equal(c1-c2, Color(0.2, 0.5, 0.5)));
        CHECK(equal(c1*2, Color(1.8, 1.2, 1.5)));
        CHECK(equal(c1*c2, Color(0.9*0.7, 0.6*0.1, 0.75*0.25)));
    }
}
TEST_CASE("Canvas Test"){
    Canvas canvas(10, 20);
    CHECK(canvas.width == 10);
    CHECK(canvas.height == 20);

    for(unsigned int i=0;i<canvas.width;++i){
        for(unsigned int j=0;j<canvas.height;++j){
            CHECK(equal(canvas[i][j], Color(0, 0, 0)));
        }
    }

    canvas[5][7] = Color(0.3, 0.5, 0.7);
    CHECK(equal(canvas[5][7], Color(0.3, 0.5, 0.7)));

}

TEST_CASE("Matrix Test"){
    Matrix id_matrix = IdentityMatrix();
    CHECK(id_matrix.data[0][0] == doctest::Approx(1));
    Matrix m1 = Matrix({1, 2, 3, 4,
                       5, 6, 7, 8,
                       9, 8, 7, 6,
                       5, 4, 3, 2});
    Matrix m2 = Matrix({-2, 1, 2, 3,
                       3, 2, 1, -1,
                       4, 3, 6, 5,
                       1, 2, 7, 8});
    Matrix m3 = Matrix({1, 2, 3, 4,
                       2, 4, 4, 2,
                       8, 6, 4, 1,
                       0, 0, 0, 1});
    Tuple t(1, 2, 3, 1);
//    Matrix m4 = m1; //test copy constructor
    Matrix m5({1, 2, 3, 4,
               5, 6, 7, 8,
               9, 8, 7, 6,
               5, 4, 3, 2});
//    Matrix m6 = m1;
//    Matrix m7 = m1;
//    CHECK(equal(m6, m7));
//    CHECK(equal(m6, m7));
//    CHECK(equal(m6, m7));
    CHECK(equal(m1, m5));
    CHECK(equal(m1, m5));
//    CHECK(!equal(m1, Matrix({1, 2, 3, 4,
//                           5, 6, 6, 8,
//                           9, 8, 7, 6,
//                           5, 4, 3, 2})));
//    // matrix-matrix multiplication
//    CHECK(equal(m1*m2, Matrix({20, 22, 50, 48,
//                              44, 54, 114, 108,
//                              40, 58, 110, 102,
//                              16, 26, 46, 42})));
//
//    CHECK(equal(m3*t, Tuple(18, 24, 33, 1)));
//    CHECK(equal(m3*id_matrix, m3));
//    CHECK(equal(id_matrix*m3, m3));
//    CHECK(equal(id_matrix*t, t));
//    CHECK(equal(m3.transposed(), Matrix({1, 2, 8, 0,
//                                        2, 4, 6, 0,
//                                        3, 4, 4, 0,
//                                        4, 2, 1, 1})));
//    Matrix trans = Translation(5, -3, 2);
//    Tuple p = Point(-3, 4, 5);
//    CHECK(equal(trans*p, Point(2, 1, 7)));
}