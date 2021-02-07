#include "../include/vector3d.hpp"
#include <ostream>
#include <string>

Vector3d Vector3d::operator+(const Vector3d &vector){

    return Vector3d(x+vector.x, y+vector.y, z+vector.z);
}

Vector3d &Vector3d::operator+=(const Vector3d &vector){

    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3d Vector3d::operator-(const Vector3d &vector){

    return Vector3d(x-vector.x, y-vector.y, z-vector.z);
}

Vector3d &Vector3d::operator-=(const Vector3d &vector){

    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

Vector3d Vector3d::operator*(double value){

    return Vector3d(x*value, y*value, z*value);
}

Vector3d &Vector3d::operator*=(double value){

    x *= value;
    y *= value;
    z *= value;
    return *this;
}

Vector3d Vector3d::operator/(double value){

    assert(value!=0);
    return Vector3d(x/value, y/value, z/value);
}

Vector3d &Vector3d::operator/=(double value){

    assert(value!=0);
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

Vector3d &Vector3d::operator=(const Vector3d &vector){
    x = vector.x;
    y = vector.y;
    z = vector.z;
    return *this;
}

std::string Vector3d::to_string(){
    char buf[255];
    sprintf(buf,"[%f,%f,%f]", x,y,z);

    std::string res = buf;
    return res;
}

double Vector3d::scalar_product(const Vector3d &vector){
    return x*vector.x + y*vector.y + z*vector.z;
}

Vector3d Vector3d::cross_product(const Vector3d &vector){
    double newx = y*vector.z - z*vector.y;
    double newy = z*vector.x - x*vector.z;
    double newz = x*vector.y - y*vector.x;
    return Vector3d(newx, newy, newz);
}

double Vector3d::lenght(){
    return sqrt((x*x)+(y*y)+(z*z));
}

Vector3d Vector3d::normalise(){
    assert(lenght()!=0);
    *this/=lenght();
    return *this;
}

double Vector3d::distance(const Vector3d &vector){
    Vector3d connection = *this-vector;
    return connection.lenght();
}

void Vector3d::turnonaxis(Vector3d axis, double alpha){

    double a,b,c,d, oldx = x, oldy = y, oldz = z;

    a = cos(alpha/2);
    b = sin(alpha/2) * axis.x;
    c = sin(alpha/2) * axis.y;
    d = sin(alpha/2) * axis.z;

    double rotationmatrix[3][3] = { {a*a + b*b - c*c - d*d, 2*(b*c - a*d), 2*(b*d + a*c)},{2*(b*c + a*d), a*a + c*c - b*b - d*d, 2*(c*d - a*b)},{2*(b*d - a*c), 2*(c*d + a*b), a*a + d*d - b*b - c*c}};

    x = rotationmatrix[0][0] * oldx + rotationmatrix[0][1] * oldy + rotationmatrix[0][2] * oldz;
    y = rotationmatrix[1][0] * oldx + rotationmatrix[1][1] * oldy + rotationmatrix[1][2] * oldz;
    z = rotationmatrix[2][0] * oldx + rotationmatrix[2][1] * oldy + rotationmatrix[2][2] * oldz;

    return;
}
