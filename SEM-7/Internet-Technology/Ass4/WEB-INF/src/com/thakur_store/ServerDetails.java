/*
AUTHOR: SOUMYADEEP THAKUR
DATE: 27 OCT 2018
*/

package com.thakur_store;

/* JAVA BEAN TO REPRESENT THE SERVLET_CONTEXT DETAILS SPECIFIC TO THE BACKEND */
class ServerDetails
{
	private String dbName, serverIp;
	private int portNo;
	public ServerDetails()
	{
		dbName = serverIp = null;
		portNo = 0;
	}
	public ServerDetails(String dbName, int portNo, String serverIp)
	{
		this.dbName = dbName;
		this.portNo = portNo;
		this.serverIp = serverIp;
	}
	public String getDatabaseName()
	{
		return dbName;
	}
	public int getPortNo()
	{
		return portNo;
	}
	public String getServerIP()
	{
		return serverIp;
	}
}