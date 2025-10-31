#include <stdio.h>
#include <stdlib.h>
const int exten1 = 0;//disable extension1 as false, if true enter 5 denominations
int getAmount();
int bills(int d, int* denominations);
void getDenominations(int *denominations);//for extension1
int cmp(const void *e1, const void *e2);//for sorting the denominations descending

int main() {
	int denominations[] = {100, 20, 10, 5, 1};
	if(exten1)//if run extension1
		getDenominations(denominations);
	qsort(denominations, sizeof(denominations)/sizeof(*denominations), sizeof(*denominations), cmp);
	//debug: print all denominations
	//for(int i=0;i<5;i++){
	//
	// 	printf("%d ", denominations[i]);
	//}
	int b = bills(getAmount(), denominations);
	if(b==0)
		printf("there's no way to get all your bills back");
	else
		printf("You get %d bills back.", b);
	return 0;
}
int getAmount() {
	int d;
	while(1) {
		printf("Enter a dollar amount: ");
		scanf("%d", &d);
		if(d>0)
			return d;
		printf("Please enter a positive number.");
	}
}
//use greedy on usd$ can get optimized but not others
int bills(int d, int* denominations) {
	//apporoch from bottom up with dp
	int* dp = (int*)malloc(d * sizeof(int));
	//init dp array
	for(int i=0; i<d; i++) {
		dp[i]=0;
	}
	// put all denominations as 1 in dp
	for(int i=0; i<5; i++) {
		dp[denominations[i]-1]=1;
	}
	//calc O(n^2)
	for(int i=0; i<d; i++) {
		int num = i+1; //num count from 1-d

		//skip when denominations = num
		int flag = 0;
		for(int k=0; k<5; k++) {
			if (denominations[k] == num)
				flag = 1;
		}
        //skip when num = denomination
		if(flag==1)
			continue;
        //skip all that's bigger than the smallest denomination
		if(num<denominations[0])
			continue;
		for(int k=1; k<=num/2; k++) {
			int op = num - k;
			if(dp[op-1]!=0 && dp[k-1]!=0) { //if sub exist
				if(dp[i]==0)//if empty
					dp[i] = dp[op-1] + dp[k-1];
				else {
					if(dp[op-1] + dp[k-1]<dp[i])//replace min
						dp[i] = dp[op-1] + dp[k-1];
				}
			}
		}
	}


	//debug:
	//for(int i=0;i<d;i++){
	//
	//printf("%d ", dp[i]);
	//}
	return dp[d-1];
}
void getDenominations(int *arr) {
	for(int i=0; i<5; i++) {
		printf("enter denomination %d:", i+1);
		scanf("%d", arr+i);
	}
}

int cmp(const void *e1, const void *e2) {
	return *((int *)e1) - *((int *)e2);
}
