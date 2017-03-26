package assignment1;
import java.util.*;
import java.text.*;

class BasicStudent
{
    protected static int totalStudents=0;
    protected String name, roll, course, admissionDate;
    protected int[] marks;
    protected boolean receivedMarks;
    BasicStudent()
    {
        name="";
        roll="";
        course="";
        marks=new int[5]; // marks of 5 subjetcs
        receivedMarks=false;
        totalStudents++;
    }
    void set_details()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter name of student: ");
        name=sc.nextLine();
        System.out.println("Enter roll number of student: ");
        roll=sc.nextLine();
        System.out.println("Enter course of student: ");
        course=sc.nextLine();
        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        Date date = new Date();
        //System.out.println(dateFormat.format(date));
        admissionDate=dateFormat.format(date);
        //System.out.println(admissionDate);
        //sc.close();
        System.out.println("Admission done on "+admissionDate);
    }
    void set_marks()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println ("Enter marks of 5 subjects: ");
        for (int i=0; i<5; i++)
        {
            marks[i]=sc.nextInt();
        }
        receivedMarks=true;
        //sc.close();
    }
    void display_marksheet()
    {
        if (!receivedMarks)
        {
            System.out.println("Marks not yet updated");
        }
        else
        {
            int total=0, grade;
            double sgpa=0;
            boolean failure=false;
            for (int i=0; i<5; i++)
            {
                total+=marks[i];
                grade=Math.min(10,(int)(marks[i]/10)+1);
                if (grade<5)
                {
                    failure=true;
                }
                if (!failure) sgpa+=grade;
            }
            sgpa=sgpa/5;
            System.out.println("Name: "+name+"\nRoll No: "+roll+"\nCourse: "+course+"\nDate of Admission: "+admissionDate);
            System.out.println("Total Marks: "+total+ " out of 500");
            if (!failure)
            {
                System.out.println("SGPA: "+sgpa);
            }
        }
    }
    protected void finalize()
    {
        roll=null;
        course=null;
        admissionDate=null;
        marks=null;
        System.out.println(name+" deleted from list");
        name=null;
        totalStudents--;
    }
}
class Student extends BasicStudent implements Comparable<Student>
{
    private String department;
    private static String depts[] = {"CSE", "ETCE", "EE", "ME", "CHE", "CE"};
    Student()
    {
        super();
        department="";
    }
    public void set_details()
    {
        Scanner sc=new Scanner(System.in);
        System.out.println("Enter name of student: ");
        name=sc.nextLine();
        System.out.println("Enter roll number of student: ");
        roll=sc.nextLine();
        System.out.println("Enter course of student: ");
        course=sc.nextLine();
        System.out.println("Enter department");
        department=sc.nextLine();
        DateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        Date date = new Date();
        admissionDate=dateFormat.format(date);
        System.out.println("Admission done on "+admissionDate);
        //sc.close();
    }
    public int compareTo(Student stud)
    {
        int i=0, total1=0, total2=0;
        for (i=0; i<marks.length; i++)
        {
            total1+=marks[i];
            total2+=stud.marks[i];
        }
        return (total1-total2);
    }
}
class StudentList
{
    Student stList[];
    int no_students;
    static int MAX_SIZE=100;
    StudentList()
    {
        stList=new Student[MAX_SIZE];
        no_students=0;
    }
    private boolean isFull()
    {return (no_students==MAX_SIZE);}
    public void add(Student newStdnt)
    {
        if (isFull())
        {
            System.out.println("List is full");
            return;
        }
        stList[no_students++]=newStdnt;
    }
    public void


}
public class StudentMain
{
    public static void main(String args[])
    {
        ArrayList<Student> stlist=new ArrayList<Student>(); //
        Student st1=new Student();
        Student st2=new Student();
        st1.set_details();
        st2.set_details();
        st1.set_marks();
        st2.set_marks();
        stlist.add(st1);
        stlist.add(st2);
        System.out.println ("Contents of list: "+stlist);
        ListIterator<Student> i=stlist.listIterator(0);
        stlist.get(0).display_marksheet();
        stlist.get(1).display_marksheet();
        Collections.sort(stlist);
        stlist.get(0).display_marksheet();
        stlist.get(1).display_marksheet();
        stlist.remove(0);
        System.gc();


    }
}