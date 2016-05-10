#include <iostream>

using namespace std;
int i=0;
int j=0;
int gcd(int, int );
int main(){
    int numA,numB,ans_gcd;
    while(1){
        cin >> numA >> numB;
        if(cin.eof())
            break;
        ans_gcd=gcd(numA, numB);
        cout << i << " "<< j << " "<< ans_gcd<<endl;
    }
    return 1;
}

int gcd(int a, int b )
{
    int i_ = 1, j_ = 0;
    i = 0, j = 1;
    int c = a, d = b;

    while (true)
    {
        int q = c / d, r = c % d, t;
        if (r == 0) break;
        c = d; d = r;
        t = i_; i_ = i; i = t - q * i;
        t = j_; j_ = j; j = t - q * j;
    }
    return d;
}
