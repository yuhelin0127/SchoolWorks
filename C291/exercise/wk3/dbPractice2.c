//Program to read elements in a 2X2 matrix and then print them on the screen

 #include<stdio.h>

  int main(void) {
     int size = 2;
     int Matrix [2][2];
     printf("Enter 4 elements of the matrix");
     int i,j;
     for (i=0; i<size; i++){
        for (j=0; j<size; j++){
         scanf("%d", &Matrix[i][j]);
 }
 }
         display(size, Matrix);
     return 0;
 }
 int display(int size,int Matrix[size][size]) {
     int i,j;
         for (i=0; i<size; i++) {
             for (j=0; j<size; j++) {
             printf("%d ,", Matrix[i][j]);
 }
         printf("\n");
 }
     return 0;
 }
    
