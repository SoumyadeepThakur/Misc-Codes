import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class QueryProcessor extends HttpServlet
{
	@Override
	public void doPost(HttpServletRequest request, HttpServlet response) throws IOException, ServletException
	{
		// resonse message MIME type
		response.setContentType("text/html; charset=UTF-8");
		PrintWriter out;

		try
		{
			out.println("<!DOCTYPE html>");
			out.println("<html><head>");
			out.println("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
			out.println("<title>Echo Servlet</title></head>");
			out.println("<body><h2>You have enter</h2>");

			String query = request.getParameter("query");

			out.println("<p>QUERY: "+query+"</p>");
		}
	}
}