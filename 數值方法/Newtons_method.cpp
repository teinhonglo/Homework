#include <iostream>
#include <iomanip>
#include <cmath>

#define fx value_of_function(chose, x)
#define diff_fx diff_function(chose, x, errors)
#define format 15
#define demarcation "----------------------------------------------------------------------------"

using namespace std;
double diff_function(int, double, double);
double newton_method(int, double, int, double);
double value_of_function(int, double);

double initial_v = 0;

int main()
{
	int chose, do_N_time;
	double errors;
	cout << "Please input Initial point, Times, Tolerance and chose" << endl;
	cin >> initial_v >> do_N_time >> errors >> chose ;
	cout << "Time:" << setw(2) << "N" << setw(format) << "point" << endl;
	cout << demarcation << endl;
	if ( initial_v >= 0)
        newton_method(chose, initial_v, do_N_time, errors);
    else
        cout << "error, input number cannot be negative" << endl;
    return 0;
}
double newton_method(int chose, double x, int do_N_time, double errors)
{
    double x2 = 0;
    for(int i = 0 ; i < do_N_time ; i++)
    {
        cout << "Step:" << setw(2) << i + 1 << setw(format) << x << endl;
        if (diff_fx != 0)
        {
            x2 = x - fx / diff_fx;
            if (abs( (x2 - x) / x) < errors)
            {
                cout << demarcation << endl;
                cout << "can tolerance, root is :" << x2 << endl;
                return 0;
            }
            x = x2;
        }
        else
        {
            return x;
        }
    }
    return 0;
}
/**
    differential format
    (1).give chose function and differential x
    (2).section h = errors(precision)
*/
double diff_function(int chose, double x, double errors)
{
    double h = errors;
    return (value_of_function(chose, x + h ) - value_of_function(chose, x - h )) / (2 * h) ;
}

double value_of_function(int chose, double x)
{
    switch (chose)
    {
        case 0:
            return x * x - initial_v ;
            break;
        default :
            return x * x - initial_v ;
            break;
    }
}
