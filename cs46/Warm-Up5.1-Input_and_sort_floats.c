#include<stdio.h>
void getPrice(float* a, float* b, float* c);
void swap(float* a, float* b);

int main() {
	float a, b, c;
	getPrice(&a, &b, &c);
	printf("The three price are: %.2f %.2f %.2f\n", a, b, c);
}

void getPrice(float* a, float* b, float* c) {
	printf("Enter the price of item 1: ");
	scanf("%f", a);
	printf("Enter the price of item 2: ");
	scanf("%f", b);
	printf("Enter the price of item 3: ");
	scanf("%f", c);
	for(int i=0; i<2; i++) {
		if(*b<*a)
			swap(a, b);
		if(*c<*b)
			swap(b, c);
	}
}
void swap(float* a, float* b) {
	float temp = *a;
	*a = *b;
	*b = temp;
}
