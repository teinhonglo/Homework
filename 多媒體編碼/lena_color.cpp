#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <queue>
#define PI 3.14159265359

using namespace std;
const int N_Dimension = 256;
short B[N_Dimension][N_Dimension];
short G[N_Dimension][N_Dimension];
short R[N_Dimension][N_Dimension];
double Y[N_Dimension][N_Dimension];
double CR[N_Dimension][N_Dimension];
double CB[N_Dimension][N_Dimension];
double DCT_Matrix[N_Dimension][N_Dimension];
double IDCT_Matrix[N_Dimension][N_Dimension];

struct index {
    int i;
    int j;
};

void printArray(short matrix[][N_Dimension], int N){
    for(int row = 0 ; row < N; row++){
        for(int col = 0 ; col < N; col++)
            printf("%x ", matrix[row][col]);
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
    int does = 0;
    int c = 0;
    while((get_byte = fgetc(input))!= EOF){
        if(does > 2){
            does %= 3;
            curCol++;
            if(curCol >= N_Dimension){
                curRow++;
                curCol %= N_Dimension;
            }

        }
        switch(does){
            case 0:
                B[curRow][curCol] = get_byte;
                break;
            case 1:
                G[curRow][curCol] = get_byte;
                break;
            case 2:
                R[curRow][curCol] = get_byte;
                break;
        }
        does++;
        c++;
    }
    printf("%x ", c);
    fclose(input);
}

void file_output(char * FILENAME, short B[][N_Dimension], short G[][N_Dimension], short R[][N_Dimension]){
    FILE *input;
    input = fopen(&FILENAME[11], "wb");
    for(int row = 0; row < N_Dimension; row++){
        for(int col = 0; col < N_Dimension; col++){
            fwrite(&B[row][col], sizeof(char), 1, input);
            fwrite(&G[row][col], sizeof(char), 1, input);
            fwrite(&R[row][col], sizeof(char), 1, input);
        }
    }
    fclose(input);
}

void chrom2Lumin(int N, short B[][N_Dimension], short G[][N_Dimension], short R[][N_Dimension]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            Y[i][j]  = 0.299 * R[i][j] + 0.587 * G[i][j] + 0.144 * B[i][j];        // Y
            CB[i][j] = 0.564 * (B[i][j] - Y[i][j]);                                 // CB
            CR[i][j] = 0.713 * (R[i][j] - Y[i][j]);                                 // CR
        }
    }

}

void lumin2Chrom(int N, double Y[][N_Dimension], double CR[][N_Dimension], double CB[][N_Dimension]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            R[i][j] = (short)(Y[i][j] + 1.402 * CR[i][j]);
            G[i][j] = (short)(Y[i][j] - 0.344 * CB[i][j] - 0.714 * CR[i][j]);
            B[i][j] = (short)(Y[i][j] + 1.772 * CB[i][j]);
        }
    }
}
void sampling(int N, int i_start, int j_start, double Y[][N_Dimension], double CR[][N_Dimension], double CB[][N_Dimension]){
    // 4:1:1
    double avg_CR = 0;
    double avg_CB = 0;
    for(int i = i_start; i < N + i_start; i += 2){
        for(int j = j_start; j < N + j_start; j += 2){
            avg_CR = ( CR[i][j] + CR[i+1][j] + CR[i][j+1] + CR[i+1][j+1]) / 4;
            avg_CB = ( CB[i][j] + CB[i+1][j] + CB[i][j+1] + CB[i+1][j+1]) / 4;
            CR[i][j] = CR[i+1][j] = CR[i][j+1] = CR[i+1][j+1] = avg_CR;
            CB[i][j] = CB[i+1][j] = CB[i][j+1] = CB[i+1][j+1] = avg_CB;
        }
    }
}
int main() {
    // file path
    char InputPath[65535] = "lena_color";
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
            //16* 16 block sampling
            chrom2Lumin(N_Dimension, B, G, R);
            for (int i = 0; i < N_Dimension; i += 16){
                for(int j = 0; j < N_Dimension; j += 16){
                    sampling(16, i, j, Y, CR, CB);
                }
            }
            lumin2Chrom(N_Dimension, Y, CR, CB);
            file_output(FILENAME, B, G, R);
            printf("%s\n", FILENAME);
        }
    }
    FindClose(hList);
    return 0;
}
