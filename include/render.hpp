#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>
#include <algorithm>
#include <assert.h>
#include <string>
#include <sstream>
#include "vector3d.hpp"
#include "polygon.hpp"
#include "windowmanager.hpp"
#include "colorlut.hpp"

#define PI 3.14159265

bool sortbyz(Polygon& lhs, Polygon& rhs);
void fast_bresenham(Windowmanager &wm, Vector3d& colorstart, Vector3d& colorend, int height, int xstart, int ystart, int zstart, int xend, int yend, int zend);
void render(Windowmanager &wm, Polygon poly);
void render_object(Windowmanager &wm, std::vector<Polygon> polygons);

#endif