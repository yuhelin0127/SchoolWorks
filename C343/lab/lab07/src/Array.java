// C343 / Summer 2018
// Lab 07
// Name: Yuheng Lin
// Username: yuhelin

public class Array {

    Integer[] arr;

    public Array(int size) {
        arr = new Integer[size];
    }

    /**
     * Removes the element found at the specified index-th position by replacing it with a null value.
     * @param index     The index in the array of the element to be removed.
     * @return          The object that was deleted.
     */
    Integer removeAt(int index){
        int n = arr[index - 1];
        arr[index - 1] = null;
        return n;
    }

}