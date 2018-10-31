/*
AUTHOR: SOUMYADEEP THAKUR
DATE: 5 Oct 2018
*/

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import com.mongodb.MongoClient; 
import com.mongodb.MongoCredential;  
import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;
import com.mongodb.DBCursor;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.client.*;
import com.mongodb.client.model.*;
import org.bson.Document;

class Authentication
{
    private MongoClient mongo;
    private MongoCredential credential;
    private MongoDatabase database;
    private DB db;
    private String serverIp, dbName, collectionName;
    private int port; 
    //private static void initDB()
    public Authentication(String ip, int port, String dbName, String collName)
    {
        this.serverIp = ip;
        this.port = port;
        this.dbName = dbName;
        this.collectionName = collName;
    }
    public void initDB()
    {
        // Creating a Mongo client 
        mongo = new MongoClient(serverIp , port); 
   
        // Creating Credentials 
        credential = MongoCredential.createCredential("sthakur", dbName, "cleopatra7".toCharArray()); 
        System.out.println("Connected to the database successfully");  
      
        // Accessing the database 
        db = mongo.getDB(dbName);
        System.out.println("Credentials ::"+ credential);


        //database.createCollection("user_query");
       // System.out.println("Collection created successfully"); 
    }


    //public static String executeQuery(String query, String clientIP)
    public String login(String uname, String passwd)
    {
        
        DBCollection collection = db.getCollection(collectionName);
        System.out.println("Collection selected successfully");
        
        BasicDBObject filter = new BasicDBObject(), field = new BasicDBObject();
        filter.put("name", uname);
        field.put("dob",uname);
        DBCursor cursor = collection.find(filter, field);
        if (!cursor.hasNext()) return null;
        String value="";
        while(cursor.hasNext())
        {
            BasicDBObject obj = (BasicDBObject)cursor.next();
            value = obj.getString("dob");
        }
        return value;
        //else if (queryType.equals("manager")) // handle manager permission request
        //{
        //    
        //}
        //return null;
    }
}
 
public class AuthServlet extends HttpServlet {
    
    private Authentication authHandler;

    @Override
    public void init()
    {
        String dbName = getServletConfig().getInitParameter("db-name");
        //System.out.println("DB NAME::::" + dbName);
        int portNo = Integer.parseInt(getServletConfig().getInitParameter("port"));
        //System.out.println("PORT::::" + portNo);
        String serverIp = getServletConfig().getInitParameter("ip");
        //System.out.println("IP::::" + serverIp);
        String collName = getServletConfig().getInitParameter("db-collection");
        //System.out.println("COLLECTION::::" + collName);
        authHandler = new Authentication(serverIp, portNo, dbName, collName);
        authHandler.initDB();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      // Set the response message's MIME type
        response.setContentType("text/html; charset=UTF-8");
        PrintWriter out = response.getWriter();
        
        try 
        {
            String ipAddress = request.getHeader("X-FORWARDED-FOR");  
            if (ipAddress == null)
            {  
                ipAddress = request.getRemoteAddr();  
            }
            
            /*
            EXTRACT USERNAME AND PASSWORD INFO FROM REQUEST
            */
            String uname = request.getParameter("uname");
            String passwd = request.getParameter("passwd");

            String authString = authHandler.login(uname, passwd);
            out.println("<h2>Welcome to apparel store</h2>");
            if (authString == null)
            {
            	//response.sendRedirect("/itlab/error.html");
                out.println("<p>null</p>");
            }
            else
            {
                //request.setAttribute("clientIP", ipAddress);
                //request.setAttribute("result", result);
                //RequestDispatcher requestDispatcher = request.getRequestDispatcher("view.jsp");
                //requestDispatcher.forward(request, response);
                out.println("<p>" + authString +"</p>");
            }
            out.close();
        }
        finally
        {
            //out.close();
        }
		 
   }
   @Override
   public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
   {
        doPost(request, response);
   }
}
