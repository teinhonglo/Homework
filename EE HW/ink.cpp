#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include <stdio.h>

using namespace std;
void generateRandomArray(int*, int);
int totalConsumption(string, int *, int);
string transNumberSystem(int , int);
int Char2Integer (char);
void printArr(int arr [], int);

int main(void){
    srand(time(NULL));
    int maxNumberSystem = 36;
	int usrNum;
	int inkConsumption [maxNumberSystem];
	generateRandomArray(inkConsumption, maxNumberSystem);
	printArr ( inkConsumption, maxNumberSystem);

    cout << "Please input a non-zero positive number:" << "\n";
    cin >> usrNum;
    while(usrNum > 0){
        string numSystemString ;
        int minConsumption = 2000000;
        int minConsumptionNumSystem = 0;
        int curConsumption = 0;

        for(int numSystem = 2; numSystem < maxNumberSystem; numSystem++){
            numSystemString = transNumberSystem(usrNum, numSystem);
            curConsumption = totalConsumption(numSystemString , inkConsumption, maxNumberSystem);
            if (curConsumption < minConsumption){
                minConsumption = curConsumption;
                minConsumptionNumSystem = numSystem;
            }
        }

        cout << endl;
        cout << "The number system having the minimum ink consumption is :" << minConsumptionNumSystem << "\n";
        cout << "The minimum ink consumption is:" << minConsumption << "\n";
        cout << endl;

        cout << "Please input a non-zero positive number:" << "\n";
        cin >> usrNum;
    }

    getchar();
	return 0;
}

void generateRandomArray(int * arr, int length){
	for (int i = 0; i < length; i++)
        arr[i] = (int)(1 + rand()%10);
	return ;
}

int totalConsumption(string numberStr, int * consumptionList, int sizeOfConsumption){
	int ink = 0;
	for (int index = 0; index < numberStr.size(); index++ )
		ink += consumptionList [Char2Integer (numberStr[index])];
	return ink;
}

string transNumberSystem(int usrNum, int numSystem){
	string targetStr = "";
	char letter [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int temp = 0;
	while(usrNum > 0){
		temp = usrNum % numSystem;
        targetStr = letter[temp] + targetStr;
		usrNum /= numSystem;
    }
	return targetStr;
}

int Char2Integer (char c){
	char letter [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int length = sizeof(letter) / sizeof(letter[0]);
	for (int i = 0; i < length; i++)
		if ( c == letter[i])
			return i;
}

void printArr ( int arr [], int len ){
    int chanage_Line = (int)sqrt(len);
    cout <<"The table of ink consumption is:";
    for (int i = 0 ; i< len ; i++){
        if (i % chanage_Line == 0)
            cout << endl;
        cout << setw(2) << arr [i] << " ";
    }
    cout << endl ;
}
