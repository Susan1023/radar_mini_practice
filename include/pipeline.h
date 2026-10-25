#pragma once

#include <vector>
#include "tracker.h"

void processLidarFrame(

    Tracker& tracker,
    const std::vector<Point>& points,
    double now
);