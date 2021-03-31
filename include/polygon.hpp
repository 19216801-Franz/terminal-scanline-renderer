#ifndef POLYGON_HPP
#define POLYGON_HPP

#include "vector3d.hpp"

class Polygon{
    public:
        /* Members */
        Vector3d a,b,c,n;
        Vector3d a_color, b_color, c_color;

        /* Methods */
        Polygon(Vector3d a1, Vector3d b1, Vector3d c1, Vector3d n1):Polygon(a1, b1, c1, n1, Vector3d(255,255,255),Vector3d(255,255,255),Vector3d(255,255,255)){}; 
        Polygon(Vector3d a1, Vector3d b1, Vector3d c1, Vector3d n1, Vector3d a_color1, Vector3d b_color1, Vector3d c_color1);
        std::string to_string();
        double getlastz();
        void turnx(double alpha);
        void turny(double alpha);
        void turnz(double alpha);
        void turnonaxisinplace(Vector3d direction, double alpha);
        void scale(double amount);

};
#endif
