// C343 / Summer 2018
// Lab Mini-Assignment 02
// Name: Yuheng Lin
// Username: yuhelin

public class RunTimes {

  public void countInstructions(int n){


     // Example 1
      int i;
     int count1 = 0;
     int sum1 = 0;
     for(i = 1; i <= n; i++, count1++){
       sum1 ++;
     }
     System.out.println("For Example 1, " + "n = " + n + "   instructioncounter = " + count1 + "   (instructioncounter / n) = " + count1/n );

    // Example 7
      int[][] d = new int[n+1][n+1];
      int[] a = new int[n+1];
      int[] b = new int[n+1];
      int j,c;
      int count7 = 0;
      d[0][0] = 0;
      for(i = 1; i <= n; i ++, count7++)  {
          for(j = 1; j <= n; j ++, count7++) {
              if(a[i] == b[j]) {
                  c = 0;
                  count7++;
              }
              else {c = 1;
              count7++;}
              d[i][j] = Math.min(Math.min(d[i-1][j] + 1, d[i][j-1] + 1), Math.min(d[i][j-1] + 1, d[i-1][j-1]+c));
          }
      }
      System.out.println("For Example 7, " + "n = " + n + "   instructioncounter = " + count7 + "   (instructioncounter / n) = " + count7/n );
  }

}
