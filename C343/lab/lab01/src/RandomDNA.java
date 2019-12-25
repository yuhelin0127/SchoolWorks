import java.util.ArrayList;
import java.util.Random;


public class RandomDNA {
    public static void main (String[] args) {
        String s = "";
        ArrayList<String> ls = new ArrayList<>();
        ls.add("A");
        ls.add("T");
        ls.add("C");
        ls.add("G");
        for (int i = 0; i <= 42; i++){
            Random n = new Random();
            int p = n.nextInt(4);
            s += ls.get(p);
        }
        System.out.println(s);



    }
}
