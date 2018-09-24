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

class QueryHandler
{
    private MongoClient mongo;
    private MongoCredential credential;
    private MongoDatabase database;
    private DB db;
    private String serverIp, dbName, collectionName;
    private int port; 
    //private static void initDB()
    public QueryHandler(String ip, int port, String dbName, String collName)
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
        credential = MongoCredential.createCredential("sthakur", dbName, 
        "cleopatra7".toCharArray()); 
        System.out.println("Connected to the database successfully");  
      
        // Accessing the database 
        //database = mongo.getDatabase("itDb"); 
        db = mongo.getDB(dbName);
        System.out.println("Credentials ::"+ credential);


        //database.createCollection("user_query");
       // System.out.println("Collection created successfully"); 
    }


    //public static String executeQuery(String query, String clientIP)
    public String executeQuery(String query, String clientIP)
    {
        //initDB();
        System.out.println ("QUERY ::::");
        System.out.println (query);
        String params[] = query.split(" ");
        System.out.println ("QUERY PARAMS ::::");
        for (String param : params) System.out.print(param + " , ");
        System.out.println();
        String queryType = params[0];
        //MongoCollection<Document> collection = database.getCollection("user_query");
        DBCollection collection = db.getCollection(collectionName);
        System.out.println("Collection selected successfully");
        if (queryType.equals("get")) //handle get request from user
        {
            //handle error
            String key = params[1], value="";
            //collection.updateOne(Filters.eq("id", 1), Updates.set())
            BasicDBObject filter = new BasicDBObject(), field = new BasicDBObject();
            filter.put("ip", clientIP);
            field.put(key,1);
            DBCursor cursor = collection.find(filter, field);
            if (!cursor.hasNext()) return "No Data Found";
            while(cursor.hasNext())
            {
                BasicDBObject obj = (BasicDBObject)cursor.next();
                value = obj.getString(key);
            }
            return value;
            
        }
        else if (queryType.equals("put")) // handle put request from user
        {
            // handle error

            String key = params[1];
            String value = params[2];
            BasicDBObject filter = new BasicDBObject();
            filter.put("ip", clientIP);
            DBCursor cursor = collection.find(filter);
            if (cursor.hasNext()) 
            {
                    //collection.updateOne(Filters.eq("ip", clientIP), Updates.set(key, value));
                BasicDBObject updateQuery = new BasicDBObject();
                updateQuery.append("$set", new BasicDBObject().append(key,value));
                collection.update(filter, updateQuery);
            }

            else
            {
                BasicDBObject document = new BasicDBObject("ip", clientIP).append(key,value);
                collection.insert(document);
                System.out.println("New Document Inserted");
            }
            return "Put Successful";
            
        }
        else if (queryType.equals("manager")) // handle manager permission request
        {
            
        }
        return "";
    }
}
 
public class QueryServlet extends HttpServlet {
    
    private QueryHandler queryHandler;
    @Override
    public void init()
    {
        String dbName = getServletConfig().getInitParameter("db-name");
        System.out.println("DB NAME::::" + dbName);
        int portNo = Integer.parseInt(getServletConfig().getInitParameter("port"));
        System.out.println("PORT::::" + portNo);
        String serverIp = getServletConfig().getInitParameter("ip");
        System.out.println("IP::::" + serverIp);
        String collName = getServletConfig().getInitParameter("db-collection");
        System.out.println("COLLECTION::::" + collName);
        queryHandler = new QueryHandler(serverIp, portNo, dbName, collName);
        queryHandler.initDB();
    }

    @Override
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
      // Set the response message's MIME type
        response.setContentType("text/html; charset=UTF-8");
        //PrintWriter out = response.getWriter();
        
      
        try 
        {
            String ipAddress = request.getHeader("X-FORWARDED-FOR");  
            if (ipAddress == null)
            {  
                ipAddress = request.getRemoteAddr();  
            }
            
            String query = request.getParameter("querystring");

            String result = queryHandler.executeQuery(query, ipAddress);
            //out.println("<p>"+result+"</p>");
            //ConnectToDB.test();
         
            //out.println("<p>"+query+"</p>");
            //out.println("<a href='index.html'>BACK</a>");

            //out.println("</body></html>");
            request.setAttribute("clientIP", ipAddress);
            request.setAttribute("result", result);
            RequestDispatcher requestDispatcher = request.getRequestDispatcher("view.jsp");
            requestDispatcher.forward(request, response);

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
