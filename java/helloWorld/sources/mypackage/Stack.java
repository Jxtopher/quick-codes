/**
 * @author
 */
package mypackage;

import java.util.ArrayList; 
import java.util.logging.Level;
import java.util.logging.Logger;

public class Stack<T> {
    private static final Logger LOGGER = Logger.getLogger(Main.class.getName());
    private ArrayList<T> data;

    public Stack() {
        LOGGER.log(Level.INFO, 
            Thread.currentThread().getStackTrace()[1].getFileName() +":" + 
            Thread.currentThread().getStackTrace()[1].getLineNumber()+ " Create a Stack");
        data = new ArrayList<T>();
    }
    
    public void push(T element) {
        data.add(element); 
    }

    public T pop() {
        T tmp = data.get(data.size()-1);
        data.remove(data.size()-1);
        return tmp;
    }

    public Boolean isEmpty() {
        return true;
    }

    public Integer size() {
        return data.size();
    }
}