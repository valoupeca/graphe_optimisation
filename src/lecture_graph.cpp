/*
 * git_code.cpp
 *
 *  Created on: 17 mai 2018
 *      Author: lamure
 */

#include <boost/graph/graphml.hpp>
#include <string>
#include <fstream>


using namespace std;
using namespace boost;

//On définit les caractéristiques de nos noeuds, arc pour notre graphe

 // vertex = correspond aux noeuds

struct vertex_info {
  std::string name;
  std::string label;
  int type;

};

/*  edges -> correspond aux arcs*/
struct edge_info {
  double weight;
};

/* Define the type of graph */
typedef boost::adjacency_list<
   boost::vecS, boost::vecS, boost::bidirectionalS,
   vertex_info,
   edge_info
> Graph_t;


/* Declare dynamic properties for graphml format. */
boost::dynamic_properties dp;


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
  dp.property("weight", get(&edge_info::weight, designG));

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
 /* if(argc < 2)
  {
    cerr<<"USAGE : ./a.out filename"<<endl;
    exit(0);
  }
  */
  std::string file = "/home/lamure/Documents/developpement/table.gml";

  Graph_t graph_t;

  std::ifstream is(file.c_str());

  readGraphMLFile(graph_t, file);


}


