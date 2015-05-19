package algorithm.graph

import reference.BoundedPriorityQueue

import scala.collection.mutable
import scala.io.Source

/**
 *
 * @param graph
 */
class TopKShortestPaths(graph: ChangableWeightedDirectedGraph) {

  private var pathCandidates = mutable.PriorityQueue[Path]()
  private val pathDerivationNodeIndex = mutable.Map[Path, Node]()
  private val paths = mutable.ListBuffer[Path]()

  def findPaths(start: Node, end: Node, k: Int): List[Path] = {

    require(k > 0, "The number of paths should be positive")
    require(start != end, "the path is loopless, so the ends of paths should be different")

    // all results would be put in a priority queue with fixed length
    pathCandidates = new mutable.PriorityQueue[Path] with BoundedPriorityQueue[Path] {
      override val maxSize = k
    }

    //
    pathDerivationNodeIndex.clear()

    //
    searchAll(start, end, k)
  }

  private def searchAll(start: Node, end: Node, k: Int): List[Path] = {
    if (paths.isEmpty && pathCandidates.isEmpty) {
      // initialization by getting the shortest path
      new ShortestPath(graph).getShortestPath(start, end) match {
        case None => return List.empty
        case Some(path) => {
          pathCandidates += path
          pathDerivationNodeIndex.put(path, start)
        }
      }
      searchAll(start, end, k)
    } else if (paths.size == k || pathCandidates.isEmpty) {
      paths.toList
    } else {
      // big work below !!!

      //1. remove the edges and nodes from the graph
      val nextPath = pathCandidates.dequeue()
      val nextDerivatedNode = pathDerivationNodeIndex.get(nextPath).get
      val nextDerivatedNodeSeq = nextPath.nodeList.indexOf(nextDerivatedNode)
      val nextSubPathNodeList: List[Node] = nextPath.nodeList.dropRight(nextPath.nodeList.size - nextDerivatedNodeSeq)

      paths.filter(path =>
          path.nodeList.contains(nextDerivatedNode) &&
          path.nodeList.dropRight(path.nodeList.size - path.nodeList.indexOf(nextDerivatedNode)) == nextSubPathNodeList).
        foreach(path =>
          graph.remove((nextDerivatedNode, path.nodeList(path.nodeList.indexOf(nextDerivatedNode) + 1)))
      )

      for (nodeSeq <- 0 until nextSubPathNodeList.size-1) {
        graph.remove(nextSubPathNodeList(nodeSeq))
        graph.remove((nextSubPathNodeList(nodeSeq), nextSubPathNodeList(nodeSeq+1)))
      }

      //2. recover from the very ending and calculate the few more candidates
      //2.1 calculate the shortest tree rooted at target vertex in the graph
      val findShortestPath = new ShortestPath(graph)
      findShortestPath.getShortestPathFlowerRootAt(end)

      //2.2 recover the deleted vertices and update the cost and identify the new candidate results
      for (nodeSeq <- nextPath.nodeList.size-2 to nextDerivatedNodeSeq by -1) {
        val recoveredNode = nextPath.nodeList(nodeSeq)
        graph.recover(recoveredNode)

        findShortestPath.getSubShortestPath(recoveredNode) match {
          case None =>
          case Some(subPath) => {
            findShortestPath.correctCostBackward(recoveredNode)
            val prefix = nextPath.nodeList.dropRight(nextPath.nodeList.size-nodeSeq)
            var cost = 0.0
            for (i <- 0 to prefix.size) {
              cost += graph.edge(prefix(i), prefix(1+i)).get.getWeight
            }
            val newPath = new Path(prefix ::: subPath.nodeList)
            newPath.setWeight(cost + subPath.getWeight)

            if (!pathDerivationNodeIndex.contains(newPath)) {
              pathDerivationNodeIndex.put(newPath, recoveredNode)
              pathCandidates += newPath
            }
          }
        }

        //2.3 recover edges
        val nextNode = nextPath.nodeList(nodeSeq+1)
        graph.recover((recoveredNode, nextNode))

        //2.4 update cost if necessary
        val newCost = graph.edge(recoveredNode, nextNode).get.getWeight + findShortestPath.startVertexDistanceIndex.get(nextNode).getOrElse(Double.MaxValue)
        if (findShortestPath.startVertexDistanceIndex.get(recoveredNode).getOrElse(Double.MaxValue) > newCost) {
          findShortestPath.startVertexDistanceIndex.put(recoveredNode, newCost)
          findShortestPath.predecessorIndex.put(recoveredNode, nextNode)
          findShortestPath.correctCostBackward(recoveredNode)
        }
      }

      //3. recover all and update the result list
      paths += nextPath
      graph.recover()

      //4. try it again
      searchAll(start, end, k)
    }
  }
}


object TopKShortestPaths {

  def importGraph(fileName: String): ChangableWeightedDirectedGraph = {
    val graph = new ChangableWeightedDirectedGraph()
    val pattern = "([0-9]+) ([0-9]+) ([0-9\\.]+)".r
    val pattern2 = "([0-9]+)".r
    for(line <- Source.fromFile(fileName).getLines().filterNot(_.trim.isEmpty)) {
      line match {
        case pattern(start, end, weight) => graph.addEdge(new Node(start.toInt), new Node(end.toInt)).setWeight(weight.toDouble)
        case pattern2(number) =>
        case _ =>
      }
    }
    graph
  }

  def find(graph: ChangableWeightedDirectedGraph, start: Node, end: Node, k: Int): Unit = {
    val finder = new TopKShortestPaths(graph);
    val results = finder.findPaths(start, end, k)
    results.foreach(println)
  }

}