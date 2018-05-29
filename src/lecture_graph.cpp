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
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/property_map/property_map_iterator.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/lookup_edge.hpp>
#include <boost/graph/random.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>


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
  int id;


};

/*  edges -> correspond aux arcs*/
struct edge_info {
  double weight;
  long count;
  long ftime;
   long ctime;
};



/*def graph*/
typedef adjacency_list <boost::listS, boost::vecS, boost::directedS,vertex_info,
		   edge_info >  Graph_t;




/* Declare dynamic properties for graphml format. */
boost::dynamic_properties dp;

typedef graph_traits < Graph_t >::vertex_iterator VertexIterator;
typedef graph_traits < Graph_t >::edge_iterator EdgeIterator;
typedef graph_traits < Graph_t >::adjacency_iterator AdjacencyIterator;

typedef graph_traits < Graph_t >::vertex_descriptor vertex_descriptor;
typedef graph_traits < Graph_t >::edge_descriptor edge_descriptor;

typedef property_map < Graph_t, vertex_index_t >::type IndexMap;



/*property map*/


/*in & out edges*/
typedef graph_traits<Graph_t>::in_edge_iterator inEdge;
typedef graph_traits<Graph_t>::out_edge_iterator outEdge;


/*id vertex*/


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
	 dp.property("id", get(&vertex_info::id, designG));
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

  int N = num_vertices(graph_t);

  /* property map iterator pour rechercher des objets qui nous interessent dans le graphe*/



  /* Puis après avoir ajouté des vertex et edges, je peux accéder par exemple à la liste des vertex comme suite: */
    /* Affiche le nom des sommets */

  int selector =  0 ;
  vertex_descriptor node_select;

  vertex_descriptor u_in,u_out,v_in,v_out;

  std::pair<inEdge, inEdge> inedge;

  std::pair<outEdge, outEdge> outedge;

  //node_id index = get(vertex_index,graph_t);

  std::pair<VertexIterator, VertexIterator> it_2 = boost::vertices(graph_t);
 /*for( ; it_2.first != it_2.second; ++it_2.first)
  {
	  node_select = *it_2.first;
	  if(selector < 10)
	  {
		test.added_vertex(node_select);
		cout << "node is : " << node_select << endl;
		outedge = out_edges(node_select,graph_t);
		inedge = in_edges(node_select,graph_t);

		/* arrive à notre noeuds
		for(inEdge in_e = inedge.first ; in_e != inedge.second; ++in_e) {


				  u_in = source(*in_e, graph_t);
				  v_in = target(*in_e, graph_t);

			long a = index[u_in];
			long b = index[v_in];

			cout << selector << " : " << a << " --> " << b   << endl;
		}

		/* depuis notre noeuds vers un autre
		for(outEdge out_e =  outedge.first ; out_e != outedge.second; ++out_e) {

			 u_out = source(*out_e, graph_t);
			 v_out = target(*out_e, graph_t);

						long a1 = index[u_out];
						long b1 = index[v_out];

						cout << selector << " : " << a1 << " --> " << b1   << endl;
				}

	  }

	  selector++;

  }
*/


 // print_graph(test);

  pair<EdgeIterator, EdgeIterator> ei = edges(graph_t);


  //vertex_descriptor u,v;
  //vector<vector<int> > mat(N,vector<int>(N));

 /* for(EdgeIterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter) {

	  u = source(*edge_iter, graph_t);
	            v = target(*edge_iter, graph_t);

	         //   node_id index = get(vertex_index, graph_t)[u];

	            long a = index[u];
	            long b = index[v];
  }

  cout << num_edges(graph_t)<< '\n';



  for(EdgeIterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter) {

	  u = source(*edge_iter, graph_t);
	  v = target(*edge_iter, graph_t);

	  //   node_id index = get(vertex_index, graph_t)[u];

	  long a = index[u];
	  long b = index[v];

	  if( a < 10 && b < 10)
	  {
		  add_edge(vertex(a,test),vertex(b,test),)
	  }
		  mat[a][b] = get(boost::edge_bundle, graph_t)[*ei.first].count;
		  mat[b][a] = get(boost::edge_bundle, graph_t)[*ei.first].count;

	  }

*/
 /*int i = 0;
for (EdgeIterator edge_iter = ei.first; edge_iter != ei.second; ++edge_iter){


          u = source(*edge_iter, graph_t);
          v = target(*edge_iter, graph_t);


          long a = index[u];
          long b = index[v];

         mat[a][b] = 1;
         mat[b][a] = 1;
          cout << i << " : " << a << " --> " << b   << endl;
          i++;
	  }


 for (int i=0; i<20; i++){
        for (int j=0; j<20; j++){
            cout << mat[i][j]<<" ";
        }
        cout <<endl;
    }




*/

  /* v2 , prendre noeud arrivée et de départ, chercher les plus court voisins et développé la matrice OT*/

  vertex_descriptor noeud1, noeud2;





  IndexMap index = get(vertex_index,graph_t);


  graph_traits<Graph_t>::vertex_iterator i, iend;

  pair<AdjacencyIterator,AdjacencyIterator> voisins = adjacent_vertices(vertex(150,graph_t),graph_t);

  for(; voisins.first != voisins.second ; ++voisins.first)
  {
	  cout << index[*voisins.first] << endl;

  }

  noeud1 = vertex(150,graph_t);

  cout << get(vertex_bundle,graph_t)[noeud1].name  << endl;



  std::vector<vertex_descriptor> p(num_vertices(graph_t));
  std::vector<int> d(num_vertices(graph_t));



  	  dijkstra_shortest_paths(graph_t, noeud1,
                              predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, graph_t))).
                              distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, graph_t))));

      std::cout << "distances and parents:" << std::endl;
      graph_traits < Graph_t >::vertex_iterator vi, vend;
      for (boost::tie(vi, vend) = vertices(graph_t); vi != vend; ++vi) {
        std::cout << "distance(" << get(vertex_bundle,graph_t)[*vi].name << ") = " << d[*vi] << ", ";
        std::cout << "parent(" << get(vertex_bundle,graph_t)[*vi].name << ") = " << get(vertex_bundle,graph_t)[p[*vi]].name << std::endl;
      }
      std::cout << std::endl;


}


