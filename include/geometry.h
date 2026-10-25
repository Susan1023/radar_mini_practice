#pragma once 

#include <utility>
#include "types.h"

double distance(Point a, Point b);

std::pair<double,double>
pixelTofield(
    double pixelX, double pixelY,
    double left, double top,
    double right, double bottom 
);

