package algorithm.graph

import scala.annotation.tailrec
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


  @tailrec
  private def getReversePath(sink: Node, list: ListBuffer[Node]): ListBuffer[Node] = {
    list.append(sink)
    predecessorIndex.get(sink) match {
      case Some(pre) => getReversePath(pre, list)
      case None => list
    }
  }

  @tailrec
  private def updateVertex (end: Node, isOpposite: Boolean): Unit = {
    if (vertexCandidateQueue.isEmpty) return
    val node = vertexCandidateQueue.dequeue()
    if (node != end) {
      determinedVertexSet += node
      val neighborSet = if (isOpposite) graph.fanIn(node) else graph.fanOut(node)

      neighborSet.filterNot(determinedVertexSet.contains(_)).foreach(next => {

        val edgeWeight = if (isOpposite) graph.edgeWeight(next, node) else graph.edgeWeight(node, next)
        val curDistance = startVertexDistanceIndex.get(node).getOrElse(Double.MaxValue - edgeWeight)
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
   * Construct a flower rooted at "root" with
   * the shortest paths from the other vertices.
   *
   * @param root
   */
  def getShortestPathFlowerRootAt(root: Node) {
    determineShortestPaths(null, root, true)
  }

  /**
   * Correct costs of successors of the input vertex using backward star form.
   * (FLOWER)
   * @param node
   */
  def correctCostBackward(node: Node): Unit = {
    graph.fanIn(node).foreach(pre => {
      val newWeight = graph.edgeWeight(pre, node) + startVertexDistanceIndex.get(node).get
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
    graph.fanOut(node).filter(startVertexDistanceIndex.contains(_)).foreach(next => {
      val newWeight = graph.edgeWeight(node, next) + startVertexDistanceIndex.get(next).get
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
        val path = new Path(getReversePath(source, ListBuffer()).toList)
        path.setWeight(cost)
        Option(path)
      }
    }
  }

}
