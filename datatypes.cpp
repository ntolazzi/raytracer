#include <stdexcept>
#include <cmath>

#include "datatypes.h"
#include "functions.h"

Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
    if(equal(w,1.0)){
        is_vector = false;
    }else if(equal(w, 0.0)){
        is_vector = true;
    }else{
        throw std::invalid_argument( "Tuple can only have 0.0 or 1.0 as w argument");
    }
}


Tuple Tuple::operator-(const Tuple& other) const {
    return {x-other.x, y-other.y, z-other.z, w-other.w};
}

Tuple Tuple::operator-() const {
    return {-x, -y, -z, -w};
}

Tuple Tuple::operator+(const Tuple& other) const {
    return {x+other.x, y+other.y, z+other.z, w+other.w};
}

Tuple Tuple::operator*(const float& scalar) const {
    return {x*scalar, y*scalar, z*scalar, w*scalar};
}

//the dot product
float Tuple::operator*(const Tuple &other) const {
    return x*other.x + y*other.y + z*other.z + w*other.w;
}

Tuple Tuple::operator/(const float &scalar) const {
    return {x/scalar, y/scalar, z/scalar, w/scalar};
}

float Tuple::len() const {
    return std::sqrt(x*x + y*y + z*z + w*w);
}

Tuple Tuple::norm() const {
    float length = len();
    return {x/length, y/length, z/length, w/length};
}

Tuple Tuple::cross(const Tuple& other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
            0.0};
}

