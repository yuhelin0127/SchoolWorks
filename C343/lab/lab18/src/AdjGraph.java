// C343 Summer 2018

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

    // array of to-be-distances:
    private int[] d;


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
        d = new int[totalNodes];
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

    // ----------------
    // Lab 17 solution:
    // ----------------

    // the edge relaxation operation, as seen at Lecture 19, operating on the d[] array:
    private void relax(int u, int v, int w) {
        if ( d[v] > ( d[u] + w ) ) {
            d[v] = d[u] + w;
            // we don't need parent/predecessor nodes for Dijkstra's algorithm,
            //  but if necessary it would be set here:
            // predecessor[v] = u;
        }
    } // end of relax()


    // the minVertex() method, as from textbook page 391 :
    //   find the next closest vertex to the set of visited vertices
    //   (uncomment println() statements for lots of debugging printout)
    private int minVertex() {
        // System.out.println("---- starting minVertex() ----");
        int v = 0;
        // System.out.println("minVertex() choosing first v:");
        // initialize v to any unvisited vertex:
        for (int i = 0; i < totalNodes; i++) {
            // System.out.println("minVertex()     i = " + i);
            if (ifVisited(i) == false) {
                v = i;
                // System.out.println("minVertex()     v = " + v);
                break;
            }
        }
        // System.out.println("minVertex() looking for min d[i] :");
        // now look for the closest unvisited vertex:
        for (int i = 0; i < totalNodes; i++) {
            // System.out.println("minVertex()     i = " + i);
            // System.out.println("minVertex()     d[i] = " + d[i]);

            if ( (ifVisited(i) == false) && (d[i] < d[v]) ) {
                // System.out.println("minVertex()     d[v] = " + d[v]);
                v = i;
                // System.out.println("minVertex()     v changed to = " + i);
            }
        }
        // System.out.println("---- minVertex() chose vertex " + v + " ----");
        return v;
    }


    // Dijkstra's shortest path algorithm, implemented as from textbook page 391 :
    public void dijkstra1(String sNode) {
        System.out.println ("");
        System.out.println("Dijkstra's shortest path algorithm, starting from node " + sNode);

        d = new int[totalNodes];
        int s = getNode(sNode);

        // initialize the d array:
        for (int i = 0; i < totalNodes; i++) {
            d[i] = Integer.MAX_VALUE;
        }
        d[s] = 0;


        // print out the d array:
        System.out.println("the initial d[] array is : ");
        for (int i = 0; i < totalNodes; i++) {  System.out.print(d[i] + " " ); } System.out.println ("");

        // make sure that all vertices are unmarked:
        clearWalk();

        // starting Dijkstra's main loop:
        for (int i = 0; i < totalNodes; i++) {

            // find the closest vertex to all visited nodes:
            //   Note: the O() of minVertex impacts the O() of the entire Dijkstra's algorithm:
            int v = minVertex();

            setVisited(v);
            if (d[v] == Integer.MAX_VALUE) {
                System.out.println("unreachable vertex found in Dijkstra's algorithm!");
                return;
            }
            // now *relax* all neighbors of the node v:
            for (int neighbor : adjList.elementAt(v) ) {
                relax(v, neighbor, getWeight(v, neighbor));
            }

            System.out.println("after step " + i + " the d[] array is : ");
            for (int j = 0; j < totalNodes; j++) {  System.out.print(d[j] + " " ); } System.out.println ("");

        }
    }


    public void DFS(int v) {
        setVisited(v);
        LinkedList<Integer> neighbors = adjList.elementAt(v);
        for (int i = 0; i < neighbors.size(); i ++) {
            int v1 = neighbors.get(i);
            if (ifVisited(v1) == false) DFS(v1);
        }
    }
    public void BFS(int s) {
        ArrayList<Integer> toVisit = new ArrayList<Integer>();
        toVisit.add(s);
        while(toVisit.size() > 0) {
            int v = toVisit.remove(0); // first-in, first-visit
            setVisited(v);
            LinkedList<Integer> neighbors = adjList.elementAt(v);
            for (int i = 0; i < neighbors.size(); i ++) {
                int v1 = neighbors.get(i);
                if ((ifVisited(v1) == false) && (toVisit.contains(v1) == false)) {
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


    public int Mindis(ArrayList<Integer> ls, int[] dist){
        int v = ls.get(0);
        int minDis = dist[v];
        for (int i = 1; i < ls.size(); i++){
            if (dist[ls.get(i)] < minDis){
                v = ls.get(i);
                minDis = dist[v];
            }
        }
        return v;
    }

    public void mstPrim(){
        int n = nodeList.size();
        ArrayList<Integer> S = new ArrayList<>(n);
        for (int i = 0; i < n; i++){
            S.add(i);
        }
        int[] pre = new int[n];
        int[] dist = new int[n];
        for (int i = 0; i < n; i++){
            dist[i] = Integer.MAX_VALUE;
            pre[i] = -1;
        }
        int s = 0;
        dist[s] = 0;
        int cost = 0;
        while(S.isEmpty() == false){
            int u = Mindis(S, dist);
            S.remove(S.indexOf(u));
            cost += dist[u];
            if (dist[u] == Integer.MAX_VALUE) break;

            LinkedList<Integer> neighbors = getNeighbors(u);
            for (int j = 0; j < neighbors.size(); j++){
                int v = neighbors.get(j);
                if (S.contains(v) == true){
                    if (getWeight(u, v) < dist[v]){
                        dist[v] = getWeight(u, v);
                        pre[v] = u;
                    }
                }
            }
        }

        System.out.println("Edges in the MST: ");
        for (int i = 0; i < n; i++){
            int p = pre[i];
            if(p != -1){
                System.out.println("edge: " + nodeList.get(p) + " " + nodeList.get(i) + " " + getWeight(p ,i));
            }
        }
        System.out.println("The total cost of the spanning tree: " + cost);
        for(int i = 0; i < pre.length; i++){
            System.out.print(pre[i] + " ");
        }

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
        g1.dijkstra1("A");
        g1.mstPrim();

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
        g2.dijkstra1("a");
        g2.mstPrim();
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
        g3.dijkstra1("A");
        g3.mstPrim();
        System.out.println("------------------ ");
        System.out.println("That's all, folks! ");

    } // end of main()



} // end of class AdjGraph
