/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package model;

/**
 *
 * @author Lee
 */
public class MyTime {
    private int hour;
    private int minute;
    
    public MyTime(){}
    
    public MyTime(int hour, int minute){
        this.hour = hour;
        this.minute = minute;
    }
    
    public void updateTime(int hour, int minute){
        this.hour = hour;
        this.minute = minute;
    }
    public int getTimeHour(){
        return hour;
    }
    public int getTimeMinute(){
        return minute;
    }
}
