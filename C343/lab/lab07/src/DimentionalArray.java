// C343 / Summer 2018
// Lab 07
// Name: Yuheng Lin
// Username: yuhelin

public class DimentionalArray {
    Integer[] arr;

    public DimentionalArray(int size) {
        arr = new Integer[size];
    }


    /**
     * Removes the element found at the specified index-th position by shifting all elements that come after it to the "left".
     * That is, if we are removing the 2nd element, the 3rd element becomes the 2nd, the 4th element becomes the 3rd and so on.
     * Finally, the size of the array is decreased, so we know that next time we add, we can overwrite what was the last element
     * of the array.
     *
     * @param index     The index in the array of the element to be removed.
     * @return          The object that was removed. null if the the specified index does not exist in the array.
     */
    Integer removeAt2(int index){
        if (index >= arr.length) {
            return null;
        }
        boolean a = false;
        int n = arr[index - 1];
        Integer[] narr = new Integer[arr.length - 1];
        for (int i = 0; i < arr.length - 1; i++){
            if (i == index - 1){
                a = true;
            }
            if (a) {
                int c = arr[i + 1];
                narr[i] = c;
            }
            else {
                narr[i] = arr[i];
            }
            }
        arr = narr;
        return n;
    }
}
