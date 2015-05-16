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

  val nodeIndex = Map[Int, Node]()
  val edgeIndex = Map[(Node, Node), Edge]()
  val fanOutIndex = Map[Node, Set[Node]]()
  val fanInIndex = Map[Node, Set[Node]]()

  def addNode(node: Node): Node = {
    require(!nodeIndex.contains(node.id), node.id + " in " + nodeIndex) // necessary?
    nodeIndex(node.id) = node
    node
  }

  def addEdge(start: Node, end: Node): Edge = {
    if (!nodeIndex.contains(start.id)) {
      addNode(start)
    }

    if (!nodeIndex.contains(end.id)) {
      addNode(end)
    }

    if (fanInIndex.contains(end)) {
      fanInIndex(end) += start
    }
    else {
      var idList = Set[Node]()
      idList += start
      fanInIndex.put(end, idList)
    }
    if (fanOutIndex.contains(start)) {
      fanOutIndex(start) += end
    } else {
      var idList = Set[Node]()
      idList += end
      fanOutIndex.put(start, idList)
    }
    val edge = new Edge(start, end)
    edgeIndex.put((start, end), edge)
    edge
  }
}