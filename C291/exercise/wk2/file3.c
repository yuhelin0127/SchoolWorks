/*Debugging quiz - File No: 3 */
/* The program should give out the appropriate message, given the grade as input */

#include<stdio.h>

int main(void) {
	char input;
	printf("Enter the grade (A/B/C/D/F): (Q to Quit) \n");
	scanf("%s", &input);
	while(input != 'Q' ){
		if(input == 'F'){
			printf("You have not passed the course.\\n");
			main();
		}
		else if(input == 'A' | input == 'B' | input == 'C' | input == 'D') {
			printf("You have passed!\n");
		        main();
		}
	}
	printf("Quit the menu.\n");
	return 0;
}
