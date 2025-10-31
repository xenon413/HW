#include <stdio.h>
void print_line(int l, char sign) { //l = width -2
	printf("%c", sign);
	for(int i=0; i<l; i++) {
		printf("%c", '-');
	}
	printf("%c\n", sign);
}

int main() {
	int w, h;//declare
	printf("%s", "Enter grill width: ");//prompt for width
	scanf("%d", &w);//user enter w val
	printf("%s", "Enter grill height: ");//prompt for height
	scanf("%d", &h);//user enter h val
	if(h<2 || h>12 || w<2 || w>30) { // all error cases
		if(h<2) {
			printf("%s", "Grill height is too low.\n");
		}
		else if(h>12) {
			printf("%s", "Grill height is too high.\n");
		}
		if(w<2) {
			printf("%s", "Grill width is too low.\n");
		}
		else if(w>30) {
			printf("%s", "Grill width is too high.\n");
		}
		printf("%s", "The width must be 2-30 and the height must be 2-12.\n");
	}
	else { //print grill
		for(int i=0; i<h; i++) { //height
			if(i==0 || i == h-1) { //top and bottom of the grill
				print_line(w-2, '+');
			}
			else { //mid hight of the grill
				print_line(w-2, '|');
			}
		}
	}
	return 0;
}