#include "ball.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace cv;

Ball::Ball(unsigned int r, Vec3b c) 
    : radius(r), color(c)
{
    srand(static_cast<unsigned int>(time(0)) + rand());
    center.x = rand() % (960 - 2*radius) + radius;
    center.y = rand() % (720 - 2*radius) + radius;
    x_velocity = rand() % 20 + 10;
    y_velocity = rand() % 20 + 10;
}

void Ball::updatePos()
{
    center.x += x_velocity;
    center.y += y_velocity;

    if (center.x <= radius || center.x >= 960 - radius)
    {
        x_velocity = -x_velocity;
    }else if (center.y <= radius || center.y >= 720 - radius)
    {
        y_velocity = -y_velocity;
    }
}

void Ball::drawBall(Mat &frame)
{
    circle(frame, center, radius, color, FILLED);
}

Point Ball::getBallPos()
{
    return this->center; 
}
