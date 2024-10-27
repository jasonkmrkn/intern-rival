#include <iostream>
#include <cmath>

using namespace std;

void DHARMI(double theta1, double theta2, double theta3);
void LILDAN(double theta1, double theta2, double theta3);

int main() {
    char robot;
    double theta1, theta2, theta3;
    
    cin >> robot >> theta1 >> theta2 >> theta3;
    
    if(robot == 'L') 
    {
        LILDAN(theta1, theta2, theta3);
    } else if(robot == 'D') 
    {
        DHARMI(theta1, theta2, theta3);
    }
    
    return 0;
}


double degToRad(double deg) 
{
    return deg * M_PI / 180.0;
}

void DH_Transform(double alpha, double a, double d, double theta, double matrix[4][4]) 
{
    double c_theta = cos(degToRad(theta));
    double s_theta = sin(degToRad(theta));
    double c_alpha = cos(degToRad(alpha));
    double s_alpha = sin(degToRad(alpha));
    
    matrix[0][0] = c_theta;
    matrix[0][1] = -s_theta * c_alpha;
    matrix[0][2] = s_theta * s_alpha;
    matrix[0][3] = a * c_theta;
    
    matrix[1][0] = s_theta;
    matrix[1][1] = c_theta * c_alpha;
    matrix[1][2] = -c_theta * s_alpha;
    matrix[1][3] = a * s_theta;
    
    matrix[2][0] = 0;
    matrix[2][1] = s_alpha;
    matrix[2][2] = c_alpha;
    matrix[2][3] = d;
    
    matrix[3][0] = 0;
    matrix[3][1] = 0;
    matrix[3][2] = 0;
    matrix[3][3] = 1;
}

void multiply_matrix(double A[4][4], double B[4][4], double result[4][4]) 
{
    double temp[4][4] = {0};
    for(int i = 0; i < 4; i++) 
    {
        for(int j = 0; j < 4; j++) 
        {
            temp[i][j] = 0;
            for(int k = 0; k < 4; k++) 
            {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for(int i = 0; i < 4; i++) 
    {
        for(int j = 0; j < 4; j++) 
        {
            result[i][j] = temp[i][j];
        }
    }
}

void copy_matrix(double source[4][4], double dest[4][4]) 
{
    for(int i = 0; i < 4; i++) 
    {
        for(int j = 0; j < 4; j++) 
        {
            dest[i][j] = source[i][j];
        }
    }
}

void LILDAN(double theta1, double theta2, double theta3) 
{
    double d1 = 5.0; 
    double a2 = 3.0; 
    double a3 = 2.0; 
    
    double T1[4][4], T2[4][4], T3[4][4];
    double result[4][4] = {0};
    double temp[4][4] = {0};
    
    DH_Transform(90, 0, d1, theta1, T1); 
    DH_Transform(0, a2, 0, theta2, T2);   
    DH_Transform(0, a3, 0, theta3, T3);   
    
    multiply_matrix(T1, T2, temp);
    multiply_matrix(temp, T3, result);
    
    double x = round(result[0][3] * 100) / 100;
    double y = round(result[1][3] * 100) / 100;
    double z = round(result[2][3] * 100) / 100;
    
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
}

void DHARMI(double theta1, double theta2, double theta3) 
{
    double d1 = 6.0; 
    double a2 = 3.0; 
    double a3 = 2.0; 
    
    double T1[4][4], T2[4][4], T3[4][4];
    double result[4][4] = {0};
    double temp[4][4] = {0};
    
    DH_Transform(90, 0, d1, theta1, T1);  
    DH_Transform(0, a2, 0, theta2, T2);   
    DH_Transform(0, a3, 0, theta3, T3);  
    
    multiply_matrix(T1, T2, temp);
    multiply_matrix(temp, T3, result);
    
    double x = round(result[0][3] * 100) / 100;
    double y = round(result[1][3] * 100) / 100;
    double z = round(result[2][3] * 100) / 100;
    
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
}