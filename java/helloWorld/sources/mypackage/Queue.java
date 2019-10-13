/**
 * @author
 */
package mypackage;

import java.util.ArrayList; 
import java.util.logging.Level;
import java.util.logging.Logger;

public class Queue<T> {
    private static final Logger LOGGER = Logger.getLogger(Main.class.getName());
    private ArrayList<T> data;

    public Queue() {
        LOGGER.log(Level.INFO, 
            Thread.currentThread().getStackTrace()[1].getFileName() +":" + 
            Thread.currentThread().getStackTrace()[1].getLineNumber()+ " Create a Pile");
        data = new ArrayList<T>();
    }
    


    public Boolean isEmpty() {
        return true;
    }

    public Integer size() {
        return data.size();
    }
}