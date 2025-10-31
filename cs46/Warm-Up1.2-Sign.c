#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void print_reverse(char *c) {
	for(int i=strlen(c)-1; i>=0; i--) {
		printf("%c", c[i]);
	}
	printf("%c", '\n');
}
void toString(int h) {
	char name[] = "| Your Name |";
	char tb[] = "|----------------+";//top or bottom
	//the top of the flag(when not neg h)
	if(h>0) { //case 1: pos
		printf("%s\n%s\n%s\n", tb, name, tb);
		for(int i=0; i<h-3; i++) {
			printf("|\n");
		}
	}
	else { //case 2: neg
		for(int i=0; i<abs(h)-3; i++) {
			printf(" |\n");
		}
		print_reverse(tb);
		print_reverse(name);
		print_reverse(tb);
	}
}
int main() {
	int h, l;//hight contain + or - length contain only + (the magnitude)
	printf("Enter the height of the sign: ");
	scanf("%d", &h);
	l = abs(h);
	//error
	if(l<3) {
		printf("error: too short!");
	}
	else if(l>12) {
		printf("error: too long!");
	}
	else { //print flag
		toString(h);
	}
}