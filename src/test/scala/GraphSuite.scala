import org.scalatest.FunSuite

import scala.collection.mutable

import algorithm.graph._

/**
 * Created by yqi on 5/6/2015.
 */
class GraphSuite extends FunSuite {
  test("Validate the usage of set in Graph") {
    val vertexSet = Set(1, 2, 3)
    assert(vertexSet(10) == false)

    val rand = scala.util.Random
    val g = new WeightedDirectedGraph
    val n1 = g.addNode(new Node(1))
    n1.setWeight(1.1)
    val n2 = g.addNode(new Node(2))
    n2.setWeight(0.2)
    val n3 = g.addNode(new Node(3))
    n3.setWeight(0.03)
    g.addEdge(n1, n2, 7)

    val pq = new mutable.PriorityQueue[Node]()
    pq += n1
    pq += n2
    pq += n3
    println(pq)
    println(pq.dequeue())
    println(pq)


    val nlist1 = List(n1, n2)
    val nlist2 = List(n2, n3)
    val p1 = new Path(List(n1,n2))
    p1.setWeight(0.3)
    val p2 = new Path(List(n1,n3,n2))
    p2.setWeight(0.53)
    val ppq = new mutable.PriorityQueue[Path]()
    ppq += p2
    ppq += p1
    println(ppq)

    val shortestPath = new ShortestPath(g)
    println(shortestPath.getShortestPath(n1, n2))
  }

  test("Find the top k shortest paths in a graph") {
    val graph = TopKShortestPaths.importGraph("data/test_6_2")
    TopKShortestPaths.find(graph, graph.node(4), graph.node(5), 100).foreach(println)
  }
}
