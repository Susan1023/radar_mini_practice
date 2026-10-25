#pragma once 

#include <vector>
#include "types.h"

int countNearby(Point center,std::vector<Point> points, double radius);

Point clusterCentetr(Point seed, std::vector<Point> points, double radius);

std::vector<Point> findClusters(
    std::vector<Point> points,double radius, int minPoints);