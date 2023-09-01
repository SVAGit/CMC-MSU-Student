#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

int palindrom(char* a,int count){
	int flag = 1;
	count--;
	for (int i = 0; i <= count; i++, count--){
		if( a[i] != a[count]){
			flag = 0;
			break;
			}
		}
	if (flag == 0)
		return 0;
	else
		return 1;
	}

char* scan_string(char* arr, int razmer){
	arr = calloc(razmer, sizeof(char));
	char bykva = getchar();
	for(int index = 0; bykva != '\n'; index++){
		if(&(arr[index]) == NULL){
			razmer += 8;
			arr = realloc(arr, razmer);
		}
		arr[index] = bykva;
		bykva = getchar();
	}
	return arr;
	}	

int main(){
	
	char* a = NULL;
	int n = 8;
	a = scan_string(a, n);
	int flag = palindrom(a, n);	
	if(flag == 1) 
		printf("This is polindrom");
	else
		printf("This is not polindrom");
	return 0;
}
