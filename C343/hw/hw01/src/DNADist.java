// C343 / Summer 2018
// Homework 01
// Name: Yuheng Lin
// Username: yuhelin

public class DNADist {

    public int DNADist(String a, String b){
        int counter = 0;
        for(int i = 0; i <= 99; i++){
            if (! a.substring(i, i + 1).equals(b.substring(i, i + 1))){
                counter += 1;
            }
        }
        return counter;
    }
}
