#include "../include/main.hpp"

#define FPS_REFRESH 1.0
#define FPS_PRINTLEN 9 // 8 chars + '\0+ '\0'
#define X_ORIGIN 30
#define Y_ORIGIN 30
#define MOVE_AMOUNT 200
#define ROTATE_AMOUNT 50
#define IDLE_MOVEMENT (ROTATE_AMOUNT / 50)
#define COLOR_THRESHOLD 95
#define COLOR_MAX 255

using namespace std;

void move3dobject(Vector3d direction, std::vector<Polygon> &polygons)
{

    for (std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i)
    {

        (*i).a += direction;
        (*i).b += direction;
        (*i).c += direction;
    }
}

void turn3dobject(Vector3d axis, double alpha, std::vector<Polygon> &polygons)
{

    std::vector<double> xs, ys, zs;
    Vector3d center, ba, ca;
    int j = 0;

    //sum all vertex nodes up
    for (std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i)
    {

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
    for (int k = 0; k < j; k++)
    {

        center.x += xs.back();
        center.y += ys.back();
        center.z += zs.back();
    }

    center.x /= j;
    center.y /= j;
    center.z /= j;

    //move the object to (0,0,0), apply turning matrix and then move back to original coordinates
    for (std::vector<Polygon>::iterator i = polygons.begin(); i != polygons.end(); ++i)
    {

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

int parse_file(const char *filename, std::vector<Polygon> &result, bool colorful)
{

    std::vector<Polygon> tmp;
    std::ifstream infile(filename);
    std::string str, garbage1, garbage2;

    //Debugging strings
    std::string facet("facet");
    std::string normal("normal");
    std::string vertex("vertex");
    std::string outer("outer");
    std::string loop("loop");
    std::string endloop("endloop");
    std::string endfacet("endfacet");
    std::string endsolid("endsolid");

    Vector3d n, a, b, c, ba, ca, offset, color = Vector3d(COLOR_MAX, 0, 0);
    double x, minx, maxx, y, miny, maxy, z, minz, maxz;
    long currentColor = 0;

    if (!infile)
    {
        return -1;
    }

    //initial "solid"
    getline(infile, str);

    /*
    * Now we will parse all polygons and add them to our container.
    * The file format is the following:
    * facet normal [x_n] [y_n] [z_n]
    *  outer loop
    *   vertex [v1_x] [v1_y] [v1_z]
    *   vertex [v2_x] [v2_y] [v2_z]
    *   vertex [v3_x] [v3_y] [v3_z]
    *  endloop
    * endfacet
    * 
    */

    while (getline(infile, str))
    {
        std::istringstream firstLine(str);
        firstLine >> garbage1 >> garbage2 >> x >> y >> z;

        //if garbage1 == 'endsolid' we are nicely done
        if (garbage1.compare(endsolid) == 0)
        {
            break;
        }

        //check if we parsed a line with 'facet' and 'normal'
        if ((garbage1.compare(facet) != 0) && garbage2.compare(normal) != 0)
        {
            return -1;
        }
        /*
        n.x = x;
        n.y = y;
        n.z = z;*/

        //get next line
        getline(infile, str);
        std::istringstream secondLine(str);
        secondLine >> garbage1 >> garbage2;

        //check if we parsed the line with 'outer loop'
        if ((garbage1.compare(outer) != 0) && garbage2.compare(loop) != 0)
        {
            return -1;
        }

        //get first vertex line
        getline(infile, str);
        std::istringstream thirdLine(str);
        thirdLine >> garbage1 >> x >> y >> z;

        //check if we parsed a line with 'vertex x y z'
        if ((garbage1.compare(vertex)) != 0)
        {
            return -1;
        }

        a.x = x;
        a.y = y;
        a.z = z;

        if (x < minx)
            minx = x;
        if (x > maxx)
            maxx = x;
        if (y < miny)
            miny = y;
        if (y > maxy)
            maxy = y;
        if (z < minz)
            minz = z;
        if (z > maxz)
            maxz = z;

        //get second vertex line
        getline(infile, str);
        std::istringstream fourthLine(str);
        fourthLine >> garbage1 >> x >> y >> z;

        //check if we parsed a line with 'vertex x y z'
        if ((garbage1.compare(vertex)) != 0)
        {
            return -1;
        }

        b.x = x;
        b.y = y;
        b.z = z;

        if (x < minx)
            minx = x;
        if (x > maxx)
            maxx = x;
        if (y < miny)
            miny = y;
        if (y > maxy)
            maxy = y;
        if (z < minz)
            minz = z;
        if (z > maxz)
            maxz = z;

        //get third vertex line
        getline(infile, str);
        std::istringstream fifthLine(str);
        fifthLine >> garbage1 >> x >> y >> z;

        //check if we parsed a line with 'vertex x y z'
        if ((garbage1.compare(vertex)) != 0)
        {
            return -1;
        }

        c.x = x;
        c.y = y;
        c.z = z;

        if (x < minx)
            minx = x;
        if (x > maxx)
            maxx = x;
        if (y < miny)
            miny = y;
        if (y > maxy)
            maxy = y;
        if (z < minz)
            minz = z;
        if (z > maxz)
            maxz = z;

        //get line with 'endloop'
        getline(infile, str);
        std::istringstream sixthLine(str);
        sixthLine >> garbage1;

        //check if we parsed a line with 'endloop'
        if ((garbage1.compare(endloop)) != 0)
        {
            return -1;
        }

        //get line with 'endfacet'
        getline(infile, str);
        std::istringstream seventhLine(str);
        seventhLine >> garbage1;

        //check if we parsed a line with 'endfacet'
        if ((garbage1.compare(endfacet)) != 0)
        {
            return -1;
        }

        //Since some models off the internet are faulty, we will calculate our normal vectors by ourselves.
        //update n
        ba = a - b;
        ca = a - c;

        n = ba.cross_product(ca);
        if (n.lenght() == 0)
        {
            cout << "Found a polygon with a normal vector of lenght 0. Skipping it.\n";
            continue;
        }
        n = n.normalise();

        //we succesfully parsed a whole Polygon. Lets append it on our container.
        if (colorful)
        {
            if (currentColor == 0)
            {
                // red colors
                color.x -= 1;
                if(color.x < COLOR_THRESHOLD){
                    color.x = 0;
                    color.y = COLOR_MAX;
                    currentColor = 1;
                }
            }
            else if (currentColor == 1)
            {
                // green colors
                color.y -= 1;
                if(color.y < COLOR_THRESHOLD){
                    color.y = 0;
                    color.z = COLOR_MAX;
                    currentColor = 2;
                }
            }
            else
            {
                // blue colors
                color.z -= 1;
                if(color.z < COLOR_THRESHOLD){
                    color.z = 0;
                    color.x = COLOR_MAX;
                    currentColor = 0;
                }
            }
            tmp.push_back(Polygon(a,b,c,n, color, color, color));
        }
        else
        {
            tmp.push_back(Polygon(a, b, c, n));
        }

    }

    offset = Vector3d((X_ORIGIN - minx), (Y_ORIGIN - miny), (-1) * ((abs(maxz) - abs(minz)) / 2));

    for (Polygon &poly : tmp)
    {
        poly.a += offset;
        poly.b += offset;
        poly.c += offset;
    }

    result = tmp;

    return 1;
}

int main(int argc, char **argv)
{

    // Parsed object vector
    std::vector<Polygon> polys;

    if (!(argc == 2 || (argc == 3 && (std::string(argv[2]).compare("-colorful") == 0))))
    {
        cout << "Please specifiy file to inspect. Usage: './render file.stl'" << endl;
        return 1;
    }

    if (std::string(argv[1]).compare("-help") == 0)
    {
        cout << "Usage: './render file.stl'. If you would like to randomly color polygons use './render file.stl -colorful'" << endl;
        return 0;
    }
    else if (parse_file(argv[1], polys, (argc == 3)) == -1)
    {
        cout << "Parsing of the file failed.\nPlease make sure file is in directory, and in ASCII STL format." << endl;
        return 1;
    }
    else
    {
        cout << "Parsed file succesfully! :-)" << endl;
    }

    // Initialise ncurses library and windows
    Windowmanager wm(SCREENHEIGHT, SCREENWIDTH, 10, 10);
    setlocale(LC_ALL, "");

    // Local vars
    int c, hits, fps = 0, oldfps = 0;
    bool idle = true;
    char buf[255];
    std::array<int, KEY_MAX> keyhits;
    keyhits.fill(0);
    auto start = std::chrono::system_clock::now();
    auto last = start;
    double deltaTime;

    // Main loop
    while (true)
    {

        hits = 0;
        while ((c = getch()) != -1)
        {
            keyhits[c] = 1;
            ++hits;
        }

        if (idle && hits == 0)
        {
            turn3dobject(Vector3d(0, 1, 0), -IDLE_MOVEMENT * deltaTime, polys);
        }

        if (keyhits[' '] == 1)
        {
            idle = !idle;
        }

        if (keyhits['q'] == 1)
        {
            break;
        }
        if (keyhits['j'] == 1)
        {
            turn3dobject(Vector3d(0, 1, 0), ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['l'] == 1)
        {
            turn3dobject(Vector3d(0, 1, 0), -ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['i'] == 1)
        {
            turn3dobject(Vector3d(1, 0, 0), ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['k'] == 1)
        {
            turn3dobject(Vector3d(1, 0, 0), -ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['u'] == 1)
        {
            turn3dobject(Vector3d(0, 0, 1), ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['o'] == 1)
        {
            turn3dobject(Vector3d(0, 0, 1), -ROTATE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['w'] == 1)
        {
            move3dobject(Vector3d(0, -1, 0) * MOVE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['a'] == 1)
        {
            move3dobject(Vector3d(-1, 0, 0) * MOVE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['s'] == 1)
        {
            move3dobject(Vector3d(0, 1, 0) * MOVE_AMOUNT * deltaTime, polys);
        }
        if (keyhits['d'] == 1)
        {
            move3dobject(Vector3d(1, 0, 0) * MOVE_AMOUNT * deltaTime, polys);
        }

        // render current iteration
        render_object(wm, polys);

        // calc fps
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        deltaTime = std::chrono::duration<double>(end - last).count();
        last = end;

        if (elapsed.count() > FPS_REFRESH)
        {
            start = std::chrono::system_clock::now();
            oldfps = fps;
            fps = 0;
        }

        snprintf(buf, FPS_PRINTLEN, "fps: %3i", oldfps);
        wm.printxyc(0, 0, ColorLut::getInstance().rgb_to_8bit(0, 255, 0), COLOR_BLACK, true, buf);

        std::ostringstream stream;
        long distance = std::distance(polys.begin(), polys.end());
        stream << "Currently rendering " << distance << " Polygons per iteration\n";
        wm.printxyc(0, 1, ColorLut::getInstance().rgb_to_8bit(255, 0, 0), COLOR_BLACK, true, stream.str().c_str());

        ++fps;

        keyhits.fill(0);
    }

    return 0;
}
