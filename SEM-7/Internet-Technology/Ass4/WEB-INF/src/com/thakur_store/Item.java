package com.thakur_store;

public class Item
{
	private String itemName, itemCode;
	private double price;
	private boolean gender;
	private String tag;
	private int date;
	public Item()
	{
		itemName = "";
		itemCode = "";
		price = -Double.MAX_VALUE;
		gender = false;
		tag = "";
		date = Integer.MIN_VALUE;
	}
	public Item(String itemName, String itemCode, double price,  boolean gender, String tag, int date)
	{
		this.itemName = itemName;
		this.itemCode = itemCode;
		this.price = price;
		this.gender = gender;
		this.tag = tag;
		this.date = date;
	}
	@Override
	public String toString()
	{
		return "ITEM NAME: " +itemName + " ITEM CODE: "+itemCode + " ITEM PRICE: "+price + " GENDER: "+gender + " DATE: "+date;
	}
	public int getDate()
	{
		return date;
	}
}