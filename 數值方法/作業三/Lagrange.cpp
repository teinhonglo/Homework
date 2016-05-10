#include<iostream>
#include<stdio.h>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <conio.h>
#define PI 3.141592654

using namespace std;

struct point{
    double x;
    double y;
};
double calculate_the_q(point [] , int, int);
double calculate_lagrange_polynomial(point[], double[], int, double);

int main(void){
    int test_case, n;
    cout << "Please enter test case" << endl;
    cin >> test_case;
    int size_of_poly;
    if(test_case == 1 || test_case == 2){
        // TEST 1 && TEST 2
        // User input n, x, y
        // TEST 2 compute Q(3.4)
        cout << "Please enter N:" << endl;
        cin >> n;
        size_of_poly = n + 1;
        point poly[size_of_poly];
        double coefficient[size_of_poly];
        // user input x, y
        cout << "Please enter X of polynomial:" << endl;
        for(int i = 0 ; i < size_of_poly; i++)
            cin >> poly[i].x;
        cout << "Please enter F(X) of polynomial:" << endl;
        for(int i = 0 ; i < size_of_poly; i++)
            cin >> poly[i].y;
        // compute coefficient of lagrange
        for (int i = 0; i < size_of_poly; i++){
            coefficient[i] = calculate_the_q(poly, i, size_of_poly);
            printf( "q%d is %10f \n", i, coefficient[i]);
        }
        // if there are test case 2, we will compute Q(3.4)
        if(test_case == 2)
            cout << "Q(3.4) = " << calculate_lagrange_polynomial(poly, coefficient, size_of_poly, 3.4);
    }
    else if(test_case == 3 || test_case == 4){
        // TEST 3 && TEST 4
        // In TEST 3, default x is 0,2 * PI / 10, 4 * PI / 10 ... etc
        // In TEST 4, default x is 0,2 * PI / 20, 4 * PI / 20 ... etc
        // In TEST 3 and TEST 4, default Y is sin(x)
        size_of_poly = (test_case == 3)? 11 : 24;
        int interval_area = size_of_poly - 1;
        point poly[size_of_poly];
        double origin_x[size_of_poly];
        double coefficient[size_of_poly];

        for(int i = 0 ; i < size_of_poly; i++){
            poly[i].x = i * (2 * PI / interval_area);
            poly[i].y = sin(poly[i].x);
            origin_x[i] = poly[i].x;
        }
        // compute coefficient of polynomial
        for (int i = 0; i < size_of_poly; i++){
            coefficient[i] = calculate_the_q(poly, i, size_of_poly);
            printf( "q%d is %10f \n", i, coefficient[i]);
        }
        // compute error with original polynomial
        double error;
        cout << "Error:" << endl;
        for(int i = 0; i < size_of_poly; i++){
            error = abs(sin(origin_x[i]) - calculate_lagrange_polynomial(poly, coefficient, size_of_poly, poly[i].x));
            cout << "F(" << poly[i].x << ") - Q("<< poly[i].x<<"):"<< error << endl;
            if(i < size_of_poly - 1 ){
                double d = (poly[i].x + poly[i+1].x)/2.0;
                error = abs(sin(d) - calculate_lagrange_polynomial(poly, coefficient, size_of_poly, d));
                cout << "F("<<d << ") - Q("<< d <<"):" << error << endl;
            }
        }
    }
    getch();
    return 0;
}
double calculate_the_q(point poly [], int cur_index, int size_of_poly){
    double coefficient_q = 0;
    double temp_number= 1;
    double cur_x = poly[cur_index].x;
    double cur_y = poly[cur_index].y;

    for(int i = 0; i < size_of_poly; i++){
        if (i != cur_index)
            temp_number = temp_number * (cur_x - poly[i].x);
    }
    coefficient_q = cur_y / temp_number;
    return coefficient_q;
}
double calculate_lagrange_polynomial(point poly[], double coefficient[], int size_of_poly, double var){
    double answer = 0;
    for(int i = 0; i < size_of_poly; i++){
        double temp = coefficient[i];
        if (temp == 0)
            continue;
        for(int j = 0; j < size_of_poly; j++){
            if(i != j){
                temp = temp*(var - poly[j].x);
            }
        }
        answer += temp;
    }
    return answer;
}
