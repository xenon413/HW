#include <stdio.h>
// Max string length
#define STR_MAX 100
// Function prototypes here:
void reverse(char* s);
int stringLength(char* s);
void trim(char* s);
// Main function
int main()
{
	char input[STR_MAX];
	// Loop until we break out
	while (1)
	{
		printf("Enter a string: ");
		fgets(input, STR_MAX, stdin); // Finish this call to fgets
		if (input[0] == '.') // Break out of loop when first char is '.'
		{
			break;
		}
		// Trim the newline
		trim(input);
		// Print the trimmed string
		printf("After trim: %s\n", input);
		// Reverse the string
		reverse(input);
		// Print the reversed string
		printf("Reversed: %s\n", input);
	}
}
void trim(char* s) {
	for(int i=0; s[i]!='\0'; i++) {
		if (s[i] == '\n') {
			s[i] = '\0';
			break;
		}
	}
}
int stringLength(char* s) {
	int i=0;
	while (1) {
		if (s[i] == '\0')
			break;
		i++;
	}
	return i;
}
void reverse(char* s) {
	int start=0, end = stringLength(s)-1;
	while(start<end) {
		char temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start ++;
		end --;
	}
}