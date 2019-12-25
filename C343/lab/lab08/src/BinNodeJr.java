// C343 / Summer 2018
// Lab 08
// Name: Yuheng Lin
// Username: yuhelin

//a simple class for binary tree (mini-assignment)
public class BinNodeJr <E extends Comparable<?super E>>{
    private E value;
    private BinNodeJr<E> left;
    private BinNodeJr<E> right;
    public BinNodeJr(E e) {
        value = e;
        left = right = null;
    }
    public void setLeft(BinNodeJr<E> node) {
        left = node;
    }
    public void setRight(BinNodeJr<E> node) {
        right = node;
    }
    public boolean find(E q) {
        return findHelper(this,q);
    }
    public boolean findHelper(BinNodeJr<E> n,E q){
        if (n == null){
            return false;
        }
        if (n.value == q) {
            return true;
        }
        else {
            return findHelper(n.left, q) || findHelper(n.right, q);
        }
    }

    public static void main(String[] argv) {
        BinNodeJr<Integer> root = new BinNodeJr<Integer>(10);
        BinNodeJr<Integer> node1 = new BinNodeJr<Integer>(30);
        BinNodeJr<Integer> node2 = new BinNodeJr<Integer>(40);
        BinNodeJr<Integer> node3 = new BinNodeJr<Integer>(50);
        BinNodeJr<Integer> node4 = new BinNodeJr<Integer>(60);
        node1.setLeft(node3);
        node1.setRight(node4);
        root.setLeft(node1);
        root.setRight(node2);
        //find() is to be implemented
        System.out.println("40 is found in the tree: " + root.find(60));
        //find(40) shall return true
        System.out.println("100 is found in the tree: " + root.find(100));
        //find(100) shall return false
    }
}