#include "../include/main.hpp"

#define FPS_REFRESH 1.0
#define FPS_PRINTLEN 9 // 8 chars + '\0+ '\0'

using namespace std;

void move3dobject(Vector3d direction, std::vector<Polygon> &polygons){

    for(std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i){

        (*i).a += direction;
        (*i).b += direction;
        (*i).c += direction;
    }

}


void turn3dobject(Vector3d axis, double alpha,  std::vector<Polygon> &polygons){

    std::vector<double> xs, ys, zs;
    Vector3d center, ba, ca;
    int j = 0;

    //sum all vertex nodes up
    for(std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i){

        xs.push_back((*i).a.x);
        xs.push_back((*i).b.x);
        xs.push_back((*i).c.x);
 
        ys.push_back((*i).a.y);
        ys.push_back((*i).b.y);
        ys.push_back((*i).c.y);
        
        zs.push_back((*i).a.z);
        zs.push_back((*i).b.z);
        zs.push_back((*i).c.z);
        
        j++;
    }

    //calc median value to turn the objekt in-place and from a central point
    for( int k = 0; k < j; k++){ 

        center.x += xs.back();
        center.y += ys.back();
        center.z += zs.back();
    
    }

    center.x /= j;
    center.y /= j;
    center.z /= j;


    //move the object to (0,0,0), apply turning matrix and then move back to original coordinates
    for(std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i){

        (*i).a -= center;
        (*i).b -= center;
        (*i).c -= center;
        
        (*i).a.turnonaxis(axis, alpha);
        (*i).b.turnonaxis(axis, alpha);
        (*i).c.turnonaxis(axis, alpha);

        (*i).a += center;
        (*i).b += center;
        (*i).c += center;

        //update n
        ba = (*i).a - (*i).b;
        ca = (*i).a - (*i).c;

        (*i).n = ba.cross_product(ca);
        (*i).n = (*i).n.normalise();
        
   }

}

int main (){

    // Initialise ncurses library and windows
    Windowmanager wm(1000,1000,10,10);
    setlocale(LC_ALL, "");
    
    // Local vars
	int c, fps = 0, oldfps = 0;
    char buf[255];
	std::array<int, KEY_MAX> keyhits;
    keyhits.fill(0);	
	auto start = std::chrono::system_clock::now();
    
    //testpoly
    std::vector<Polygon> polys;
    polys.push_back(Polygon(Vector3d(20,30,12),Vector3d(40,30,-16),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));
    polys.push_back(Polygon(Vector3d(40,30,-16),Vector3d(40,30,12),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));
    polys.push_back(Polygon(Vector3d(40,30,12),Vector3d(20,30,12),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));

    // Main loop
	while(true){

		while((c = getch()) != -1){
			keyhits[c] = 1;
		}

		if(keyhits['q'] == 1){
			break;
		}if(keyhits['r'] == 1){
            polys.clear();
            polys.push_back(Polygon(Vector3d(20,30,12),Vector3d(40,30,-16),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));
            polys.push_back(Polygon(Vector3d(40,30,-16),Vector3d(40,30,12),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));
            polys.push_back(Polygon(Vector3d(40,30,12),Vector3d(20,30,12),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255)));
		}if(keyhits['j'] == 1){ 
            turn3dobject(Vector3d(0,1,0), 0.2, polys);
		}if(keyhits['l'] == 1){ 
            turn3dobject(Vector3d(0,1,0), -0.2, polys);
		}if(keyhits['i'] == 1){ 
            turn3dobject(Vector3d(1,0,0), 0.2, polys);
		}if(keyhits['k'] == 1){ 
            turn3dobject(Vector3d(1,0,0), -0.2, polys);
		}if(keyhits['u'] == 1){
            turn3dobject(Vector3d(0,0,1), 0.2, polys);
		}if(keyhits['o'] == 1){
            turn3dobject(Vector3d(0,0,1), -0.2, polys);
		}if(keyhits['t'] == 1){
        }if(keyhits['w'] == 1){
            move3dobject(Vector3d(0,-1,0), polys);
        }if(keyhits['a'] == 1){
            move3dobject(Vector3d(-1,0,0), polys);
        }if(keyhits['s'] == 1){
            move3dobject(Vector3d(0,1,0), polys);
        }if(keyhits['d'] == 1){
            move3dobject(Vector3d(1,0,0), polys);
        }

        render_polygon(wm, polys); 

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;

		if(elapsed.count() > FPS_REFRESH ){
			start = std::chrono::system_clock::now();
            oldfps = fps;
			fps = 0;
		}		

        snprintf(buf, FPS_PRINTLEN, "fps: %3i", oldfps);
        wm.printxyc(0,0, ColorLut::getInstance().rgb_to_8bit(0,255,0), COLOR_BLACK, true, buf);

		++fps;	

		keyhits.fill(0);
	}

	return 0;
}
