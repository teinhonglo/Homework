#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <iostream>
#include<math.h>
#define PI 3.14159265359

using namespace std;
const int N_Dimension = 64;
short Gray_Matrix[N_Dimension][N_Dimension];
double DCT_Matrix[N_Dimension][N_Dimension];
double IDCT_Matrix[N_Dimension][N_Dimension];

void printArray(short matrix[][N_Dimension], int N_Dimension){
    for(int row = 0 ; row < N_Dimension; row++){
        for(int col = 0 ; col < N_Dimension; col++)
            printf("%x ", matrix[row][col]);
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

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
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
                    tempDCTSum += cu * cv * DCT[u][v] * cos( (2*i+1) * u *PI / (2 * N)) * cos( (2*j+1) * v *PI / (2 * N));
                }
            }
            IDCT_Matrix[i][j] = (2.0 / N ) * tempDCTSum;
            tempDCTSum = 0;
        }
    }
}
void file_input(char * FILENAME){
    FILE *input;
    short get_byte;
    input = fopen(FILENAME, "r");

    int curRow = 0;
    int curCol = 0;

    while((get_byte = fgetc(input))!= EOF){
        Gray_Matrix[curRow][curCol] = get_byte;
        curCol++;
        if(curCol > 63){
            curRow++;
            curCol %= 64;
        }
    }
    fclose(input);
}
void file_output(char * FILENAME, double outMat[][N_Dimension]){
    FILE *input;
    input = fopen(&FILENAME[11], "wb");
    for(int row = 0; row < N_Dimension; row++){
        for(int col = 0; col < N_Dimension; col++){
            char dct_add = outMat[row][col];
            fwrite(&dct_add, sizeof(char), 1, input);
        }
    }
    fclose(input);
}

int main() {

    char InputPath[65535] = "../RawData";
    char szDir[65535];
    char FILENAME[65535];

    WIN32_FIND_DATA FileData;
    HANDLE          hList;
    sprintf(szDir, "%s\\*", InputPath );
    if ( (hList = FindFirstFile(szDir, &FileData))==INVALID_HANDLE_VALUE )
        printf("No files be found.\n\n");
    else {
        while (1) {
            if (!FindNextFile(hList, &FileData)) {
                if (GetLastError() == ERROR_NO_MORE_FILES)
                    break;
            }
            sprintf(FILENAME, "%s\\%s", InputPath, FileData.cFileName);

            file_input(FILENAME);
            DCT_Convert(N_Dimension, Gray_Matrix);
            Inverse_DCT_Convert(N_Dimension, DCT_Matrix);
            file_output(FILENAME, IDCT_Matrix);

            printf("%s\n", FILENAME);
        }
    }
    FindClose(hList);

    return 0;
}



