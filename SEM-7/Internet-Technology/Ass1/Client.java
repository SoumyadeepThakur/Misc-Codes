import java.io.*;
import java.net.*;
import java.util.*;

public class Client
{
	private static String parseArgs(String[] args)
	{
		String request="";
		for (int i=2; i<args.length;)
		{
			if (args[i].equals("put"))
			{
				request += "[PUT-"+args[i+1]+":"+args[i+2]+"]";
				i+=3;
			}
			else if (args[i].equals("get"))
			{
				request += "[GET-"+args[i+1]+"]";
				i+=2;
			}
		}
		return request;
	}

    private static void sendRequest(Socket socket, String[] args) throws IOException
    {
    	Scanner sc = new Scanner(System.in);
        String input;
    
    	System.out.println("\r\nSending Request...");
        //input = sc.nextLine();
		input = parseArgs(args);
		System.out.println(input);
		PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
		out.println(input);
		out.flush();
        System.out.println("Request Sent");
    }
    
    public static void main(String[] args) throws Exception {
		Socket socket;
		socket = new Socket(InetAddress.getByName(args[0]), Integer.parseInt(args[1]));
		System.out.println("\r\nConnected to Server: " + socket.getInetAddress());
		sendRequest(socket, args);

		BufferedReader br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
		String str;

		System.out.println("\r\nServer Response: \n");
		str = br.readLine();
		String[] tokens = str.split("%");
		for (String token : tokens) System.out.println(token);
		socket.close();
    }
}
