package assignments;
import java.io.*;
import java.util.*;

class PatientDetails
{
	private double lowBloodPressure, upBloodPressure, temperature;
	private Date lastRecorded;
	PatientDetails(double ubp, double lbp, double temp)
	{
		upBloodPressure=ubp;
		lowBloodPressure=lbp;
		temperature=temp;
		lastRecorded=new Date(System.currentTimeMillis());
	}
	public String toString()
	{
		return ("Time of Record: "+lastRecorded.toString()+" Blood Pressure: "+upBloodPressure+"/"+lowBloodPressure+" Body Temperature: "+temperature+" F");
	}
} 

class Doctor
{
	private static int noDoctors=0;
	private String name, docCode;
	Doctor(String docName)
	{
		name=docName;
		noDoctors++;
		docCode="DOC"+String.format("%03d",noDoctors);
	}
	int getTotalDoctors()
	{return noDoctors;}
	String getDoctorCode()
	{return docCode;}
	public String toString()
	{
		return ("Name: "+name+" UID: "+docCode);
	}
}
class Patient
{
	private static int noPatients=0;
	private String name, patCode;
	ArrayList<PatientDetails> record;
	Doctor doctor;
	Patient(String patName)
	{
		name=patName;
		noPatients++;
		patCode="PAT"+String.format("%03d",noPatients);
		record=new ArrayList<PatientDetails>();
		doctor=null;
	}
	int getTotalPatients()
	{return noPatients;}
	void setDoctor(Doctor doc)
	{doctor=doc;}
	String getPatientCode()
	{return patCode;}
	boolean doctorAppointed()
	{return (doctor!=null);}
	void addDetails(PatientDetails detail)
	{
		if (detail==null)
		{
			System.out.println("Invalid details");
		}
		record.add(detail);
	}
	void showPatientInformation()
	{
		System.out.println ("Name: "+name+"\nUnique Patient Code: "+patCode+"\nAssigned Doctor: "+doctor);	
	}
	void showPatientDetails()
	{
		showPatientInformation();
		System.out.println ("Recorded details: ");
		for (int i=0; i<record.size(); i++)
		{
			System.out.println (record.get(i));
		}
	}
}
public class Hospital
{
	HashMap<String,Doctor> doctorRegister;
	HashMap<String,Patient> patientRegister;
	Hospital()
	{
		patientRegister=new HashMap<String,Patient>();
		doctorRegister=new HashMap<String,Doctor>();
	}
	private Doctor getDoctor(String code)
	{
		Doctor temp=doctorRegister.get(code);
		return temp;
	}
	public void registerNewDoctor() throws IOException
	{
		BufferedReader br=new BufferedReader(new InputStreamReader (System.in));
		System.out.println("Enter name of the doctor: ");
		String name=br.readLine();
		Doctor temp=new Doctor(name);
		String code=temp.getDoctorCode();
		doctorRegister.put(code,temp);
		System.out.println("Doctor Registration Complete\n Your unique ID is: "+code);
	}
	public void registerNewPatient() throws IOException
	{
		BufferedReader br=new BufferedReader(new InputStreamReader (System.in));
		System.out.println("Enter name of the patient: ");
		String name=br.readLine();
		Patient temp=new Patient(name);
		String code=temp.getPatientCode();
		patientRegister.put(code,temp);
		System.out.println("Patient Registration Complete\n Your unique patient code is: "+code);
	}
	public void assignDoctor(String patCode) throws IOException
	{	
		BufferedReader br=new BufferedReader (new InputStreamReader(System.in));
		System.out.println("List of available doctors: ");
		Set<String> docSet=doctorRegister.keySet();
		Iterator<String> it=docSet.iterator();
		while (it.hasNext())
		{
			System.out.println(doctorRegister.get(it.next()));
		}
		System.out.println ("Enter code of the doctor: ");
		String docCode=br.readLine();
		patientRegister.get(patCode).setDoctor(getDoctor(docCode));
	}
	public void recordPatientDetails(String patCode) throws IOException
	{
		BufferedReader br=new BufferedReader (new InputStreamReader(System.in));
		if (!patientRegister.containsKey(patCode))
		{
			System.out.println ("Invalid Patient Code");
			return;
		}
		if (!patientRegister.get(patCode).doctorAppointed())
		{
			System.out.println("No doctor appointed yet");
			return;
		}
		System.out.println ("Enter systolic blood pressure of patient: ");
		double ubp=Double.parseDouble(br.readLine());
		System.out.println ("Enter diastolic blood pressure of patient: ");
		double lbp=Double.parseDouble(br.readLine());
		System.out.println ("Enter body temperature of patient: ");
		double temp=Double.parseDouble(br.readLine());
		PatientDetails details=new PatientDetails(ubp,lbp,temp);
		patientRegister.get(patCode).addDetails(details);
	}
	public void releasePatient(String patCode)
	{
		if (!patientRegister.containsKey(patCode))
		{
			System.out.println ("Invalid Patient Code");
			return;
		}
		patientRegister.remove(patCode);
	}
	public void showDetails(String patCode)
	{
		if (!patientRegister.containsKey(patCode))
		{
			System.out.println ("Invalid Patient Code");
			return;
		}
		patientRegister.get(patCode).showPatientDetails();
	}
	public void displayRegister()
	{
		Set<String> patSet=patientRegister.keySet();
		Iterator<String> it=patSet.iterator();
		while (it.hasNext())
		{
			String temp=it.next();
			if (patientRegister.get(temp)!=null)
			patientRegister.get(temp).showPatientInformation();
		}
	}
}
