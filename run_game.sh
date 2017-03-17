#!/bin/bash
bash compile.sh
python $3 &
./$1 127.0.0.1 12345 & >p1
./$2 127.0.0.1 12345 & >p2
