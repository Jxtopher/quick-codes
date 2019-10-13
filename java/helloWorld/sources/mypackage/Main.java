package mypackage;

import org.apache.commons.cli.*;

import java.util.logging.LogManager;
import java.util.logging.Level;
import java.util.logging.Logger;



class Main {
    private static Logger LOGGER = null;

    static {
        System.setProperty("java.util.logging.SimpleFormatter.format", "[%1$tF %1$tT] [%4$-7s] %5$s %n");
        LOGGER = Logger.getLogger(Main.class.getName());
    }

    public static void main(String args[]) {
        // Parse args
        // Options options = new Options();
        // options.addOption("h", "help", false, "prints the help content");
        // options.addOption("l", "logging", false, "logging (default:false)");


        //
        Stack<Integer> p = new Stack<Integer>();
        Integer a = 5;

        p.push(a);
        p.push(20);
        p.push(4);
        p.push(35);
    }
}
