#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <queue>
#define PI 3.14159265359

using namespace std;
const int N_Dimension = 256;
short Chrom_Matrix[N_Dimension][N_Dimension];
double Lumin_Matrix[N_Dimension][N_Dimension];
double DCT_Matrix[N_Dimension][N_Dimension];
double IDCT_Matrix[N_Dimension][N_Dimension];

struct index {
    int i;
    int j;
};

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
    input = fopen(FILENAME, "r");

    int curRow = 0;
    int curCol = 0;

    while((get_byte = fgetc(input))!= EOF){
        Chrom_Matrix[curRow][curCol];
        curCol++;
        if(curCol >= N_Dimension){
            curRow++;
            curCol %= N_Dimension;
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

void chrom2Lumin(int N, short Chrom_Matrix[][N_Dimension]){
    int does = 0;
    short B = 0;
    short G = 0;
    short R = 0;
    queue <index> idxQueue;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(does > 2){
                index Idx = idxQueue.front();
                int i_st = Idx.i;
                int j_st = Idx.j;
                idxQueue.pop();

                Idx = idxQueue.front();
                int i_nd = Idx.i;
                int j_nd = Idx.j;
                idxQueue.pop();

                Idx = idxQueue.front();
                int i_rd = Idx.i;
                int j_rd = Idx.j;
                idxQueue.pop();
                /**
                B = Chrom_Matrix[i_st][j_st];
                G = Chrom_Matrix[i_nd][j_nd];
                R = Chrom_Matrix[i_rd][j_rd];
                **/
                Lumin_Matrix[i_st][j_st]  = 0.299 * R + 0.587 * G + 0.144 * B;      // Y
                Lumin_Matrix[i_nd][j_nd] = 0.564 * (B - Lumin_Matrix[i_st][j_st]);  // CB
                Lumin_Matrix[i_rd][j_rd] = 0.299 * (R - Lumin_Matrix[i_st][j_st]);                  // CR
                does %= 3;
            }else{
                index curIdx;
                curIdx.i = i;
                curIdx.j = j;
                idxQueue.push(curIdx);
                does++;
                switch(does){
                    case 0:
                        B = Chrom_Matrix[i][j];
                        break;
                    case 1:
                        G = Chrom_Matrix[i][j];
                        break;
                    case 2:
                        R = Chrom_Matrix[i][j];
                        break;
                }
            }
        }
    }
}

void lumin2Chrom(int N, double Lumin_Matrix[][N_Dimension]){
    int does = 0;
    double Y = 0;
    double CB = 0;
    double CR = 0;
    queue <index> idxQueue;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(does > 2){
                index Idx = idxQueue.front();
                int i_st = Idx.i;
                int j_st = Idx.j;
                idxQueue.pop();

                Idx = idxQueue.front();
                int i_nd = Idx.i;
                int j_nd = Idx.j;
                idxQueue.pop();

                Idx = idxQueue.front();
                int i_rd = Idx.i;
                int j_rd = Idx.j;
                idxQueue.pop();
                /**
                CY = Lumin_Matrix[i_st][j_st];
                CB = Lumin_Matrix[i_nd][j_nd];
                CR = Lumin_Matrix[i_rd][j_rd];
                **/
                Chrom_Matrix[i_st][j_st] = (short)(Y + 1.402 * CR);
                Chrom_Matrix[i_nd][j_nd] = (short)(Y - 0.344 * CB - 0.714 * CR);
                Chrom_Matrix[i_nd][j_nd] = (short)(Y + 1.772 * CB);            // CR
                does %= 3;
            }else{
                index curIdx;
                curIdx.i = i;
                curIdx.j = j;
                idxQueue.push(curIdx);
                does++;
                switch(does){
                    case 0:
                        Y = Lumin_Matrix[i][j];
                        break;
                    case 1:
                        CB = Lumin_Matrix[i][j];
                        break;
                    case 2:
                        CR = Lumin_Matrix[i][j];
                        break;
                }
            }
        }
    }
}
void sampling(int N, double Lumin_Matrix){

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
            chrom2Lumin(N_Dimension, Chrom_Matrix);
            // do 8*8 block scan
            for(int i = 0 ; i <= N_Dimension; i += 16){
                for(int j = 0; j <= N_Dimension; j += 16){
                    //DCT_Convert(8, i, j, Gray_Matrix);
                    //Inverse_DCT_Convert(8, i, j, DCT_Matrix);
                }
            }
            lumin2Chrom(N_Dimension, Lumin_Matrix);
            file_output(FILENAME, IDCT_Matrix);
            printf("%s\n", FILENAME);
        }
    }
    FindClose(hList);
    return 0;
}
