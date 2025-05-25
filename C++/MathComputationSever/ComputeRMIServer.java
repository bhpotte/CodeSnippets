/*Ben Potter - IT 386 Program 2*/

import java.io.*;
import java.rmi.Naming;
import java.rmi.server.*;

/*Basically HelloRMIServer but for ComputeImpl instead of HelloImplementation*/

public class ComputeRMIServer {
    public static void main(String args[]) {
        try {
            // check if arguments are provided
            if (args.length != 1) {
                System.out.println ("Usage: java ComputeRMIServer <port number>");
                return;
            }
            int portNumber = Integer.parseInt(args[0]);

            ComputeImpl obj = new ComputeImpl("Hello IT 386 from RMI!!");
            // Bind this object instance to the name "HelloServer"
            Naming.rebind("//localhost:"+portNumber+"/ComputeRMIServer", obj);
            System.out.println("The Compute server is ready");


        } catch (Exception e) {
            System.out.println("Compute Server failed: " + e.getMessage());
            e.printStackTrace();
        }
    }

}
