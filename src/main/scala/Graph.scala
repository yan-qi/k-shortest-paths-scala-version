package algorithm.graph

import scala.collection.mutable._

trait Weight {
  var weight: Double = 0
  def getWeight = weight
  def setWeight(weight: Double): Unit = {
    this.weight = weight
  }
}

class Node(val id: Int) extends Weight with Ordered[Node] {

  override def toString:String = id.toString //+ "[" + weight + "]"

  override def compare(that: Node): Int =
    if (this.getWeight - that.getWeight < 0)
      1
    else if (this.getWeight - that.getWeight > 0)
      -1
    else
      0
}

class Edge(start: Node, end: Node) extends Weight

class Path(val nodeList: List[Node]) extends Weight with Ordered[Path] {
  override def compare(that: Path): Int =
    if (this.getWeight - that.getWeight < 0)
      1
    else if (this.getWeight - that.getWeight > 0)
      -1
    else
      0
  override def toString = nodeList.toString() + "[" + this.getWeight + "]"
}

class WeightedDirectedGraph {

  private val nodeIndexMap = Map[Int, Node]()
  private val edgeIndexMap = Map[(Node, Node), Edge]()
  private val fanOutIndexMap = Map[Node, Set[Node]]()
  private val fanInIndexMap = Map[Node, Set[Node]]()

  def fanOut(node: Node) = fanOutIndexMap.get(node).getOrElse(Set[Node]())
  def fanIn(node: Node) = fanInIndexMap.get(node).getOrElse(Set[Node]())
  def edge(start: Node, end: Node) = edgeIndexMap.get((start, end)

  def addNode(node: Node): Node = {
    require(!nodeIndexMap.contains(node.id), node.id + " in " + nodeIndexMap) // necessary?
    nodeIndexMap(node.id) = node
    node
  }

  def addEdge(start: Node, end: Node): Edge = {
    if (!nodeIndexMap.contains(start.id)) {
      addNode(start)
    }

    if (!nodeIndexMap.contains(end.id)) {
      addNode(end)
    }

    if (fanInIndexMap.contains(end)) {
      fanInIndexMap(end) += start
    }
    else {
      var idList = Set[Node]()
      idList += start
      fanInIndexMap.put(end, idList)
    }
    if (fanOutIndexMap.contains(start)) {
      fanOutIndexMap(start) += end
    } else {
      var idList = Set[Node]()
      idList += end
      fanOutIndexMap.put(start, idList)
    }
    val edge = new Edge(start, end)
    edgeIndexMap.put((start, end), edge)
    edge
  }
}

class ChangableWeightedDirectedGraph(graph: WeightedDirectedGraph) extends  WeightedDirectedGraph {
  private val removedNodeSet = Set[Node]()
  private val removedEdgeSet = Set[(Node, Node)]()

  @override def fanIn(node: Node) = super.fanIn(node).get.diff(removedNodeSet)
}