#include <stdio.h>
int main() {
	int l, w, a;//declare without init
	printf("Enter the height and width of a rectangle: ");//print promp
	scanf("%d %d", &l, &w);//user enter val
	a = l * w;//calc area
	printf("The area is %d sq in.", a);//print area
	return 0;
}
//./a.out
