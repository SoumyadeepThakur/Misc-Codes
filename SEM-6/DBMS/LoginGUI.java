import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class LoginGUI
{
	JFrame loginFrame;
	JTextField unameField;
	JPasswordField passwdField;
	JButton loginButton, cancelButton;
	String uname, passwd;
	boolean loginInfo = false;
	public LoginGUI()
	{
		loginFrame = new JFrame("Login");
		loginFrame.setLayout(new FlowLayout());
		loginFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		loginFrame.setSize(400,400);

		unameField = new JTextField(20);
		passwdField = new JPasswordField(20);
		loginButton = new JButton("Log In");
		loginButton.addActionListener(new LoginListener());

		cancelButton = new JButton("Cancel");
		cancelButton.addActionListener( (e) -> {System.exit(0);});

		loginFrame.add(unameField);
		loginFrame.add(passwdField);
		loginFrame.add(loginButton);
		loginFrame.add(cancelButton);

		loginFrame.setVisible(true);

	}
	private class LoginListener implements ActionListener
	{
		public void actionPerformed(ActionEvent ae)
		{
			uname = unameField.getText();
			passwd = new String(passwdField.getPassword());
			loginInfo = true;
		}
	}
	public String getUname()
	{return uname;}
	public String getPassword()
	{return passwd;}
	public boolean hasInfo()
	{return loginInfo;}
}