package assignment2;
import java.io.*;
import java.util.*;

class FileCoordinate
{
	private int line, column;
	FileCoordinate()
	{
		line=0;
		column=0;
	}
	FileCoordinate(int line, int column)
	{
		this.line=line;
		this.column=column;
	}
	public String toString()
	{
		return ("Line="+line+" Column="+column); // display format
	}
}
class BookIndexing
{
	private int noLines;
	private String curFile;
	private ArrayList<String> fileContent;
	private HashMap<String,ArrayList<FileCoordinate> > wordIndex=new HashMap<String,ArrayList<FileCoordinate> >();
	BookIndexing(String filePath)
	{
		noLines=0;
		curFile=filePath;
		fileContent=new ArrayList<String>(); // store lines of the file
	}
	private void readFile() throws IOException
	{
		BufferedReader br=new BufferedReader(new FileReader(curFile));
		String line;
		while ((line=br.readLine())!=null)
		{
			fileContent.add(line); // read file and store lines in arraylist
			noLines++;
		}
	}
	public void makeIndexTable() throws IOException
	{
		readFile();
		for (int i=0; i<noLines; i++)
		{
			StringTokenizer stTok=new StringTokenizer(fileContent.get(i),".,!?; ");
			String word="";
			int row, col, cur=0;
			while (stTok.hasMoreTokens())
			{
				word=stTok.nextToken(); // extract word
				word=word.toUpperCase(); // convert to upper case to resolve case sensitivity issues
				row=i+1; // find coordinate of current word
				col=cur+1;
				cur+=word.length()+1;
				FileCoordinate coordn=new FileCoordinate(row,col);
				if (wordIndex.containsKey(word)) // if word is in Hash Map then add current coordinate to list
				{
					wordIndex.get(word).add(coordn);
				}
				else // create a new entry with that word
				{
					ArrayList<FileCoordinate> temp=new ArrayList<FileCoordinate>();
					temp.add(coordn);
					wordIndex.put(word,temp);
				}
			}
		}
	}
	public void displayMap()
	{
		Set<String> setWord=wordIndex.keySet();
		Iterator<String> it=setWord.iterator();
		System.out.println("List of words and their locations: (NOTE: Words are in Upper Case) ");
		ArrayList<String> words=new ArrayList<String>();
		int k=0;
		while (it.hasNext())
		{
			words.add(it.next()); // get each word in the Hash Map and put it in a list
		}
		Collections.sort(words); // sort the list
		for (int i=0; i<words.size(); i++)
		{
			System.out.println(words.get(i)+" - "+wordIndex.get(words.get(i))); // show locations
		}
	}

}

public class IndexFile
{
	public static void main(String args[]) throws IOException
	{
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		System.out.println ("Enter name of the file containing the paragraph: ");
		String fileName=br.readLine();
		BookIndexing bk=new BookIndexing(fileName);
		bk.makeIndexTable();
		bk.displayMap();
	}
}