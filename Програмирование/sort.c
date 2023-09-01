#include <stdio.h> 
	
int main(){
	int n;
	printf("How much elements in your array?\n");
	scanf("%d", &n);
	int array[n];
	printf("Plese scan your array\n");
	for(int i=0; i<n; i++){
		scanf("%d", &array[i]);
	}
	for( int i=0; i<n-1; i++){
		int minIndex=i;
		int j=i+1;
		for( ; j<n; j++ ){
			int count;
			if(array[minIndex] > array[j]){
				count=array[minIndex];
				array[minIndex]=array[j];
				array[j]=count;
				}
			}
		}
	for(int i=0; i<n; i++)
		printf("%d ",array[i]);
}
	 	
