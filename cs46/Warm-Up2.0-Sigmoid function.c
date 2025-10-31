#include <stdio.h>
#include <math.h>
//prototypes
float sigmoid(float x);
int main() {
	for(float i=-5; i<=5; i++) {
		printf("%.3f %.3f\n", i, sigmoid(i));
	}
	return 0;
}
float sigmoid(float x) {
	return 1/(1+exp(-x));
}
