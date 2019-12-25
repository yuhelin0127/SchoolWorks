// C343 / Summer 2018
// lab 06
// Name: Yuheng Lin
// Username: yuhelin

import java.util.*;
import java.net.*;

public class TweetCollection {

    private LinkedList<Tweet> ls;

    public TweetCollection() {
        ls = new LinkedList<Tweet>();
    }

    // read the URL and add tweets into the Array of tweets
    public void readURL() {
        try {
            URL url = new URL("http://homes.soic.indiana.edu/classes/summer2018/csci/c343-mitja/test2018/tweet-data-May16.txt");
            Scanner in = new Scanner(url.openStream());
            int i = 0;
            while (in.hasNext()) {
                String str = in.nextLine();
                String[] p = str.split(" ", 2);
                Tweet t = new Tweet(p[0],p[1]);
                ls.add(t);
                i++;
            }
            in.close();
        } catch (Throwable e) {
            System.out.println("exception is " + e);
            e.printStackTrace();
        }
    }

    // remove a Tweet at a particular position in the Array
    public void rmTweet(int n){
        ls.remove(n);
    }

    // Find the name that post the content c, if we do not find it, return "No Match"
    public String searchName(String c){
        String n = "No Match";
        Iterator<Tweet> lt = ls.iterator();
        while (lt.hasNext()){
            Tweet t = lt.next();
            if (t.getContent().equals(c)){
                n = t.getName();
            }
        }
        return n;
    }

    // Find the content from a particular name
    public String getContentByName(String n){
        String c = "No such name";
        Iterator<Tweet> lt = ls.iterator();
        while (lt.hasNext()){
            Tweet t = lt.next();
            if (t.getName().equals(n)){
                c = t.getContent();
            }
        }
        return c;
    }

    // Check if a substring is in any tweet.
    public boolean contains(String c){
        boolean result = false;
        Iterator<Tweet> lt = ls.iterator();
        while (lt.hasNext()){
            Tweet t = lt.next();
            if (t.contain(c)){
                result = true;
            }
        }
        return result;
    }




    // Test
    public static void main(String[] args){
        TweetCollection a = new TweetCollection();
        a.readURL();
       // for (int i = 0; i < a.ls.size(); i++){
       //     a.getList().get(i).printName();
            //a.getList().get(i).printContent();
       // }
        System.out.println(a.searchName("Will somebody please tell me how I've managed to use 7gb of data this month"));
        System.out.println(a.searchName("hahahahha"));
        System.out.println(a.getContentByName("Pvalsfr"));
        System.out.println(a.getContentByName("hahahha"));
        System.out.println(a.contains("comes"));
        System.out.println(a.contains("hahahahahaah"));
    }

}