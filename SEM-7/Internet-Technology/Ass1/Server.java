import java.io.*;
import java.net.*;
import java.util.*;

class ServerThread implements Runnable
{
    private Socket client;
    private String clientAddress;
    private HashMap<String, HashMap<String, String> > clientDataMap;
    ServerThread(Socket socket, HashMap<String, HashMap<String, String> > clientMap) {client = socket; clientDataMap=clientMap;}
    public void run()
    {
        try
        {
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));        
            clientAddress = client.getInetAddress().getHostAddress();
            //int clientPort = client.getPort();
            String data;
            while ((data = in.readLine()) != null ) 
            {
                //System.out.println("\r\nMessage from " + clientAddress + ":" + clientPort + " - " + data);
                parseData(data);
            }
            client.close();
        }
        catch(IOException ioe)
        {ioe.printStackTrace();}
        catch(Exception e)
        {e.printStackTrace();}
    }
    private void parseData(String data) throws IOException
    {
        PrintWriter out = new PrintWriter(client.getOutputStream(), true);
        String[] requests = data.split("]"); 
        String response="";
        for (String request : requests)
        {
            if (request.length()==0) continue;
            int delim;
            String reqType = request.substring(1,delim=request.indexOf('-'));
            if (reqType.equals("PUT"))
            {
                String[] params = request.substring(delim+1).split(":");
                if (!clientDataMap.containsKey(clientAddress)) 
                {
                    clientDataMap.put(clientAddress,new HashMap<String, String>());
                }
                clientDataMap.get(clientAddress).put(params[0], params[1]);
            }
            else
            {
                String param = request.substring(delim+1);
                String t;
                if (!clientDataMap.containsKey(clientAddress)) t = "<null>";
                else t = clientDataMap.get(clientAddress).containsKey(param)?clientDataMap.get(clientAddress).get(param):"<null>";
                //System.out.println(t);
                response =response+t+"%";
            }
        }
        
        out.println(response);
        out.flush();
    }
}
public class Server
{
    private ServerSocket server;
    private HashMap<String, HashMap<String, String> > clientDataMap;
    public Server() throws Exception 
    { 
        this.server = new ServerSocket(0, 1, InetAddress.getLocalHost());
        this.clientDataMap = new HashMap<String, HashMap<String, String> >();
    }
    private void listen() throws Exception
    {
        while(true)
        {
            Socket client = this.server.accept();
            String clientAddress = client.getInetAddress().getHostAddress();
            System.out.println("\r\nNew connection from " + clientAddress);
            
            new Thread(new ServerThread(client, clientDataMap)).start();
        }
    }
    public InetAddress getSocketAddress()
    {
        return this.server.getInetAddress();
    }
    
    public int getPort()
    {
        return this.server.getLocalPort();
    }
    public static void main(String[] args) throws Exception
    {
        Server app = new Server();
        System.out.println("\r\nRunning Server: " + "Host=" + app.getSocketAddress().getHostAddress() + " Port=" + app.getPort());
        
        app.listen();
    }
}
