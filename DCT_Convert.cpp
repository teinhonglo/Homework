#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include<math.h>
#define PI 3.14159265359

using namespace std;
const int N_Dimension = 64;
short Gray_Matrix[N_Dimension][N_Dimension];
double DCT_Matrix[N_Dimension][N_Dimension];

void printArray(double matrix[][N_Dimension], int N_Dimension){
    for(int row = 0 ; row < N_Dimension; row++){
        for(int col = 0 ; col < N_Dimension; col++)
            printf("%f ", matrix[row][col]);
        cout << '\n';
    }
}

void DCT_Convert(int N, short matrix[][N_Dimension]){
    double cu = 0;
    double cv = 0;
    double tempDCTSum = 0;

    for(int u = 0; u < N; u++){
        for(int v = 0; v < N; v++){
            if(u){
                cu = 1;
            } else{
                cu = 1 / sqrt(2);
            }
            if(v){
                cv = 1;
            } else{
                cv = 1 / sqrt(2);
            }

            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    tempDCTSum += matrix[i][j] * cos( (2*i+1) * u *PI / (2 * N)) * cos( (2*j+1) * v *PI / (2 * N));
                }
            }
            DCT_Matrix[u][v] = (2.0 / N ) * cu * cv * tempDCTSum;
            tempDCTSum = 0;
        }
    }
}

void Inverse_DCT_Convert(int N, double DCT[][N_Dimension]){
    double cu = 0;
    double cv = 0;
    double tempDCTSum = 0;

    for(int u = 0; u < N; u++){
        for(int v = 0; v < N; v++){
            if(u){
                cu = 1;
            } else{
                cu = 1 / sqrt(2);
            }
            if(v){
                cv = 1;
            } else{
                cv = 1 / sqrt(2);
            }

            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    tempDCTSum += cu * cv * DCT[i][j] * cos( (2*i+1) * u *PI / (2 * N)) * cos( (2*j+1) * v *PI / (2 * N));
                }
            }
            Gray_Matrix[u][v] = (2.0 / N ) * tempDCTSum;
            tempDCTSum = 0;
        }
    }
}

int main() {
    FILE *input;
    short get_byte;
    input = fopen("BABOON64.RAW", "r");

    int curRow = 0;
    int curCol = 0;
    while((get_byte=fgetc(input))!= EOF){
        Gray_Matrix[curRow][curCol] = get_byte;
        curCol++;
        if(curCol > 63){
            curRow++;
            curCol %= 64;
        }
    }
    DCT_Convert(N_Dimension, Gray_Matrix);
    printArray(DCT_Matrix,N_Dimension);
    fclose(input);


    return 0;
}



