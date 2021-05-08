#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Idea:
 * 	-	Maintain an array for open braces
 * 	-	When an open brace is seen, add the string index of the open
 * 		brace in the array and increment the number of valid entries by 1.
 * 	-	If a closed brace is seen, check the (valid index - 1) of the opening
 * 		brace array and fetch that character from the string.
 * 	-	If there is a match, decrement the valid entries by 1.
 * 	-	Unbalanced if:
 * 		1.	there is a closing brace and the valid entries val is 0.
 * 		2.	at the end of parsing the whole string, valid entries val is non zero.
 * 	-	Balanced if:
 * 		1.	at the end, valid entries val is 0.
 */
int is_parenthesis_balanced(char *str) {
	char *tmp = str;
	char ch;
	int len;
	unsigned int *arr;
	int i;
	int valid_entries = 0;
	len = strlen(str);
	/*
	 * Allocate dynamic memory - assumption is that the string is max 2^32 - 1 of size;
	 * Code breaks if that is not the case.
	 */
	arr = (unsigned int *)calloc(len, sizeof(int));
	for (i=0; i<len; i++) {
		switch (str[i]) {
			/*
			 * 	In all the following 3 opening braces cases,
			 * 	add the opening brace index into the array
			 * 	& increment the valid entries by 1.
			 */
			case '{':
			case '[':
			case '(':
				arr[valid_entries] = i;
				valid_entries++;
				break;
			/*
			 * 	Whereas, in the closing brace case, check the
			 * 	last valid entry and see if it indeed the expected
			 * 	opening brace. If not, return 0. Else, decrement
			 * 	valid entries by 1.
			 */
			case ')':
				if (valid_entries == 0)	{
					free(arr);
					return 0;
				}
				else if (str[arr[valid_entries - 1]] != '(') {
					free(arr);
					return 0;
				}
				else {
					valid_entries--;
				}
				break;
			case ']':
				if (valid_entries == 0)	{
					free(arr);
					return 0;
				}
				else if (str[arr[valid_entries - 1]] != '[') {
					free(arr);
					return 0;
				}
				else {
					valid_entries--;
				}
				break;
			case '}':
				if (valid_entries == 0)	{
					free(arr);
					return 0;
				}
				else if (str[arr[valid_entries - 1]] != '{') {
					free(arr);
					return 0;
				}
				else {
					valid_entries--;
				}
				break;
			default:
				/*	Ignore other characters	*/
				break;
		}
	}
	free(arr);
	return (valid_entries == 0);
}

int main(int argc, char **argv) {
	printf("%s\n", is_parenthesis_balanced(argv[1]) ? "Balanced" : "Unbalanced");
	return 0;
}
