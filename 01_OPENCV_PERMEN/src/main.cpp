#include "../include/ball.h"
#include "../include/tangkap.h"
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;


int hmin = 0, smin = 0, vmin = 0, hmax = 255, smax = 255, vmax = 255;

void typingEffect(const char *kalimat){
    while (*kalimat)
    {
        cout << *kalimat << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
        kalimat++;
    }
    cout << endl;
}

int main() {
    //Capture device untuk sumber video
    VideoCapture capture(0);
    if (!capture.isOpened())
    {
        cerr << "Webcam tidak bisa dibuka!" << endl;
        return 0;
    }

    typingEffect("Halo Mulyadi! Kamu kesulitan menangkap permen kamu?");
    typingEffect("Sini ku bantu!");
    typingEffect("Setelah prompt ini selesai, akan muncul 3 buah window untuk");
    typingEffect("kamu mengkonfigurasi jaring mu!");
    typingEffect("Atur trackbars dari hue min sampai val max agar window \"Camera Mask\"");
    typingEffect("hanya menampilkan warna putih pada jaring yang kamu mau.");
    typingEffect("Setelah selesai mengkonfigurasi jaring mu tekan \033[1mesc\033[0m!");    
    typingEffect("Siap menangkap permen mu Mulyadi? input 'y' jika kamu siap!");
    char input;
    cin >> input;
    
    namedWindow("Konfigurasi Jaring", 0);
    createTrackbar("Hue Min", "Konfigurasi Jaring", &hmin, 180);
    createTrackbar("Hue Max", "Konfigurasi Jaring", &hmax, 180);
    createTrackbar("Sat Min", "Konfigurasi Jaring", &smin, 255);
    createTrackbar("Sat Max", "Konfigurasi Jaring", &smax, 255);
    createTrackbar("Val Min", "Konfigurasi Jaring", &vmin, 255);
    createTrackbar("Val Max", "Konfigurasi Jaring", &vmax, 255);

    Mat frame, frame_flip, frame_hsv, frame_mask;

    while (true)
    {
        capture >> frame;
        flip(frame, frame_flip, 1);
        cvtColor(frame_flip, frame_hsv, COLOR_BGR2HSV);

        Scalar lower_tresh(hmin, smin, vmin);
        Scalar upper_tresh(hmax, smax, vmax);

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
        
        namedWindow("Camera");
        namedWindow("Camera Mask");
        imshow("Camera", frame_flip);
        imshow("Camera Mask", frame_mask);
        if (waitKey(30) == 27)                  //exit loop kalau user pencet 'esc' button
        {
            break;
        }
    }

    destroyAllWindows();
    capture.release();
    tangkap(Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax));

    return 0;
}