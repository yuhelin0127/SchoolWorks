// HW01 - rpn.c
// Name: Yuheng Lin
// Username: yuhelin
// Date: 2019/09/10

#include<stdio.h>
#include<stdlib.h>
#include<errno.h> //print out error messege


typedef struct CELL *LIST;

struct CELL{
	int val;
	LIST next;
};

LIST stack;

// push
int push(int val){
	LIST c = (LIST) malloc(sizeof(struct CELL));
	if(c){
		c->val = val;
		c->next = stack;
		stack = c;
	}
	else{/*handle error*/
		fprintf(stderr, "Error allocating the memory.\n");	
	}
	return 0;
}

// pop - return a value and deallocate the cell
int pop(){
	LIST c;
	int val;
	if (stack){
		val = stack->val;
		c = stack;
		stack = stack->next;
		free(c);
		return val;
	}
	else{/*handle error*/
		fprintf(stderr, "dc: stack empty\n", strerror(stack));
		return 0;
	}
}

// main client:
int main(void){
	char c;
	printf("Welcome to RPN calculator, please enter your calculation and commands\n");
	for(;;) {

		scanf("%s", &c);
		
		if(isdigit(c)){
			push(atoi(&c));
		}
		
		// read binary operators:
		else if(c == '+' || c == '-' || c == '*' || c == '/'){
			// declare two elements for binary operation
			int x, y;
			if(stack){
				x = pop();
				y = pop();
			}
			else {
				fprintf(stderr, "dc: stack empty\n", strerror(stack));
				continue;
			}
			switch(c){
				case '+':
					y += x;
					break;
				case '-':
					y -= x;
					break;
				case '*':
					y *= x;
					break;
				case '/':
					y /= x;
					break;
				default:
					break;
			}
			push(y);
		}
		
		// miscellaneous commands:
		else if(c == 'p' || c == 'f' || c == 'c' || c == 'a' || c == 'm' || c == 'd'){
			if(stack){
				LIST stack_tmp;
				switch(c){
					case 'p':
						printf("%d\n", stack->val);
						break;
					case 'f':
						stack_tmp = stack;
						while(stack_tmp){
							printf("%d\n", stack_tmp->val);
							stack_tmp = stack_tmp->next;
						}
						break;
					case 'c':
						while(stack) pop();
						break;
					case 'a':
						stack->val = abs(stack->val);
						break;
					case 'm':
						stack->val = -stack->val;
						break;
					case 'd':
						push(stack->val);
						break;
					default:
						break;
				}
			} else {
				fprintf(stderr, "dc: stack empty\n", strerror(stack));
			}
		} 
		else if (c == 'q' || c == EOF) break;
		
	}
	return 0;
}
	
