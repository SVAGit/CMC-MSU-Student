#include <stdio.h>

int main(void){
	int n,m,k,l;
	scanf("%d %d",&n,&m);
	printf("Введите К строку и L столбец");
	scanf("%d %d",&k,&l);
	int mas[n][m];
	int new_k[n-1][m-1];
	//первая часть кода//
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			scanf("%d", &mas[i][j]);
	for(int i=0;i<n;i++){
		int count=0;
		for(int c=0;c<k-1;c++){
			new_k[i][c]=mas[i][c];
			count=c++;
		}}
		if(count=k-1){
			for(int c=count;c<m-1;c++)
				new_k[i][c]=mas[i][c+1];
		}
	//вторая часть кода//
	for(int j=0;j<m-1;j++){
		int count=0;
		for(int c=0;c<l-1;c++){
			new_k[c][j]=mas[c][j];
			count=c++;
		}
		if(count=l-1){
			for(int c=count;c<n-1;c++)
				new_k[c][j]=mas[c+1][j];
		}
	}
	//выводим массив new_k//
	
}	
