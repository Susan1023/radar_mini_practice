#include "cluster.h"
#include "geometry.h"
#include <stdexcept>

int countNearby(Point center, std::vector<Point> points, double radius) {
    
    int count = 0;

    for (Point p : points) {
        if (distance(center, p) <= radius) {
            count++;
        }
    }
    return count;
}


Point clusterCenter(Point seed,std::vector<Point> points, double radius) {
    double sumX =0;
    double sumY =0;
    int count =0;

    for (Point p: points) {
        if (distance(seed, p) <= radius) {
            sumX += p.x;
            sumY += p.y;
            count++;
        }
    }
    
    if (count ==0){
        throw std::invalid_argument("附近没有雷达点");
    }

    return {sumX / count, sumY / count};

}

std::vector<Point> findClusters(
    std::vector<Point> points,
    double radius,
    int minPoints)
{
    std::vector<Point> centers;
    std::vector<bool> used(points.size(),false);
    for (std::size_t i= 0; i < points.size(); i++){
        if (used[i]){
            continue;
        }
        
    std::vector<Point> group;
    group.push_back(points[i]);
    used[i]= true;
    for (std::size_t k= 0; k<group.size(); k++){
        for (std::size_t j= 0; j < points.size(); j++){
            if (!used[j] && distance(group[k], points[j]) <= radius){
                group.push_back(points[j]);
                used[j]= true;
            }
        }
    }

    if (group.size() < static_cast<std::size_t>(minPoints)){
        continue;
    }
    double sumX = 0;
    double sumY = 0;

    for (Point p : group) {
        sumX += p.x;
        sumY += p.y;
    }

    Point center{
        sumX / group.size(),
        sumY / group.size()
    };

    centers.push_back(center);
    }
    return centers;
}
