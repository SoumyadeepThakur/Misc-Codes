package com.thakur_store;

import javax.servlet.*;
import com.mongodb.MongoClient; 
import com.mongodb.MongoCredential;
import com.mongodb.DB;

public class ContextInitListener implements ServletContextListener
{
	@Override
	public void contextInitialized(ServletContextEvent event)
	{
		System.out.println("----------------------------------------------------------------------\nLISTENER INIT");
		ServletContext sc = event.getServletContext();
		String dbName = sc.getInitParameter("db-name");
		int portNo = Integer.parseInt(sc.getInitParameter("port"));
		String serverIp = sc.getInitParameter("ip");

		ServerDetails serverDetails = new ServerDetails(dbName, portNo, serverIp);
		sc.setAttribute("server-details", serverDetails);

		// Creating a Mongo client 
		MongoClient mongo = new MongoClient(serverIp , portNo); 
   
		// Creating Credentials 
		MongoCredential credential = MongoCredential.createCredential("sthakur", dbName, "cleopatra7".toCharArray()); 
		System.out.println("Connected to the database successfully");  
      
		// Accessing the database 
		DB db = mongo.getDB(dbName);
		System.out.println("Credentials ::"+ credential);
		sc.setAttribute("db-instance", db);


	}
	@Override
	public void contextDestroyed(ServletContextEvent event)
	{}
}