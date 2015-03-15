# How to use version 2.1 #

## Introduction ##

In the latest version of Java implementation, we allow to obtain shortest paths in two ways.


### Batch Computation ###

In the batch mode, the user can set the number of shortest paths that he/she wants, and all results can be obtained at a time.

For example:
```
Graph graph = new VariableGraph("data/test_7");
YenTopKShortestPathsAlg yenAlg = new YenTopKShortestPathsAlg(graph);
List<Path> shortest_paths_list = yenAlg.get_shortest_paths(
		graph.get_vertex(0), graph.get_vertex(2), 100);
```
### Obtain by Iteration ###

In this mode, the user can access paths between any pair of nodes in the graph, in increasing order.

```
Graph graph = new VariableGraph("data/test_7");
YenTopKShortestPathsAlg yenAlg = new YenTopKShortestPathsAlg(
		graph, graph.get_vertex(0), graph.get_vertex(2));
while(yenAlg.has_next())
{
   Path cur_result = yenAlg.next();
   ...
}
```