// C343 / Summer 2018
// Lab 07
// Name: Yuheng Lin
// Username: yuhelin

public class lab07 {

    public static void main(String[] args){


        Array a1 = new Array(6);
        DimentionalArray b1 = new DimentionalArray(6);

        a1.arr[0] = 1;
        a1.arr[1] = 2;
        a1.arr[2] = 3;
        a1.arr[3] = 4;
        a1.arr[4] = 5;
        a1.arr[5] = 6;

        b1.arr[0] = 2;
        b1.arr[1] = 4;
        b1.arr[2] = 6;
        b1.arr[3] = 8;
        b1.arr[4] = 10;
        b1.arr[5] = 12;


        System.out.println(a1.removeAt(4));
        System.out.println(b1.removeAt2(3));
        System.out.println(b1.removeAt2(8));

        System.out.println(b1.arr[0]);
        System.out.println(b1.arr[1]);
        System.out.println(b1.arr[2]);
        System.out.println(b1.arr[3]);
        System.out.println(b1.arr[4]);


        System.out.println(a1.arr.length);
        System.out.println(b1.arr.length);

    }

}
