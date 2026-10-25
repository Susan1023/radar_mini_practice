#pragma once

struct Point {
    double x;
    double y;
};

struct Track {
    int id;
    Point position;
    int robotId = -1;
    double lastSeen = 0;
};

struct RadioPosition{
    int robotId;
    Point position;
    double lastSeen;
};