set xrange [-1:3]
set yrange [-1:3]
set label at 0, 0 "0" point pointtype 3 pointsize 2
set label at 0, 1 "1" point pointtype 5 pointsize 2
set label at 1, 0 "1" point pointtype 5 pointsize 2
set label at 1, 1 "1" point pointtype 5 pointsize 2
set xtics 0,1
set ytics 0,1
plot (0 - 0 * x) / 0.2 title 'i = 0'     ,\
     (0 - 0.2 * x) / 0.2 title 'i = 1'   ,\
     (0.2 - 0.2 * x) / 0.2 title 'i = 2' ,\
     -(-0.35 + 0.35 * x) / 0.35 title 'η = 0.1, w = (0,0,0), i = 3'
