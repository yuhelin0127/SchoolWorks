/*
 * Author: Yuheng Lin
 * Date: 2018/02/06
 * Assigment 4
 */

#include<stdio.h>

int main(void) {
	short int value1,value2;
	value1 = 40000;
	

	// 2.(a)
	short int * lPtr;

	// 2.(b)
	lPtr = &value1;

	// 2.(c)
	printf("%d\n",*lPtr);

	// 2.(d)
 	value2 = *lPtr;

	// 2.(e)
	printf("%d\n",value2);

	// 2.(f)
	printf("%p\n",&value1);

	// 2.(g)
	printf("%p\n",&*lPtr);
	// The addresses are the same;
	

	return 0;
}

	
