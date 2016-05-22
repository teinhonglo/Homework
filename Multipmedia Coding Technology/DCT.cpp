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

void printArray(double matrix[][N_Dimension], int N){
    for(int row = 0 ; row < N; row++){
        for(int col = 0 ; col < N; col++)
            printf("%f ", matrix[row][col]);
        cout << '\n';
    }
}

void DCT_Convert(int N, int i_start, int j_start, short matrix[][N_Dimension]){
    double cu = 0;
    double cv = 0;
    double tempDCTSum = 0;

    for(int u = i_start; u < N + i_start; u++){
        for(int v = j_start; v < N + j_start; v++){
            int _u = u - i_start;
            int _v = v - j_start;

            if(_u){
                cu = 1;
            } else{
                cu = 1 / sqrt(2);
            }
            if(_v){
                cv = 1;
            } else{
                cv = 1 / sqrt(2);
            }

            for(int i = i_start; i < N + i_start; i++){
                for(int j = j_start; j < N + j_start; j++){
                    int _i = i - i_start;
                    int _j = j - j_start;

                    tempDCTSum += matrix[i][j] * cos( (2 * _i  + 1) * _u *PI / (2 * N)) * cos( ( 2 * _j + 1) * _v *PI / (2 * N));
                }
            }
            DCT_Matrix[u][v] = (2.0 / N ) * cu * cv * tempDCTSum;
            tempDCTSum = 0;
        }
    }
}

void onlyDC (int N, int i_start, int j_start,double DCT[][N_Dimension]){
    for(int i = i_start; i < N + i_start; i++){
        for(int j = j_start; j < N + j_start; j++){
            if ( i == i_start && j == j_start){
                continue;
            } else{
                DCT[i][j] = 0;
            }
        }
    }
}

void remainDiag (int N, int i_start, int j_start, double DCT[][N_Dimension]){
    for(int i = i_start; i < N + i_start; i++){
        for(int j = j_start; j < N + j_start; j++){
            int _i = i - i_start;
            int _j = j - j_start;
            if (_i + _j <= 6){
                continue;
            } else{
                DCT[i][j] = 0;
            }
        }
    }
}

void top3row (int N, int i_start, int j_start, double DCT[][N_Dimension]){
    for(int i = i_start + 3; i < N + i_start; i++)
        for(int j = j_start; j < N + j_start; j++)
            DCT[i][j] = 0;
}

void top3col (int N, int i_start, int j_start, double DCT[][N_Dimension]){
    for(int i = i_start; i < N + i_start; i++)
        for(int j = j_start + 3; j < N + j_start; j++)
            DCT[i][j] = 0;
}

void Inverse_DCT_Convert(int N, int i_start, int j_start,double DCT[][N_Dimension]){
    double cu = 0;
    double cv = 0;
    double tempDCTSum = 0;

    for(int i = i_start; i < N + i_start; i++){
        for(int j = j_start; j < N + j_start; j++){
            for(int u = i_start; u < N + i_start; u++){
                for(int v = j_start; v < N + j_start; v++){
                    int _u = u - i_start;
                    int _v = v - j_start;
                    int _i = i - i_start;
                    int _j = j - j_start;

                    if(_u){
                        cu = 1;
                    } else{
                        cu = 1 / sqrt(2);
                    }
                    if(_v){
                        cv = 1;
                    } else{
                        cv = 1 / sqrt(2);
                    }
                    tempDCTSum += cu * cv * DCT[u][v] * cos( (2*_i+1) * _u *PI / (2 * N)) * cos( (2*_j+1) * _v *PI / (2 * N));
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
    input = fopen(FILENAME, "rb");

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
    input = fopen(&FILENAME[8], "wb");
    for(int row = 0; row < N_Dimension; row++){
        for(int col = 0; col < N_Dimension; col++){
            char dct_add = outMat[row][col];
            fwrite(&dct_add, sizeof(char), 1, input);
        }
    }
    fclose(input);
}

int main() {
    // file path
    char InputPath[65535] = "RawData";
    char szDir[65535];
    char FILENAME[65535];

    WIN32_FIND_DATA FileData;
    HANDLE          hList;
    // scan directory file
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
            // do 8*8 block scan
            for(int i = 0 ; i <= 56; i += 8){
                for(int j = 0; j <= 56; j += 8){
                    DCT_Convert(8, i, j, Gray_Matrix);
                    remainDiag(8, i, j, DCT_Matrix);
                    Inverse_DCT_Convert(8, i, j, DCT_Matrix);
                }
            }
            file_output(FILENAME, IDCT_Matrix);
            printf("%s\n", FILENAME);
        }
    }
    FindClose(hList);
    return 0;
}
