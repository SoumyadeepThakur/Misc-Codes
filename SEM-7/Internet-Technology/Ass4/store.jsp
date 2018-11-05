<%@ page import="java.util.*, java.io.*, com.thakur_store.*" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
	<meta charset='UTF-8'>
	<meta http-equiv="X-UA-Compatible" content="chrome=1">
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
	<!--<script src="/js/order.js"></script>!-->
	<script>
		$(document).ready(function() {
			$('.group').hide();
			$('#option1').show();
			$('#select').change(function() {
		  		$('.group').hide();
				$('#'+$(this).val()).show();
		  	});
		});
	</script>
	<title>Home</title>
</head>
<body>
	<% 	String uname = (String)request.getAttribute("user-name");
		//Item i = new Item();
		ArrayList<Item> itemsList = (ArrayList<Item>)request.getAttribute("item-list");
		List<Item> newArrival = OrderItems.order(itemsList,1);
	%>

	<h1>Welcome <%= uname %></h1>
	<p>Logged in as <%= (String)request.getSession(false).getAttribute("user-name") %></p>

	Order By:
	<select class="dropdown" id="select" data-target=".order">
		<option value="option1">Default</option>
		<option value="option2">New Arrivals</option>
		<option value="option3">Discounted</option>
	</select>
	<div class="order">
		<h2> Suggested Items </h2>
		<div id="option1" class="group">
			<ul>
				<% for (Item i : itemsList)
					{
						%><li><%= i %></li><%
					}
				%>
			</ul>
		</div>
		<div id="option2" class="group">
			<ul>
				<% for (Item i : newArrival)
					{
						%><li><%= i %></li><%
					}
				%>
			</ul>
		</div>
		<div id="option3" class="group">
			<ul>
				<% for (Item i : itemsList)
					{
						%><li><%= i %></li><%
					}
				%>
			</ul>
		</div>

		<!--<c:forEach items="${items}" var="store-item">
			
			<p> <c:out value="${store-item}" /> </p>
			
		</c:forEach>!-->
		

	</div>
</body>
</html>