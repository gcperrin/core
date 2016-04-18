var cron = require('cron');
var http = require('http');
var mqtt = require('mqtt');
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
var BoardPacket = function() {
    this.id = 'bDA';
    this.status = null;
    this.data = null;
}

client.on('connect', function () {
    console.log("Connected to MQTT.");
    publishEvent.emit('publish', 'test', 'test_message');
});

publishEvent.on('publish', function(topic, payload) {
    const CronJob = cron.CronJob;
    var new_pay;
    var packet = new BoardPacket();
    new CronJob('*/7 * * * * *', function() {
	redisClient.get('bDA_status', function(err, boardStatus) {
	    packet.status = boardStatus;
	    if (boardStatus === 'up') {
		redisClient.get('bDA_data', function(err, data) {
		    packet.data = data;
		});
	    }
	});
	var packetString = JSON.stringify(packet);
	console.log('Sending packet');
	client.publish(topic, packetString);
	if (DEBUG === true) {
	    console.log(packet);
	}
    }, null, true, 'America/Los_Angeles');
});
