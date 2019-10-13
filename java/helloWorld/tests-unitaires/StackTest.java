package mypackageTest.test.junit;

import junit.framework.TestCase;
import org.junit.*;

import mypackage.Stack;

public class StackTest extends TestCase {
   private Stack<Integer> stack = null;

   public StackTest(String arg0) {
         super(arg0);
         
   }

   protected void setUp() throws Exception {
         super.setUp();
         stack = new Stack<Integer>();
   }

   protected void tearDown() throws Exception {
         super.tearDown();
         stack = null;
   }

   @Test
   public void testSize() {
         assertTrue(stack.size() == 0);           
   }

   @Test
   public void testPush() {
      stack.push(5);
      assertTrue(stack.size() == 1);           
   }
}