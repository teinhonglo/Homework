#include <iostream>
#include <cstring>
#include <sstream>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <conio.h>
#define PI 3.141592654

using namespace std;
void divide_difference(double[], double[], double [], int);
void generate_newton_polynomial(double[], double[], int);
double calculate_newton_polynomial(double[], double[], int, double);
string db2Str(double);

int main(){
    int test_case, n;
    cout << "Please enter test case:" << endl;
    cin >> test_case;
    int size_of_poly;
    if(test_case == 1 || test_case == 2){
        // TEST 1 && TEST 2
        // User input n, x, y
        // TEST 2 compute P(3.4)
        // User can chose print polynomial or not.
        cout << "Please enter n:" << endl;
        cin >> n;
        size_of_poly = n + 1;
        double x[size_of_poly];
        double y[size_of_poly];
        double coefficient[size_of_poly];
        int maximum_step = n; //if n + 1 times , we have n step
        cout << "Please enter x:" << endl;
        for(int i = 0; i < size_of_poly; i++)
            cin >> x[i];
        cout << "Please enter y:" << endl;
        for(int i = 0; i < size_of_poly; i++)
            cin >> y[i];
        // using divide difference method
        divide_difference(x, y, coefficient, maximum_step);
        // if now is test2 we must print P(3.4)
        if(test_case == 2)
            cout << "P(3.4) = " << calculate_newton_polynomial(x, coefficient, size_of_poly, 3.4) << endl;
        // user can chose print polynomial or not.
        int prt = 0;
        cout << "Print polynomial?(yes:1, no:0)";
        cin >> prt ;
        if(prt == 1)
            generate_newton_polynomial(x, coefficient, size_of_poly);
    }
    else if(test_case == 3 || test_case == 4){
        // TEST 3 && TEST 4
        // In TEST 3, default x is 0,2 * PI / 10, 4 * PI / 10 ... etc
        // In TEST 4, default x is 0,2 * PI / 20, 4 * PI / 20 ... etc
        // In TEST 3 and TEST 4, default Y is sin(x)
        int test_point = 0;
        test_point = (test_case == 3)? 11 : 21;
        int interval_area = test_point - 1;
        double x[test_point];
        double y[test_point];
        double origin_x[test_point];
        double coefficient[test_point];
        //if n + 1 times , we have n step
        int maximum_step = test_point;
        for(int i = 0; i < test_point; i++){
            x[i] = i * (2 * PI / interval_area);
            y[i] = sin(x[i]);
            origin_x[i] = i * (2 * PI / interval_area);
        }
        // using divide method
        divide_difference(x, y, coefficient, maximum_step);
        // compute error with origin polynomial
        double error;
        cout << "Error:" << endl;
        int times = 0;
        for(int i = 0; i < test_point; i++){
            error = abs(sin(origin_x[i]) - calculate_newton_polynomial(x, coefficient, test_point, x[i]));
            cout << "F(" <<x[i] << ") - P ("<<x[i]<<"):"<< error << endl;
            if(i < test_point - 1 ){
                double d = (x[i] + x[i + 1])/2.0;
                error = abs(sin(d) - calculate_newton_polynomial(x, coefficient, test_point, d));
                cout << "F(" <<d<< ") - P("<<d<<"):" << error << endl;
            }
        }
        // user can chose print polynomial or not.
        int prt = 0;
        cout << "Print polynomial?(yes:1, no:0)";
        cin >> prt ;
        if(prt == 1)
            generate_newton_polynomial(x, coefficient, test_point);
    }
    getch();
    return 0;
}

void divide_difference(double x [],double y[], double coefficient [], int maximum_step){
    // divide difference
    cout << "Divide Difference:" << endl;
    coefficient[0] = y[0];
    for(int step = 0; step < maximum_step; step++){
        int eachStep = maximum_step - step; //for each step, we have n - step
        for(int j = 0; j < eachStep; j++){
            y[j] = (y[j + 1] - y[j]) / (x[j + step + 1] - x[j]);
        }
        coefficient[step + 1] = y[0];
    }
    // print coefficient of divide difference
    for(int i = 0; i < maximum_step; i++ ){
        cout << "F[X0";
        for (int j = 1 ; j <= i ; j++)
            cout << ",X" << j;
        cout << "] = " << coefficient[i] << endl;
    }
    cout << endl;
}

void generate_newton_polynomial(double x[], double coefficient[], int size_of_poly){
    cout << "Polynomial:" << endl;
    string polynomial = "" + db2Str(coefficient[0]);
    for(int i = 1; i < size_of_poly; i++){
        string temp = "+" + db2Str(coefficient[i]);
        for(int j = 0; j < i; j++)
            temp = temp + "*(x - " + db2Str(x[j]) + ")";
        polynomial += temp;
    }
    cout << polynomial;
    cout << endl;
}

double calculate_newton_polynomial(double x[], double coefficient[], int size_of_poly, double var){
    double answer = coefficient[0];
    for(int i = 1; i < size_of_poly; i++){
        double temp = coefficient[i];
        for(int j = 0; j < i; j++){
            temp = temp*(var - x[j]);
        }
        answer += temp;
    }
    return answer;
}

string db2Str(double d){
    string str;
    stringstream ss;
    ss << d;
    ss >> str;
    return str;
}
