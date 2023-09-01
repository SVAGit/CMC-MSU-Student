#include <stdio.h> 

int fib(int n, int fib1, int fib2) { 
 if (n == fib1 + fib2) { 
  return 1; 
 } 
 if (fib1 + fib2 > n) { 
  return 0; 
 } 
  return fib(n, fib1 + fib2, fib1); 
} 

int main() { 
	int n; 
	scanf("%d", &n); 
	int arr[n];
	for (int i = 0; i < n; i++) 
		scanf("%d", &arr[i]);
	printf("Fibanachi items:\n");
	for (int i = 0; i < n; i++){
		if(arr[i]==0)
			printf("%d", arr[i]);
		if(fib(arr[i],1,0) == 1){ 
			printf("%d ", arr[i]); 
		}
	} 
}
