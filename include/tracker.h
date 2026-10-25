#pragma once

#include <vector>
#include "types.h"

bool updateTrack(Track& track,Point measurement,double gate);

int findNearestTrack(std::vector<Track> tracks,Point measurement,double gate);

void updateTracks(std::vector<Track>& tracks,std::vector<Point> measurements,
    double gate,int& nextId  ,double now);
class Tracker {
    public:
        Tracker(double gate);
        void update(std::vector<Point> measurements, double now);
        void print();
        void identify(Point cameraPosition,
        int robotId, double gate);
        void removeExpired(double now, double ttl);
        std::vector<Track>
        getTracks();

    private:
        std::vector<Track> tracks_;
        int nextId_ = 1;
        double gate_;

};