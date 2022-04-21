const express = require('express');
const router = express.Router();

router.use((req, res, next) => {
  console.log('hoe');
  next()
});


router.post('/', function(req, res) {
    


    var execFile = require('child_process').execFile;
  
    var program = "./cpp/build/release/standalone";

    
    var child = execFile(program, $_POST[link],
      function (error, stdout, stderr) {
       
        var mapdata = stdout.split("\n");

        var splay = mapdata[0].split(" ")
                                .map(function (line) {
                                    return parseInt(line);
                                  });
        var graph = mapdata[1].split(" ")
                           .map(function (line) {
                             return parseInt(line);
                           });

        res.setHeader('Content-Type', 'application/json');
        res.end(JSON.stringify({
          results: mapdata
        }));

        console.log("Maps generated from " + type);
    });

});

module.exports = router;