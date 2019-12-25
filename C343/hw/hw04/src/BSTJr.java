// C343 / Summer 2018
// Lab 08
// Name: Yuheng Lin
// Username: yuhelin

// a simple BST tree:
//  it's so simple we call it BSTJr...
//
// for C343 

public class BSTJr <K extends Comparable<?super K>> {
    BinNode<K> root;
    BinNode<K> curr;
    // TODO for C343/Summer 2018 - Lab 08
    // use "unbalanced" for balance checking: if a node is unbalanced, the tree will be unbalanced
    BinNode<K> unbalanced = null;

    public BSTJr() {
        root = null;
        curr = null;
    }

    public void build(K[] ks) {
        for (int i = 0; i < ks.length; i++) insert(ks[i]);
    }

    public void insert(K k) {
        BinNode<K> t = new BinNode<K>(k);
        if (root == null) {
            root = curr = t;
        } else {
            curr = search(root, k);
            if (k.compareTo(curr.getKey()) < 0) curr.setLeft(t);
            else curr.setRight(t);
        }
    }

    public BinNode<K> search(BinNode<K> entry, K k) {
        if (entry == null) return null;
        else {
            entry.setSize(entry.getSize() + 1); //update the size of the subtree by one
            if (entry.isLeaf()) return entry;
            if (k.compareTo(curr.getKey()) < 0) {
                if (entry.getLeft() != null) return search(entry.getLeft(), k);
                else return entry;
            } else {
                if (entry.getRight() != null) return search(entry.getRight(), k);
                else return entry;
            }
        }
    }

    public void display() {
        if (root == null) return;
        System.out.println("Preorder enumeration: key(size-of-the-subtree)");
        preorder(root);
        System.out.println();
    }

    public void displayInorder() {
        if (root == null) return;
        System.out.println("Preorder enumeration: key(size-of-the-subtree)");
        inorder(root);
        System.out.println();
    }

    public void displayPostorder() {
        if (root == null) return;
        System.out.println("Preorder enumeration: key(size-of-the-subtree)");
        postorder(root);
        System.out.println();
    }

    public void preorder(BinNode<K> entry) {
        System.out.print(entry.getKey() + "(" + entry.getSize() + ") ");
        if (entry.getLeft() != null) preorder(entry.getLeft());
        if (entry.getRight() != null) preorder(entry.getRight());
    }

    //  Exercise 5.
//  (a)
    public void inorder(BinNode<K> entry) {
        if (entry == null) {
        } else {
            inorder(entry.getLeft());
            System.out.print(entry.getKey() + "(" + entry.getSize() + ") ");
            inorder(entry.getRight());
        }
    }

    // (b)
    public void postorder(BinNode<K> entry) {
        if (entry == null) {
        } else {
            postorder(entry.getLeft());
            postorder(entry.getRight());
            System.out.print(entry.getKey() + "(" + entry.getSize() + ") ");
        }
    }


    // TODO for C343/Summer 2018 - Lab 08
    // implement checkBalance(), perhaps write treeHeight(node) as helper function
    public boolean checkBalance() {
        checkBalanceHelper(root);
        if (unbalanced == null) {
            return true;
        } else {
            return false;
        }
    }

    public void checkBalanceHelper(BinNode<K> n) {
        if (n == null) {
        } else {
            int a = getHeight(n.getLeft());
            int b = getHeight(n.getRight());
            int c = a - b;
            if (Math.abs(c) > 1) {
                unbalanced = n;
            } else {
                checkBalanceHelper(n.getLeft());
                checkBalanceHelper(n.getRight());
            }
        }
    }

    public int getHeight(BinNode<K> n) {
        if (n == null) {
            return 0;
        } else {
            int a = getHeight(n.getLeft());
            int b = getHeight(n.getRight());
            return (1 + Math.max(a, b));
        }
    }


    public BinNode<K> findKthSmallest(int k) {
        return findKthHelp(root, k);
    }

    public BinNode<K> findKthHelp(BinNode<K> n, int k) {
        if (root == null || k <= 0 || k > root.getSize()) {
            throw new IllegalArgumentException();
        }
        int a;
        if (n.getLeft() == null) {
            a = 0;
        }
        else {
            a = n.getLeft().getSize();
        }
        if (k < a + 1) {
            n = n.getLeft();
            return findKthHelp(n, k);
        }
        if (k == a + 1) {
            return n;
        }
        else {
            k = k - a - 1;
            n = n.getRight();
            return findKthHelp(n, k);
        }
    }


    
    public static void main(String[] argv) {
        BSTJr<Integer> tree = new BSTJr<Integer>();
        Integer[] ks = {37, 24, 42, 7, 2, 40, 120};
        Integer[] ks1 = {37,24,21,7};
        tree.build(ks);
        tree.display();
        tree.displayInorder();
        tree.displayPostorder();
        System.out.println(tree.findKthSmallest(3).getKey());
        System.out.println(tree.findKthSmallest(4).getKey());
        System.out.println(tree.checkBalance());
    }
}