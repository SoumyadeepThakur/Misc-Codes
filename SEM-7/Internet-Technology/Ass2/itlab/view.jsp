<!DOCTYPE html>
<html>
<head>
	<meta charset='utf-8'>
	<meta http-equiv="X-UA-Compatible" content="chrome=1">
	<title>Query Response</title>
</head>
<body>
	<% 	String clientIp = (String)request.getAttribute("clientIP");
		String result = (String)request.getAttribute("result");
	%>
	Client IP:
	<p><% out.println(clientIp); %></p>
	<h2>Response:</h2>
	<p><% out.println(result); %></p>

	<a href='index.html'>BACK</a>
</body>
</html>
