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

Matrix::Matrix(std::initializer_list<float> coefficients) {
    if(coefficients.size()!=16 && coefficients.size()!=9 && coefficients.size()!=4){
        throw std::invalid_argument("Size must be between either 2x2, 3x3 or 4x4");
    }
    dim = std::lround(sqrt(coefficients.size()));
    data.reserve(dim);
    for(unsigned int i=0;i<dim;++i){
        for(unsigned int j=0;j<dim;++j){
            data[i].push_back(*(coefficients.begin()+i*dim+j));
        }
    }
}


// matrix-matrix multiplication
Matrix Matrix::operator*(const Matrix& other) const {
    Matrix result(dim);
    for(unsigned int row = 0; row < dim; row++){
        for(unsigned int col = 0; col < dim; col++){
            float sum = 0.0;
            for(unsigned int idx = 0; idx < dim; idx++){
                sum += data[row][idx]*other.data[idx][col];
            }
            result.data[row][col] = sum;
        }
    }
    return result; //hopefully NRVO happens, too lazy to test right now
}
// matrix-vector multiplication
Tuple Matrix::operator*(const Tuple& other) const {
    if(dim !=4){
        throw std::logic_error("Not supported for other than 4x4 vectors");
    }
    float result[4];
    for(unsigned row = 0; row < 4; row++){
        Tuple row_vector(data[row][0], data[row][1], data[row][2], data[row][3]);
        result[row] = row_vector.dot(other);
    }
    return Tuple(result[0], result[1], result[2], result[3]); //hopefully NRVO happens, too lazy to test right now
}

Matrix::Matrix(unsigned int dim) : dim(dim){
    data.reserve(dim);
    for(unsigned int i=0;i<dim;++i){
        for(unsigned int j=0;j<dim;++j){
            data[i].push_back(0);
        }
    }
}

Matrix Matrix::transposed() const {
    Matrix result(dim);
    for(unsigned i = 0; i<dim; i++){
        for(unsigned j = 0; j<dim; j++){
            result.data[i][j] = data[j][i];
        }
    }
    return result;
}

std::vector<float>& Matrix::operator[](int idx) {
    return data[idx];
}

Matrix::Matrix(const Matrix& other) {
    dim = other.dim;
    data.reserve(dim);
    for(unsigned i = 0; i<dim; i++){
        for(unsigned j = 0; j<dim; j++) {
            float val = other.data.at(i).at(j);
            data[i].push_back(val);
            std::cout << "Copy: " << val << std::endl;
        }
    }
    std::cout << "Done" <<std::endl;
}



//float Matrix::determinant() const {
//    return data[1][1]*data[1][1]*data[1][1]*data[1][1] +
//}


Matrix IdentityMatrix() {
    return Matrix({1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1});
}

Matrix Translation(float x, float y, float z) {
    return Matrix({1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1});
}