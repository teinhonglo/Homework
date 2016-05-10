#include <iostream>
#include <cmath>
#include <iomanip>
#define format 15
#define demarcation "----------------------------------------------------------------------------"
#define fa value_of_function(chose, a)
#define fb value_of_function(chose, b)

using namespace std;
double value_of_function(int, double);
int trisection (double, double, int, double, int);


int main()
{
    double a, b,tolerance;
    int do_N_time, chose;
    cout << "";
    cout << "Please input two point, maximum time, tolerance and chose function:" << "\n";
    cin >> a >> b >> do_N_time >> tolerance >> chose;
    cout << demarcation << endl;
    cout << setw(format) << "N_time" << setw(format) << "a" << setw(format) << "b" << setw(format)<< "p" << setw(format) << "f(p)" << endl;
    cout << demarcation << endl;
    if ( fa * fb < 0)
        trisection (a, b, do_N_time, tolerance, chose);
    else
        cout << setw(format) << " " << "error. " << endl;
    return 0;
}
/***
    get two point and divided into three equal sections.
    (1).using recursive.
    (2).please given point a, point b, maximum time, tolerance and chose function
***/
int trisection (double a, double b, int do_N_time, double tolerance, int chose)
{
    double  point [4] = {a, a + abs( b - a ) / 3.0, a + abs( b - a ) * 2.0 / 3.0, b};
    int root = 0;

    if (do_N_time > 0)
    {
        for (int i = 0; i < 3 ; i++)
        {
            //check root between of p1 or p2
            if (value_of_function(chose, point[i]) == 0 || value_of_function(chose, point[i+1]) == 0)
            {
                root = (value_of_function(chose, point[i]) == 0 )? point[i]: point[i+1];
                cout << setw(format)<< " " << "root is " << root << endl;
                return 0;
            }
            //check | p1 - p2 | < tolerance
            double interval = abs(point[i] - point[i+1]);
            if (interval < tolerance)
            {
                cout << demarcation << endl;
                cout << setw(format)<< " " <<"can tolerance, root is " <<(point[i] + point[i+1]) / 2 << endl;
                cout << demarcation << endl;
                return 0;
            }
            //check sign of p1 and p2 are difference
            double sign_of_points = value_of_function(chose, point[i]) * value_of_function(chose, point[i+1]);
            cout << setw(format) << 16 - do_N_time << setw(format) << point[i] << setw(format) << point[4] << setw(format)<< point[i+1] << setw(format) << value_of_function(chose, point[i+1]) << endl;
            if(sign_of_points < 0)
            {
                trisection (point[i], point[i+1], do_N_time-1, tolerance, chose);
            }
            else if(sign_of_points > 0)
            {
                continue;
            }
        }
    }
    else
    {
        cout << demarcation << endl;
        cout << setw(format)<< " "<< "Time to leave" << "\n";
        cout << demarcation << endl;
        return 0;
    }
}
/***
    get the value of function
    (1).give chose and unknown quantity x
***/
double value_of_function(int chose, double x)
{
    switch (chose)
    {
        case 0:
            return x * x * x + 4 * x * x - 10 ;
            break;
        case 1:
            return x * x - exp( -1 * x );
            break;
        case 2:
            return asin((x * 3 * x) / 4);
            break;
        default:
			return x * x * x + 4 * x * x - 10 ;
            break;
    }
}



