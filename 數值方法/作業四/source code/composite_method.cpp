#include<iostream>
#include<math.h>
#include<conio.h>
#include<cmath>
#define PI 3.14159265359

using namespace std;
void midPoint(double, double, int);
void trapezoidal(double, double, int);
void simpson(double, double, int);
double poly_value(double, int);

int main(){
	int testCase = 0;
	double startPoint, endPoint;
	for(;testCase <= 5; testCase++){
        cout << "Test case:" << testCase + 1 << endl;
        switch(testCase){
            case 0:
                startPoint = 0;
                endPoint = PI;
            break;
            case 1:
                startPoint = 0;
                endPoint = 1;
            break;
            case 2:
                startPoint = 0;
                endPoint = 1;
            break;
            case 3:
                startPoint = -2;
                endPoint = 10;
            break;
            case 4:
                startPoint = 0;
                endPoint = 2;
            break;
            case 5:
                startPoint = -1;
                endPoint = 1;
            break;
        }
        midPoint(startPoint, endPoint, testCase);
        trapezoidal(startPoint, endPoint, testCase);
        simpson(startPoint, endPoint, testCase);
        cout << "----------------------------------------------" << endl << endl;
    }
	getch();
	return 0;
}
/*composite midpoint*/
void midPoint(double startPoint,double endPoint, int testCase){
	cout << "Composite Midpoint rule:" << endl;
	double h = 0;
	double valueX = 0;
	double curApproximation = 0;
	double lastApproximation = 0;
	double error = 0.000001;
	int m = 0;
	// initial step, n = 0
	h = (endPoint - startPoint) / 2;
    m = 1;
    for(int j = 0; j <= 1 / 2.0; j++){
        valueX = startPoint + (2 * j + 1) * h;
        lastApproximation += poly_value(valueX, testCase);
    }
    lastApproximation = 2 * h * lastApproximation;
    //other step, n = 2 to limit
	for(int n = 2; true; n += 2){
        h = (endPoint - startPoint) / (n + 2);
        m = (n + 2) / 2;
        for(int j = 0; j <= n / 2; j++){
            valueX = startPoint + (2 * j + 1) * h;
            curApproximation += poly_value(valueX, testCase);
        }
        curApproximation = 2 * h * curApproximation;
        if(abs(curApproximation - lastApproximation) > error){
            lastApproximation = curApproximation;
            curApproximation = 0;
        } else{
            break;
        }

	}
	cout << "Final Approximation : " << curApproximation << endl;
	cout << "Value of m : " << m << endl;
	cout << endl;
}
/*composite trapezoidal*/
void trapezoidal(double startPoint,double endPoint, int testCase){
	cout << "Composite Trapezoidal rule:" << endl;
	double h = 0;
	double valueX = 0;
	double curApproximation = 0;
	double lastApproximation = 0;
	double error = 0.000001;
	int m = 0;
	// initial step, n = 1
	h = (endPoint - startPoint);
    m = 1;
    for(int j = 1; j <= 0; j ++){
        valueX = startPoint + j * h;
        lastApproximation += poly_value(valueX, testCase);
    }
    lastApproximation *= 2;
    lastApproximation += poly_value(startPoint, testCase) + poly_value(endPoint, testCase);
    lastApproximation *= (h / 2);

    //other step, n = 2 to limit
	for(int n = 2; true; n++){
        h = (endPoint - startPoint) / n;
        m = n;
        for(int j = 1; j <= n - 1; j++){
            valueX = startPoint + j * h;
            curApproximation += poly_value(valueX, testCase);
        }
        curApproximation *= 2;
        curApproximation = curApproximation + poly_value(startPoint, testCase) + poly_value(endPoint, testCase);
        curApproximation = (h / 2) * curApproximation;

        if(abs(curApproximation - lastApproximation) > error){
            lastApproximation = curApproximation;
            curApproximation = 0;
        } else{
            if (curApproximation == 0) continue;
            break;
        }
	}
	cout << "Final Approximation : " << curApproximation << endl;
	cout << "Value of m : " << m << endl;
	cout << endl;
}
/*composite simpson's rule*/
void simpson(double startPoint,double endPoint, int testCase){
	cout << "Composite Simpson's rule:" << endl;
	double h = 0;
	double valueX = 0;
	double curApproximation = 0;
	double lastApproximation = 0;
	double error = 0.000001;
	int m = 0;
	double even_term = 0;
	double odd_term = 0;
	// initial step, n = 1
	h = (endPoint - startPoint);
    m = 1;
    for(int j = 1; j <= 2 / 2 - 1; j++){
        valueX = startPoint + 2 * j * h;
        even_term += poly_value(valueX, testCase);
    }
    even_term *= 2;
    for(int j = 1; j <= 2 / 2; j++){
        valueX = startPoint + (2 * j - 1) * h;
        odd_term += poly_value(valueX, testCase);
    }
    odd_term *= 4;
    lastApproximation = (h / 3) * ( poly_value(startPoint, testCase) + even_term + odd_term + poly_value(endPoint, testCase) );

    //other step, n = 2 to limit
	for(int n = 4; true; n += 2){
        even_term = 0;
        odd_term = 0;
	    h = (endPoint - startPoint) / n;
        m = n / 2;
        for(int j = 1; j <= n / 2 - 1; j++){
            valueX = startPoint + (2 * j) * h;
            even_term += poly_value(valueX, testCase);
        }
        even_term *= 2;
        for(int j = 1; j <= n / 2; j++){
            valueX = startPoint + (2 * j - 1) * h;
            odd_term += poly_value(valueX, testCase);
        }
        odd_term *= 4;
        curApproximation = (h / 3) * (poly_value(startPoint, testCase) + even_term + odd_term + poly_value(endPoint, testCase));
        if(abs(curApproximation - lastApproximation) > error){
            lastApproximation = curApproximation;
            curApproximation = 0;
        } else{
            if (curApproximation == 0) continue;
            break;
        }
	}
	cout << "Final Approximation : " << curApproximation << endl;
	cout << "Value of m : " << m << endl;

}
// return value of function
double poly_value(double value, int testCase){
	double x = value;
	switch(testCase){
		case 0: if(x == PI) return sin(0);
                else return sin(x);
		break;
		case 1:	return exp(x);
		break;
		case 2: return atan(x);
		break;
		case 3: return x * x + 2 * x + 8;
		break;
		case 4: return log(1 + x * x);
		break;
		case 5: return PI / ((1 + x * x) * (1 + x * x));
		break;
	}
}
