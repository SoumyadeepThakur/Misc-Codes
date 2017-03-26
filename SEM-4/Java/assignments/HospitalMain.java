package assignments;
import java.io.*;
import java.util.*;

public class HospitalMain
{
	public static void main(String args[]) throws IOException
	{
		BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
		Hospital h=new Hospital();
		/*
		h.registerNewDoctor();
		h.registerNewDoctor();
		h.registerNewDoctor();
		h.registerNewPatient();
		h.registerNewPatient();
		h.assignDoctor("PAT001");
		h.recordPatientDetails("PAT001");
		h.recordPatientDetails("PAT001");
		h.showDetails("PAT001");
		h.displayRegister();
		//Patient p=new Patient("bubu");
		//p.showPatientDetails();
		*/
		int choice;
		boolean flag=true;
		String code="";
		while (flag)
		{
			System.out.println("1.Register new patient\n2. Register new doctor\n3. Assign new doctor to a patient\n4. Record test results for a patient\n5. Show details of a patient\n6. Release Patient\n7. Show patient register\n0. Exit");
			System.out.println("Enter your choice: ");
			choice=Integer.parseInt(br.readLine());
			switch (choice)
			{
				case 1: h.registerNewPatient();
						break;
				case 2: h.registerNewDoctor();
						break;
				case 3: System.out.println ("Enter unique patient code: ");
						code=br.readLine();
						h.assignDoctor(code);
						break;
				case 4: System.out.println ("Enter unique patient code: ");
						code=br.readLine();
						h.recordPatientDetails(code);
						break;
				case 5: System.out.println ("Enter unique patient code: ");
						code=br.readLine();
						h.showDetails(code);
						break;
				case 6: System.out.println ("Enter unique patient code of patient to be released: ");
						code=br.readLine();
						h.releasePatient(code);
						break;
				case 7: h.displayRegister();
						break;
				case 0: flag=false;
						break;
				default: System.out.println("Invalic Choice");
			}
		}
	}
}
