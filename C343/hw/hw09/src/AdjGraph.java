// C343 Summer 2018
// Homework 09
// Name: Yuheng Lin
// Username: yuhelin

// we use a few java.util classes:
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Vector;

public class AdjGraph implements Graph {

    // is it a directed graph (true or false) :
    private boolean digraph;

    private int totalNodes;
     // all the nodes in the graph:
    private Vector<String> nodeList;

    private int totalEdges;    
     // all the adjacency lists, one for each node in the graph:
    private Vector<LinkedList<Integer>>  adjList;

    // all the weights of the edges, one for each node in the graph:
    private Vector<LinkedList<Integer>> adjWeight;
    
    // every visited node:
    private Vector<Boolean> visited;
    // list of nodes pre-visit:
    private Vector<Integer> nodeEnum;
    
    public AdjGraph() {
        init();
    }

    public AdjGraph(boolean ifdigraph) {
        init();
        digraph = ifdigraph;
    }

    public void init() {
        nodeList = new Vector<String>(); 
        adjList = new Vector<LinkedList<Integer>>(); 
        adjWeight = new Vector<LinkedList<Integer>>();
        visited = new Vector<Boolean>();
        nodeEnum = new Vector<Integer>();
        totalNodes = totalEdges = 0;
        digraph = false;
    }

    // set vertices
    public void setVertices(String[] nodes) {
        for (int i = 0; i < nodes.length; i ++) {
            nodeList.add(nodes[i]);
            adjList.add(new LinkedList<Integer>());
            adjWeight.add(new LinkedList<Integer>());
            visited.add(false);
            totalNodes ++;
        }
    }
    
    // add a vertex
    public void addVertex(String label) {
        nodeList.add(label);
        visited.add(false);
        adjList.add(new LinkedList<Integer>());
        adjWeight.add(new LinkedList<Integer>());
        totalNodes ++;
    }
    public int getNode(String node) {
        for(int i = 0; i < nodeList.size(); i ++) {
            if(nodeList.elementAt(i).equals(node)) return i;
        }
        return -1;
    }

    // return the number of vertices
    public int length() {
        return nodeList.size();
    }

    // add edge from v1 to v2:
    public void setEdge(int v1, int v2, int weight) {
        LinkedList<Integer> tmp = adjList.elementAt(v1);
        if(adjList.elementAt(v1).contains(v2) == false) {
            tmp.add(v2);
            adjList.set(v1,  tmp);
            totalEdges ++;
            LinkedList<Integer> tmp2 = adjWeight.elementAt(v1);
            tmp2.add(weight);
            adjWeight.set(v1,  tmp2);
        }
    }

    public void setEdge(String v1, String v2, int weight) {
        if ((getNode(v1) != -1) && (getNode(v2) != -1)) {
            // add edge from v1 to v2:
            setEdge(getNode(v1), getNode(v2), weight);
            // for undirected graphs, add edge from v2 to v1 as well:
            if (digraph == false) {
                setEdge(getNode(v2), getNode(v1), weight);
            }
        }
    }

    // keep track whether a vertex has been visited or not,
    //    for graph traversal purposes:
    public void setVisited(int v) {
        visited.set(v, true);
        nodeEnum.add(v);
    }

    public boolean ifVisited(int v) {
        return visited.get(v);
    }
    
    
        // new for Lab 17:
    public LinkedList<Integer> getNeighbors(int v) {
        return adjList.get(v);
    }
    public int getWeight(int v, int u) {
        LinkedList<Integer> tmp = getNeighbors(v);
        LinkedList<Integer> weight = adjWeight.get(v);
        if (tmp.contains(u)) {
            return weight.get(tmp.indexOf(u));
        } else {
            return Integer.MAX_VALUE;
        }
    }
    
    
    
    public void clearWalk() {
        nodeEnum.clear();
        for (int i = 0; i < nodeList.size(); i ++)
            visited.set(i, false);
    }

    public void walk(String method) {
        clearWalk();
        // traverse the graph:
        for (int i = 0; i < nodeList.size(); i ++) {
            if (ifVisited(i) == false) {
                if (method.equals("BFS")) BFS(i);      // i is the start node
                else if (method.equals("DFS")) DFS(i); // i is the start node
                else {
                    System.out.println("unrecognized traversal order: " + method);
                    System.exit(0);
                }
            }
        }
        System.out.println(method + ":");
        displayEnum();
    }
    
    // Lab 17 TODO:
    //
    // write your methods here.
    //


    public int minVertex(int[] D){
        int v = 0;
        for (int i = 0; i < nodeList.size(); i++){
            if (!visited.get(i)){
                v = i;
                break;
            }
        }
        for (int i = 0; i < nodeList.size(); i++){
            if (!visited.get(i) && D[i] < D[v]){
                v = i;
            }
        }
        return v;
    }


    public void Dijkstra1(int s){
        clearWalk();
        int[] D = new int[nodeList.size()];
        for (int i = 0; i < D.length; i++){
            D[i] = Integer.MAX_VALUE;
        }
        D[s] = 0;
        for (int i = 0; i < D.length; i++){
            int v = minVertex(D);
            setVisited(v);
            if (D[v] == Integer.MAX_VALUE){
                System.out.print("Unreachable ");
            }
            else {
                for (int w: getNeighbors(v)){
                    if (D[w] > D[v] + getWeight(v, w)) {
                        D[w] = D[v] + getWeight(v, w);
                    }
                }
            }
        }
        System.out.print("List: ");
        for (int i = 0; i < D.length; i++){
            if (i == D.length - 1){
                System.out.print(D[i] + " ");
                System.out.println();
            }
            else {
                System.out.print(D[i] + " ");
            }
        }
    }


    public void Dijkstra2(int s){
        clearWalk();
        int v;
        int[] D = new int[nodeList.size()];
        BinNode[] E = new BinNode[totalEdges];
        E[0] = new BinNode(s, 0);
        MinHeap<Integer,Integer> H = new MinHeap(totalEdges, 1, E);
        for (int i = 0; i < nodeList.size(); i++){
            D[i] = Integer.MAX_VALUE;
        }
        D[s] = 0;
        for (int i = 0; i < nodeList.size(); i++){
            do { v = (H.removeMin()).getKey(); }
            while (ifVisited(v) == true);
            setVisited(v);
            if (D[v] == Integer.MAX_VALUE){
                System.out.print("Unreachable");
            }
            for (int w: getNeighbors(v)) {
                if (D[w] > D[v] + getWeight(v, w)) {
                    D[w] = D[v] + getWeight(v, w);
                    H.insert(new BinNode(w, D[w]));
                }
            }
        }
        System.out.print("List: ");
        for (int i = 0; i < D.length; i++){
            if (i == D.length - 1){
                System.out.print(D[i] + " ");
                System.out.println();
            }
            else {
                System.out.print(D[i] + " ");
            }
        }


    }



    
    public void DFS(int v) {
        setVisited(v);
        LinkedList<Integer> neighbors = adjList.elementAt(v);
        for(int i = 0; i < neighbors.size(); i ++) {
            int v1 = neighbors.get(i);
            if(ifVisited(v1) == false) DFS(v1); 
        }
    }
    public void BFS(int s) {
        ArrayList<Integer> toVisit = new ArrayList<Integer>();
        toVisit.add(s);
        while(toVisit.size() > 0) {
            int v = toVisit.remove(0); // first-in, first-visit
            setVisited(v);
            LinkedList<Integer> neighbors = adjList.elementAt(v);
            for(int i = 0; i < neighbors.size(); i ++) {
                int v1 = neighbors.get(i);
                if((ifVisited(v1) == false) && (toVisit.contains(v1) == false)) {
                    toVisit.add(v1);
                }
            }
        }
    }
    public void display() {
        System.out.println("total nodes: " + totalNodes);
        System.out.println("total edges: " + totalEdges);
    }
    public void displayEnum() {
        for(int i = 0; i < nodeEnum.size(); i ++) {
            System.out.print(nodeList.elementAt(nodeEnum.elementAt(i)) + " ");
        }
        System.out.println();
    }
    public static void main(String argv[]) {
        // first example: g1 is the graph in textbook Figure 11.16
        AdjGraph g1 = new AdjGraph(true);
        String[] nodes1 = {"A", "B", "C", "D", "E"};
        g1.setVertices(nodes1);
        g1.setEdge("A", "B", 10);
        g1.setEdge("A", "C", 3);
        g1.setEdge("A", "D", 20);
        g1.setEdge("B", "D", 5);
        g1.setEdge("C", "B", 2);
        g1.setEdge("C", "E", 15);
        g1.setEdge("D", "E", 11);
        System.out.println("-------------------- ");
        System.out.println("first graph example: ");
        g1.display();
        g1.walk("DFS");
        g1.walk("BFS");
        g1.Dijkstra2(0);

        // second example: g2 is the graph from
        //    https://commons.wikimedia.org/wiki/File:Dijkstra_Animation.gif
        AdjGraph g2 = new AdjGraph(false);
        String[] nodes2 = {"a", "b", "c", "d", "e", "f"};
        g2.setVertices(nodes2);
        g2.setEdge("a", "b", 7);
        g2.setEdge("a", "c", 9);
        g2.setEdge("a", "f", 14);
        g2.setEdge("b", "c", 10);
        g2.setEdge("b", "d", 15);
        g2.setEdge("c", "d", 11);
        g2.setEdge("c", "f", 2);
        g2.setEdge("d", "e", 6);
        g2.setEdge("e", "f", 9);
        System.out.println("--------------------- ");
        System.out.println("second graph example: ");
        g2.display();
        g2.walk("DFS");
        g2.walk("BFS");
        g2.Dijkstra2(0);
        System.out.println("------------------ ");
        System.out.println("That's all, folks! ");


        // third example: g3 is the graph from
        //    https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-videos/MIT6_006F11_lec16.pdf
        AdjGraph g3 = new AdjGraph(true);
        String[] nodes3 = {"A", "B", "C", "D", "E"};
        g3.setVertices(nodes3);
        g3.setEdge("A", "B", 10);
        g3.setEdge("A", "C", 3);
        g3.setEdge("B", "C", 1);
        g3.setEdge("B", "D", 2);
        g3.setEdge("C", "B", 4);
        g3.setEdge("C", "D", 9);
        g3.setEdge("C", "E", 2);
        g3.setEdge("D", "E", 7);
        g3.setEdge("E", "D", 9);
        System.out.println("--------------------- ");
        System.out.println("third graph example: ");
        g3.display();
        g3.walk("DFS");
        g3.walk("BFS");
        g3.Dijkstra2(0);
        System.out.println("------------------ ");
        System.out.println("That's all, folks! ");



    }


    // Lab 17 TODO:

    // write your new main() method here:

    // provide 3 different examples, using the two different versions of Dijkstra's algorithm
    //   with at least 10 nodes for each different graph




}
