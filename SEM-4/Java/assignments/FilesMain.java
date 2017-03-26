package assignments;
import java.io.*;
import java.util.*;

class UnsupportedFormatException extends Exception
{
    String errorMessage;
    UnsupportedFormatException()
    {
        errorMessage="Given option is not supported";
    }
    public String toString()
    {
        return errorMessage;
    }
}
class FileDetails implements Comparable<FileDetails>
{
    private String name;
    private double sizeKB;
    private int ordering;
    private Date lastModifiedDate;
    FileDetails()
    {
        name="";
        sizeKB=0.0;
        ordering=0;
        lastModifiedDate=new Date();
    }
    FileDetails(String name, double size, int order, Date lastMod)
    {
        this.name=name;
        sizeKB=size;
        ordering=order;
        lastModifiedDate=lastMod;
    }
    public int compareTo(FileDetails newFile)
    {
        if (ordering==0) return (name.compareToIgnoreCase(newFile.name));
        else if (ordering==1) return (int)(sizeKB-newFile.sizeKB);
        else if (ordering==2) return (lastModifiedDate.compareTo(newFile.lastModifiedDate));
        return 0;
    }
    public String toString()
    {
        return (name+"\t\t"+sizeKB+" KB\t\t"+lastModifiedDate);
    }
}
class FileList
{
    private String orderingType;
    FileList(String type)
    {
        orderingType=type;
        System.out.println(orderingType);
    }


    private int getOrder() throws UnsupportedFormatException
    {
        int ordering=0;
        if (orderingType.equals("")) ordering=0;
        else if (orderingType.equals("-s")) ordering=1;
        else if (orderingType.equals("-d")) ordering=2;
        else 
        {
            throw new UnsupportedFormatException();
        }
        return ordering;
    }
    private double getFileSize(File file)
    {
        double sizeKB=0.0;
        if (file.isFile())
        {
            sizeKB=file.length()/1024.0;
        }
        else
        {
            System.out.println ("Not a File!");
        }
        return sizeKB;
    }
    private double getDirectorySize(File dir)
    {
        if (!dir.isDirectory())
        {
            System.out.println("Not a directory!");
            return 0.0;
        }
        double sizeKB=0;
        File[] fList=dir.listFiles();
        if (fList==null) return 0.0;
        for (int i=0; i<fList.length; i++)
        {
            if (fList[i].isFile()) sizeKB+=getFileSize(fList[i]);
            else if (fList[i].isDirectory())
            {
                sizeKB+=getDirectorySize(fList[i]);
            }
        }
        return sizeKB;
    }
    void showList() throws IOException
    {
        try
        {
            BufferedReader br=new BufferedReader (new InputStreamReader (System.in));
            String dirName="."; // current directory
            File curDir=new File(dirName);
            File[] fList=curDir.listFiles();
            ArrayList<FileDetails> fileList=new ArrayList<FileDetails>();
            int ordering=0;
            for (int i=0; i<fList.length; i++)
            {
                double size=0;
                if (fList[i].isFile()) size=getFileSize(fList[i]);
                else if (fList[i].isDirectory()) size=getDirectorySize(fList[i]);
                FileDetails temp=new FileDetails(fList[i].getName(),size,getOrder(),new Date(fList[i].lastModified()));
                fileList.add(temp);
                //System.out.println(fList[i].getName()+" "+size+" "+new Date(fList[i].lastModified()));
            }
            Collections.sort(fileList);
            System.out.println("Name\t\t\tSize\t\t\tLast Modified");
            for (int i=0; i<fileList.size(); i++)
            {
                System.out.println(fileList.get(i));
            }
        }
        catch(UnsupportedFormatException ufe)
        {
            //System.err.println(ufe);
            ufe.printStackTrace();
        }
        finally
        {
            System.out.println("Thank You!");
        }
    }
}


public class FilesMain {
    public static void main(String[] args) throws IOException
    {
        String ordering="";
        if (args.length>0) ordering=args[0];
        FileList fl=new FileList(ordering);
        fl.showList();
        
    }
}
