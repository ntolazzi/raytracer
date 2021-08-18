#ifndef RAYTRACER_DATATYPES_H
#define RAYTRACER_DATATYPES_H

constexpr float EPSILON = 0.00001;

struct Tuple{
    float x;
    float y;
    float z;
    float w;
    Tuple(float x, float y, float z, float w);
    Tuple operator+(const Tuple&) const;
    Tuple operator-(const Tuple&) const;
    Tuple operator-() const;
    Tuple operator*(const float& scalar) const;
    float operator*(const Tuple& other) const;
    Tuple operator/(const float& scalar) const;
    float len() const;
    Tuple norm() const;
    Tuple cross(const Tuple& other) const;
    bool is_vector;
};

#endif //RAYTRACER_DATATYPES_H