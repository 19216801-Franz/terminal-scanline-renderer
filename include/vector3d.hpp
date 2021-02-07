#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>
#include <math.h>
#include <assert.h>
#include <ostream>
#include <string>
#include <stdio.h>

class Vector3d{

    public: 
        /* Members */
        double x,y,z;
        /* Methods */
        Vector3d():Vector3d(0,0,0){}
        Vector3d(const Vector3d &vector):Vector3d(vector.x, vector.y, vector.z){}; //copy
        Vector3d(double x1, double y1, double z1){ x = x1; y = y1; z = z1;}
        Vector3d operator+(const Vector3d &vector); //operators
        Vector3d &operator+=(const Vector3d &vector);
        Vector3d operator-(const Vector3d &vector);
        Vector3d &operator-=(const Vector3d &vector);
        Vector3d operator*(double value);
        Vector3d &operator*=(double value);
        Vector3d operator/(double value);
        Vector3d &operator/=(double value);
        Vector3d &operator=(const Vector3d &vector);
        std::string to_string();
        double scalar_product(const Vector3d &vector); //Scalarproduct
        Vector3d cross_product(const Vector3d &vector);
        double lenght();
        Vector3d normalise();
        void turnonaxis(Vector3d axis, double alpha);
        Vector3d turnx(double alpha);
        Vector3d turny(double alpha);
        Vector3d turnz(double alpha);

        double distance(const Vector3d &vector);
        double gety(){ return y;}
        double getz(){ return z;}
};
#endif
