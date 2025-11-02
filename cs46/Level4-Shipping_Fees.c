#include<stdio.h>
#include <math.h>
#define STR_MAX 100
float weight(char c);
int stringLength(char* s);
float price(char* s, int start, int end);
float fee(char* s);
int main() {
	char input[STR_MAX];
	int cnt = 0;
	float total = 0;
	while (1) {
		printf("Container: ");
		fgets(input, STR_MAX, stdin);
		if(input[0]=='.')
			break;
		total += fee(input);
		cnt++;
	}
	printf("%d containers, total shipping fee %.2f", cnt, total);
}
float weight(char c) {
	if(c>=97) {
		return (c-96)*0.1;
	}
	else {
		return (c - 38)*0.1;
	}
}
int stringLength(char* s) {
	int i=0;
	while (1) {
		if (s[i] == '\0')
			break;
		i++;
	}
	return i;
}
float price(char* s, int start, int end) {
	float p = 0;
	for(int i=start; i<=end; i++) {
		p+=weight(s[i])*2.75;
	}
	return p;
}
float fee(char* s) {
	int len = stringLength(s)-1;
	int Rstart = (len)/2;
	float l = price(s, 0, Rstart-1);
	float r = price(s, Rstart, len-1);
	if(l>r)
		return l;
	return r;
}
