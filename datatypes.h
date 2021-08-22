#ifndef RAYTRACER_DATATYPES_H
#define RAYTRACER_DATATYPES_H

#include <vector>
#include <string>

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
    Tuple operator*(const Tuple& other) const;
    Tuple operator/(const float& scalar) const;
    float len() const;
    Tuple norm() const;
    float dot(const Tuple& other) const;
    Tuple cross(const Tuple& other) const;
    bool is_vector;
};

struct Matrix{
    float data [4][4];
    Matrix(float c00, float c01, float c02, float c03,
           float c10, float c11, float c12, float c13,
           float c20, float c21, float c22, float c23,
           float c30, float c31, float c32, float c33);
    Matrix();
    Tuple operator*(const Tuple& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix transposed() const;
};

struct Canvas{
    unsigned int width;
    unsigned int height;
    Canvas(unsigned int width, unsigned int height);
    std::vector<Tuple>& operator[](int);
    bool save(std::string filename);

private:
    std::vector<std::vector<Tuple>> data;
};

Tuple Point(float x, float y, float z);
Tuple Vector(float x, float y, float z);
Tuple Color(float x, float y, float z);

Matrix IdentityMatrix();
Matrix Translation(float x, float y, float z);


#endif //RAYTRACER_DATATYPES_H