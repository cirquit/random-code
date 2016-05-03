set xrange [-1:3]
set yrange [-1:5]
set label at 2, 4     "1" point pointtype 3 pointsize 2
set label at 0.5, 1.5 "1" point pointtype 3 pointsize 2
set label at 1, 0.5   "0" point pointtype 5 pointsize 2
set label at 0, 0.5   "0" point pointtype 5 pointsize 2
plot -(-0.7 + 0.0 * x) / 0.875 title 'η = 0.35, w = (0,0,0), i = 3' ,\
     -(-0.2 + 0.0 * x) / 0.25  title 'η = 0.1, w = (0,0,0), i = 3'  ,\
     -(-0.5 + -1.0 * x) / 0.75  title 'η = 0.1, w = (0,-1,1), i = 8'