// C343 / Summer 2018
// Lab  03
// Name: Yuheng Lin
// Username: yuhelin


public class Lab03 {

    public static void main(String[] args){


        // Task A testing
        MyCard a = new MyCard();
        a.initialize();
        System.out.println(a.drawRandomCard());
        System.out.println(a.drawRandomCard());
        System.out.println(a.drawRandomCard());
        System.out.println(a.getDeck());



        // Task B testing
        Tweet t = new Tweet("someperson", "It is now possible to learn about a person's mobility preferences from data generated by his or her smartphone");
        t.printContent();
        System.out.println(t.contain("person"));
        System.out.println(t.contain("men"));
    }

}
