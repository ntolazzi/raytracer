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

bool equal(Matrix a, Matrix b) {
    for(unsigned i = 0;i<4;i++){
        for(unsigned j=0;j<4;j++){
            if(std::abs(a.data[i][j]-b.data[i][j])>EPSILON){
                return false;
            }
        }
    }

    return true;
}
