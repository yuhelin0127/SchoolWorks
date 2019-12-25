// C343 / Summer 2018
// Lab  03
// Name: Yuheng Lin
// Username: yuhelin


import java.util.*;

public class MyCard implements Card {


    private ArrayList<String> deck;
    public MyCard(){
        this.deck = new ArrayList<String>();
    }


    public void initialize(){
        int count = 0;
        int[] n = {1,2,3,4,5,6,7,8,9,10,11,12,13};
        String[] s = {"S", "C", "H", "D"};
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 13; j++){
                String card = s[i] + Integer.toString(n[j]);
                deck.add(card);
            }
        }
    };


    public String drawRandomCard(){
        String card;
        int t;
        Random n = new Random();
        t = n.nextInt(52);
        card = deck.get(t);
        return card;
    };


    public ArrayList<String> getDeck() {
        return deck;
    }
}
