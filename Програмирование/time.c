#include <stdio.h>

struct time {
	int second;
	int minute;
	int hours;
};

void plus(struct time* n, int delta, int* count){
	int absolute;
	absolute = (n->second) + (n->minute)*60 + (n->hours)*3600;
	absolute += delta;
	n->second= absolute % 60;
	absolute/=60;
	n->minute= absolute % 60;
	absolute/=60;
	if(absolute > 24)
	(*count)++;
	n->hours = absolute % 24;
}

int print(struct time n, int count){
	if(count > 0){ 
	return printf("Time %d:%d:%d and next day.", n.hours, n.minute, n.second);
}
	else return printf("Time %d:%d:%d\n", n.hours, n.minute, n.second);	
}

int main(void){
	int delta;
	struct time start;
	int count=0;
	printf("Print delta:\n");
	scanf("%d", &delta);
	printf("Print your time:\n");
	scanf("%d %d %d", &start.hours, &start.minute, &start.second);
	plus(&start, delta, &count);
	print(start, count);
}
	
