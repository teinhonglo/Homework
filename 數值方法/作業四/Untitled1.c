#include <stdio.h>
int main(){
  FILE *fPtr;   /*�ŧiFILE��ƫ��A�� ����*/
  fPtr = fopen("test.txt","w");  /* fopen function , �����ɮצW�١A�M�g�J�覡 */
  fprintf(fPtr, " �n�g�J���r�� ");   /* �N�r��g�J�ɮ� */
  fclose(fPtr); /* �����ɮ� */

 return 0;
}

