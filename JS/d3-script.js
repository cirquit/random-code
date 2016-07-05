

var data = [4,8,15,16,23,42]

var body  = d3.select("body");
var chart = body.append("div")
                .attr("class", "chart")

chart.selectAll("div")
         .data(data)
     .enter().append("div")
         .style("width", function(d) { return String(d * 10) + "px"; })
         .text (function(d) { return String(d); });