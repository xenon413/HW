
#include <stdio.h>
#include "ansi-colors.h"
#include <stdlib.h>
const int NODE_NUM = 5;
struct node {
	int num;
	char* state;//RED, BLUE, WHITE
	struct node** neighbor;//store neighbor pointer 2-4
};
// Function prototypes
void init(struct node** nodes);
int if_move(struct node* n);
void show_board(struct node** nodes);
void print_color(char* color, char*text);
int move(struct node** nodes, char* color, int a, int b);
int main() {
	int a, b, cnt=0;
	char* color;
//create nodes
	struct node* nodes[NODE_NUM]; //array of node pointers
	for(int i=0; i<NODE_NUM; i++) {
//use heap to create different memory address
		struct node* temp = (struct node*)malloc(1 * sizeof(struct node));
//printf("%d\n", temp);//test for seeing memory address
		nodes[i] = temp;
	}
	init(nodes);
//description
	printf("this is Pong Hau K'i game made by Chen\n");
	printf("The first player plays with two blue pieces and the second player plays with two red pieces.\n");
    printf("rules:\n");
    printf("Move any one of your pieces to an adjacent unoccupied node.\nYou win if your opponent cannot move either of their pieces on their turn.\n");
	printf("the formate of moving is the starting point to target e.g. 0 2, you'll move red 0 to 2\n");
	while(1) {
	cnt ++;
	show_board(nodes);
		printf("round %d: ", (cnt+1)/2);
        //set color
		if(cnt%2) {
			color = BLU;
			printf("blue's turn\n");
		}
		else {
			color = RED;
			printf("red's turn\n");
		}
        //input
		scanf("%d %d", &a, &b);
		while(move(nodes, color, a, b)) {
			scanf("%d %d", &a, &b);
		}
        //check if someone wins
		int rcnt=0, bcnt=0;
		for(int i=0; i<NODE_NUM; i++) {
			if(if_move(nodes[i]) == -1) {
				if(nodes[i]->state == RED)
					rcnt++;
				if(nodes[i]->state == BLU)
					bcnt++;
			}
		}
//break point
		if(rcnt==2) {
			printf("blue wins in %d rounds\n", (cnt+1)/2);
			break;
		}
		if(bcnt==2) {
			printf("red wins in %d rounds\n", (cnt+1)/2);
			break;
		}
	}
	show_board(nodes);
}
void init(struct node** nodes) {
    //struct node* temp[NODE_NUM][NODE_NUM-1];//arr of neighbor not including self
    //need dynamic memory so temp memory won't release after finishing init
    //create a 2d pointer array
	struct node*** temp = (struct node***)malloc(NODE_NUM*sizeof(struct node**));
	for(int i=0; i<NODE_NUM; i++) {
		struct node** t1 = (struct node**)malloc((NODE_NUM-1) * sizeof(struct
		                   node*));
		for(int k=0; k<NODE_NUM; k++) {
			struct node* t2 = (struct node*)malloc(1 * sizeof(struct node));
			t2->num = -1;
			t2->state = NULL;
			t2->neighbor = NULL;
			t1[k] = t2;
		}
		temp[i] = t1;
	}
//init num
	nodes[0]->num = 0;
	nodes[1]->num = 1;
	nodes[2]->num = 2;
	nodes[3]->num = 3;
	nodes[4]->num = 4;
//init state
	nodes[0]->state = RED;
	nodes[1]->state = RED;
	nodes[2]->state = WHT;
	nodes[3]->state = BLU;
	nodes[4]->state = BLU;
//init left top neighbor
	temp[0][0] = nodes[2];
	temp[0][1] = nodes[3];
	nodes[0]->neighbor = temp[0];
//init right top neighbor
	temp[1][0] = nodes[2];
	temp[1][1] = nodes[4];
	nodes[1]->neighbor = temp[1];
//init left bottom neighbor
	temp[3][0] = nodes[2];
	temp[3][1] = nodes[0];
	temp[3][2] = nodes[4];
	nodes[3]->neighbor = temp[3];
//init right bottom neighbor
	temp[4][0] = nodes[2];
	temp[4][1] = nodes[1];
	temp[4][2] = nodes[3];
	nodes[4]->neighbor = temp[4];
//init middle neighbor
	temp[2][0] = nodes[0];
	temp[2][1] = nodes[1];
	temp[2][2] = nodes[3];
	temp[2][3] = nodes[4];
	nodes[2]->neighbor = temp[2];
}
//return -1 if can't, else destination num
int if_move(struct node* n) {
	for(int i=0; i<NODE_NUM-1; i++) {
//directly cmp address ignore worning
		if(n->neighbor[i]->state==WHT) {
			return n->neighbor[i]->num;
		}
	}
	return -1;
}
void show_board(struct node** nodes) {
	printf("%s0%s %s1\n", nodes[0]->state, WHT, nodes[1]->state);
	printf("%s|\\ /|\n", WHT);
	printf("| %s2 %s|\n", nodes[2]->state, WHT);
	printf("|/ \\|\n");
	printf("%s3%s---%s4\n", nodes[3]->state, WHT, nodes[4]->state);
	printf("%s", WHT);//reset to white
}
//move a to b
int move(struct node** nodes, char* color, int a, int b) {
//check num range
	if(a<0||b<0||a>4||b>4) {
		printf("all value must be in the range of 0-4\n");
		return 1;
	}
//check start color
	if(nodes[a]->state != color) {
		printf("you can only move your own color's pieces\n");
		return 1;
	}
//check if available to move
	int check = if_move(nodes[a]);
	if(check == -1) {
		printf("you only can move to adjacent node\n");
		return 1;
	}
	if(check != b) {
		printf("you only can move to unoccupied node\n");
		return 1;
	}
//move
	nodes[a]->state = WHT;
	nodes[b]->state = color;
	return 0;
}