#include <stdio.h>
int main(){
  FILE *fPtr;   /*宣告FILE資料型態的 指標*/
  fPtr = fopen("test.txt","w");  /* fopen function , 給予檔案名稱，和寫入方式 */
  fprintf(fPtr, " 要寫入的字串 ");   /* 將字串寫入檔案 */
  fclose(fPtr); /* 關閉檔案 */

 return 0;
}

