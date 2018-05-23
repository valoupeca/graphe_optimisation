/*
 * git_code.cpp
 *
 *  Created on: 17 mai 2018
 *      Author: lamure
 */

#include <string>
#include <fstream>
#include <utility>

#include <boost/graph/graphml.hpp>
#include <boost/config.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/breadth_first_search.hpp>


using namespace std;
using namespace boost;

//On définit les caractéristiques de nos noeuds, arc pour notre graphe

 // vertex = correspond aux noeuds

struct vertex_info {
  std::string name;
  std::string label;
  string country;
  string rir;
  long prefixnum;
  long prefixall;
  long ftime;
  long ctime;
  float size;
  string asn;
  int r,g,b;
  float x,y;
  long count;

};

/*  edges -> correspond aux arcs*/
struct edge_info {
  double weight;
  long count;
  long ftime;
   long ctime;
};

/* Define the type of graph */
typedef boost::adjacency_list<
   boost::vecS, boost::vecS, boost::bidirectionalS,
   vertex_info,
   edge_info
> Graph_t;


/* Declare dynamic properties for graphml format. */
boost::dynamic_properties dp;

typedef graph_traits < Graph_t >::vertex_iterator VertexIterator;
typedef graph_traits < Graph_t >::edge_iterator EdgeIterator;
typedef graph_traits < Graph_t >::adjacency_iterator AdjacencyIterator;

typedef property_map < Graph_t, vertex_index_t >::type IndexMap;


/*  Declare function prototype */
void readGraphMLFile(Graph_t& graphToBuild, string gmlFileToRead);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  readGraphMLFile
 *  Description:  Read a graphml file and update the graph designG.
 * =====================================================================================
 */
void readGraphMLFile ( Graph_t& designG, string fileName )
{
  dp.property("name", get(&vertex_info::name, designG));
  dp.property("label", get(&vertex_info::label, designG));
  dp.property("asn", get(&vertex_info::asn, designG));
  dp.property("rir", get(&vertex_info::rir, designG));
  dp.property("country", get(&vertex_info::country, designG));
  dp.property("prefixnum", get(&vertex_info::prefixnum, designG));
  dp.property("prefixall", get(&vertex_info::prefixall, designG));
  dp.property("ftime", get(&vertex_info::ftime, designG));
  dp.property("ctime", get(&vertex_info::ctime, designG));
  dp.property("size", get(&vertex_info::size, designG));
  dp.property("r", get(&vertex_info::r, designG));
  dp.property("g", get(&vertex_info::g, designG));
  dp.property("b", get(&vertex_info::b, designG));
  dp.property("x", get(&vertex_info::x, designG));
  dp.property("y", get(&vertex_info::y, designG));
  dp.property("count", get(&vertex_info::count, designG));

  dp.property("weight", get(&edge_info::weight, designG));
  dp.property("count", get(&edge_info::count, designG));
  dp.property("ftime", get(&edge_info::ftime, designG));
    dp.property("ctime", get(&edge_info::ctime, designG));

  ifstream gmlStream;
  gmlStream.open(fileName.c_str(), ifstream::in);

  boost::read_graphml(gmlStream, designG, dp);
  gmlStream.close();

}		/* -----  end of method ExpressionGraph::readGraphMLFile  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:
 * =====================================================================================
 */
int main(int argc, char** argv)
{

  string file = "/home/lamure/Documents/developpement/test.graphml";

  Graph_t graph_t;

  ifstream is(file.c_str());

  readGraphMLFile(graph_t, file);

  int i = 0 ;

  /* property map iterator pour rechercher des objets qui nous interessent dans le graphe*/

  const IndexMap index = get(vertex_index, graph_t);

  /* Puis après avoir ajouté des vertex et edges, je peux accéder par exemple à la liste des vertex comme suite: */
    /* Affiche le nom des sommets */
  std::pair<VertexIterator, VertexIterator> it_2 = boost::vertices(graph_t);
  for( ; it_2.first != it_2.second; ++it_2.first)
  {
	  i++;
     std::cout << get(boost::vertex_bundle, graph_t)[*it_2.first].name << std::endl;
  }


  cout << "nb sommet " << i <<endl;

  queue < graph::vertex_descriptor> q;

  bfs_visitor<null_visitor> vis;

  breadth_first_search(graph_t, topLeft, q, vis, index.data());

  /* pair<EdgeIterator, EdgeIterator> it_e;

  for( it_e =  edges(graph_t); it_e.first != it_e.second; ++it_e.first)
  {
	  cout << get(boost::edge_bundle, graph_t)[*it_e.first].weight << endl;
  }


*/
}


