package com.thakur_store;


import java.util.*;
import java.util.stream.*;

public class OrderItems
{
	public static List<Item> order(ArrayList<Item> items, int order)
	{
		List<Item> sortedItems = new ArrayList<Item>();
		if (order == 1) // new arrivals firts
		{
			sortedItems = items.stream().sorted(Comparator.comparing(Item::getDate).reversed()).collect(Collectors.toList());
		}
		return sortedItems;
	}
	public static void main(String[] args) {
		ArrayList<Item> i = new ArrayList<Item>();
		i.add(new Item("ABCD", "I1", 100, true, "es", 20180110));
		i.add(new Item("WXYZ", "I2", 200, true, "df", 20180711));
		i.add(new Item("PQRS", "I3", 1000, true, "cv", 20180111));
		i.add(new Item("LMNO", "I4", 500, true, "gh", 20180421));
		List<Item> i2 = order(i,1);
		for (Item x:i2) System.out.println(x);
	}
}