#include <stdio.h>

int main(){
	int mas[10] = {1,-1,2,3,4,5,-3,-4,7,8};
	int max = 1;
	int max2 = 1;
	int i_count = 0;
	int i_count2 =0;
	for(int i=0; i<9; i++){
		if(mas[i]*mas[i+1] > 0){
			max2 += 1;
			if(max2 > max){
				max = max2;
				i_count = i_count2;
			}
		}
		else {
			max2 = 1;
			i_count2 = mas[i+1];
		}
	}
	for(int i=1; i <= max; i++ ){
		printf("%d ", mas[i_count]);
		i_count++;
	}
}
			
			
