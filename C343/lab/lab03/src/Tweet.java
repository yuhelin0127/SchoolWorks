// C343 / Summer 2018
// Lab  03
// Name: Yuheng Lin
// Username: yuhelin


public class Tweet {

    private String name;
    private String content;

    public Tweet(String name, String content){
        this.name = name;
        this.content = content;
    }

    public void printContent(){
        System.out.println(this.content);
    }

    public boolean contain(String a){
        String c = this.content;
        return c.toLowerCase().contains(a.toLowerCase());
    }

}
