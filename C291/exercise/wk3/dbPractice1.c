//A number is said to be a palindrome if reverse of //the number is the 
//original number itself //eg: Original number = 535, Reverse = 535. 
//Hence, 535 is a palindrome // Original number = 676, Reverse = 676. 
//Hence, 676 is a palindrome // Original number = 5678, Reverse = 8765. 
//Hence, 5678 is NOT a palindrome

 #include<stdio.h>



  int main(void) {
     int originalInteger;
     printf("Enter an integer: ");
     scanf("%d", &originalInteger);
     int result = checkPalindrome(originalInteger);
     // palindrome if result = 1
     if (result == 1){
         printf("%d is a palindrome.\n", originalInteger);
 }
     else {
         printf("%d is not a palindrome.\n", originalInteger);
 }
     return 0;
 }
 int checkPalindrome(int originalInteger) {
  int remainder;
  int reversedInteger = 0;
  int n = originalInteger;
  //logic to reverse the number
  while (n!=0) {
         remainder = n%10;
         reversedInteger  = reversedInteger*10 + remainder;  
 	 n -= remainder;
	 n = n / 10;
     }
     // palindrome if orignalInteger and reversedInteger are equal
     if (originalInteger == reversedInteger){
         return 1;
 }
     else{
         return 0;
 }
 }
