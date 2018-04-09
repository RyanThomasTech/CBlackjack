#include <stdlib.h>
#include <stdio.h>

int main(){
	int i, j, k, maxNum, printNum;
	for (i=1; i<9; i++){
		for (int toCenter = 9; toCenter>i; toCenter--){
			printf(" ");
		}
		for (j=0; j<i; j++){
			maxNum=i+j;
			printNum=maxNum%10;
			printf("%d",printNum);
		}
		for (k=(maxNum-1); k>(i-1); k--){
			printf("%d",k%10);
		}
		printf("\n");
	}
	return 0;
}
