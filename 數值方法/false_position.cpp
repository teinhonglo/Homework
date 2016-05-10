#include <iostream>
#include <cmath>
#include <iomanip>

#define format 15
#define demarcation "----------------------------------------------------------------------------"
#define f0 value_of_function(chose, p[0])
#define f1 value_of_function(chose, p[1])
#define fp value_of_function(chose, p2)
#define interval abs(p[0] - p[1])

double value_of_function(int, double);
int false_postion(double, double, int, double, int);

using namespace std;
int main()
{
    double a, b,tolerance;
    int do_N_time, chose;
    cout << "";
    cout << "Please input two point, maximum time, tolerance and chose function:" << "\n";
    cin >> a >> b >> do_N_time >> tolerance >> chose;
	false_postion (a, b, do_N_time, tolerance, chose);
	return 0;
}
/***
    false postion method
    (1).given a, b, N and TOL
    (2).chose function
***/
int false_postion (double a, double b, int do_N_time, double tolerance, int chose)
{
	double p[2];
    p[0] = a;
    p[1] = b;

    double p2 ;
    int bound_of_two_point[2] = {0, 0};
    cout << demarcation << endl;
    cout << "Time" << setw(2) << "N" << setw(format) << "a" << setw(format) << "b" << setw(format) << "p" << setw(format) << "f(p)" << endl;
    cout << demarcation << endl;
    if (  f0 * f1 < 0 )
    {
        for (int i = 0; i < do_N_time ; i++)
        {
            if( f0 == 0 || f1 == 0)
            {
                double root = (f0 == 0)? p[1] : p[0];
                cout << demarcation << endl;
                cout << setw(format) << " "<< "root is " << root << endl;
                cout << demarcation << endl;
                return 0;
            }
            if( interval < tolerance)
            {
                cout << demarcation << endl;
                cout << setw(format) << " "<<"can tolerance, root is " << (p[0] + p[1]) / 2 << endl;
                cout << demarcation << endl;
                return 0;
            }
            p2 = p[1] - f1 * ( p[1] - p[0] ) / (f1 - f0);
            cout  << "Step" << setw(2) << i + 1 << setw(format) << p[0] << setw(format) << p[1] << setw(format) << p2 << setw(format) << fp << endl;
            if (fp * f0 > 0)
            {
                p[0] = p[1];
                p[1] = p2;
            }
            else
            {
                p[1] = p2;
            }

            if (p[1] < p[0])
            {
                bound_of_two_point[1]++;
                bound_of_two_point[0] = 0;
            }
            else
            {
                bound_of_two_point[0]++;
                bound_of_two_point[1] = 0;
            }
            if (bound_of_two_point[0] >= 3 || bound_of_two_point[1] >= 3)
            {
                p[0] /= 2;
            }
        }
    }
    else
    {
        cout << setw(format) << " " << "error. " << endl;
    }
    return 0;
}

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
