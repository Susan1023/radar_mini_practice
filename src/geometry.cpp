#include "geometry.h"
#include <cmath>
#include <stdexcept>//异常类型声明

std::pair<double , double> pixelTofield(
    double pixelX, double pixelY,
    double left, double top, double right ,double bottom)
{
    if (left >= right || top>= bottom)
    {
        throw std::invalid_argument("画面宽或高不能为零");

    }

    double fieldX = (pixelX - left) / (right - left) * 28.0;
    double fieldY = (pixelY - top) / (bottom - top) * 15.0;
    return {fieldX, fieldY};

}


double distance(Point a, Point b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

