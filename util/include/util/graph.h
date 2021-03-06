#ifndef CC_UTIL_GRAPH_H
#define CC_UTIL_GRAPH_H

#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <functional>

namespace cc 
{
namespace util 
{

class GraphPimpl;

/**
 * This class helps in creating a graph. The built graph can be written to the
 * output in several formats, like DOT or SVG. Since this implementation uses
 * GraphViz's representation, it is trivial to layout the graph with different
 * algorithms.
 */
class Graph
{
public:
  enum Format {DOT, SVG};

  struct Node     { std::string id; };
  struct Edge     { std::string id; };
  struct Subgraph { std::string id; };

  /**
   * By this constructor you can set the default properties of the graph. This
   * constructor only creates a root graph (not subgraph).
   * @param name_ Name of the graph.
   * @param directed_ This sets whether the graph is directed or not.
   * @param strict_ The graph can be strict, which means that there are no
   * parallel and loop edges.
   */
  Graph(
    const std::string name_ = "",
    bool directed_ = true,
    bool strict_ = false);

  ~Graph();

  /**
   * This static function converts a DOT formatted graph to SVG format.
   * @param graph_ Input graph in DOT format.
   * @return SVG format of input graph.
   */
  static std::string dotToSvg(const std::string& graph_);

  /**
   * This function returns whether the graph is directed.
   * @return True if the graph is directed; otherwise, false.
   */
  bool isDirected() const;

  /**
   * This function returns whether the graph is strict.
   * @return True if the graph is strict; otherwise, false.
   */
  bool isStrict() const;

  /**
   * This function returns whether the graph is a subgraph.
   * @return True if the graph is subgraph; otherwise, false.
   */
  bool isSubGraph() const;

  /**
   * This function returns the number of nodes in the graph.
   */
  int nodeCount() const;

  /**
   * This function returns the number of edges in the graph.
   */
  int edgeCount() const;

  /**
   * This function adds a node to the graph.
   * @param subgraph_ Subgraph to which the node will be added. If a default
   * constructed graph is given (i.e. its ID is empty) then the node is added to
   * the root graph.
   * @return Node object.
   */
  Node addNode(const Subgraph& subgraph_ = Subgraph());

  /**
   * This function adds an edge to the graph.
   * @param from_ Source node.
   * @param to_ Target node.
   * @return Edge object.
   */
  Edge addEdge(const Node& from_, const Node& to_);

  /**
   * This function adds a subgraph to the graph.
   * @param id_ ID of the subgraph. If empty, a unique id is generated by
   * default. If an ID is given which is already used, then the function returns
   * the old subgraph, and doesn't add a new one.
   */
  Subgraph addSubgraph(const std::string& id_);

  /**
   * This function returns true if the given node (its identifier) exists.
   */
  bool hasNode(const Node& node_) const;

  /**
   * This function returns true if the given edve exists.
   */
  bool hasEdge(const Node& from_, const Node& to_) const;

  /**
   * This function removes the given node from the graph.
   */
  void delNode(const Node& node_);

  /**
   * This function removes the given edve from the graph.
   */
  void delEdge(const Node& from_, const Node& to_);

  /**
   * This function sets the attributes of the graph. These attributes are listed
   * at this link: http://www.graphviz.org/content/attrs.
   */
  void setAttribute(const std::string& key_, const std::string& value_);

  /**
   * This function sets the attributes of a node. These attributes are listed at
   * this link: http://www.graphviz.org/content/attrs.
   * @param html_ If true then the value_ is interpreted as HTML.
   */
  void setAttribute(
    const Node& node_,
    const std::string& key_,
    const std::string& value_,
    bool html_ = false);

  /**
   * This function sets the attributes of an edge. These attributes are listed
   * at this link: http://www.graphviz.org/content/attrs.
   * @param html_ If true then the value_ is interpreted as HTML.
   */
  void setAttribute(
    const Edge& edge_,
    const std::string& key_,
    const std::string& value_,
    bool html_ = false);

  /**
   * This function sets the attributes of a subgraph. These attributes are
   * listed at this link: http://www.graphviz.org/content/attrs.
   * @param html_ If true then the value_ is interpreted as HTML.
   */
  void setAttribute(
    const Subgraph& graph_,
    const std::string& key_,
    const std::string& value_,
    bool html_ = false);

  /**
   * This function copies the attributes of a node. These attributes are
   * listed at this link: http://www.graphviz.org/content/attrs.
   */
  void setAttribute(const Node& targetNode_, const Node& sourceNode_);

  /**
   * This function copies the attributes of an edge. These attributes are
   * listed at this link: http://www.graphviz.org/content/attrs.
   */
  void setAttribute(const Edge& targetEdge_, const Edge& sourceEdge_);

  /**
   * This function retrieves an attribute of a node. These attributes are
   * listed at this link: http://www.graphviz.org/content/attrs.
   */
  std::string getAttribute(const Node& node_, const std::string& key_);

  /**
   * This function retrieves an attribute of an edge. These attributes are
   * listed at this link: http://www.graphviz.org/content/attrs.
   */
  std::string getAttribute(const Edge& edge_, const std::string& key_);

  /**
   * This function generates the string representation of the graph in the
   * given format.
   */
  std::string output(Format format_) const;

  /**
   * This function returns the child nodes of a given node.
   */
  std::vector<Node> getChildren(const Node& node) const;

  /**
   * This function returns the parent nodes of a given node.
   */
  std::vector<Node> getParents(const Node& node) const;

private:
  /**
   * Copy constructor of the graph. This contructor doesn't do anything. We use
   * it so that nobody can copy the graph because of its inner representation.
   */
  Graph(const Graph& other_);

  /**
   * Assignment operator of the graph. This operator doesn't do anything. We use
   * it so that nobody can copy the graph because of its inner representation.
   */
  Graph& operator=(const Graph& other_);

  struct NodeHash
  {
    std::size_t operator()(const Node& node) const
    {
      return std::hash<std::string>()(node.id);
    }
  };

  /**
   * This function is used to generate a unique ID for graph elements if needed.
   * The graph elements need a char* identifier.
   */
  std::string generateId();
  std::string currentId;

  GraphPimpl* _graphPimpl;

  bool _directed;
  bool _strict;
  bool _isSubgraph;
};

bool operator<(const Graph::Node& n1, const Graph::Node& n2);
bool operator<(const Graph::Edge& e1, const Graph::Edge& e2);
bool operator<(const Graph::Subgraph& s1, const Graph::Subgraph& s2);

bool operator==(const Graph::Node& n1, const Graph::Node& n2);
bool operator==(const Graph::Edge& e1, const Graph::Edge& e2);
bool operator==(const Graph::Subgraph& s1, const Graph::Subgraph& s2);

/**
 * This function builds a graph in the order of breadth-first search. If style
 * descriptor maps are given then the added nodes and edges are decorated.
 * @param graph_ The graph will be appended by the new nodes and edges.
 * @param startNode_ Breadth-first search starts from this node. This node is
 * not inserted into the returning set unless there is a loop in the graph which
 * contains this node.
 * @param relations_ This function describe the relation which determine the
 * child nodes of a given node.
 * @param nodeDecoration_ This parameter maps the style attributes for the newly
 * created nodes.
 * \see{Graph::setAttribute(
 *   const Graph::Node&,
 *   const std::string&,
 *   const std::string&)}.
 * @param edgeDecoration_ This parameter maps the style attributes for the newly
 * created edges.
 * \see{Graph::setAttribute(
 *   const Graph::Edge&,
 *   const std::string&,
 *   const std::string&)}.
 * @return This function returns a set of nodes which are added to the graph.
 */
inline std::set<Graph::Node> bfsBuild(
  Graph& graph_,
  const Graph::Node& startNode_,
  std::function<std::vector<Graph::Node>(const Graph::Node&)> relations_,
  const std::map<std::string, std::string>& nodeDecoration_
    = std::map<std::string, std::string>(),
  const std::map<std::string, std::string>& edgeDecoration_
    = std::map<std::string, std::string>())
{
  std::set<Graph::Node> visitedNodes;

  std::queue<Graph::Node> queue;
  queue.push(startNode_);

  while (!queue.empty())
  {
    Graph::Node current = queue.front();
    queue.pop();

    for (const Graph::Node& to : relations_(current))
    {
      Graph::Edge edge = graph_.addEdge(current, to);

      for (const auto& decoration : edgeDecoration_)
        graph_.setAttribute(edge, decoration.first, decoration.second);

      if (visitedNodes.find(to) == visitedNodes.end())
      {
        queue.push(to);
        visitedNodes.insert(to);

        for (const auto& decoration : nodeDecoration_)
          graph_.setAttribute(to, decoration.first, decoration.second);
      }
    }
  }

  return visitedNodes;
}

} // util
} // cc

#endif // CC_UTIL_GRAPH_H

