#include <stdio.h>
#include <stdlib.h>
long long int getStart();
long long int nextCollatz(long long int x);
int main() {
	long long int num, cnt = 0;
	num = getStart();
	while(1) {
		printf("%lld", num);
		cnt++;//cnt current
		if(num==1 && cnt>=9)//break point
			break;
		printf(", ");
		num = nextCollatz(num);//to next val
	}
	printf("\nlength: %lld\n", cnt);
	//--------------------------
	//Extension:
	const int SIZE = 1001;
	//use dp to avoid recalculation (without 4, 2, 1)
	long long int *dp = (long long int*)malloc(SIZE * sizeof(long long int));
	//init dp arr
	for(int i=0; i<SIZE; i++) {
		dp[i]=0;
	}
	int max = 0, index=0;
	//loop through 1-SIZE(1000)
	for(int i=1; i<SIZE; i++) {
		int cnt = 0, num = i;
		//check val with dp or if is 4, 2, 1 then pass
		if(dp[num]!=0 || num==4 || num==2 || num==1) {
			continue;//if is recoreded means length must be <=max so check next val and 4,2,1 can't be the max
		}
		//calc new val len
		while(1) {
			cnt ++;//cnt this
			if(num==1)//break point
				break;
			num = nextCollatz(num);//to next
			//check next val with dp
			if(num<SIZE && dp[num]!=0) { //prevent core dumped(memory overflow) set
				num<1000;
				cnt += dp[num];
				break;
			}
		}
		//check max
		if(cnt>max) {
			max = cnt;
			index = i;
		}
		//record new val len
		dp[i] = cnt;
	}
	printf("\nlongest sequence:\nstarting number: %d\nlength: %d\n",index, max);
	//debug:check ans in dp
	//for(int i=0;i<SIZE;i++){
	// printf("(%d, %lld)\n", i, dp[i]);
	//}
	return 0;
}
long long int getStart() {
	long long int num;
	while(1) {
		printf("Enter the starting number: ");
		scanf("%lld", &num);
		if(num>0)//if is pos break
			break;
		printf("The number should be a positive integer.\n");
	}
	return num;
}
long long int nextCollatz(long long int x) {
	if(x%2==0)
		return x/2;
	return x*3+1;
}