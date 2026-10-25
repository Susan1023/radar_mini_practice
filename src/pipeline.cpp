#include "pipeline.h"
#include "cluster.h"

void processLidarFrame(
    Tracker& tracker,
    const std::vector<Point>& points,
    double now

)
{
    std::vector<Point> centers =findClusters(points, 0.3 ,2 );
    tracker.update(centers,now);
}