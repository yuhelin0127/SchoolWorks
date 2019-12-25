/*
 * Author: Yuheng Lin
 * Date: 2018/2/13 21:35
 *
 * Assignment 5
 *
 *
 * 1. 
 *  a) customerRecord.lastname
 *  b) customerPtr->lastname
 *  c) customerRecord.firstname
 *  d) customerPtr->firstname
 *  e) customerRecord.customerNumber
 *  f) customerPtr->customerNumber
 *  g) customerRecord.personal.phoneNumber
 *  h) (customerPtr->personal).phoneNumber
 *  i) customerRecord.personal.address
 *  j) (customerPtr->personal).address
 *  k) customerRecord.personal.city
 *  l) (customerPtr->personal).city
 *  m) customerRecord.personal.state
 *  n) (customerPtr->personal).state
 *  o) customerRecord.personal.zipCode
 *  p) (customerPtr->personal).zipCode
 */


#include<stdio.h>

double bmi;
long m,d,y;
double mhr;
double lowthr, highthr;
double temp1,temp2;




struct date{
	int year;
	int month;
	int day;	
};




struct profile{
	char firstname[15];
	char lastname[15];
	char gender[15];
	struct date birth;
	int height;
	int weight;
	}person;




void getdata(){

	printf("Enter your first name: \n");
	scanf("%s",person.firstname);

	printf("Enter your last name: \n");
	scanf("%s",person.lastname);

	printf("Enter your gender: \n");
	scanf("%s",person.gender);

	printf("What is your data of birth? \n");

	printf("Enter the month: \n");
	scanf("%d", &person.birth.month);

	printf("Enter the year: \n");
	scanf("%d", &person.birth.year);

	printf("Enter the day: \n");
	scanf("%d", &person.birth.day);

	printf("Enter your height: \n");
	scanf("%d", &person.height);

	printf("Enter your weight: \n");
	scanf("%d", &person.weight);

}
	

void getage(){
	long cd,cm,cy;

	printf("Enter the current year: \n");
	scanf("%ld", &cy);

	printf("Enter the current month: \n");
	scanf("%ld", &cm);

	printf("Enter the current day: \n");
	scanf("%ld", &cd);

	if(person.birth.day > cd){
		if(person.birth.day == 2){
			cd += 28;
		}
		else {
		cd += 30;
		}
	}

	d = cd - person.birth.day;

	if(person.birth.month > cm){
		cm += 12;
		cy -= 1;
	}

	m = cm - person.birth.month;
	y = cy - person.birth.year;
	temp1 = (m * 30 + d)/365;
	temp2 = y + temp1;

}	



void getbmi(){

	bmi = person.weight * 703 / (person.height * person.height);

}



void showbmi(){
	
	printf("BMI is %.2f", bmi);

	if(bmi < 18.5)
	  printf("\nUnderweight\n");
	else if(bmi >= 18.5 && bmi <= 24.9)
	  printf("\nNormal\n");
	else if(bmi >= 25 && bmi <= 29.9)
	  printf("\nOverweight\n");
	else if(bmi >= 30)
	  printf("\nObese\n");

}


	

void showdata(){

	printf("First name: %s\n", person.firstname);
	printf("Last name: %s\n", person.lastname);
	printf("Gender: %s\n", person.gender);
	printf("Birth: %d/%d/%d \n", person.birth.year, person.birth.month, person.birth.day);
	printf("Height: %d inches\n", person.height);
	printf("Weight: %d pounds\n", person.weight);


}




void showhrate(){

	printf("Your age: %.2f\n", temp2);
	mhr = 220 - temp2;
	printf("Your maximum heart rate: %.2f\n", mhr);
	lowthr = mhr * 0.5;
	highthr  = mhr * 0.85;
	printf("Your target heart rate range: ");
	printf("%.2lf - %.2lf\n", lowthr, highthr);
	
}







int main(void){
	
	getdata();
	getage();
	showdata();
	showhrate();
	getbmi();
	showbmi();

	return 0;
}
