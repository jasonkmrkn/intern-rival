#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define R 0.15
#define r_lildan 0.0635
#define r_dharmi 0.024

void LILDAN(vector<vector<double>> const &inputRobotVel);
void DHARMI(vector<vector<double>> const &inputRobotVel);

int main()
{
    string robot;
    getline(cin, robot);
    string flag;

    vector<vector<double>> inputRobotVel;

    while (true) 
    {
        string input;
        getline(cin, input);
        if (input == "GAS") break;

        vector<double> tempInput(3);
        stringstream ss(input);
        for (int i = 1; i < 4; i++) 
        {
            if (i == 3) ss >> tempInput[0];
            else ss >> tempInput[i];
        }
        inputRobotVel.push_back(tempInput);
    }

    cout << "\n";

    cout << "Received input velocities:" << endl;
    for (const auto& vel : inputRobotVel) 
    {
        cout << "omega: " << vel[0] << ", vx: " << vel[1] << ", vy: " << vel[2] << endl;
    }

    cout << "\n";
    
    if (robot == "LILDAN")
    {
        printf("∇\n");
        LILDAN(inputRobotVel);
    }
    else
    {
        printf("Δ\n");
        DHARMI(inputRobotVel);
    }
}

double degToRad(double deg) 
{
    return deg * M_PI / 180.0;
}

void LILDAN(vector<vector<double>> const &inputRobotVel)
{

    double matrix_h[3][3] = {
        {sin(degToRad(135)), -cos(degToRad(135)), R},
        {sin(degToRad(135)), cos(degToRad(135)), R},
        {sin(degToRad(90)), -cos(degToRad(90)), R}
        };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix_h[i][j] /= r_lildan;
        }
    }

    for (int i = 0; i < inputRobotVel.size(); i++)
    {
        double w1, w2, w3;
        double vx = inputRobotVel[i][1];
        double vy = inputRobotVel[i][2];
        double omega = inputRobotVel[i][0];

        w1 = matrix_h[0][0] * vx + matrix_h[0][1] * vy + matrix_h[0][2] * omega;
        w2 = matrix_h[1][0] * vx + matrix_h[1][1] * vy + matrix_h[1][2] * omega;
        w3 = matrix_h[2][0] * vx + matrix_h[2][1] * vy + matrix_h[2][2] * omega;

        cout << w1 << endl;
        cout << w2 << endl;
        cout << w3 << endl;
    }
}

void DHARMI(vector<vector<double>> const &inputRobotVel)
{
    double matrix_h[3][3] = {
        {-R, 1, 0},
        {-R, -0.5, -sin(degToRad(120))},
        {-R, -0.5, sin(degToRad(120))}
        };

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix_h[i][j] /= r_dharmi;
        }
    }

    for (int i = 0; i < inputRobotVel.size(); i++)
    {
        double w1, w2, w3;
        double omega = inputRobotVel[i][0];
        double vx = inputRobotVel[i][1];
        double vy = inputRobotVel[i][2];

        w1 = matrix_h[0][0] * omega + matrix_h[0][1] * vx + matrix_h[0][2] * vy;
        w2 = matrix_h[1][0] * omega + matrix_h[1][1] * vx + matrix_h[1][2] * vy;
        w3 = matrix_h[2][0] * omega + matrix_h[2][1] * vx + matrix_h[2][2] * vy;

        cout << w1 << endl;
        cout << w2 << endl;
        cout << w3 << endl;
    }
}
