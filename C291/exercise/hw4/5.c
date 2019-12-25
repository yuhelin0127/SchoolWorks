/*
 * Author: Yuheng Lin
 * Date: 2018/02/06
 * Assignment 4
 */

#include<stdio.h>

int main(void){

	char *topics[5] = {"political issues", "domestic violence", "cyber threat", "sports competition", "military"};
	int rate[5][10];
	int count = 0;
	int max = 0;
	int min = 100000;
        char* minIss;
	char* maxIss;  
	while(count < 10){
	printf("Welcome user %d!\n", count+1);
	int i;
	for(i = 0; i < 5; i++){
	printf("Rate topic: %s from 1 to 10:  ", topics[i]);
	scanf("%d",&rate[i][count]);
	
	}
	count++;
	}
	printf("Thank you for your helps!\n");
  
 	int j;
	for(j = 0; j < 5; j++){
	int sum = rate[j][0] + rate[j][1] + rate[j][2] + rate[j][3] + rate[j][4] + rate[j][5] + rate[j][6] + rate[j][7] + rate[j][8] + rate[j][9];
	float av = sum/10;
	printf("%s %d %d %d %d %d %d %d %d %d %d  Avg: %f\n", topics[j], rate[j][0], rate[j][1], rate[j][2], rate[j][3], rate[j][4], rate[j][5], rate[j][6], rate[j][7], rate[j][8], rate[j][9], av);
	if(sum > max){
	max = sum;
	maxIss = topics[j];
	}
	if(sum < min){
	min = sum;
	minIss = topics[j];
	}
	}
	printf("Maximum is %s: %d\n",maxIss,max);
	printf("Minimun is %s: %d\n",minIss,min);
	

	
	return 0;
}
