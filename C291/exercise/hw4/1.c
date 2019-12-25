/* Author : Yuheng Lin
 * Date: 2018/02/06
 * 
 * Assignment 4
 */


#include<stdio.h>

int main(void){

	// 1.(a)
	int SIZE = 10;
	unsigned long values[10] = {1,3,5,7,9,11};

	// 1.(b)
	unsigned long * vPtr = values;

	// 1.(c)
	int i;
	for(i = 0; i < SIZE; i++){
	printf("%d\n", values[i]);
	}  

	// 1.(d)
	//vPtr = values;
	//vPtr = values[0];

	// 1.(e)
	for(i = 0; i < SIZE; i++){
	printf("%d\n", *(vPtr + i));
	}
	
	// 1.(f)
	for(i = 0; i < SIZE; i++){
	printf("%d\n",*(values + i));
	}

	// 1.(g)
	for(i = 0; i < SIZE; i++){
	printf("%d\n",vPtr[i]);
	}

	// 1.(h)
	printf("%d\n",values[4]);
	printf("%d\n",*(values + 4));
	printf("%d\n",vPtr[4]);
	printf("%d\n",*(vPtr + 4));

	// 1.(i)
	// The address of vPtr + 7 should be 400514.
	// The value stored will be 0.

	// 1.(j)
	// The address of vPtr will be 400512.
	// The value stored at vPtr will be 0.

	return 0;
}
