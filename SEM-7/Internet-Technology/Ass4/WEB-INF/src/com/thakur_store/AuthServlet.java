/*
AUTHOR: SOUMYADEEP THAKUR
DATE: 5 Oct 2018
*/

package com.thakur_store;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;
import com.mongodb.MongoClient; 
import com.mongodb.MongoCredential;  
import com.mongodb.BasicDBObject;
import com.mongodb.BasicDBList;
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
    //public Authentication(String ip, int port, String dbName, String collName)
    //{
     //   this.serverIp = ip;
      //  this.port = port;
       // this.dbName = dbName;
        //this.collectionName = collName;
    //}
    public Authentication(DB db, String collName)
    {
        this.db = db;
        this.collectionName = collName;
    }
    public void initDB()
    {
        /*
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
       */
    }


    //public static String executeQuery(String query, String clientIP)

    public String login(String uname, String passwd)
    {
        
        DBCollection collection = db.getCollection(collectionName);
        System.out.println("Collection selected successfully");
        
        BasicDBObject filter = new BasicDBObject(), field = new BasicDBObject();
        filter.put("name", uname);
        field.put("tags",uname);
        DBCursor cursor = collection.find(filter, field);
        if (!cursor.hasNext()) return null;
        String value=null;
        while(cursor.hasNext())
        {
            BasicDBObject obj = (BasicDBObject)cursor.next();
            BasicDBList bdblist = (BasicDBList)obj.get("tags");
            value = bdblist.toString();
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
    private DB db;

    @Override
    public void init()
    {
        //String dbName = getServletContext().getInitParameter("db-name");
        //System.out.println("DB NAME::::" + dbName);
        //int portNo = Integer.parseInt(getServletContext().getInitParameter("port"));
        //System.out.println("PORT::::" + portNo);
        String serverIp = getServletContext().getInitParameter("ip");
        //System.out.println("IP::::" + serverIp);
        String collName = getServletContext().getInitParameter("db-collection");
        //System.out.println("COLLECTION::::" + collName);
        db = (DB)getServletContext().getAttribute("db-instance");
        authHandler = new Authentication(db, collName);
        //authHandler.initDB();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      // Set the response message's MIME type
        response.setContentType("text/html; charset=UTF-8");
        //PrintWriter out = response.getWriter();
        ArrayList<Item> items = new ArrayList<Item>();

        ServerDetails sd = (ServerDetails)getServletContext().getAttribute("server-details");
        System.out.println("SD:--------------------------------------------------------"+sd);
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
            //out.println("<h2>Welcome to apparel store</h2>");
            if (authString == null)
            {
            	//response.sendRedirect("/itlab/error.html");
              //  out.println("<p>null</p>");


            }
            else
            {
                //get tags of items from the auth string
                //String[] suggestedItems = getSuggestedItems()
                HttpSession session = request.getSession(false);
                if (session==null) // create new session
                {
                	session = request.getSession();
                }
                session.setAttribute("user-name", uname);
                ItemLoader itemLoader = new ItemLoader(db, "items", authString);
                itemLoader.createItemsList();
                items = itemLoader.getItemsAsList();
                /*
                out.println("<p>" + authString +"</p>");
                out.println("<p>" + sd.getDatabaseName() +"</p>");
                out.println("<p>" + sd.getPortNo() +"</p>");
                out.println("<p>" + sd.getServerIP() +"</p>");
                */

                for (Item i: items)
                {
                	//out.println("<p>" + i +"</p>");
                	System.out.println(i);
                }
            }
            request.setAttribute("user-name", uname);
            request.setAttribute("item-list", items);
            RequestDispatcher requestDispatcher = request.getRequestDispatcher("store.jsp");
            requestDispatcher.forward(request, response);
            //out.close();
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