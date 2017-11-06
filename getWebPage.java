import java.net.*;
import java.io.*;
import java.util.*;

public class getWebPage
{
    public static void printWebPage(URLConnection u)
    throws IOException
    {
        DataInputStream in = new
        DataInputStream(u.getInputStream());
        
        String text;
        
        while ((text = in.readLine()) != null)
        {
            System.out.println("  " + text);
        }
    }
    // Create a URL from the specified address, open a
    // connection to it,
    // and then display information about the URL.
    
    public static void main(String[] args)
    throws MalformedURLException, IOException
    {
        URL url = new URL(args[0]);
        URLConnection connection = url.openConnection();
        printWebPage(connection);
    }
}
