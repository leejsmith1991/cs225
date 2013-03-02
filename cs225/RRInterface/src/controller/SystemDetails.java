/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import java.awt.Dimension;
import java.awt.Toolkit;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Timer;
import model.MyTime;

/**
 *
 * @author Lee
 */
public class SystemDetails {
    Toolkit toolkit = Toolkit.getDefaultToolkit();
    Dimension screenSize;
    SystemTime systemTime;
    Calendar date;
    
    
    public SystemDetails(){
        screenSize = toolkit.getScreenSize();
        systemTime = new SystemTime();
        systemTime.start();
    }
       
    public int getScreenSizeX(){
        return screenSize.width;
    }
    
    public int getScreenSizeY(){
        return screenSize.height;
    }
   
}
