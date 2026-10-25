#include <iostream>
#include <stdexcept>
#include <utility>
#include <cmath>
#include <vector>
#include "types.h"
#include "geometry.h"
#include "tracker.h"
#include "fusion.h"
#include "cluster.h"
#include "pipeline.h"

int main()
{
    Tracker tracker(1.0);

    // 第一帧：两辆车，每辆车产生两个雷达点。
    std::vector<Point> frame1{
        {5.0, 4.0}, {5.2, 4.0},
        {12.0, 8.0}, {12.2, 8.0},
        {24.0, 2.0}  // 孤立噪声点
    };

    processLidarFrame(tracker, frame1, 0.0);

    // 相机识别到机器人 101。
    auto [cameraX, cameraY] = pixelTofield(
        51, 40, 0, 0, 280, 150);
    tracker.identify({cameraX, cameraY}, 101, 0.8);

    std::cout << "frame 1:\n";
    tracker.print();

    // 第二帧：两辆旧车移动，同时出现第三辆车。
    std::vector<Point> frame2{
        {5.5, 4.0}, {5.7, 4.0},
        {12.3, 8.0}, {12.5, 8.0},
        {20.0, 10.0}, {20.2, 10.0}
    };


    processLidarFrame(tracker , frame2, 0.5);


    std::cout << "frame 2:\n";
    tracker.print();

    // 第三帧：只看到了第一辆车。
    std::vector<Point> frame3{
        {5.9, 4.0}, {6.1, 4.0}
    };



    processLidarFrame(tracker, frame3 , 1.0);

    // 到第 1.6 秒时，删除超过 1 秒没被观测到的轨迹。
    tracker.removeExpired(1.6, 1.0);

    std::cout << "after timeout:\n";
    tracker.print();

    std::vector<Track> currentTracks = tracker.getTracks();
    Track radar = currentTracks[0];

    RadioPosition radio{101, {6.2, 4.1}, 1.5};

    Point fresh = selectPosition(radar, radio, 1.6, 0.3);
    std::cout << "fresh radio: " << fresh.x << "," << fresh.y << '\n';

    Point expired = selectPosition(radar, radio, 1.9, 0.3);
    std::cout << "expired radio: " << expired.x << "," << expired.y << '\n';




}