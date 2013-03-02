/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Lee
 */
public class Entrants {
    private int entrantNumber;
    private char courseLetter;
    private String firstName;
    private String lastName;

    public int getEntrantNumber() {
        return entrantNumber;
    }

    public void setEntrantNumber(int entrantNumber) {
        this.entrantNumber = entrantNumber;
    }

    public char getCourseLetter() {
        return courseLetter;
    }

    public void setCourseLetter(char courseLetter) {
        this.courseLetter = courseLetter;
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
