// ==UserScript==
// @name        mineAI
// @namespace   minesAI
// @include     http://minesweeperonline.com/#beginner-night
// @version     1
// @required    http://localhost:8000/convnetjs.js
// @grant       none
// ==/UserScript==

// Load the library.
var D           = document;
var appTarg     = D.getElementsByTagName ('head')[0]  ||  D.body  ||  D.documentElement;
var jsNode      = D.createElement ('script');

jsNode.src      = 'http://localhost:8000/convnetjs.js';
jsNode.addEventListener ("load", initConvNetJsOnDelay, false);

appTarg.appendChild (jsNode);


// Allow some time for the library to initialize after loading.
function initConvNetJsOnDelay () {
    setTimeout (initConvNetJs, 666);
}

// Call the library's start-up function, if any. Note needed use of unsafeWindow.
function initConvNetJs () {
    
    // species a 2-layer neural network with one hidden layer of 20 neurons
    var layer_defs = [];
  
    // ConvNetJS works on 3-Dimensional volumes (sx, sy, depth), but if you're not dealing with images
    // then the first two dimensions (sx, sy) will always be kept at size 1
    layer_defs.push({type:'input', out_sx:1, out_sy:1, out_depth:2});
  
    // declare 4 neurons, followed by ReLU (rectified linear unit non-linearity)
    layer_defs.push({type:'fc', num_neurons:4, activation:'relu'});
  
    // 3 more for good measure 
    layer_defs.push({type:'fc', num_neurons:3, activation:'relu'}); 
 
    // declare the linear classifier on top of the previous hidden layer
    layer_defs.push({type:'softmax', num_classes:2});

    // defined our net with unsafeWindow for use in GreaseMonkey
    var net = new unsafeWindow.convnetjs.Net();
  
    // create our net with layers as defined above
    net.makeLayers(layer_defs);

    // define trainer
    var trainer = new convnetjs.SGDTrainer(net, {learning_rate:0.01, l2_decay:0.001});

    // define inputs (XOR)
    var t1 = new convnetjs.Vol([0, 0]);  // class 0
    var t2 = new convnetjs.Vol([0, 1]);  // class 1
    var t3 = new convnetjs.Vol([1, 0]);  // class 1
    var t4 = new convnetjs.Vol([1, 1]);  // class 0

    // train for 1000 iterations with corresponding classes
    for (var i = 0; i < 1000; i++) {
        trainer.train(t1, 0);
        trainer.train(t2, 1);
        trainer.train(t3, 1);
        trainer.train(t4, 0);
    }

    // learned probability
    var prob00 = net.forward(t1);
    var prob01 = net.forward(t2);
    var prob10 = net.forward(t3);
    var prob11 = net.forward(t4);

    // log probability
    console.log('p(0 | 00): ' + prob00.w[0] + ", p(1 | 00): " + prob00.w[1]);
    console.log('p(0 | 01): ' + prob01.w[0] + ", p(1 | 01): " + prob01.w[1]);
    console.log('p(0 | 10): ' + prob10.w[0] + ", p(1 | 10): " + prob10.w[1]);
    console.log('p(0 | 11): ' + prob11.w[0] + ", p(1 | 11): " + prob11.w[1]);
  
}

alert("Done");