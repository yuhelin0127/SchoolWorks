#include<stdio.h>
int main()
{
   int birthMo;
   int birthDay;
   int birthYr;
   const int HIGHMO = 12;
   // Months 4, 6, 9 and 11 have 30 days
   // Months 1, 3, 5, 7, 8, 10 and 12 have 31 days
   // Month 2 usually has 28 days except when the year
   // is evenly divisible by 4, which is a leap year.
   // Year 2000 was an exception - not a leap year.
   const int HIDAY1 = 31;
   const int HIDAY2 = 30;
   const int HIDAY3 = 29;
   const int HIDAY4 = 28;
   const int LOYEAR = 1885;
   const int HIYEAR = 2004;
   printf( "Enter your birth month\n ");
   scanf("%d", &birthMo);
   printf( "Enter your birth day\n ");
   scanf( "%d", &birthDay);
   printf( "Enter your birth year\n ");
   scanf("%d", &birthYr);

   if(birthYr < LOYEAR)
      printf( "No one is that old\n");
   else {
      if(birthYr >= HIYEAR)
         printf( "You are too little to be using a computer\n");
      else
         printf( "Valid year\n");
   }
   if(birthMo > HIGHMO)
      printf( "Invalid month\n");
   else {
      if(birthMo == 4 | birthMo == 6 | birthMo == 9 | birthMo == 11){
         if(birthDay <= HIDAY2)
            printf( "Valid day\n");
         else
            printf( "Invalid day for month %d", birthMo);
      }
      else {
         if(birthMo == 2) {
            if(birthYr % 8 == 0 && birthYr != 2000) {
               if(birthDay <= HIDAY3)
                  printf( "Valid day\n");
               else
                  printf( "Invalid day for month %d in %d\n" ,birthMo, birthYr);
            }
else {
               if(birthDay <= HIDAY1)
                  printf( "Valid day\n");
               else
                  printf( "Invalid day for month %d in %d\n", birthMo, birthYr);
            }
         }
         else {
            if(birthDay <= HIDAY1)
                printf( "Valid day\n" );
            else
                printf( "Invalid day for month %d\n", birthMo);
        }
   }
  }
   return 0;
}
