## Introduction ##

This project aims to provide an implementation to the top-k shortest paths in Scala.
 
Yen’s algorithm is one of derivation algorithms for ranking the K shortest paths between a pair of nodes `[`1`]`. It always searches the shortest paths in a “pseudo”-tree containing K shortest loopless paths. The very shortest one is obtained in the first place, and the second shortest path is always explored on the basis of the shortest paths that are shorter. In our paper, we exploit the implementation of Yen’s algorithm in `[`1`]`. Compared with the straightforward implementation of Yen’s algorithm, the one present in `[`1`]` is proved to have a better performance in computational experiments, although the complexity of them are the same, O(Kn(m+nlogn)) in the worst case analysis.

## Implementation ##
  * Scala language is used to implement Yen's algorithm.
  
## Reference ##
  1. M. Pascoal and E. Martins. A new implementation of Yen’s ranking loopless paths algorithm. 4OR – Quarterly Journal of the Belgian, French and Italian Operations Research Societies, 2003.
  1. http://www.mat.uc.pt/~eqvm/OPP/KSPP/KSPP.html.

## Update ##
  * A checking is added in the C++ implementation to make sure the number of vertices in the input file is correct.
  * The C++ version of the algorithm is ready for downloading. This implementation follows the similar design as its Java counterpart.
  * A bug is fixed in the Java implementation. The algorithm presented in Reference `[`1`]` is not always right. Specifically, the test case with the graph (see 'test\_6\_1' in the source package) can not return all results if the algorithm is applied.
  * A fix on the comparator associated with Class QYDirectedPath is provided for the CPP implementation. Thanks a lot to timothyahahn.
  * The implementation of top-k shortest path algorithm in **C#** by Vinh Bui (vinhqb@gmail.com) is added. Note that I won't test this code completely.