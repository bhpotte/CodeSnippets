/*Ben Potter - IT 386 Program 2*/

import java.rmi.*;
import java.rmi.server.*;

/*Remote server class that implements Compute Interface*/

public class ComputeImpl extends UnicastRemoteObject implements ComputeInterface
{
    private String message;

    /** Constructor for remote object */
    public ComputeImpl (String msg) throws RemoteException{
        message = msg;
    }

    /*Implemented sum of two numbers*/
    public double sum(double num1, double num2) throws RemoteException
    {
        double result = num1 + num2;
        return Math.round(result*100.0)/100.0;
    }

    /*Implemented subtraction of two numbers*/
    public double subtract(double num1, double num2) throws RemoteException
    {
        double result = num1 - num2;
        return Math.round(result*100.0)/100.0;
    }

    /*Implemented multiplication of two numbers*/
    public double multiply(double num1, double num2) throws RemoteException
    {
        double result = num1*num2;
        return Math.round(result*100.0)/100.0;
    }

    /*Implemented division of two numbers, but num2 cannot be 0.*/
    public int divide(int num1, int num2) throws RemoteException
    {
        try 
        {
            int result = num1/num2;
            return result;
        }
        catch (java.lang.ArithmeticException e)
        {
            throw new ArithmeticException("Cannot divide by zero.");
        }
    }

    /*Implemented greatest common denominator using Euclidian Algorithm.*/
    public int GCD(int num1, int num2) throws RemoteException
    {
        if (num1 > num2)
        {
            /*if we reach here and num2 is less than/equal to 1, we return 1
              otherwise move on and subtract*/
            if (num2 <= 1) {return 1;}
            else {return GCD(num1-num2, num2);}
            
        }
        else if (num1 < num2)
        {
            /*if we reach here and num1 is less than/equal to 1, we return 1
              otherwise move on and subtract*/
            if (num1 <= 1) {return 1;}
            else{return GCD(num1, num2-num1);}
        }
        /*If we reach here without returning 1, that means we reached a GCD.*/
        else
        {
            return num1;
        }
    }

    /*Implemented calculation of finding the area of a circle given radius.*/
    public double Circle_Area(double r) throws RemoteException
    {
        // area of circle = r^2*pi
        // round to two decimal places
        double result = Math.round(((Math.pow(r,2))*Math.PI)*100.0)/100.0;
        return result;
    }

    /*Implemented calculation of finding the area of a rectangle given width and length.*/
    public double Rectangle_Area(double length, double width) throws RemoteException
    {
        // area of rectangle = length*width
        double result = length*width;
        return Math.round(result*100.0)/100.0;
    }
}