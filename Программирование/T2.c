#include <stdio.h> 
#include <stdlib.h> 

void check(char* s) { 
    int mas[64] = { 0 }; 
    for (int i = 0; mas[i] != '\0'; i++) { 
        i++; 
        if (mas[i] == 2) { 
            return; 
        } 
    } 
    printf("%s ", s); 
} 
int main() { 
    int size = 1; 
    char c; 
    int i = 0;
    char* s1 = (char*)calloc(1, sizeof(char)); 
     
    while(c != '\n') { 
		c = getchar();
        s1[i] = c; 
        size++; 
        s1 = (char*)realloc(s1, size);
        i++; 
    } 
    s1[i] = '\0'; 
    int size2 = 1; 
    char* s2 = (char*)calloc(1, sizeof(char)); 
    for (int i = 0; i < size; i++) { 
        if (s1[i] != ' '&&s1[i]!='\0') { 
            s2[size2 - 1] = s1[i]; 
            size2++; 
            s2 = (char*)realloc(s2, size2); 
        } 
        else if(s1[i]==' '||s1[i]=='\0') { 
            s2[size2 - 1] = '\0'; 
            check(s2); 
            size2 = 1; 
            s2 = (char*)realloc(s2, size2); 
        } 
    } 
}
