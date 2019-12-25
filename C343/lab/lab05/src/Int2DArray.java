// C343 / Summer 2018
// Lab 05
// Name: Yuheng Lin
// Username: yuhelin

import java.lang.reflect.Array;
import java.util.*;

public class Int2DArray implements Int2DArrayADT{

    private int[][] a;

    public Int2DArray(int[][] a){
        this.a = a;
    }

    public void set(int r, int c, int n){

        a[r - 1][c - 1] = n ;
    }

    public int get(int r, int c){
        return a[r - 1][c - 1];
    }

    public boolean zeroArray(){
        if (a.length == 0){
            return true;
        }
        else {
            return false;
        }
    }

    public void setRow(int r, int[] n){
        a[r - 1] = n;
    }

    public int[] getRow(int r){
        return a[r - 1];
    }

    public void setColumn(int c, int[] n){
        for(int i = 0; i < a.length; i++){
            a[i][c - 1] = n[i];
        }
    }

    public int[] getColumn(int c){
        int[] n = new int[a.length];
        for(int i = 0; i < a.length; i++){
            n[i] = a[i][c - 1];
        }
        return n;
    }


    public static void main(String[] args){

        int[][] n = {{1,2,3}, {4,5,6},{7,8,9}};
        int[][] m = {};
        int[] c = {3,2,1};
        Int2DArray a = new Int2DArray(n);
        Int2DArray b = new Int2DArray(m);
        System.out.println(a.get(1,1));
        a.set(1, 1, 12);
        System.out.println(a.get(1,1));
        System.out.println(b.zeroArray());
        for (int i = 0; i < a.getRow(1).length; i++){
            System.out.println(a.getRow(1)[i]);
        }
        a.setRow(1, c);
        for (int i = 0; i < a.getRow(1).length; i++){
            System.out.println(a.getRow(1)[i]);
        }
        for (int i = 0; i < a.getColumn(2).length; i++){
            System.out.println(a.getColumn(2)[i]);
        }
        a.setColumn(2, c);
        for (int i = 0; i < a.getColumn(2).length; i++){
            System.out.println(a.getColumn(2)[i]);
        }

    }



}
