package model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;

/**
 *
 * @author Lee
 */
public class Event {

    ArrayList<Node> nodes;
    ArrayList<Course> courses;
    ArrayList<Entrant> entrants;

    public Event() {
        nodes = new ArrayList<Node>();
        courses = new ArrayList<Course>();
        entrants = new ArrayList<Entrant>();
        populateNodes(readFile("nodes.txt"));
        populateCourses(readFile("courses.txt"));
        populateEntrants(readFile("entrants.txt"));
                
    }

    public ArrayList<String[]> readFile(String filename) {
        ArrayList<String[]> fileContents = new ArrayList<String[]>();
        String readLine;
        BufferedReader br;
        try {
            br = new BufferedReader(new FileReader("../Common/" + filename));
            while ((readLine = br.readLine()) != null) {
                String[] split = readLine.split(" ");
                fileContents.add(split);
            }
        } catch (Exception ex) {
            System.out.println("File not found");
        }
        return fileContents;
    }

    public void populateNodes(ArrayList<String[]> array) {
        Node tmpNode;
        NodeType tmpType;
        for (String[] s : array) {
            int nodeNumber = Integer.parseInt(s[0]);
            switch (s[1]) {
                case ("CP"):
                    tmpType = NodeType.CP;
                    break;
                case ("MC"):
                    tmpType = NodeType.MC;
                    break;
                default:
                    tmpType = NodeType.JN;
            }
            
            tmpNode = new Node(nodeNumber, tmpType);
            nodes.add(tmpNode);
        }
        for (Node m : nodes){
            System.out.println(m.getNodeNumber() + " " + m.getNodeType().toString());
        }
    }
    
    public void populateCourses(ArrayList<String[]> array){
        Course c;
        Node n;
        for (String[] s : array){
            char name = s[0].charAt(0);
            int numberNodes = Integer.parseInt(s[1]);
            c = new Course(name, numberNodes);
            for (int i = 2; i < numberNodes + 2 ; i++){
                n = nodes.get(Integer.parseInt(s[i])-1);
                c.addNode(n);
            }
            courses.add(c);
            System.out.print(c.getName() + " " + c.getNumberOfNodes() + " ");
            for (Node node : c.getNodes()){
                System.out.print(node.getNodeNumber() + ", ");
            }
            System.out.println();
        }
    }
    
    public void populateEntrants(ArrayList<String[]> array){
        Entrant e;
        
        for (String[] s : array){
            e = new Entrant();  
            e.setEntrantNumber(Integer.parseInt(s[0]));
            for (Course c : courses){
                if (c.getName() == s[1].charAt(0)){
                    e.setCourse(c);
                    break;
                }
            }
            e.setFirstName(s[2]);
            e.setLastName(s[3]);
            entrants.add(e);
        }
        for (Entrant a : entrants){
            System.out.println(a.getEntrantNumber() + " " + a.getCourse().getName() + " " + a.getFirstName() + " " + a.getLastName());
        }
    }
}
