#include <cmath>
#include "functions.h"

bool equal(float a, float b){
    if(std::abs(a-b)<EPSILON){
        return true;
    }else{
        return false;
    }
}

bool equal(Tuple a, Tuple b){
    if(std::abs(a.x-b.x)>EPSILON){
        return false;
    }
    if(std::abs(a.y-b.y)>EPSILON){
        return false;
    }
    if(std::abs(a.z-b.z)>EPSILON){
        return false;
    }
    if(std::abs(a.w-b.w)>EPSILON){
        return false;
    }
    return true;
}

Tuple point(float x, float y, float z){
    return {x, y, z, 1.0};
}

Tuple vector(float x, float y, float z){
    return {x, y, z, 0.0};
}