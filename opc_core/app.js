var cron = require('cron');
var http   = require('http');
var mqtt   = require('mqtt');
var events = require('events');
var assert = require('assert');
var fs = require('fs');
var redis = require('redis');

var PORT = 8092;
var IP = 'localhost';
var CLIENT_IP = 'mqtt://169.54.207.21';
var DEBUG = true;

var server = http.createServer(function (req, res) {
    res.writeHead(200);
    res.end();
}).listen(PORT, IP);
console.log('Server running at http://' + IP + ':' + PORT + '/');

var client  = mqtt.connect(CLIENT_IP);
var redisClient = redis.createClient();
var publishEvent = new events.EventEmitter();


client.on('connect', function () {
    console.log("Connected to MQTT.");
    publishEvent.emit('publish', 'test', 'test_message');
});
/*
client.on('message', function (topic, message) {
    var retvalkeys = Object.keys(returnval);
    // Parse message
    var removeNS = (message.toString()).split('=');
    var msgSplit = (removeNS[2].toString()).split(',');

});
*/
publishEvent.on('publish', function(topic, payload) {
    var CronJob = cron.CronJob;
    var new_pay;
    new CronJob('* * * * * *', function() {
	redisClient.get("bDA_data", function(err, reply) {
	    // reply is null when the key is missing 
	    console.log(reply);
	    new_pay = reply;
	});
	console.log('You will see this message every second');
	client.publish(topic, new_pay);
    }, null, true, 'America/Los_Angeles');
});
