package com.thakur_store;

import java.io.*;
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

public class ItemLoader
{
	String tags;
	String[] tagArray;
	private DB db;
	private String collName;
	private ArrayList<Item> itemList;
	public ItemLoader()
	{
		tags = null; db = null; collName = null;
		itemList = new ArrayList<Item>();
	}
	public ItemLoader(DB dbName, String collectionName, String tagString)
	{
		db = dbName;
		collName = collectionName;
		tags = tagString;
		itemList = new ArrayList<Item>();
	}
	private void getTagArray()
	{
		String temp = tags.substring(1,tags.length()-1);
		tagArray = temp.split(", ");
		for (String s : tagArray)
		{
			System.out.println("TAG--------------------------------------" + s);
		}

	}
	private int month(String mon)
	{
		if (mon.equals("Jan")) return 1;
		else if (mon.equals("Feb")) return 2;
		else if (mon.equals("Mar")) return 3;
		else if (mon.equals("Apr")) return 4;
		else if (mon.equals("May")) return 5;
		else if (mon.equals("Jun")) return 6;
		else if (mon.equals("Jul")) return 7;
		else if (mon.equals("Aug")) return 8;
		else if (mon.equals("Sep")) return 9;
		else if (mon.equals("Oct")) return 10;
		else if (mon.equals("Nov")) return 11;
		else if (mon.equals("Dec")) return 12;
		return Integer.MIN_VALUE;

	}
	private Item itemize(String name, String code, double price, String gender,  String tag, String date)
	{
		System.out.println("In itemize..........................");
		boolean gen = gender.charAt(0) == 'M' || gender.charAt(0) == 'm';
		String datestr[] = date.split(" ");
		int mon = month(datestr[1]);
		int dateint = Integer.parseInt(datestr[5])*10000 + mon*100 +  Integer.parseInt(datestr[2]);
		System.out.println("dateint.........................." + dateint);
		Item item = new Item(name, code, price, gen, tag, dateint);
		return item;
	}
	public void createItemsList()
	{
		getTagArray(); // split tags String into array of tags

		// open the collection for items
		DBCollection collection = db.getCollection(collName);
		System.out.println("Collection selected successfully");

		for (String tag : tagArray)
		{
			BasicDBObject filter = new BasicDBObject(), field = new BasicDBObject();
			filter.put("tag", tag);
			//field.put("")	
			Item item;

			DBCursor cursor = collection.find(filter);
			/* retrieve each document from the cursor and add the corresponding item to the list */
			while(cursor.hasNext())
			{
				BasicDBObject dBObject = (BasicDBObject)cursor.next();
				String name = dBObject.getString("itemname");
				String code = dBObject.getString("itemcode");
				double price = dBObject.getDouble("price");
				String gender = dBObject.getString("gender");
				String itemtag = dBObject.getString("tag");
				String date = dBObject.getString("date");

				item = itemize(name, code, price, gender, itemtag, date);
				itemList.add(item);

				System.out.println("-----------------------------------\n"+item);
				// double price = (Double)
			}
		}

	}
	public ArrayList<Item> getItemsAsList()
	{
		return itemList;
	}
}