#include "../include/render.hpp"

#define padnum 13
const char* padders[padnum] = {".", ",", "o", "*", "a", "x", "n", "m", "O", "0", "#", "N", "M",};

bool sortbyz(Polygon& lhs, Polygon& rhs){
    return lhs.getlastz() < rhs.getlastz();
}

int sgn(int x){
    return (x>0) ? 1 : (x<0) ? -1 : 0;
}

int findpad(int z){
    
    z += padnum/2 + 1;

    if(z < 0){ z = 0;}
    if(z > padnum-1){ z = padnum-1;}
    return z;
}

void fast_bresenham(Windowmanager &wm, int *raster, short *colors, int polyid, Vector3d& colorstart, Vector3d& colorend, int height, int xstart, int ystart, int zstart, int xend, int yend, int zend){

    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, deltaslowdir, deltafastdir, err;
    short color;
    int zcolors = zstart, zcolore = zend;
    ColorLut& lut = ColorLut::getInstance();

    if(zstart > 0){ 
        zcolors = 0;
    }else{
        zcolors *= 5;
    }
    if(zend > 0){
        zcolore = 0;
    }else{
        zcolore *= 5;
    }

    // calc distances
    dx = xend-xstart;
    dy = yend-ystart;

    // check sign
    incx = sgn(dx);
    incy = sgn(dy);
    if(dx<0) dx = -dx;
    if(dy<0) dy = -dy;

    // find the fast direction
    if(dx>dy){
        // x is fast
        pdx = incx;
        pdy = 0; //pd is parralel step and dd is diagonal step
        ddx = incx;
        ddy = incy;
        deltaslowdir = dy; 
        deltafastdir = dx;
    }else{
        // y is fast
        pdx = 0;
        pdy = incy;
        ddx = incx;
        ddy = incy;
        deltaslowdir = dx;
        deltafastdir = dy;
    }

    // last initialisations
    x = xstart;
    y = ystart;
    err = deltafastdir/2;
    
    color = lut.getInstance().rgb_to_8bit(colorstart.x + zcolors, colorstart.y + zcolors, colorstart.z + zcolors);
    wm.printxyc(x, y, color, COLOR_BLACK, true, padders[findpad(zstart)]);
    raster[y*height + x] = polyid;
    colors[y*height + x] = color;

    for(t = 0; t < deltafastdir; ++t){
        
        // adjusting the error term
        err -= deltaslowdir;
        
        if(err<0){
            // we have to go a step in the slow direction
            err += deltafastdir;
            x += ddx;
            y += ddy;
        }else{
            // fast step
            x += pdx;
            y += pdy;
        }

        float fast = static_cast<float>(deltafastdir);
        float red = (((fast - t)/fast) * (colorstart.x + zcolors)) + ((t/fast) * colorend.x + zcolore);
        float green = (((fast - t)/fast) * (colorstart.y + zcolors)) + ((t/fast) * colorend.y + zcolore);
        float blue = (((fast - t)/fast) * (colorstart.z + zcolors)) + ((t/fast) * colorend.z + zcolore);
        int curz = (((fast - t)/fast) * zstart) + ((t/fast) * zend);
        color = lut.getInstance().rgb_to_8bit(red, green, blue);
        
        // rasterise the pixel
        wm.printxyc(x, y, color, COLOR_BLACK, true, padders[findpad(curz)]);
        raster[y*height + x] = polyid;
        colors[y*height + x] = color;
    }

}
int max(int a, int b, int c){
    return a > b ? (a > c? a : c) : (b > c? b : c);
}

void fast_bresenham3d(Windowmanager &wm, Vector3d start, Vector3d end, Vector3d colorstart, Vector3d colorend, int polyid, int* raster, short* colors){

    int x0 = static_cast<int>(start.x), x1 = static_cast<int>(end.x), y0 = static_cast<int>(start.y), y1 = static_cast<int>(end.y), z0 = static_cast<int>(start.z), z1 = static_cast<int>(end.z);
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int dz = abs(z1 - z0), sz = z0 < z1 ? 1 : -1;
    int dm = max(dx,dy,dz), i = dm;
    x1 = y1 = z1 = dm/2;
    int red,green,blue;
    short color;
    ColorLut& lut = ColorLut::getInstance();

    for(;;){

        red = (((i) / dm) * colorstart.x) + (((dm - i)/dm) * colorend.x);
        green = (((i) / dm) * colorstart.y) + (((dm - i)/dm) * colorend.y);
        blue = (((i) / dm) * colorstart.z) + (((dm - i)/dm) * colorend.z);
        color = lut.getInstance().rgb_to_8bit(red, green, blue);
        
        wm.printxyc(x0,y0,COLOR_RED, COLOR_BLACK, true, "#");
        raster[y0 + wm.screenheight + x0] = polyid;
        colors[y0 + wm.screenheight + x0] = color;

        if(i-- == 0) break;

        x1 -= dx; if(x1 < 0){ x1 += dm; x0 += sx;}
        y1 -= dy; if(y1 < 0){ y1 += dm; y0 += sy;}
        z1 -= dz; if(z1 < 0){ z1 += dm; z0 += sz;}
    
    }

}

void render(Windowmanager &wm, Polygon poly){
    float angle, camera_len, n_len, cosphi;
    Vector3d camera_angle(0,0,1);
    int* edges = new int[wm.screenheight];

    // make sure poly is not out of bounds of screensize.
    assert(poly.a.x >= 0 && poly.a.x < wm.screenwidth);
    assert(poly.b.x >= 0 && poly.b.x < wm.screenwidth);
    assert(poly.c.x >= 0 && poly.c.x < wm.screenwidth);

    assert(poly.a.y >= 0 && poly.a.y < wm.screenheight);
    assert(poly.b.y >= 0 && poly.b.y < wm.screenheight);
    assert(poly.c.y >= 0 && poly.c.y < wm.screenheight);

    // init rastermatrix (array here to have one single block of mem)
    int* raster = new int[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ raster[i] = -1;}

    // init colormatrix to save color of nodes
    short* colors = new short[wm.screenwidth * wm.screenheight];
    for(int i = 0; i < (wm.screenwidth * wm.screenheight); ++i){ colors[i] = -1;}

    // rasterise the polygon from a-b, b-c and c-a
    fast_bresenham(wm, raster, colors, poly.polyid, poly.a_color, poly.b_color, wm.screenheight, poly.a.x, poly.a.y, poly.a.z, poly.b.x, poly.b.y, poly.b.z); 
    fast_bresenham(wm, raster, colors, poly.polyid, poly.b_color, poly.c_color, wm.screenheight, poly.b.x, poly.b.y, poly.b.z, poly.c.x, poly.c.y, poly.c.z);
    fast_bresenham(wm, raster, colors, poly.polyid, poly.c_color, poly.a_color, wm.screenheight, poly.c.x, poly.c.y, poly.c.z, poly.a.x, poly.a.y, poly.a.z);
 
    // find out if we see the front or the triangle, otherwise we dont need to draw it
    camera_len = camera_angle.lenght();
    n_len = poly.n.lenght();
    cosphi = camera_angle.scalar_product(poly.n) / (camera_len * n_len);
    angle = acos(cosphi) * 180.0 / PI;

/*
    if(angle <= 90){

        for(int y = 0; y < wm.screenheight; ++y){
            for(int x = 0; x < wm.screenwidth; ++x){
                if(raster[y * wm.screenheight + x] != -1){
                    edges[y]++;
                }
            }
        }

        for(int y = 0; y < wm.screenheight; ++y){

            bool inside = false;
            short curcolor;

            for(int x = 0; x < wm.screenwidth; ++x){
                if(edges[y] <= 0) {break;}

                // if we hit the border 
                if(raster[y * wm.screenheight + x] != -1){
                    // for the first time
                    inside = true;
                    curcolor = colors[y * wm.screenheight + x];
                    edges[y]--;
                    continue;
                }            
                if(inside && (edges[y] > 0)){
                    // we are inside, lets print a "pixel". 
                    wm.printxyc(x,y,curcolor, COLOR_BLACK, true, "*");
                }
            }
            
        }
    }*/

    delete []edges;
    delete []raster;
    delete []colors;
    return;
}

void render_polygon(Windowmanager &wm, std::vector<Polygon> polygons){

    wm.clearscreen();
    // Sorting the polygons to start rendering from the back.
    std::sort(polygons.begin(), polygons.end(), sortbyz);
 

    for(std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i){
 
        render(wm, *i);
    }

    return;
}
