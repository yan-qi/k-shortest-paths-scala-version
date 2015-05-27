package algorithm.graph

import scala.collection.mutable._

/**
 * Trait for the weight of graph elements, such as node, edge, path etc.
 */
trait Weight {
  var weight: Double = 0
  def getWeight = weight
  def setWeight(weight: Double): Unit = {
    this.weight = weight
  }
}

/**
 * The node in the graph which is identified with an integer
 * @param id
 */
class Node(val id: Int) extends Weight with Ordered[Node] {

  override def toString:String = id.toString

  override def compare(that: Node): Int =
    if (this.getWeight - that.getWeight < 0)
      1
    else if (this.getWeight - that.getWeight > 0)
      -1
    else
      0


  def canEqual(other: Any): Boolean = other.isInstanceOf[Node]

  override def equals(other: Any): Boolean = other match {
    case that: Node =>
      (that canEqual this) &&
        id == that.id
    case _ => false
  }

  override def hashCode(): Int = {
    val state = Seq(id)
    state.map(_.hashCode()).foldLeft(0)((a, b) => 31 * a + b)
  }
}

//class Edge(start: Node, end: Node) extends Weight

/**
 * A path has weight, composed of a list of nodes
 * @param nodeList
 */
class Path(val nodeList: List[Node]) extends Weight with Ordered[Path] {

  override def compare(that: Path): Int =
    if (this.getWeight - that.getWeight < 0)
      1
    else if (this.getWeight - that.getWeight > 0)
      -1
    else
      0

  override def toString = nodeList.toString() + "[" + this.getWeight + "]"

  def canEqual(other: Any): Boolean = other.isInstanceOf[Path]

  override def equals(other: Any): Boolean = other match {
    case that: Path =>
      (that canEqual this) &&
        nodeList == that.nodeList
    case _ => false
  }

  override def hashCode(): Int = {
    val state = Seq(nodeList)
    state.map(_.hashCode()).foldLeft(0)((a, b) => 31 * a + b)
  }
}


class WeightedDirectedGraph {

  private val nodeIndexMap = Map[Int, Node]()
  private val edgeWeightIndexMap = Map[(Node, Node), Double]()
  private val fanOutIndexMap = Map[Node, Set[Node]]()
  private val fanInIndexMap = Map[Node, Set[Node]]()

  def fanOut(node: Node) = fanOutIndexMap.get(node).getOrElse(Set.empty)
  def fanIn(node: Node) = fanInIndexMap.get(node).getOrElse(Set.empty)
  def edgeWeight(start: Node, end: Node) = edgeWeightIndexMap.get((start, end)).getOrElse(Double.MaxValue)
  def node(id: Int) = nodeIndexMap.get(id).get
  def edge = edgeWeightIndexMap.keySet

  def addNode(node: Node): Node = {
    require(!nodeIndexMap.contains(node.id), node.id + " in " + nodeIndexMap) // necessary?
    nodeIndexMap(node.id) = node
    node
  }

  def addEdge(start: Node, end: Node, weight: Double): Unit = {
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
    edgeWeightIndexMap.put((start, end), weight)
  }
}

class ChangableWeightedDirectedGraph extends  WeightedDirectedGraph {

  private val removedNodeSet = Set[Node]()
  private val removedEdgeSet = Set[(Node, Node)]()

  def remove(node: Node) = { removedNodeSet += node }
  def remove(edge: (Node,Node)) = { removedEdgeSet += edge }

  def recover(node: Node) = { removedNodeSet -= node }
  def recover(edge: (Node, Node)) = { removedEdgeSet -= edge }
  def recover() = { removedEdgeSet.clear(); removedNodeSet.clear() }

  override def fanIn(node: Node) = if (removedNodeSet.contains(node)) Set.empty else
    super.fanIn(node).--(removedNodeSet).filterNot(pre => removedEdgeSet.contains((pre, node)))

  override def fanOut(node: Node) = if (removedNodeSet.contains(node)) Set.empty else
    super.fanOut(node).--(removedNodeSet).filterNot(next => removedEdgeSet.contains(node, next))

  override def edgeWeight(start: Node, end: Node) = if (removedEdgeSet.contains((start, end))) Double.MaxValue else super.edgeWeight(start, end)

  override def edge = super.edge.--(removedEdgeSet)

  def edgeOriginalWeight(start: Node, end: Node) = super.edgeWeight(start, end)

}