// C343 / Summer 2018
// Homework 01
// Name: Yuheng Lin
// Username: yuhelin


import java.util.ArrayList;
import java.util.Random;


public class RandomDNA {

    String listOfC;
    public RandomDNA(){
        this.listOfC = listOfC;
        listOfC = "";
        ArrayList<String> ls = new ArrayList<>();
        ls.add("A");
        ls.add("T");
        ls.add("C");
        ls.add("G");
        for (int i = 0; i <= 99; i++){
            Random n = new Random();
            int p = n.nextInt(4);
            listOfC += ls.get(p);
        }
    }

    public String getDNA(){
        return listOfC;
    }


    public static void main (String[] args) {
        RandomDNA a = new RandomDNA();
        RandomDNA b = new RandomDNA();
        RandomDNA c = new RandomDNA();
        System.out.println(a.getDNA());
        System.out.println(b.getDNA());
        System.out.println(c.getDNA());


        DNADist distance = new DNADist();
        System.out.println(distance.DNADist(a.getDNA(), b.getDNA()));
        System.out.println(distance.DNADist(a.getDNA(), c.getDNA()));
        System.out.println(distance.DNADist(b.getDNA(), c.getDNA()));

    }
}
