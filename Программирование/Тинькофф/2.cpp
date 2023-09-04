#include <iostream>
#include <string.h>
using namespace std;
#define LENGHT 200000

int main(){
	char word[] = {'s','h','e','r','i','f','f','\0'};
	char s[LENGHT];
	cin >> s;
	size_t lenght = strlen(s);
	int count = 0;
	size_t edge = strlen(word);
	size_t index = 0;
	size_t total = 0;
	for(size_t i = 0; i < lenght; i++){
		for(size_t j = index; j < edge; j++){
			if(word[j] != s[i]){
				break;
			}
			s[i] = s[total];
			s[total] = word[j];
			i = total;
			index++;
			total++;
			break;
		}
		if(index == edge){
			count++;
			index = 0;
		}
	}
	cout<< count;
	return 0; 
}
