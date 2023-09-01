#include <stdio.h>

int romanToInt(char * s){
  int sum = 0;
  for(int i = 0; s[i]; i++){
    if(s[i] == 'I' && (s[i++] == 'V' || s[i++] == 'X'))
      sum -= 2;
    if(s[i] == 'X' && (s[i++] == 'L' || s[i++] == 'C'))
      sum -= 20;
    if(s[i] == 'I' && (s[i++] == 'D' || s[i++] == 'M'))
      sum -= 200;
    if(s[i] == 'I')
      sum += 1;
    if(s[i] == 'V')
      sum += 5;
    if(s[i] == 'X')
      sum += 10;
    if(s[i] == 'L')
      sum += 50;
    if(s[i] == 'C')
      sum += 100;
    if(s[i] == 'D')
      sum += 500;
    if(s[i] == 'M')
      sum += 1000;
  }
  return sum;
}
int main(){
	char s[] = {'M','X'};
	printf("INT: %d", romanToInt(s));
}
