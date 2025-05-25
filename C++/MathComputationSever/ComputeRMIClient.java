/*Ben Potter - IT 386 Program 2*/

import java.io.*;
import java.rmi.Naming;
import java.util.Scanner;

/*Remote class that demonstrates Compute methods from 
  the ComputeInterface and calls from the ComputeImpl class*/

public class ComputeRMIClient{

public static void main (String[] args) {

    try {

      // check if arguments are provided
      if (args.length != 1) {
        System.out.println ("Usage: java ComputeRMIClient <port number>");
        return;
      }

      /* rename to ComputeInterface and ComputeRMIServer in appropriate places*/
      int portNumber = Integer.parseInt(args[0]);
      ComputeInterface remoteObj =
        (ComputeInterface) Naming.lookup("//localhost:"+portNumber+"/ComputeRMIServer");

      // Scanner object to get user input
      Scanner input = new Scanner(System.in);

      /* enter two numbers that will be used in the basic math operators*/
      System.out.println("enter 2 numbers for methods: sum, subtract, multiply and divide");

      double Math_Num1 = input.nextDouble();
      double Math_Num2 = input.nextDouble();

      // call one of each method
      System.out.println("sum: "+remoteObj.sum(Math_Num1, Math_Num2));
      System.out.println("subtract: "+remoteObj.subtract(Math_Num1, Math_Num2));
      System.out.println("multiply: "+remoteObj.multiply(Math_Num1, Math_Num2));
      System.out.println("divide: "+remoteObj.divide((int)Math_Num1, (int)Math_Num2));


      /* enter two integer numbers that will be used to calculate the GCD of the two given*/
      System.out.println("enter 2 numbers for method: GCD (Greatest Common Denominator)");
      int GCD_Num1 = input.nextInt();
      int GCD_Num2 = input.nextInt();

      System.out.println("GCD of "+GCD_Num1+" and "+GCD_Num2+": "+remoteObj.GCD(GCD_Num1, GCD_Num2));

      /* enter the radius that will be used to calculate the area of a circle*/
      System.out.println("Enter a radius for method: Circle_Area");
      double radius = input.nextDouble();
      System.out.println("Circle of radius "+radius+" = "+remoteObj.Circle_Area(radius));

      /* enter the length and width to determine the area of a rectangle (same idea as multiply)*/
      System.out.println("Enter length and width for method: Rectangle_Area");
      double length = input.nextDouble();
      double width = input.nextDouble();
      System.out.println("Area of rectangle = "+remoteObj.Rectangle_Area(length,width));

    } catch (Exception e) {
      System.out.println ("ComputeClient exception: " + e);
    }
  }
}
