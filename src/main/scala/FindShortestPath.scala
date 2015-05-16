package algorithm.graph

import scala.collection.mutable._

/**
 * An implementation of Dijkstra Shortest Path Algorithm
 * However it is changed to support an efficient implementation of
 * the top-k shortest paths algorithm
 *
 * @param graph
 */
class FindShortestPath(graph: WeightedDirectedGraph) {

  val determinedVertexSet = Set[Node]()
  val vertexCandidateQueue = PriorityQueue[Node]()
  val startVertexDistanceIndex = Map[Node,Double]()
  val predecessorIndex = Map[Node,Node]()

  def clear(): Unit = {
    determinedVertexSet.clear
    vertexCandidateQueue.clear
    startVertexDistanceIndex.clear
    predecessorIndex.clear
  }

  def getShortestPath(source: Node, sink: Node): Option[Path] = {
    determineShortestPaths(source, sink, false)

    if (startVertexDistanceIndex.contains(sink)) {
      val list = ListBuffer

    } else {
      return None
    }
//    determineShortestPaths(sourceVertex, sinkVertex, true);
//    //
//    List<BaseVertex> vertexList = new Vector<BaseVertex>();
//    double weight = startVertexDistanceIndex.containsKey(sinkVertex) ?
//      startVertexDistanceIndex.get(sinkVertex) : Graph.DISCONNECTED;
//    if (weight != Graph.DISCONNECTED) {
//      BaseVertex curVertex = sinkVertex;
//      do {
//        vertexList.add(curVertex);
//        curVertex = predecessorIndex.get(curVertex);
//      } while (curVertex != null && curVertex != sourceVertex);
//      vertexList.add(sourceVertex);
//      Collections.reverse(vertexList);
//    }
//    return new Path(vertexList, weight);
  }

  private def updateVertex (node: Node, isOpposite: Boolean): Unit = {
    val neighborSet = if (isOpposite) graph.fanInIndex.get(node) else graph.fanOutIndex.get(node)

    neighborSet.get.filter(determinedVertexSet.contains(_)).foreach(next => {

      val edgeWeight = if (isOpposite) graph.edgeIndex.get((next, node)).get.getWeight else
        graph.edgeIndex.get((node, next)).get.getWeight
      val curDistance = if (startVertexDistanceIndex.contains(node)) startVertexDistanceIndex.get(node).get else Double.MaxValue - edgeWeight
      val distance = curDistance + edgeWeight
      if (!startVertexDistanceIndex.contains(next) ||
        startVertexDistanceIndex.get(next).get > distance) {
        startVertexDistanceIndex.put(next, distance)
        predecessorIndex.put(next, node)
        next.setWeight(distance)
        vertexCandidateQueue += next
      }
    })
  }

  private def determineShortestPaths (s: Node, e: Node, isOpposite: Boolean): Unit = {
    clear
    val end = if (isOpposite) s else e
    val start = if (isOpposite) e else s
    startVertexDistanceIndex.put(start, 0d)
    start.setWeight(0d)
    var curCandidate = start
    vertexCandidateQueue += start
    do {
      curCandidate = vertexCandidateQueue.dequeue()
      if (curCandidate != end) {
        determinedVertexSet += curCandidate
        updateVertex(curCandidate, isOpposite)
      }
    } while (curCandidate != end && !vertexCandidateQueue.isEmpty)
  }
}

//class Dijkstra1[G <: WeightedDirectedGraph](graph: G) {
//  type Node = G#Node
//  type Edge = G#Edge
//  /**
//   * StopCondition provides a way to terminate the algorithm at a certain
//   * point, e.g.: When target becomes settled.
//   */
//  type StopCondition = (Set[Node], Map[Node, Int], Map[Node, Node])
//  	=> Boolean
//
//  /**
//   * By default the Dijkstra algorithm processes all nodes reachable from
//   * <code>start</code> given to <code>compute()</codke>.
//   */
//  val defaultStopCondition: StopCondition = (_, _, _) => true
//  var stopCondition = defaultStopCondition
//
////  def compute(start: Node, target: Node):
////	  (Map[Node, Int], Map[Node, Node]) = {
////    var queue: Set[Node] = new HashSet()
////    var settled: Set[Node] = new HashSet()
////    var distance: Map[Node, Int] = new HashMap()
////    var path: Map[Node, Node] = new HashMap()
////    queue += start
////    distance(start) = 0
////
////    while(!queue.isEmpty && stopCondition(settled, distance, path)) {
////      val u = extractMinimum(queue, distance)
////      settled += u
////      relaxNeighbors(u, queue, settled, distance, path)
////    }
////
////    return (distance, path)
////  }
//
//  /**
//   * Finds element of <code>Q</code> with minimum value in D, removes it
//   * from Q and returns it.
//   */
//  protected def extractMinimum[T](Q: Set[T], D: Map[T, Int]): T = {
//    var u = Q.head
//    Q.foreach((node) =>  if(D(u) > D(node)) u = node)
//    Q -= u
//    return u;
//  }
//
//  /**
//   * For all nodes <code>v</code> not in <code>S</code>, neighbors of
//   * <code>u</code>}: Updates shortest distances and paths, if shorter than
//   * the previous value.
//   */
////  protected def relaxNeighbors(u: Node, Q: Set[Node], S: Set[Node],
////      D: Map[Node, Int], P: Map[Node, Node]): Unit = {
////      for(edge <- graph.edges if(edge.a == u || edge.b == u) ) {
////        var v = if(edge.a == u) edge.b else edge.a
////        if(!S.contains(v)) {
////          if(!D.contains(v) || D(v) > D(u) + edge.getWeight) {
////            D(v) = D(u) + edge.getWeight
////            P(v) = u
////            Q += v
////          }
////        }
////      }
////
////  }
//}
//
//object Dijkstra1 {
//  /**
//   * Test case:
//   *    ____________(5)
//   *   /   9           \
//   * (6)_____           \6
//   *  |      \2          \
//   *  |       \          |
//   *  |     ---(3)-----(4)
//   *  |14  /    |        |
//   *  |   /     |        |
//   *  |  / 9    |10      |
//   *  | /       |        |
//   * (1)-------(2)-------'
//   *      7         15
//   *
//   */
//  def main(args: Array[String]): Unit = {
//    // 1. Construct graph
//    val g = new WeightedDirectedGraph
//    val n1 = g.addNode
//    val n2 = g.addNode
//    val n3 = g.addNode
//    val n4 = g.addNode
//    val n5 = g.addNode
//    val n6 = g.addNode
//    g.addEdge(n1, n2).setWeight(7)
//    g.addEdge(n1, n3).setWeight(9)
//    g.addEdge(n1, n6).setWeight(14)
//    g.addEdge(n2, n3).setWeight(10)
//    g.addEdge(n2, n4).setWeight(15)
//    g.addEdge(n3, n4).setWeight(11)
//    g.addEdge(n3, n6).setWeight(2)
//    g.addEdge(n4, n5).setWeight(6)
//    g.addEdge(n5, n6).setWeight(9)
//
//    // 2. Set start, target, stop-condition and compute the path
//    val (start, target) = (n1, n5)
////    val dijkstra = new Dijkstra1[g.type](g)
////    // 2.1. Halt when target becomes settled
////    dijkstra.stopCondition = (S, D, P) => !S.contains(target)
////    val (distance, path) = dijkstra.compute(start, target)
////
////    // 3. Display the result
////    printResult[g.type](start, target, distance, path)
//  }
//
//  def printResult[G <: Graph](start: G#Node, target: G#Node,
//      distance: Map[G#Node, Int], path: Map[G#Node, G#Node]): Unit = {
//    var shortest = List(target)
//    while(shortest.head != start) {
//      shortest ::= path(shortest.head)
//    }
//    println("Shortest-path cost: " + distance(target))
//    print("Shortest-path: " + shortest.mkString(" -> "))
//  }
//}