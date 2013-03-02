/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Lee
 */
public class Node {
    private int nodeNumber;
    private NodeType nodeType;
    
    public Node(int nodeNumber, NodeType nodeType){
       this.nodeNumber = nodeNumber;
       this.nodeType = nodeType;
   }
    
   public int getNodeNumber(){
       return nodeNumber;
   }
   
   public void setNodeNumber(int nodeNumber){
       this.nodeNumber = nodeNumber;
   }
   
   public NodeType getNodeType(){
       return nodeType;
   }
   
   public void setNodeType(NodeType nodeType){
       this.nodeType = nodeType;
   }
}
