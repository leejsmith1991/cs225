/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.TimerTask;
import model.MyTime;

/**
 *
 * @author Lee
 */
public class SystemTime extends Thread {

    private int hour;
    private int minute;

    @Override
    public void run() {
        while (true) {
            String h = new SimpleDateFormat("HH").format(Calendar.getInstance().getTime());
            hour = Integer.parseInt(h);
            String m = new SimpleDateFormat("MM").format(Calendar.getInstance().getTime());
            minute = Integer.parseInt(m);

            try {
                Thread.sleep(1000);
            } catch (InterruptedException ie) {
                return;
            }
        }
    }

    public int getHour() {
        return hour;
    }

    public int getMinute() {
        return minute;
    }
}
