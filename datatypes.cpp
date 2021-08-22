#include <stdexcept>
#include <cmath>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "datatypes.h"
#include "functions.h"

Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){
    if(equal(w, 0.0)){
        is_vector = true;
    }else{
        is_vector = false;
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


Tuple Tuple::operator*(const Tuple &other) const {
    return {x*other.x,
            y*other.y,
            z*other.z,
            w*other.w};
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

float Tuple::dot(const Tuple &other) const {
    return x*other.x + y*other.y + z*other.z + w*other.w;
}

Tuple Point(float x, float y, float z){
    return {x, y, z, 1.0};
}

Tuple Vector(float x, float y, float z){
    return {x, y, z, 0.0};
}

Tuple Color(float x, float y, float z) {
    return {x, y, z, 0.0};
}


std::vector<Tuple> &Canvas::operator[](int idx) {
    return data[idx];
}

Canvas::Canvas(unsigned int width, unsigned int height) : width(width), height(height) {
    data.reserve(width);
    for(unsigned int i=0;i<width;++i){
        for(unsigned int j=0;j<height;++j){
            data[i].push_back(Color(0, 0, 0));
        }
    }
}

bool Canvas::save(std::string filename) {
    // map colors to 8 bit
    std::vector<unsigned char> converted_data(width*height*3);
    for(unsigned int y=0;y<height;++y){
        for(unsigned int x=0;x<width;++x){
            unsigned int idx = (y*width+x)*3;
            unsigned int r = static_cast<unsigned char>(std::clamp(data[x][y].x, 0.0f, 1.0f)*255);
            unsigned int g = static_cast<unsigned char>(std::clamp(data[x][y].y, 0.0f, 1.0f)*255);
            unsigned int b = static_cast<unsigned char>(std::clamp(data[x][y].z, 0.0f, 1.0f)*255);
            converted_data[idx] = r;
            converted_data[idx+1] = g;
            converted_data[idx+2] = b;
        }
    }

    // save to ppm file
    std::ofstream file;
    file.open(filename, std::ios::out | std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file" << std::endl;
        return false;
    }
    file << "P6" << "\n";
    file << width << "\n";
    file << height << "\n";
    file << "255" << "\n";
    file.write(reinterpret_cast<char*>(converted_data.data()), width*height*3);
    if (file.fail()) {
        std::cerr << "Could not write data" << std::endl;
        return false;
    }
    file.close();
    return true;
}

Matrix::Matrix(float c00, float c01, float c02,float c03,
               float c10, float c11, float c12, float c13,
               float c20, float c21, float c22, float c23,
               float c30, float c31, float c32, float c33){
    data[0][0] = c00;
    data[0][1] = c01;
    data[0][2] = c02;
    data[0][3] = c03;

    data[1][0] = c10;
    data[1][1] = c11;
    data[1][2] = c12;
    data[1][3] = c13;

    data[2][0] = c20;
    data[2][1] = c21;
    data[2][2] = c22;
    data[2][3] = c23;

    data[3][0] = c30;
    data[3][1] = c31;
    data[3][2] = c32;
    data[3][3] = c33;
}

// matrix-matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result;
    for(unsigned row = 0; row < 4; row++){
        for(unsigned col = 0; col < 4; col++){
            result.data[row][col] = data[row][0]*other.data[0][col] +
                                    data[row][1]*other.data[1][col] +
                                    data[row][2]*other.data[2][col] +
                                    data[row][3]*other.data[3][col];
        }
    }
    return result; //hopefully NRVO happens, too lazy to test right now
}
// matrix-vector multiplication
Tuple Matrix::operator*(const Tuple& other) const {
    float result[4];
    for(unsigned row = 0; row < 4; row++){
        Tuple row_vector(data[row][0], data[row][1], data[row][2], data[row][3]);
        result[row] = row_vector.dot(other);
    }
    return Tuple(result[0], result[1], result[2], result[3]); //hopefully NRVO happens, too lazy to test right now
}

Matrix::Matrix() {
    for(unsigned i = 0; i<4; i++){
        for(unsigned j = 0; j<4; j++){
            data[i][j] = 0;
        }
    }
}

Matrix Matrix::transposed() const {
    Matrix result;
    for(unsigned i = 0; i<4; i++){
        for(unsigned j = 0; j<4; j++){
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}


Matrix IdentityMatrix() {
    return {1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
}

Matrix Translation(float x, float y, float z) {
    return {1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1};
}