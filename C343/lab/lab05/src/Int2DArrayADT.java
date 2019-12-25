// C343 / Summer 2018
// Lab 05
// Name: Yuheng Lin
// Username: yuhelin

import java.util.*;

// An ADT for 2DArraylist of integers
public interface Int2DArrayADT {

    // set a number in a particular position in the 2D Arraylist
    public void set(int r, int c, int n);

    // get a number in a particular position in the 2D Arraylis
    public int get(int r, int c);

    // Return true if the 2D Arraylist is empty
    public boolean zeroArray();

    // set a row of Arraylist to a new Arraylist of integers
    public void setRow(int r, int[] n);

    // get a row of Arraylist
    public int[] getRow(int r);

    // set a column of Arraylist to a new Arraylist of integers
    public void setColumn(int c, int[] n);

    // get a column of Arraylist
    public int[] getColumn(int c);

}
