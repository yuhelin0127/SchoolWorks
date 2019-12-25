// C343 / Summer 2018
// Homework 03
// Name: Yuheng Lin
// Username: yuhelin

import sun.awt.image.ImageWatched;

import java.io.*;
import java.util.Iterator;
import java.util.LinkedList;


public class MainListTest {



    static final int testsize  = 100000; // try larger testsize values
    static final int testsize1 = 105000;
    static final int testsize2 = 110000;
    static final int testsize3 = 120000;
    static final int testsize4 = 130000;
    static final int testsize5 = 140000;
    static long time1, time2;

    static LinkedList<Integer> mergeTwoLists(LinkedList<Integer> l1, LinkedList<Integer> l2){
        LinkedList<Integer> re = new LinkedList<>();
        Iterator<Integer> L1 = l1.iterator();
        Iterator<Integer> L2 = l2.iterator();
        int l1h = L1.next();
        int l2h = L2.next();
        for (int i = 0; i < l1.size() + l2.size(); i++){
            if (l1h < l2h){
                re.add(l1h);
                if (L1.hasNext()){
                    l1h = L1.next();
                }
                else {
                    l1h = Integer.MAX_VALUE;
                }
            }
            else {
                re.add(l2h);
                if (L2.hasNext()){
                    l2h = L2.next();
                }
                else {
                    l2h = Integer.MAX_VALUE;
                }
            }
        }
        return re;
    }


    public static void main(String args[]) throws IOException {


        // Test mergeTwoLists
        LinkedList<Integer> a = new LinkedList<>();
        a.add(1);
        a.add(3);
        a.add(4);
        a.add(7);

        LinkedList<Integer> b = new LinkedList<>();
        b.add(2);
        b.add(5);
        b.add(6);
        b.add(8);
        b.add(11);
        b.add(13);

        LinkedList<Integer> c = MainListTest.mergeTwoLists(a,b);
        Iterator<Integer> ct = c.iterator();
        while(ct.hasNext()){
            System.out.println(ct.next());
        }


        // Instantiate CircularLList
        CircularLList<Integer> CL = new CircularLList<>();
        CL.insert(1);
        CL.insert(2);
        CL.insert(3);
        CL.insert(4);
        CL.insert(5);

        LList<Integer> LL = new LList<Integer>();
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize; i++) {
            LL.insert(2);
            LL.insert(3);
            LL.insert(4);
            LL.insert(5);
            LL.clear();
        }
        time2 = System.currentTimeMillis();
        long totaltime = (time2 - time1);
        System.out.println("For " + testsize + " iterations it took " + totaltime + " milliseconds.");

        LL.clear();
        LL.insert(1);
        LL.insert(2);
        LL.insert(3);
        LL.insert(4);
        LL.insert(5);
        LL.reverse();
        System.out.println(LL.toString());


        LList<Integer> LL1 = new LList<Integer>();
        LL1.insert(2);
        LL1.insert(3);
        LL1.insert(4);
        LL1.insert(5);
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize1; i++) {
            LL1.reverse();
        }
        time2 = System.currentTimeMillis();
        long totaltime1 = (time2-time1);
        System.out.println("For " + testsize1 + " iterations it took " + totaltime1 + " milliseconds.");

        LList<Integer> LL2 = new LList<Integer>();
        LL2.insert(2);
        LL2.insert(3);
        LL2.insert(4);
        LL2.insert(5);
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize2; i++) {
            LL2.reverse();
        }
        time2 = System.currentTimeMillis();
        long totaltime2 = (time2-time1);
        System.out.println("For " + testsize2 + " iterations it took " + totaltime2 + " milliseconds.");

        LList<Integer> LL3 = new LList<Integer>();
        LL3.insert(2);
        LL3.insert(3);
        LL3.insert(4);
        LL3.insert(5);
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize3; i++) {
            LL3.reverse();
        }
        time2 = System.currentTimeMillis();
        long totaltime3 = (time2-time1);
        System.out.println("For " + testsize3 + " iterations it took " + totaltime3 + " milliseconds.");

        LList<Integer> LL4 = new LList<Integer>();
        LL4.insert(2);
        LL4.insert(3);
        LL4.insert(4);
        LL4.insert(5);
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize4; i++) {
            LL4.reverse();
        }
        time2 = System.currentTimeMillis();
        long totaltime4 = (time2-time1);
        System.out.println("For " + testsize4 + " iterations it took " + totaltime4 + " milliseconds.");

        LList<Integer> LL5 = new LList<Integer>();
        LL5.insert(2);
        LL5.insert(3);
        LL5.insert(4);
        LL5.insert(5);
        System.out.println("Start");
        time1 = System.currentTimeMillis();
        for (int i = 0; i < testsize5; i++) {
            LL2.reverse();
        }
        time2 = System.currentTimeMillis();
        long totaltime5 = (time2-time1);
        System.out.println("For " + testsize5 + " iterations it took " + totaltime5 + " milliseconds.");


    }

}
