package algorithm.graph

import scala.collection.mutable._

/**
 * An implementation of Dijkstra Shortest Path Algorithm
 * However it is changed to support an efficient implementation of
 * the top-k shortest paths algorithm
 *
 * @param graph
 */
class ShortestPath(graph: WeightedDirectedGraph) {

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

  private def getReversePath(sink: Node): ListBuffer[Node] = {
    if (predecessorIndex.isEmpty) ListBuffer[Node](sink) else {
      predecessorIndex.get(sink) match {
        case Some(pre) => val rel = getReversePath(pre); rel.prepend(pre); rel
        case None => throw new RuntimeException // impossible
      }
    }
  }

  private def updateVertex (end: Node, isOpposite: Boolean): Unit = {
    if (vertexCandidateQueue.isEmpty) return
    val node = vertexCandidateQueue.dequeue()
    if (node != end) {
      determinedVertexSet += node
      val neighborSet = if (isOpposite) graph.fanIn(node) else graph.fanOut(node)

      neighborSet.filter(!determinedVertexSet.contains(_)).foreach(next => {

        val edgeWeight = if (isOpposite) graph.edge(next, node).get.getWeight
        else
          graph.edge(node, next).get.getWeight
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
      updateVertex(end, isOpposite)
    }
  }

  private def determineShortestPaths (s: Node, e: Node, isOpposite: Boolean): Unit = {
    clear
    val end = if (isOpposite) s else e
    val start = if (isOpposite) e else s
    startVertexDistanceIndex.put(start, 0d)
    start.setWeight(0d)
    vertexCandidateQueue += start
    updateVertex(end, isOpposite)
  }

  /**
   * Correct costs of successors of the input vertex using backward star form.
   * (FLOWER)
   * @param node
   */
  def correctCostBackward(node: Node): Unit = {
    graph.fanIn(node).foreach(pre => {
      val newWeight = graph.edge(pre, node).get.getWeight + startVertexDistanceIndex.get(node).get
      val oldWeight = startVertexDistanceIndex.get(pre).getOrElse(Double.MaxValue)
      if (oldWeight > newWeight) {
        startVertexDistanceIndex.put(pre, newWeight)
        predecessorIndex.put(pre, node)
        correctCostBackward(pre)
      }
    })
  }

  def correctCostForward(node: Node) = {
    var cost = Double.MaxValue
    graph.fanOut(node).get.filter(startVertexDistanceIndex.contains(_)).foreach(next => {
      val newWeight = graph.edge(node, next).get.getWeight + startVertexDistanceIndex.get(next).get
      if (startVertexDistanceIndex.get(node).getOrElse(Double.MaxValue) >  newWeight) {
        startVertexDistanceIndex.put(node, newWeight)
        predecessorIndex.put(node, next)
        cost = newWeight
      }
    })
    cost
  }

  def getSubShortestPath(source: Node): Option[Path] = {
    correctCostForward(source) match {
      case Double.MaxValue => None
      case cost => {
        val path = new Path(getReversePath(source).toList)
        path.setWeight(cost)
        Option(path)
      }
    }
  }

}