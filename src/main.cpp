#include "../include/main.hpp"

#define FPS_REFRESH 1.0

using namespace std;

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
    
    // test polygon
    Polygon testpoly(Vector3d(20,30,0),Vector3d(40,30,0),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255));
    Polygon testpoly2(Vector3d(60,30,0),Vector3d(60,30,20),Vector3d(20,40,-10), Vector3d(0,0,1), 69,Vector3d(0,0,255), Vector3d(0,255,0),Vector3d(255,0,0));


    // init lut
    init_lut();

    // Main loop
	while(true){

		while((c = getch()) != -1){
			keyhits[c] = 1;
		}

		if(keyhits['q'] == 1){
			break;
		}if(keyhits['r'] == 1){
            testpoly = Polygon(Vector3d(20,30,0),Vector3d(40,30,0),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(255,0,0), Vector3d(0,255,0),Vector3d(0,0,255));
            testpoly2 = Polygon(Vector3d(40,30,0),Vector3d(20,30,20),Vector3d(30,60,0), Vector3d(0,0,1), 69,Vector3d(0,0,255), Vector3d(0,255,0),Vector3d(255,0,0));
		}if(keyhits['j'] == 1){ 
            testpoly.turnonaxisinplace(Vector3d(0,1,0), 0.2);
            testpoly2.turnonaxisinplace(Vector3d(0,1,0), 0.2);
		}if(keyhits['l'] == 1){ 
            testpoly.turnonaxisinplace(Vector3d(0,1,0), -0.2);
            testpoly2.turnonaxisinplace(Vector3d(0,1,0), -0.2);
		}if(keyhits['i'] == 1){ 
            testpoly.turnonaxisinplace(Vector3d(1,0,0), 0.2);
            testpoly2.turnonaxisinplace(Vector3d(1,0,0), 0.2);
		}if(keyhits['k'] == 1){ 
            testpoly.turnonaxisinplace(Vector3d(1,0,0), -0.2);
            testpoly2.turnonaxisinplace(Vector3d(1,0,0), -0.2);
		}if(keyhits['u'] == 1){
            testpoly.turnonaxisinplace(Vector3d(0,0,1), 0.2);
            testpoly2.turnonaxisinplace(Vector3d(0,0,1), 0.2);
		}if(keyhits['o'] == 1){
            testpoly.turnonaxisinplace(Vector3d(0,0,1), -0.2);
            testpoly2.turnonaxisinplace(Vector3d(0,0,1), -0.2);
		}

        // test poly vector
        std::vector<Polygon> polys;
        polys.push_back(testpoly);
//        polys.push_back(testpoly2);

        render_polygon(wm, polys); 

        sprintf(buf, "Rendering poly with normal vector: %s ", testpoly.n.to_string().c_str());
        wm.printxyc(0,3,COLOR_RED,COLOR_BLACK, true, buf);
		

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed = end - start;

		if(elapsed.count() > FPS_REFRESH ){
			start = std::chrono::system_clock::now();
            oldfps = fps;
			fps = 0;
		}		

        sprintf(buf, "fps: %i", oldfps);
        wm.printxyc(0,0, 12, COLOR_BLACK, true, buf);

		++fps;	

		keyhits.fill(0);
	}

	return 0;
}
