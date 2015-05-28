package algorithm.graph

import reference.BoundedPriorityQueue

import scala.annotation.tailrec
import scala.collection.mutable
import scala.io.Source

/**
 *
 * @param graph the changeable weighted directed graph
 */
class TopKShortestPaths[T](graph: ChangableWeightedDirectedGraph[T]) {

  type Node = INode[T]
  type Path = IPath[T]

  private var pathCandidates = mutable.PriorityQueue[Path]()
  private val pathDerivationNodeIndex = mutable.Map[Path, Node]()
  private val paths = mutable.ListBuffer[Path]()

  def findPaths(start: T, end: T, k: Int): List[Path] = {

    require(k > 0, "The number of paths should be positive")
    require(start != end, "the path is loopless, so the ends of paths should be different")

    // all results would be put in a priority queue with fixed length
    pathCandidates = new mutable.PriorityQueue[Path] with BoundedPriorityQueue[Path] {
      override val maxSize = k
    }

    //
    pathDerivationNodeIndex.clear()

    //
    searchAll(graph.node(start), graph.node(end), k)
  }

  @tailrec
  private def searchAll(start: Node, end: Node, k: Int): List[Path] = {
    if (paths.isEmpty && pathCandidates.isEmpty) {
      // initialization by getting the shortest path
      new ShortestPath(graph).getShortestPath(start, end) match {
        case None => return List.empty
        case Some(path) =>
          pathCandidates += path
          pathDerivationNodeIndex.put(path, start)
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
      val nextSubPathNodeList: List[Node] = nextPath.nodeList.dropRight(nextPath.nodeList.size - nextDerivatedNodeSeq - 1)

      paths.filter(path =>
          path.nodeList.contains(nextDerivatedNode) &&
          path.nodeList.dropRight(path.nodeList.size - path.nodeList.indexOf(nextDerivatedNode) - 1) == nextSubPathNodeList).
        foreach(path =>
          graph.remove((nextDerivatedNode, path.nodeList(path.nodeList.indexOf(nextDerivatedNode) + 1)))
      )

      for (nodeSeq <- 0 until nextPath.nodeList.length - 1) {
        graph.remove(nextPath.nodeList(nodeSeq))
        graph.remove((nextPath.nodeList(nodeSeq), nextPath.nodeList(nodeSeq+1)))
      }

      //2. recover from the very ending and calculate the few more candidates
      //2.1 calculate the shortest tree rooted at target vertex in the graph
      val findShortestPath = new ShortestPath(graph)
      findShortestPath.findShortestPathFlowerRootAt(end)

      //2.2 recover the deleted vertices and update the cost and identify the new candidate results
      for (nodeSeq <- nextPath.nodeList.size-2 to nextDerivatedNodeSeq by -1 if nodeSeq>=0) {
        val recoveredNode = nextPath.nodeList(nodeSeq)
        graph.recover(recoveredNode)

        findShortestPath.getSubShortestPath(recoveredNode) match {
          case None =>
          case Some(subPath) =>
            findShortestPath.correctCostBackward(recoveredNode)
            val prefix = nextPath.nodeList.dropRight(nextPath.nodeList.size-nodeSeq-1)
            var cost = 0.0
            for (i <- 0 until prefix.size-1) {
              cost += graph.edgeOriginalWeight(prefix(i), prefix(1+i))
            }
            val newPath = new Path(prefix.dropRight(1) ::: subPath.nodeList)
            newPath.setWeight(cost + subPath.getWeight)

            if (!pathDerivationNodeIndex.contains(newPath)) {
              pathDerivationNodeIndex.put(newPath, recoveredNode)
              pathCandidates += newPath
            }
        }

        //2.3 recover edges
        val nextNode = nextPath.nodeList(nodeSeq+1)
        graph.recover((recoveredNode, nextNode))

        //2.4 update cost if necessary
        val newCost = graph.edgeWeight(recoveredNode, nextNode) + findShortestPath.startVertexDistanceIndex.getOrElse(nextNode, Double.MaxValue)
        if (findShortestPath.startVertexDistanceIndex.getOrElse(recoveredNode, Double.MaxValue) > newCost && newCost < Double.MaxValue) {
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

  def importGraph(fileName: String): ChangableWeightedDirectedGraph[Int] = {
    val graph = new ChangableWeightedDirectedGraph[Int]()
    val pattern = "([0-9]+) ([0-9]+) ([0-9\\.]+)".r
    val pattern2 = "([0-9]+)".r
    for(line <- Source.fromFile(fileName).getLines().filterNot(_.trim.isEmpty)) {
      line match {
        case pattern(start, end, weight) => graph.addEdge(new INode(start.toInt), new INode(end.toInt), weight.toDouble)
        case pattern2(number) =>
        case _ =>
      }
    }
    graph
  }

  def find(graph: ChangableWeightedDirectedGraph[Int], start: Int, end: Int, k: Int): List[IPath[Int]] = {
    val finder = new TopKShortestPaths[Int](graph)
    finder.findPaths(start, end, k)
  }

}