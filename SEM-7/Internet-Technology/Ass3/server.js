var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var bodyParser = require('body-parser');
var path = require('path');

app.set('view engine', 'ejs');
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); // support encoded bodies
app.use(express.static(path.join(__dirname + '/public')));

app.get('/', function(req, res)
{
	res.render(__dirname + '/index');
});
app.post('/chat', function(req, res)
{
	var uname = req.body.uname;
	var passwd = req.body.passwd;
	console.log(uname + ' ' + passwd);
	// code for authentication
	//res.render(__dirname + '/test', {username: uname, password: passwd});
	res.render(__dirname + '/chat', {username: uname, password: passwd});
});
io.on('connection', function(socket)
{
	console.log('A user connected');
	socket.on('disconnect', function()
	{
		console.log('A user disconnected');
	});
	socket.on('chat message', function(message)
	{
		//console.log('Message: ' + message);
		io.emit('chat message', message);
	});

});

http.listen(3000, function()
{
	console.log('Listening on *:3000');
});

