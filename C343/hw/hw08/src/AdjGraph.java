// a simple implementation for graphs with adjacency lists

// C343 Summer 2018
// Homework 08
// Name: Yuheng Lin
// Username: yuhelin

// we use a few java.util classes:
import java.time.Instant;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;

public class AdjGraph implements Graph {
    private boolean digraph;
    private int totalNode;
    private Vector<String> nodeList;
    private int totalEdge;
    private Vector<LinkedList<Integer>>  adjList; // adjacency list
    private Vector<Boolean> visited;
    private Vector<Integer> nodeEnum; // list of nodes pre visit
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
        visited = new Vector<Boolean>();
        nodeEnum = new Vector<Integer>();
        totalNode = totalEdge = 0;
        digraph = false;
    }
    // set vertices
    public void setVertices(String[] nodes) {
        for(int i = 0; i < nodes.length; i ++) {
            nodeList.add(nodes[i]);
            adjList.add(new LinkedList<Integer>());
            visited.add(false);
            totalNode ++;
        }
    }
    // add a vertex
    public void addVertex(String label) {
        nodeList.add(label);
        visited.add(false);
        adjList.add(new LinkedList<Integer>());
        totalNode ++;
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
    // add edge from v1 to v2
    public void setEdge(int v1, int v2, int weight) {
        LinkedList<Integer> tmp = adjList.elementAt(v1);
        if(adjList.elementAt(v1).contains(v2) == false) {
            tmp.add(v2);
            adjList.set(v1,  tmp);
            totalEdge ++;
        }
    }
    public void setEdge(String v1, String v2, int weight) {
        if((getNode(v1) != -1) && (getNode(v2) != -1)) {
            // add edge from v1 to v2
            setEdge(getNode(v1), getNode(v2), weight);
            // for undirected graphs, add edge from v2 to v1 as well
            if (digraph == false) setEdge(getNode(v2), getNode(v1), weight);
        }
    }

    // it is important to keep track if a vertex is visited or not (for traversal)
    public void setVisited(int v) {
        visited.set(v, true);
        nodeEnum.add(v);
    }
    public boolean ifVisited(int v) {
        return visited.get(v);
    }
    public void clearWalk() {
        // clean up before traversing
        nodeEnum.clear();
        for(int i = 0; i < nodeList.size(); i ++) visited.set(i, false);
    }
    public void walk(String method) {
        clearWalk();
        // traverse the graph 
        for(int i = 0; i < nodeList.size(); i ++) {
            if(ifVisited(i) == false) {
                if(method.equals("BFS")) BFS(i);      // i is the start node
                else if(method.equals("DFS")) DFS(i); // i is the start node
                else {
                    System.out.println("unrecognized traversal order: " + method);
                    System.exit(0);
                }
            }
        }
        System.out.println(method + ":");
        displayEnum();
    }


    public void componentsAndSizes(){
        Vector<Integer> componentNum = new Vector<>();
        int OldSize = 0;
        int NewSize = 0;
        for (int i = 0; i < nodeList.size(); i++){
            if (! ifVisited(i)) {
                BFS(i);
                for ( boolean m : visited) {
                    if (m == true) {
                        NewSize++;
                    }
                }
                NewSize -= OldSize;
                OldSize += NewSize;
                componentNum.add(NewSize);
                NewSize = 0;
            }
        }
        System.out.println("total components: " + componentNum.size());
        for (int i = 0; i < componentNum.size(); i++){
            System.out.println("component " + i + " contains " + componentNum.get(i) + " nodes");
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
        System.out.println("total nodes: " + totalNode);
        System.out.println("total edges: " + totalEdge);
    }
    public void displayEnum() {
        for(int i = 0; i < nodeEnum.size(); i ++) {
            System.out.print(nodeList.elementAt(nodeEnum.elementAt(i)) + " ");
        }
        System.out.println();
    }

    public void numberOfEdges(){
        int n = nodeList.size();
        int[][] NofE = new int[n][n];
        for (int i = 0; i < n; i++){
            NofE[i][i] = 0;
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    if (adjList.elementAt(i).contains(j)) {
                        NofE[i][j] = 1;
                    }
                    else {
                        NofE[i][j] = 999;
                    }
                }
            }
        }
        for (int k = 0; k < n; k++){
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    if (NofE[i][j] > NofE[i][k] + NofE[k][j]){
                        NofE[i][j] = NofE[i][k] + NofE[k][j];
                    }
                }
            }
        }
        System.out.print("  ");
        for (int i = 0; i < n; i++){
            System.out.print(nodeList.get(i) + " ");
        }
        System.out.println();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    System.out.print(nodeList.get(i) + " " + NofE[i][j] + " ");
                } else {
                    if (j != n - 1) {
                        System.out.print(NofE[i][j] + " ");
                    } else {
                        System.out.print(NofE[i][j]);
                        System.out.println();
                    }
                }
            }
        }
    }


    public void topologicalSortWithQueue(){
        int n = nodeList.size();
        int[] C = new int[n];
        Queue<Integer> Q = new LinkedList<>();
        Vector<Integer> topOrder = new Vector<>();
        for (int i = 0; i < n; i++){
            LinkedList<Integer> t = adjList.elementAt(i);
            for (int c : t){
                C[c]++;
            }
        }

        for (int i = 0; i < n; i++){
            if (C[i] == 0){
                ((LinkedList<Integer>) Q).add(i);
            }
        }

        int count = 0;
        while (! Q.isEmpty()){
            int u = Q.poll();
            topOrder.add(u);
            for (int c : adjList.elementAt(u)){
                if (--C[c] == 0){
                    ((LinkedList<Integer>) Q).add(c);
                }
            }
            count++;
        }

        if (count != n){
            System.out.println("No solution is found.");
        }
        else {
            for (int c : topOrder) {
                System.out.print(nodeList.get(c) + " ");
            }
        }
    }






    public static void main(String[] args){
        AdjGraph a = new AdjGraph(true);
        String[] aNodes = new String[]{"J1", "J2", "J3", "J4", "J5", "J6", "J7"};
        a.setVertices(aNodes);
        a.setEdge(a.nodeList.get(0), a.nodeList.get(1), 1);
        a.setEdge(a.nodeList.get(0), a.nodeList.get(2), 1);
        a.setEdge(a.nodeList.get(2), a.nodeList.get(3), 1);
        a.setEdge(a.nodeList.get(3), a.nodeList.get(4), 1);
        a.setEdge(a.nodeList.get(4), a.nodeList.get(6), 1);
        a.setEdge(a.nodeList.get(1), a.nodeList.get(5), 1);
        a.setEdge(a.nodeList.get(1), a.nodeList.get(4), 1);
        a.setEdge(a.nodeList.get(1), a.nodeList.get(3), 1);
        a.topologicalSortWithQueue();
    }

    // 1) instantiate a new graph,
    // 2) assign2 vertices and edges to the graph,
    // 3) then display2 the graph's content (use display() )
    // 4) finally call your componentsAndSizes() method to provide
    //    output results as from Lab 14 instructions

    // provide 3 different examples,
    //   with at least 10 nodes for each different graph

}