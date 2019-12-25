/* Instructions:
 *
 *1. Write a program to return the grade associated with a range of 
marks.
 *2. The range of marks and the associated grades are as follows:
 *   a. 95-100 = A+
 *   b. 85-94 = A
 *   c. 81-85 = B+
 *       d. 71-80 = B
 *       e. 61-70 = C
 *   d. less than or equal to 60 is a fail grade and should be given an  F
 *   e. greater than 100 is invalid and your code should print "Invalid"
 *3. Use the skeleton code provided below to create a new function 
 *   "printStudentGrade" with its appropriate
 *   data type for input of marks. For example, printStudentGrade(<data 
 *   type> marks).
 *4. Use print statements in your function to display the grade. For 
 *   example, if the input marks is 77, the output should read:
 *      "Your grade is : B"
 *5. Please adhere to standard C syntax conventions and use comments to 
 *explain your code. Failure to do so will result in a penalty.
 *
 *
 **/ 
 #include<stdio.h>

 void printStudentGrade(double marks){ 
 	 printf("Your grade is: ");
 	 if (marks >= 95 && marks <= 100){
	 printf("A+");
 }
         else if(marks >= 85 && marks <= 94){
	 printf("A");
 }
	 else if(marks >= 81 && marks <= 85){
	 printf("B");
 }
	 else if(marks >= 71 && marks <= 80){
	 printf("C");
 }
	 else if(marks >= 61 && marks <= 70){
	 printf("D");
 }
	 else if(marks >= 60){
	 printf("F");
 }
	 else if(marks > 100){
	 printf("invalid");

 }
 }

 int main(void){
	 char ch;
         double marks;
         do{
                 printf("Enter Student's marks:");
	   	 scanf("%lf",&marks);
                 printStudentGrade(marks);
                 printf("\nDo you want to continue? (Y/N)");
                 scanf(" %c",&ch); //do not modify this.
         }while(ch == 'y'|| ch == 'Y');
         return 0;
 }
