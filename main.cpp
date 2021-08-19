#include <iostream>

#include "datatypes.h"
#include "functions.h"



int main() {
    Canvas canvas(30,20);
    canvas[29][19] = Color(1.0,0.5,0.1);
    canvas.save("test.ppm");
    return 0;
}
