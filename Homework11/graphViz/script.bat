echo off
echo This program is representing graph by using GraphViz
start dot -Tpng graph.dot -o image.png
timeout 2
start image.png