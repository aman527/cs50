# cs50
My code from working through [Harvard's online CS50x course](https://cs50.harvard.edu/x/2020/).

Before this course, I had only really programmed in Python and JavaScript before, so this is my first introduction to lower-level programming in C.

My best work so far is the [tideman](https://github.com/aman527/cs50/blob/master/pset3/tideman.c) election program in problem set 3. It required that I learn and understand two concepts: recursion and directed graphs. One of the subcomponents of the tideman problem was to implement a sorting algorithm, so I formulated a c implementation of merge sort. It may not be the most efficient or idiomatic C, but it works! Secondly, I had to devise an algorithm that would check if adding a given edge to a directed graph would create a cycle -- for that, I implemented what I'll call a recursive node walker. My idea was that a directed edge from node 1 to node 2 will create a cycle if a path already exists between leading from node 2 to node 1, so my algorithm recursively walks along the graph to determine if any such path exists. Again, this may not be the best solution, but I think it works!
