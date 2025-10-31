#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Function prototypes
int getInt(char* prompt, int min, int max);
void fillBoard(int* board, int length);
void printBoard(int* arr, int len);
int isSorted(int* arr, int len);
void shuffleBoard(int* arr, int len);
void reverse(int* arr, int len, int amtToReverse);
void swap(int* arr, int i, int j);
//extra
int solver(int* arr, int len);
int main()
{
    // Seed the random number generator
	srandom(time(NULL));
    // Ask user for length of game, from 3-20
	int boardLength = getInt("Enter size of board: ", 3, 20);
    // Create board. Shuffle numbers.
	int board[boardLength];
    // Fill board in order with numbers 1..boardLength.
	fillBoard(board, boardLength);
    // Shuffle board.
    // I recommend initially only uncommenting the shuffleBoard line
    // so it doesn't get stuck in an infinite loop. Once shuffleBoard
    // is working, uncomment the rest of the loop.
	while (isSorted(board, boardLength))
	{
		shuffleBoard(board, boardLength);
	}
    // Print board
	printBoard(board, boardLength);
	int gameOver = 0;
	int moves = 0;
	while (!gameOver)
	{
        // Ask user for amount to reverse
		printf("hint: you should enter %d\n", solver(board, boardLength));
		int amt = getInt("How many to reverse? ", 2, boardLength);
        // Reverse the first (amt) numbers
		reverse(board, boardLength, amt);
        // Print the board
		printBoard(board, boardLength);
        // Check to see if the game is over
		gameOver = isSorted(board, boardLength);
		moves++;
	}
	printf("You won in %d moves!\n", moves);
}
// Get an integer from the user.
// Display the prompt.
// Get input from user.
// Check that the input is between the min and max, inclusive.
// If not, display error message that includes the min and max,
// then loop back to get input again.
int getInt(char* prompt, int min, int max)
{
    //print prompt
	printf("%s", prompt);
    //get int
	int input;
	while(1) {
		scanf("%d", &input);
        //break point
		if(input<=max && input>=min)return input;
		printf("Value must be in the range %d-%d\n", min, max);
		printf("%s", prompt);
	}
}
void fillBoard(int* board, int length) {
	for(int i=0; i<length; i++) {
		board[i] = i+1;
	}
}
void printBoard(int* arr, int len) {
	printf("Board: ");
	for(int i=0; i<len; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
int isSorted(int* arr, int len) {
	for(int i=0; i<len; i++) {
        //break point
		if(arr[i]!=i+1)return 0;
	}
	return 1;
}
void shuffleBoard(int* arr, int len) {
	for(int i=len-1; i>0; i--) {
		int j = random()%(i+1);
        //printf("%d", j);
		swap(arr, i, j);
	}
}
void reverse(int* arr, int len, int amtToReverse) {
	for(int i=0; i<amtToReverse/2; i++) {
		swap(arr, i, amtToReverse-1-i);
	}
}
void swap(int* arr, int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
//extra
int solver(int* arr, int len) {
    //the idea of solving is to move the last num to front of arr then to last repeat
	int max = len, b=0;
    //read arr from behind
	for(int i=len-1; i>=0; i--) {
		if(arr[i]!=i+1)
			b=1;
		if(b!=1)
			max--;
		else {
			if(arr[i] == max) { //find max val index
				if(i == 0)//flip to end
					return max;
				return i+1;//flip to front
			}
		}
	}
	return 0;
}