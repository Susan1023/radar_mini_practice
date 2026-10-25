#include "tracker.h"
#include "geometry.h"
#include <iostream>


bool updateTrack(Track& track,Point measurement, double gate)
{
    if (distance(track.position,measurement) >gate){
        return false;
    }
    track.position = measurement;
    return true;
}



int findNearestTrack(std::vector<Track> tracks,Point measurement,double gate)

{
    int bestIndex = -1;
    double bestDistance = gate;

    for (std::size_t i=0; i<tracks.size(); i++){
        double d =distance(tracks[i].position, measurement);
        if (d <= bestDistance){
            bestDistance = d;
            bestIndex = i;
        }
    }
    return bestIndex;
}


void updateTracks(
    std::vector<Track>& tracks,
    std::vector<Point> measurements,
    double gate,
    int& nextId ,double now)

{
    std::size_t oldCount = tracks.size();
    std::vector<bool> matched(oldCount, false);

    for (Point measurement : measurements) {
        int bestIndex = -1;
        double bestDistance = gate;

        for (std::size_t i = 0; i < oldCount; i++) {
            if (matched[i]) {
                continue;
            }

            double d = distance(tracks[i].position, measurement);
            if (d <= bestDistance) {
                bestDistance = d;
                bestIndex = static_cast<int>(i);
            }
        }  // 比较完所有旧轨迹，再决定更新或新建。

        if (bestIndex >= 0) {
            updateTrack(tracks[bestIndex], measurement, gate);
            tracks[bestIndex].lastSeen = now;
            matched[bestIndex] = true;
        } else {
            Track newTrack{nextId, measurement};
            newTrack.lastSeen = now;
            tracks.push_back(newTrack);
            nextId++;
        }
    }
}

Tracker::Tracker(double gate)
{
    gate_ = gate;
}

void Tracker::update(std::vector<Point> measurements, double now)
{
    updateTracks(tracks_, measurements, gate_, nextId_, now);
}

void Tracker::print()
{
    for (Track t : tracks_) {
        std::cout << "tracker id=" << t.id
          << " robot=" << t.robotId
          << " position=" << t.position.x
          << "," << t.position.y << '\n';
    }
}

void Tracker::identify(Point cameraPosition, int robotId,
    double gate)
{
    int index = findNearestTrack(tracks_, cameraPosition, gate);
    if (index >=0){
        tracks_[index].robotId = robotId;
    }
}


void Tracker::removeExpired(double now , double ttl)
{
    std::vector<Track> remaining;

    for (Track t : tracks_){
        if ((now - t.lastSeen) <=ttl){
            remaining.push_back(t);
        }

    }
    tracks_ = remaining;
}


std::vector<Track>
Tracker::getTracks()
{
    return tracks_;
}