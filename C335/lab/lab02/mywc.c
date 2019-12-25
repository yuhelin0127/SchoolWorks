#include<stdio.h>

int main(void){
	int chars = 0;
	int lines = 0;
	int words = 0;

	int c;
	while((c = getchar()) != EOF){
		chars++;
		if(c == '\n'){
			words++;
			lines++;
		}
		if(c == ' '){
			words++;
		}
	}
	printf("%d %d %d\n", lines, words, chars);
	return 0;\
}
