// C343 / Summer 2018
// Homework 05
// Name: Yuheng Lin
// Username: yuhelin

import java.time.Instant;

public class DNAEditDistance {

    public int hammingDistance(String a, String b){
        int counter = 0;
        for(int i = 0; i < a.length(); i++){
            if (! a.substring(i, i + 1).equals(b.substring(i, i + 1))){
                counter += 1;
            }
        }
        return counter;
    }

    public int editDistance(String a, String b){
        int[][] d = new int[a.length() + 1][b.length() + 1];
        int m = a.length();
        int n = b.length();
        int c;
        for (int i = 0; i <= m; i++) d[i][0] = i;
        for (int j = 0; j <= n; j++) d[0][j] = j;
        for (int i = 1; i <= m; i++){
            for (int j = 1; j <= n; j++){
                if (a.substring(i - 1, i).equals(b.substring(j - 1, j))) {
                    c = 0;
                }
                else {
                    c = 1;
                }
                d[i][j] = Math.min(Math.min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + c);
            }
        }
        return d[m][n];
    }


    public static void main (String[] args) {

        RandomDNA a = new RandomDNA();
        RandomDNA b = new RandomDNA();
        System.out.println("Length size: 4");
        a.getRandomDNA(4);
        b.getRandomDNA(4);
        DNAEditDistance distance = new DNAEditDistance();

        long h1 = Instant.now().toEpochMilli();
        System.out.println("The Hamming Distance of String a and b is: " + distance.hammingDistance( a.getDNA(), b.getDNA()));
        long h2 = Instant.now().toEpochMilli();
        System.out.println("For hamming distance, it took " + (h2 - h1) + " milliseconds to complete the method.");
        long e1 = Instant.now().toEpochMilli();
        System.out.println("The EDIT Distance of String a and b is: " + distance.editDistance(a.getDNA(), b.getDNA()));
        long e2 = Instant.now().toEpochMilli();
        System.out.println("For edit distance, it took " + (e2 - e1) + " milliseconds to complete the method.");
    }


}