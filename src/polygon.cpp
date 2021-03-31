#include "../include/polygon.hpp"

Polygon::Polygon(Vector3d a1, Vector3d b1, Vector3d c1, Vector3d n1, Vector3d a_color1, Vector3d b_color1, Vector3d c_color1){

    a = a1;
    b = b1;
    c = c1;
    n = n1;
    a_color = a_color1;
    b_color = b_color1;
    c_color = c_color1;
}

std::string Polygon::to_string(){
    std::string tmp("Poly n: " + n.to_string() + "\na: " + a.to_string() + "\nb: " + b.to_string() + "\nc: " + c.to_string());

    return tmp.c_str();
}

double Polygon::getlastz(){

    if(a.z < b.z){
        if(a.z < c.z){ return a.z;}
        else{ return c.z;}
    }else{
        if(b.z < c.z){ return b.z;}
        else{ return c.z;}
    }

}
void Polygon::turnonaxisinplace(Vector3d direction, double alpha){

    Vector3d center, ba, ca;

    center.x = (a.x + b.x + c.x)/3;
    center.y = (a.y + b.y + c.y)/3;
    center.z = (a.z + b.z + c.z)/3;
    
    a -= center;
    b -= center;
    c -= center;

    a.turnonaxis(direction, alpha);
    b.turnonaxis(direction, alpha);
    c.turnonaxis(direction, alpha);

    a += center;
    b += center;
    c += center;

    ba = a-b;
    ca = a-c;

    n = ba.cross_product(ca);
    n = n.normalise();
}
