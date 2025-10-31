#include <stdio.h>
int collatz(int x);
int main() {
	int arr[40];
    //0-9
	for(int i=0; i<10; i++) {
		arr[i]=i;
	}
    //10-19
	for(int i=10; i<20; i++) {
		arr[i] = i*10;
	}
    //20-25
	arr[20] = 4;
	arr[21] = 8;
	arr[22] = 15;
	arr[23] = 16;
	arr[24] = 23;
	arr[25] = 42;
    //26-39
	int this = 7;
	for(int i=26; i<40; i++) {
		arr[i] = this;
		this = collatz(this);//this = next
	}
    //debug: print arr
	for(int i=0; i<40; i++)
		printf("%d ", arr[i]);
}
int collatz(int x) {
	if(x%2==0)
		return x/2;
	return x*3+1;
}
//7 - 22 - 11 - 34 - 17 - 52 - 26 - 13 - 40 - 20 - 10 - 5 - 16 - 8
