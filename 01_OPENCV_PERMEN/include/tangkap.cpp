#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "ball.h"
#include <iostream>

using namespace cv;
using namespace std;

unsigned int jumlah_permen_tertangkap = 0;

void tangkap(Scalar lower_tresh, Scalar upper_tresh) {
    VideoCapture capture(0);

    Mat frame, frame_resize, frame_flip, frame_hsv, frame_mask;
    Vec3b colors[] = {Vec3b(0, 0, 255), Vec3b(0, 255, 0), Vec3b(255, 0, 0)};

    vector<Ball*> balls;
    for (int i = 0; i < 3; i++)
    {
        balls.push_back(new Ball(30, colors[i]));
    }
    
    while (true)
    {
        capture >> frame;
        resize(frame, frame_resize, Size(960, 720));
        flip(frame_resize,frame_flip, 1);
        cvtColor(frame_flip, frame_hsv, COLOR_BGR2HSV);

        inRange(frame_hsv, lower_tresh, upper_tresh, frame_mask);
        vector<vector<Point>> contours;
        findContours(frame_mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < contours.size(); i++)
        {
            unsigned int area = contourArea(contours[i]);
            if (area > 2500)
            {
                drawContours(frame_flip, contours, -1, Scalar(255, 255, 255), 2);
            }
        }

        for (int i = 0; i < 3; i++)
        {
            
            balls[i]->drawBall(frame_flip);
            balls[i]->updatePos();


            for(size_t j = 0; j < contours.size(); j++)
            {
                if (pointPolygonTest(contours[j], static_cast<Point2f>(balls[i]->getBallPos()), false) > 0)
                {
                    balls.erase(balls.begin() + i);
                    balls.push_back(new Ball(30, colors[i]));
                    jumlah_permen_tertangkap++;
                }
            }
        }

        string text_poin = "Permen tertangkap : " + to_string(jumlah_permen_tertangkap);
        putText(frame_flip, text_poin, Point(50,50), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 0), 2);
        
        
        namedWindow("Tangkap Permennya!");
        imshow("Tangkap Permennya!", frame_flip);
        if (waitKey(30) == 27) break;
    }
    
    for (Ball *ball : balls)
    {
        delete ball;
    }

}
