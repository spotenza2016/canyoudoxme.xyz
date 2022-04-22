var path = require('path');
var express = require('express');
var app = express();
var fs = require('fs');
const com = require('./public/com');
const { runInNewContext } = require('vm');
const router = express.Router();
const port=3000;
const hostname = '127.0.0.1';


//useful for sending data between files
app.use(express.json()); 
app.use(express.urlencoded()); 


//define home directory
var dir = path.join(__dirname, 'public');

//set up definitions for file requests
var mime = {
    html: 'text/html',
    txt: 'text/plain',
    css: 'text/css',
    gif: 'image/gif',
    jpg: 'image/jpg',
    png: 'image/png',
    svg: 'image/svg+xml',
    js: 'application/javascript'
};


//handle input/output for c++ file
app.post('/public/com.js', function(req, res) {
    var execFile = require('child_process').execFile;
    //location of built c++ file (not relative)
    var program = "./public/integrate/c++/main.out";

    // data from the browser
    var tprof = [];
    tprof.push("map", req.body.link);
    //send in twitter profile, receive locations
    var child = execFile(program, tprof,
      function (error, stdout, stderr) {
        console.log(stdout);
        var mapdata = stdout.split("\n");
        console.log(mapdata)
        var splay = mapdata[1].split(" ")
                                .map(function (line) {
                                    return parseFloat(line);
                                  });
        console.log(splay);
        var graph = mapdata[2].split(" ")
                           .map(function (line) {
                             return parseFloat(line);
                           });

        //return data to call
        console.log(graph);
        res.setHeader('Content-Type', 'application/json');
        res.end(JSON.stringify({
          splay: splay, graph: graph
        }));

    });
    
});



//handle all file requests for html, css, png, etc.

app.get('*', function (req, res) {
    var file = path.join(dir, req.path.replace(/\/$/, '/index.html'));
    if (file.indexOf(dir + path.sep) !== 0) {
        return res.status(403).end('Forbidden');
    }
    var type = mime[path.extname(file).slice(1)] || 'text/plain';
    var s = fs.createReadStream(file);
    s.on('open', function () {
        res.set('Content-Type', type);
        s.pipe(res);
    });
    s.on('error', function () {
        res.set('Content-Type', 'text/plain');
        res.status(404).end('Not found, this one');
    });

});

app.listen(3000, function () {
    console.log('Listening on ' + hostname + ':' + port);
});






















// var http = require('http');
// var fs = require('fs');

// http.createServer(function(request, response) {
//     if(request.url=='/'){
//         fs.readFile('./index.html', function (err, html) {
//              if (err) {
//                   res.send(500,{error: err});
//              }
//              response.writeHeader(200, {"Content-Type": "text/html"});
//              response.write(html);
//              response.end();
//         });
//     } else if(request.url=='images/Modified-Twitter-Logo.png'){
//         fs.readFile('images/Modified-Twitter-Logo.png', function (err, images) {
//              if (err) {
//                   res.send(500,{error: err});
//              }
//              response.writeHeader(200, {"Content-Type": "text/css"});
//              response.write(images);
//              response.end();
//         });
//     }

// }).listen(8080);
















// var http = require('http');
// var fs = require('fs');
// var url = require('url');

// // Create a server
// http.createServer( function (request, response) {  
//    // Parse the request containing file name
//    var pathname = url.parse(request.url).pathname;
   
//    // Print the name of the file for which request is made.
//    console.log("Request for " + pathname + " received.");
   
//    // Read the requested file content from file system
//    fs.readFile(pathname.substr(1), function (err, data) {
//       if (err) {
//          console.log(err);
         
//          // HTTP Status: 404 : NOT FOUND
//          // Content Type: text/plain
//          response.writeHead(404, {'Content-Type': 'text/html'});
//       } else {	
//          //Page found	  
//          // HTTP Status: 200 : OK
//          // Content Type: text/plain
//          response.writeHead(200, {'Content-Type': 'text/html'});	
         
//          // Write the content of the file to response body
//          response.write(data.toString());		
//       }
      
//       // Send the response body 
//       response.end();
//    });   
// }).listen(8081);

// // Console will print the message
// console.log('Server running at http://127.0.0.1:8081/');
