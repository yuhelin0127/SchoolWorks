// C343 / Summer 2018
// lab 13
// Name: Yuheng Lin
// Username: yuhelin

public class CountingSort {

    public CountingSort(){}

    public void sortIt(int[] a){
        // creat array b to save the total counts for array a
        int[] b = new int[a.length + 1];
        // creat array c to get ready to fill the integers in array a
        int[] c = new int[a.length];
        // Before save the total counts, fill 0s in array b
        for (int i = 0; i < b.length; i++){
            b[i] = 0;
        }
        // First step, update the counts in array b when we go through every elements in array a
        for (int i = 0; i < a.length; i++){
            // add 1 count to the particular index that matches each integer in array a
            b[a[i]] += 1;
        }
        // Second step, store the starting index in array b
        for (int i = 1; i < b.length; i++){
            // the count of each index will be updated by adding the count of the previous index
            // The purpose of this is to update the count number to starting index in array c
            b[i] += b[i - 1];
        }
        // Third step, fill the array c by using the starting index numbers in array b
        for (int i = a.length - 1; i >= 0; i--){
            // update the starting index after we fill a integer in array c
            b[a[i]] -= 1;
            // fill the number
            c[b[a[i]]] = a[i];
        }

        // print the array a and array c and maximum value k.
        String arrayA = "";
        String arrayC = "";
        for (int i = 0; i < a.length; i++){
            arrayA += " " +  a[i];
        }

        for (int i = 0; i < c.length; i++){
            arrayC += " " +  c[i];
        }
        System.out.println("Array A : " + arrayA);
        System.out.println("Array C : " + arrayC);
        System.out.println("Maximum value key k is: " + c[c.length - 1]);

    }

    public static void main(String[] args){

        int[] A = new int[]{10,4,6,2,2,3,4,8,8,7,5,1,7};
        int[] B = new int[]{10,3,4,5,1,2,7,6,9,12,11,14,15,11,13,};
        CountingSort test = new CountingSort();
        test.sortIt(A);
        test.sortIt(B);

    }


}
