#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>
#include <algorithm>
#include <assert.h>
#include "vector3d.hpp"
#include "polygon.hpp"
#include "windowmanager.hpp"

#define PI 3.14159265

void init_lut();
int rgb_to_8bit(double r, double g, double b);
bool sortbyz(Polygon& lhs, Polygon& rhs);
void fast_bresenham(Windowmanager &wm, int *raster, short colors, int polyid, Vector3d& colorstart, Vector3d& colorend, int height, int xstart, int ystart, int xend, int yend);
void render(Windowmanager &wm, Polygon poly);
void render_polygon(Windowmanager &wm, std::vector<Polygon> polygons);

#endif

/*

void render(Windowmanager &wm, Polygon poly){
 
    // make sure poly is not out of bounds of screensize.
    assert(poly.a.x >= 0 && poly.a.x < wm.screenwidth);
    assert(poly.b.x >= 0 && poly.b.x < wm.screenwidth);
    assert(poly.c.x >= 0 && poly.c.x < wm.screenwidth);

    assert(poly.a.y >= 0 && poly.a.y < wm.screenheight);
    assert(poly.b.y >= 0 && poly.b.y < wm.screenheight);
    assert(poly.c.y >= 0 && poly.c.y < wm.screenheight);

    float angle, camera_len, n_len, cosphi;
    Vector3d camera_angle(0,0,1);
    // init matrix for edges per coll
    int* edges = new int[wm.screenheight];

    // init rastermatrix (array here to have one single block of mem)
    int* raster = new int[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ raster[i] = -1;}

    // init colormatrix to save color of nodes
    float* colorsr = new float[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ colorsr[i] = -1;}

    float* colorsg = new float[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ colorsg[i] = -1;}

    float* colorsb = new float[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ colorsb[i] = -1;}


    // init colormatrix to save colors of the nodes across
    float* lastcolr = new float[wm.screenheight];
    for(int i = 0; i < wm.screenheight; ++i){ lastcolr[i] = -1;}

    float* lastcolg = new float[wm.screenheight];
    for(int i = 0; i < wm.screenheight; ++i){ lastcolg[i] = -1;}

    float* lastcolb = new float[wm.screenheight];
    for(int i = 0; i < wm.screenheight; ++i){ lastcolb[i] = -1;}


    // init lenmatrix to save colors of the nodes across
    short* collen = new short[wm.screenheight];


    // rasterise the polygon from a-b, b-c and c-a
    fast_bresenham(wm, raster, colorsr, colorsg, colorsb, poly.polyid, poly.a_color, poly.b_color, wm.screenheight, poly.a.x, poly.a.y, poly.b.x, poly.b.y); 
    fast_bresenham(wm, raster, colorsr, colorsg, colorsb, poly.polyid, poly.b_color, poly.c_color, wm.screenheight, poly.b.x, poly.b.y, poly.c.x, poly.c.y);
    fast_bresenham(wm, raster, colorsr, colorsg, colorsb, poly.polyid, poly.c_color, poly.a_color, wm.screenheight, poly.c.x, poly.c.y, poly.a.x, poly.a.y);
 
    // find out if we see the front or the triangle, otherwise we dont need to draw it
    camera_len = camera_angle.lenght();
    n_len = poly.n.lenght();
    cosphi = camera_angle.scalar_product(poly.n) / (camera_len * n_len);
    angle = acos(cosphi) * 180.0 / PI;

    // ṕrint if we need to
    if(angle <= 90){

        for(int y = 0; y < wm.screenheight; ++y){
            for(int x = 0; x < wm.screenwidth; ++x){
                if((edges[y] <= 0) && (raster[y * wm.screenheight + x] != -1)){
                    edges[y]++;
                }else if((edges[y] > 0) && (raster[y * wm.screenheight + x] !=1)){
                    edges[y]++;
                    lastcolr[y] = colorsr[y * wm.screenheight + x];
                    lastcolg[y] = colorsg[y * wm.screenheight + x];
                    lastcolb[y] = colorsb[y * wm.screenheight + x];
                }else{
                    collen[y]++;
                }
                
            }
        }

        for(int y = 0; y < wm.screenheight; ++y){

            bool inside = false;
            float curcolorr, curcolorg, curcolorb;
            float insidewalked = 0;

            for(int x = 0; x < wm.screenwidth; ++x){
                if(edges[y] <= 0) {break;}

                // if we hit the border 
                if(raster[y * wm.screenheight + x] != -1){
                    // for the first time
                    inside = true;
                    curcolorr = colorsr[y * wm.screenheight + x];
                    curcolorg = colorsg[y * wm.screenheight + x];
                    curcolorb = colorsb[y * wm.screenheight + x];
                    edges[y]--;
                    continue;
                }            
                if(inside && (edges[y] > 0)){
                    // we are inside, lets print a "pixel". 
                    float red = (((collen[y] - insidewalked)/insidewalked) * curcolorr) + ((insidewalked/collen[y]) * lastcolr[y]);
                    float green = (((collen[y] - insidewalked)/insidewalked) * curcolorg) + ((insidewalked/collen[y]) * lastcolg[y]);
                    float blue = (((collen[y] - insidewalked)/insidewalked) * curcolorb) + ((insidewalked/collen[y]) * lastcolb[y]);
                    
                    wm.printxyc(x,y, COLOR_RED, COLOR_BLACK, true, "*");
                    ++insidewalked;
                }
            }
            
        }
    }

    delete []edges;
    delete []raster;
    delete []colorsr;
    delete []colorsg;
    delete []colorsb;
    delete []lastcolr;
    delete []lastcolg;
    delete []lastcolb;
    delete []collen;
    return;
}
*/
