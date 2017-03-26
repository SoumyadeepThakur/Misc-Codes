package assignments;
import java.io.*;
class Item
{
    private int qty;
    private float rate;
    private String name, itemCode;
    Item() 
    {
        name=""; 
        itemCode="";
        qty=0;
        rate=0.0f;
    }
    Item(String icode)
    {
        name="";
        itemCode=icode;
        qty=0;
        rate=0.0f;
    }
    void setDetails() throws IOException
    {
        if (itemCode.equals("")) 
        {
            System.out.println ("Item not created");
            return;
        }
        BufferedReader br=new BufferedReader (new InputStreamReader (System.in));
        System.out.println ("Enter name of the item: ");
        name=br.readLine();
        System.out.println ("Enter quantity of the item: ");
        qty=Integer.parseInt(br.readLine());
        System.out.println ("Enter rate of the item: ");
        rate=Float.parseFloat(br.readLine());
    }
    public int getQuantity()
    {return qty;}
    void setQuantity(int quantity)
    {qty=quantity;}
    public float getRate()
    {return rate;}
    String getName()
    {return name;}
    String getCode()
    {return itemCode;}
    boolean updateRate(float newRate)
    {
        boolean status=false;
        if (newRate<=0.0)
        {
            System.out.println("Invalid Rate");
        }
        else
        {
            status=true;
            rate=newRate;
        }
        return status;
    }

    void showDetails()
    {
        System.out.println ("Name: "+name+"\nItem Code: "+itemCode+"\nQuantity: "+qty);
        System.out.printf ("Rate: Rs. %.2f\n",rate);
    }
}

class ItemList
{
    private Item[] stock;
    private int noItems;
    private static int MAX_ITEMS=100;
    ItemList()
    {
        stock=new Item[MAX_ITEMS];
        noItems=0;
    }
    private boolean isFull()
    {return (noItems==MAX_ITEMS);}
    private int search(String icode)
    {
        int pos=-1; // return -1 if not found
        for (int i=0; i<noItems; i++)
        {
            if (stock[i].getCode().compareTo(icode)==0) // check if codes match
            {
                pos=i;
                break;
            }
        }
        return pos;
    }
    public void showDetails(String icode)
    {
        int pos=-1;
        pos=search(icode); // search for code
        if (pos>=0) // if item is in stock
        {
            stock[pos].showDetails();
        }
        else System.out.println("Item not in stock");
    }
    boolean pushBack(Item it)
    {
        if (isFull())
        {
            System.out.println("List is full");
            return false;
        }
        stock[noItems++]=it;
        return true;
    }
    public boolean addItem() throws IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter code of the item: ");
        String icode=br.readLine();
        boolean status=false;
        int pos=search(icode); // search for item in stock
        if (pos==-1) // item not in stock, can be added
        {
            status=true;
            Item temp=new Item(icode);
            temp.setDetails();
            pushBack(temp);
        }
        else
        {
            System.out.println("Item already exists in stock");
        }
        return status;
    }
    public boolean changeRate(String icode, float newRate)
    {
        int pos=search(icode);
        boolean status=false;
        if (pos>=0) // item found
        {
            status=stock[pos].updateRate(newRate);
        }
        return status;
    }
    void displayStock()
    {
        for (int i=0; i<noItems; i++)
        {
            stock[i].showDetails();
        }
    }
    public boolean issueItem(String icode, int quantity)
    {
        int pos=search(icode); // find item in stock
        boolean status=false;
        float cost=0.0f;
        if(pos>=0 && (stock[pos].getQuantity()-quantity)>=0) // sufficient items in stock
        {
            status=true;
            stock[pos].setQuantity(stock[pos].getQuantity()-quantity); // reduce quantity
            cost=quantity*stock[pos].getRate(); // calculate cost
            System.out.println ("Your Bill: ");
            System.out.println ("Item Code: "+icode+"\nItem Name: "+stock[pos].getName()+"\nAmount Issued: "+quantity);
            System.out.printf("Total Cost: Rs. %.2f\n",cost);
        }
        else System.out.println ("Item not in stock");
        return status;
    }
    public boolean receiveItem(String icode, int quantity)
    {
        int pos=search(icode); // search for item in stock
        boolean status=false;
        if(pos>=0)
        {
            status=true;
            stock[pos].setQuantity(stock[pos].getQuantity()+quantity); // increase quantity
            System.out.println ("Item Received: ");
            System.out.println ("Item Code: "+icode+"\nItem Name: "+stock[pos].getName()+"\nAmount Received: "+quantity+"\nTotal Amount in Stock: "+stock[pos].getQuantity());
        }
        else System.out.println ("Item not in stock");
        return status;
    }
}
public class ItemShop
{
    public static void main(String args[]) throws IOException
    {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        ItemList itList=new ItemList();
        boolean flag=true, status;
        int choice, quant;
        float rate=0.0f;
        String code="";
        while (flag)
        {
            System.out.println ("MENU:\n1. Add item  to list\n2. Issue an item from the list\n3. Receive an item to the list\n4. Change rate of an item\n5. Show details of an item\n0. Exit");
            System.out.println("Enter Your choice: ");
            choice=Integer.parseInt(br.readLine());
            switch(choice)
            {
                case 1: status=itList.addItem();
                        if (status) System.out.println("Item added successfully");
                        else System.out.println("Operation Failed");
                        break;
                case 2: System.out.println("Enter code of the item to be issued: ");
                        code=br.readLine();
                        System.out.println("Enter quantity to be issued: ");
                        quant=Integer.parseInt(br.readLine());
                        status=itList.issueItem(code,quant);
                        if (status) System.out.println("Item issued successfully");
                        else System.out.println("Operation Failed");
                        break;
                case 3: System.out.println("Enter code of the item to be received: ");
                        code=br.readLine();
                        System.out.println("Enter quantity to be received: ");
                        quant=Integer.parseInt(br.readLine());
                        status=itList.receiveItem(code,quant);
                        if (status) System.out.println("Item received successfully");
                        else System.out.println("Operation Failed");
                        break;
                case 4: System.out.println("Enter code of the item to be received: ");
                        code=br.readLine();
                        System.out.println("Enter new rate of the item: ");
                        rate=Float.parseFloat(br.readLine());
                        status=itList.changeRate(code,rate);
                        if (status) System.out.println("Rate changed successfully");
                        else System.out.println("Operation Failed");
                        break;
                case 5: System.out.println("Enter code of the item to be received: ");
                        code=br.readLine();
                        itList.showDetails(code);
                        break;
                case 0: flag=false;
                        break;
                default: System.out.println("Invalid choice");


            }
        }

        

    }
}