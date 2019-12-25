// C343 / Summer 2018
// Homework 07
// Name: Yuheng Lin
// Username: yuhelin


// The Algorithms for recursive method and DP method are from this website:
// https://www.geeksforgeeks.org/dynamic-programming-subset-sum-problem/

// Recursive method is using a recursive algorithm to update the index of the array
// and the sum. Only do two choices, one is to include the index number integer in array and
// update the sum and index, another one is to exclude the index number integer in array and
// keep the sum unchanged.
// When sum reach to 0 return true, or if index goes to 0 when sum is not 0, return false.

public class SubsetSum {

    public boolean subSum(int[] a, int k){
        int n = a.length;
        return subSumHelper(a, n, k);
    }

    public boolean subSumHelper(int[] a, int n, int k){
        if (k == 0) {
            return true;
        }
        if (n == 0 && k != 0){
            return false;
        }
        if (a[n - 1] > k){
            return subSumHelper(a, n - 1, k);
        }
        else {
            return subSumHelper(a, n - 1, k) || subSumHelper(a, n - 1, k - a[n - 1]);
        }
    }

// DP method uses a 2D array to store boolean. column states for sum, row states for array.
// First, fill the sum of 0 with true because any set is working for sum 0; Second, fill false
// with the first row because first row does not have any previous row to track with.
// Then we check from first column to the end with the each sum with different indexs.
// We use the booleans from previous row to see if the current sum subs the current index integer has
// a boolean of true.

    public boolean subSumDP(int[] a, int k){
        int n = a.length;
        boolean[][] set = new boolean[k + 1][n + 1];
        for (int i = 0; i < n + 1; i++){
            set[0][i] = true;
        }
        for (int i = 1; i < k + 1; i++){
            set[i][0] = false;
        }
        for (int i = 1; i < k + 1; i++){
            for (int j = 1; j < n + 1; j++){
                set[i][j] = set[i][j - 1];
                if (a[j - 1] <= i){
                    set[i][j] = set[i][j] || set[i - a[j - 1]][j - 1];
                }
            }
        }
        return set[k][n];
    }


    public static void main(String[] args){
        int[] A = {1,2,3,4,5,6,7,8,9,10};
        int[] B = {2,4,6,8,10,12,14,16,18,20};
        int[] C = {1,3,5,7,9,11,13,15,17,19};
        SubsetSum a = new SubsetSum();
        System.out.println(a.subSum(A, 16));
        System.out.println(a.subSumDP(A, 16));
        System.out.println(a.subSum(B, 11));
        System.out.println(a.subSumDP(B, 11));
        System.out.println(a.subSum(C, 2));
        System.out.println(a.subSumDP(C, 2));

    }


}


