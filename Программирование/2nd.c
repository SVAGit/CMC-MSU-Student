#include <stdio.h>

int main(){
	int n=8;
	int mas[]={1,2,3,2,1,4,0,0};
	int sum=0;
	int flag=0;
	for(int i=0; i<n ; i++){
		for(int j=0; j<i; j++){
			if(mas[j] > mas[i]){
			printf("%d ", mas[i]);
			flag=1;
			break;
		}}
		if(flag == 0)
		sum += mas[i];
		flag = 0;
	}
	printf("\n%d", sum);
	return 0;
}
			
