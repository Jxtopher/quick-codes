package mypackageTest.test.junit;

import java.util.logging.LogManager;
import junit.framework.TestCase;
import org.junit.*;

import mypackage.Queue;

public class QueueTest extends TestCase {
   private Queue<Integer> queue = null;

   public QueueTest(String arg0) {
        super(arg0);
        LogManager.getLogManager().reset();
   }

   protected void setUp() throws Exception {
         super.setUp();
         queue = new Queue<Integer>();
   }

   protected void tearDown() throws Exception {
         super.tearDown();
         queue = null;
   }

   @Test
   public void testSize() {
         assertTrue(queue.size() == 0);           
   }
}