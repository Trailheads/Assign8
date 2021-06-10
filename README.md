# Assign8
A weighted multi-graph data structure without loops.
The vertices are local bars around downtown Eugene, OR, whereas the edges represents the distances between two bars in miles. 

Design: The graph is accomplished using an adjacency matrix. 
        The index for rows and columns represent vertices, and their combine positions holds the distances between the two.
        The minimum spanning tree function is accomplished using Dijkstra's algorithm where the vertex and its shortest path
        is saved into a map. This map is used to determine the shortest path between any two vertices.
        
Above the required functions, I analyzed the Big O runtimes. 
Overall, the graph's Big O is n^2 as a result of the minimum spanning tree function.

Assignment 4 was resubmitted with the files uploaded to GitHub.
