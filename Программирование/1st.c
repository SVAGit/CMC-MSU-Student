#include <stdio.h>

int main(){
	int n=5;
	int mas[]={1,2,3,7,5};
	int max=0;
	int res;
	for(int i=0; i<n; i++){
		res = mas[i]- mas[i+1];
		if(res<0)
		res = (-1)*res;
		if(res > max)
		max=res;
	}
	printf("%d", max);
}
