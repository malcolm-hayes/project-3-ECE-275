# Project 3: Graph Search!

## Overview:
You will implement Dijkstra's shortest path algorithm to search a randomly generated graph. 
Students are encouraged to utilize outside libraries to complete the task, e.g., the Boost Graph Library or LEMON. 
Graphs will be constructed from input either from `stdin` or from a file. 

## Specifics:
Project 3 will be tested as a black-box executable, i.e., the tester only cares about input and output to/from your executable. 
The tester will consider all `.cpp` files utilized in the 'src' directory to compile an executable `graphsearch`. 
The executable **shall** callable as such:

```bash
./graphsearch inputFile startNode endNode
```

or as 

```bash
./graphsearch startNode endNode
```

Note the first invocation will read the graph file from the given filename whereas the second will receive input from `stdin`. 


Graph files will be generated at random and will have the following format:

```
src dst weight
```

which denotes an edge from `src` to `dst` with weight of `weight`. 

Nodes will be identified by a string (e.g., `A`, `BB`, `ZZZZZ`) and weights will be nonzero positive integers. 
The graph structure must allow for multiple edges between nodes. 

A full example is shown below: 

```
A G 622248
A G 872009
A G 341222
A H 40298
B A 676352
B G 510175
B G 35479
B G 665581
C F 737414
C F 608912
C F 350101
C J 62951
D G 695028
D G 82954
D I 413678
D F 974334
E G 400473
E J 994358
E A 917377
E H 677216
F B 703432
F J 518717
F G 303687
F G 279940
G D 209520
G B 89436
G J 227978
G F 984018
H G 722159
H G 27516
H G 417079
H F 35386
I J 290148
I H 758062
I B 847293
I B 665569
J F 547955
J F 833890
J A 784643
J G 637685
```

Note that you should create your own input files for local testing and ensure you can produce the proper path before submitting to the tester. 


Upon finding the shortest path from `S` to `G` your program **shall** print the following format

```
W: S N1 N2 N3 ... G
```

where `W` is the total cost of the path and `Ni Nj` denotes an edge from `Ni` to `Nj`

e.g., 

```
567953: A G D
```

shows a path of cost 567953 from node `A` to `D`.

If no path is available your program **shall** print 

```
No path exists from S to G
```

where `S` and `G` are the start and goal node identifiers. 


## Libraries:
My solution utilized the LEMON library found [here](https://lemon.cs.elte.hu/trac/lemon). A useful tutorial can be found [here](https://blog.sommer-forst.de/2016/09/28/solving-the-shortest-path-problem-2-lemon-graph-library/) and a useful mailing list posting is found [here](http://lemon.cs.elte.hu/pipermail/lemon-user/2011-January/000324.html). This library (and the Boost graph library) are preinstalled in the tester. If you wish to utilize another please reach out ASAP so it may be installed in the tester. 

## Testing:
Testing is done via randomly generated graphs. There are 'small', 'medium', and 'large' tests. 
Note that a simple depth-first or breadth-first search will not conclude in the allotted time for each test. 
Each test is worth 1/3 of the overall grade and, as usual, scores are output in the results INI file. 

## Extra Credit:
Utilize both an outside library and a purpose-built executable to pass tests for 50% extra credit. Submit, via email to the instructor, a less than 2 page PDF document detailing your design choices for the purpose-built graph class and compare/contrast to the chosen library. Include the commit hash for both passing tests in the PDF submission. 
