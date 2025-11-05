#include <stdio.h>
//function prototype
void a(int* arr);//0-9
void b(int* arr);//10-19
void c(int* arr);//20-25
void d(int* arr);//26-39
int nextCollatz(int num);
void printArray(int* arr);
int main() {
	int arr[40];
	a(arr);
	b(arr);
	c(arr);
	d(arr);
	printArray(arr);
}
void a(int* arr) {
	for(int i=0; i<10; i++) {
		arr[i] = i;
	}
}
void b(int* arr) {
	for(int i=10; i<20; i++) {
		arr[i] = i*10;
	}
}
void c(int* arr) {
	*(arr+20) = 4;
	*(arr+21) = 8;
	*(arr+22) = 15;
	*(arr+23) = 16;
	*(arr+24) = 23;
	*(arr+25) = 42;
}
void d(int* arr) {
	int val = 7;
	for(int i=26; i<40; i++) {
		arr[i] = val;
		val = nextCollatz(val);
	}
}
void printArray(int* arr) {
	for(int i=0; i<40; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
int nextCollatz(int x) {
	if(x%2==0)
		return x/2;
	return x*3+1;
}
