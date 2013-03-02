
package model;

import java.util.ArrayList;

/**
 *
 * @author Lee
 */
public class Course {
    private char courseName;
    private ArrayList<Node> nodes;
    private int lastCheckIndex;
    private int numberNodes;
    
    public Course(char name, int numberNodes){
        nodes = new ArrayList<Node>();
        this.courseName = name;
        this.numberNodes = numberNodes;
    }
    
    public ArrayList<Node> getNodes(){
        return nodes;
    }
    
    public char getName(){
        return courseName;
    }
    
    public void setName(char name){
        this.courseName = name;
    }
    
    public int getNodeIndex(Node n){
        int i;
        for (i = 0; i<nodes.size(); i++){
            if (nodes.get(i) == n){
               break;
            }
        }
        return i;
    }
    public int getNumberOfNodes(){
        return numberNodes;
    }
    
    public Node getNode(int index){
        return nodes.get(index);
    }
    
    public void addNode(Node n){
        nodes.add(n);
    }
    
}
