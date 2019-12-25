// C343 / Summer 2018
// Homework 05
// Name: Yuheng Lin
// Username: yuhelin

import java.util.ArrayList;
import java.util.Random;


public class RandomDNA {

    private String listOfC;


    public  RandomDNA(){
        String listOfC = new String();
    }


    public String getRandomDNA(int n) {
        listOfC = "";
        ArrayList<String> ls = new ArrayList<>();
        ls.add("A");
        ls.add("T");
        ls.add("C");
        ls.add("G");
        for (int i = 0; i < n; i++) {
            Random m = new Random();
            int p = m.nextInt(4);
            listOfC += ls.get(p);
        }
        return listOfC;
    }

    public String getDNA() {
        return listOfC;
    }

}