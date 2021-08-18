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
        Tuple p = point(4, -4, 3);
        Tuple v = vector(4, -4, 3);
        CHECK(equal(p, Tuple(4, -4, 3, 1)));
        CHECK(equal(v, Tuple(4, -4, 3, 0)));
    }
    SUBCASE("Arithmetic Operations"){
        Tuple a(3, -2, 5, 1);
        Tuple b(-2, 3, 1, 0);
        Tuple p1 = point(3, 2, 1);
        Tuple p2 = point(5, 6, 7);
        Tuple v1 = vector(3, 2, 1);
        Tuple v2 = vector(5, 6, 7);
        Tuple zero = vector(0, 0, 0);
        Tuple v3 = vector(1, -2, 3);
        CHECK(equal(a+b, Tuple(1, 1, 6, 1)));
        CHECK(equal(p1-p2, vector(-2, -4, -6)));
        CHECK(equal(p1-v2, point(-2, -4, -6)));
        CHECK(equal(v1-v2, vector(-2, -4, -6)));
        CHECK(equal(zero - v3, vector(-1, 2, -3)));
        CHECK(equal(-v2, vector(-5, -6, -7)));
        CHECK(equal(v1*5.0, vector(15, 10, 5)));
        CHECK(equal(v1/2.0, vector(1.5, 1.0, 0.5)));

        CHECK(equal(vector(1, 2, 3).norm(),
                    vector(1.0/std::sqrt(14), 2.0/std::sqrt(14), 3.0/std::sqrt(14))));
    }
    SUBCASE("Member functions"){
        CHECK(vector(0, 1, 0).len() == doctest::Approx(1.0));
        CHECK(vector(0, 0, 1).len() == doctest::Approx(1.0));
        CHECK(vector(1, 2, 3).len() == doctest::Approx(std::sqrt(14)));
        CHECK(vector(-1, -2, -3).len() == doctest::Approx(std::sqrt(14)));

        CHECK(vector(1, 2, 3)*vector(2, 3, 4) == doctest::Approx(20));
        CHECK(equal(vector(1, 2, 3).cross(vector(2, 3, 4)), vector(-1, 2, -1)));
        CHECK(equal(vector(2, 3, 4).cross(vector(1, 2, 3)), vector(1, -2, 1)));
    }
}