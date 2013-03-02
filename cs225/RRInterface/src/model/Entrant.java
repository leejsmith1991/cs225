/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Lee
 */
public class Entrant {

    private int entrantNumber;
    private Course course;
    private String firstName;
    private String lastName;
    private Node nextCheckpoint;
    private MyTime raceTime;

    public Entrant() {
        this.raceTime = new MyTime(0,0);
    }

    public int getEntrantNumber() {
        return entrantNumber;
    }

    public void setEntrantNumber(int entrantNumber) {
        this.entrantNumber = entrantNumber;
    }

    public void setCourse(Course c) {
        this.course = c;
        nextCheckpoint = course.getNode(0);
    }

    public Course getCourse() {
        return course;
    }

    public MyTime getTime(){
        return raceTime;
    }
    
    public void setTime(int hour, int minutes){
        raceTime.updateTime(hour, minutes);
    }

    public void setNextCheckpoint() {
        int index = course.getNodeIndex(nextCheckpoint);
        if (index != course.getNodes().size() - 1) {
            for (index = +1; index < course.getNodes().size(); index++) {
                if (course.getNode(index).getNodeType() != NodeType.JN) {
                    nextCheckpoint = course.getNode(index);
                    break;
                }
            }
        }
    }

    public Node getNextCheckpoint() {
        return nextCheckpoint;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }
}
