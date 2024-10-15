#ifndef BALL_H
#define BALL_H

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

class Ball {
    private :
        Point center;
        unsigned int radius;
        int x_velocity;
        int y_velocity;
        Vec3b color;
    public :

    Ball(unsigned int r, Vec3b c);

    void updatePos();

    void drawBall(Mat &frame);

    Point getBallPos();
};


#endif