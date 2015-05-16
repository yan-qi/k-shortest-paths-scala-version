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
      val path = new Path(getPath(source, sink).toList)
      path.setWeight(startVertexDistanceIndex.get(sink).get)
      Option(path)
    } else {
      return None
    }
  }

  private def getPath(so: Node, si: Node): ListBuffer[Node] = {
    if (so == si) ListBuffer[Node](so) else {
      predecessorIndex.get(si) match {
        case Some(pre) => val rel = getPath(so, pre); rel.append(si); rel
        case None => throw new RuntimeException // should not happen!
      }
    }
  }

  private def updateVertex (node: Node, isOpposite: Boolean): Unit = {
    val neighborSet = if (isOpposite) graph.fanInIndex.get(node) else graph.fanOutIndex.get(node)

    neighborSet.get.filter(!determinedVertexSet.contains(_)).foreach(next => {

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
