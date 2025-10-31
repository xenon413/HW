#include <stdio.h>
int main() {
	int a, b, c, d;
	printf("This program will sum two fractions.\nInput the first fraction: ");
	scanf("%d/%d", &a, &b);
	printf("Input the second fraction: ");
	scanf("%d/%d", &c, &d);
	printf("The sum is: %d/%d\n", a*d+c*b, b*d);
	return 0;
}
