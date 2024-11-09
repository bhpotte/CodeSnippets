/*Ben Potter - IT 386 Program 2*/

import java.rmi.*;

/*ComputeInterface is a interface that establishes the methods
  that will be remotely called and implemented in ComputeImpl.*/

public interface ComputeInterface extends Remote 
{
    /*adds two numbers together*/
    double sum(double num1, double num2) throws RemoteException;

    /*subtracts two numbers*/
    double subtract(double num1, double num2) throws RemoteException;

    /*multiplies two numbers together*/
    double multiply(double num1, double num2) throws RemoteException;

    /*divides num1 by num2 (num2 cannot be 0)*/
    int divide(int num1, int num2) throws RemoteException;

    /*finds the greatest common denominator between two numbers given*/
    int GCD(int num1, int num2) throws RemoteException;

    /*computes area of circle given the radius*/
    double Circle_Area(double radius) throws RemoteException;

    /*computes area of rectangle given length and width*/
    double Rectangle_Area(double length, double width) throws RemoteException;
}