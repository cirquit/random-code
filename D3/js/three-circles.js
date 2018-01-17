// var circle_data = [1, 2, 4, 8, 16, 32, 64, 128];

// var svg_circles = d3.select("body").append("svg")
//                                    .attr("width",  1280)
//                                    .attr("height", 500)
//                                    .attr("id", "svg-circles");

// var circles = svg_circles.selectAll("circle")
//                          .data(circle_data)
//                          .enter()
//                          .append("circle");

// circles.attr("cy", 250)
//        .attr("cx", function(d,i) { return d*5; })
//        .attr("r",  function(d,i) { return d / 2; })
//        .style("fill", function(d,i) { return "#00" + i.toString() + "88b";});


var svg_blocks = d3.select("body").append("svg")
                                  .attr("width", 1280)
                                  .attr("height", 500)
                                  .attr("id", "svg-blocks");

var block_width = 1.5;
var block_size  = 765;
var block_data = Array.apply(null, Array(block_size)).map(function(x,i){ return block_width; });

var blocks = svg_blocks.selectAll("rect")
                       .data(block_data)
                       .enter()
                       .append("rect");

blocks.attr("width", function(d,i) { return d; })
      .attr("height", 500)
      .attr("x", function(d,i) { return i*d; })
      .style("fill", index2col);

function index2col(d,i){
    return '#'
         + index2hex(Math.min(i,255))
         + index2hex(Math.max(0, Math.min(i-255,255)))
         + index2hex(Math.max(0, Math.min(i-510,255)))}

function index2hex(i){ 
    var hex = i.toString(16);
    if (hex.length === 1) { return '0' + hex;}
    else                  { return hex; }
}