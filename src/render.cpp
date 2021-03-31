#include "../include/render.hpp"

bool sortbyz(Polygon &lhs, Polygon &rhs)
{
    return lhs.getlastz() < rhs.getlastz();
}

int max(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int sgn(int x)
{
    return (x > 0) ? 1 : (x < 0) ? -1
                                 : 0;
}

void fast_bresenham(Windowmanager &wm, Vector3d &colorstart, Vector3d &colorend, int height, int xstart, int ystart, int zstart, int xend, int yend, int zend)
{

    int x, y, t, dx, dy, incx, incy, pdx, pdy, ddx, ddy, deltaslowdir, deltafastdir, err;
    short color;
    int zcolors = zstart, zcolore = zend;
    ColorLut &lut = ColorLut::getInstance();

    if (zstart > 0)
    {
        zcolors = 0;
    }
    else
    {
        zcolors *= 5;
    }
    if (zend > 0)
    {
        zcolore = 0;
    }
    else
    {
        zcolore *= 5;
    }

    // calc distances
    dx = xend - xstart;
    dy = yend - ystart;

    // check sign
    incx = sgn(dx);
    incy = sgn(dy);
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    // find the fast direction
    if (dx > dy)
    {
        // x is fast
        pdx = incx;
        pdy = 0; //pd is parralel step and dd is diagonal step
        ddx = incx;
        ddy = incy;
        deltaslowdir = dy;
        deltafastdir = dx;
    }
    else
    {
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
    err = deltafastdir / 2;

    color = lut.getInstance().rgb_to_8bit(colorstart.x + zcolors, colorstart.y + zcolors, colorstart.z + zcolors);
    wm.printxyc(x, y, color, color, true," ");

    for (t = 0; t < deltafastdir; ++t)
    {

        // adjusting the error term
        err -= deltaslowdir;

        if (err < 0)
        {
            // we have to go a step in the slow direction
            err += deltafastdir;
            x += ddx;
            y += ddy;
        }
        else
        {
            // fast step
            x += pdx;
            y += pdy;
        }

        float fast = static_cast<float>(deltafastdir);
        float red = (((fast - t)/fast) * (colorstart.x + zcolors)) + ((t/fast) * colorend.x + zcolore);
        float green = (((fast - t)/fast) * (colorstart.y + zcolors)) + ((t/fast) * colorend.y + zcolore);
        float blue = (((fast - t)/fast) * (colorstart.z + zcolors)) + ((t/fast) * colorend.z + zcolore);
        color = lut.getInstance().rgb_to_8bit(red, green, blue);

        // rasterise the pixel
        wm.printxyc(x, y, color, color, true," ");
    }
}

void render(Windowmanager &wm, Polygon poly)
{
    // rasterise the polygon from a-b, b-c and c-a
    fast_bresenham(wm, poly.a_color, poly.b_color, wm.screenheight, poly.a.x, poly.a.y, poly.a.z, poly.b.x, poly.b.y, poly.b.z);
    fast_bresenham(wm, poly.b_color, poly.c_color, wm.screenheight, poly.b.x, poly.b.y, poly.b.z, poly.c.x, poly.c.y, poly.c.z);
    fast_bresenham(wm, poly.c_color, poly.a_color, wm.screenheight, poly.c.x, poly.c.y, poly.c.z, poly.a.x, poly.a.y, poly.a.z);

    return;
}

void render_object(Windowmanager &wm, std::vector<Polygon> polygons)
{

    float angle, n_len, cosphi;
    static Vector3d camera_angle(0, 0, 1);
    static float camera_len = camera_angle.lenght();


    wm.clearscreen();
    // Sorting the polygons to start rendering from the back.
    std::sort(polygons.begin(), polygons.end(), sortbyz);

    for (std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i)
    {
        //if the polygon's normale is facing away from us, it is a backside polygon, and we do not need to render it.
        n_len = (*i).n.lenght();
        cosphi = camera_angle.scalar_product((*i).n) / (camera_len * n_len);
        angle = acos(cosphi) * 180.0 / PI;
        if(angle >= 90){
            continue;
        }


        //if polygon is out of bounds, we can not draw it and skip.
        if (((*i).a.x < 0 && (*i).a.x > wm.screenwidth) && ((*i).b.x < 0 && (*i).b.x > wm.screenwidth) && ((*i).c.x < 0 && (*i).c.x > wm.screenwidth))
            continue;

        if (((*i).a.y < 0 && (*i).a.y > wm.screenheight) && ((*i).b.y < 0 && (*i).b.y > wm.screenheight) && ((*i).c.y < 0 && (*i).c.y > wm.screenheight))
            continue;

        render(wm, *i);
    }
    return;
}
