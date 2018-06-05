//
// Created by lamure on 05/06/18.
//

/* git_code.cpp
		*
		*  Created on: 17 mai 2018
*      Author: lamure
*/

#include <string>
#include <fstream>
#include <utility>
#include <iostream>
#include <cstring>
#include <vector>


#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/pthread/condition_variable.hpp>

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

typedef boost::iterator_property_map < double*, IndexMap, double, double& > DistanceMap;


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


void calcul_chemin(Graph_t graph_t, std::vector<int> sources, std::set<int> dests, vector<vector<int> > &mat, int indexTab  ) {

    IndexMap index = get(vertex_index, graph_t);
    graph_traits<Graph_t>::vertex_iterator i, iend;
    int cnt=0;
    std::vector<vertex_descriptor> parent(num_vertices(graph_t));
    std::vector<double> distance(num_vertices(graph_t));
    for (auto l : sources) {
        parent.clear();
        distance.clear();
        vertex_descriptor source = vertex(l, graph_t);

//        pair<AdjacencyIterator, AdjacencyIterator> voisins = adjacent_vertices(noeud_principal, graph_t);


//        mat[0][index_tab] = landmark;

//        PredecessorMap predecessorMap(&parent[0], index);
//        dijkstra_shortest_paths(graph_t, source, predecessor_map(&parent[0]).distance_map(&distance[0]));
//        DistanceMap distanceMap(&distance[0], index);

        // dijkstra_shortest_paths(graph_t, noeud1, weight_map(get(&edge_info::weight, graph_t)));

        auto weights = get(&edge_info::weight,graph_t);
        dijkstra_shortest_paths(graph_t, source,
                            //    boost::no_named_parameters().weight_map(weights));
                                        //.weight_map(get(&edge_info::weight, graph_t)));
        boost::weight_map(boost::get(&edge_info::weight,graph_t))
                .distance_map(boost::make_iterator_property_map(distance.begin(), boost::get(boost::vertex_index,graph_t)))
                .predecessor_map(boost::make_iterator_property_map(parent.begin(), boost::get(boost::vertex_index,graph_t)))
        );


        DistanceMap distanceMap(&distance[0], index);
        int cnt2 =0;
        for (auto d: dests){
            mat[cnt2][indexTab+cnt]=distanceMap[vertex(d,graph_t)];
            cout<<"Distance from AS "<< graph_t[l].asn<<" to AS "<<graph_t[d].asn<<" is "<< mat[cnt2][indexTab+cnt] <<endl;
            cnt2++;
        }
        cnt++;


   /*     typedef std::vector<Graph_t::edge_descriptor> PathType;
        PathType path;
        cout << "node : " << landmark << endl;
        vertex_descriptor v = landmark;
        cout << "name vertex landmark " << get(vertex_bundle, graph_t)[v].name << endl;
        for (vertex_descriptor u = parent[v];
             u != v; // Keep tracking the path until we get to the source
             v = u, u = parent[v]) // Set the current vertex to the current predecessor,     and the predecessor to one level up
        {
            std::pair<Graph_t::edge_descriptor, bool> edgePair = boost::edge(u, v, graph_t);
            Graph_t::edge_descriptor edge = edgePair.first;
            path.push_back(edge);
        }

        // Write shortest path
        std::cout << "Shortest path from " << noeud_principal << " to " << v << "  "
                  << get(vertex_bundle, graph_t)[noeud_principal].name;
        cout << " et noeud d'arrivée " << get(vertex_bundle, graph_t)[landmark].name << std::endl;
        float totalDistance = 0;
        for (PathType::reverse_iterator pathIterator = path.rbegin(); pathIterator != path.rend(); ++pathIterator) {
            std::cout << get(vertex_bundle, graph_t)[boost::source(*pathIterator, graph_t)].name << " -> " <<
                      get(vertex_bundle, graph_t)[boost::target(*pathIterator, graph_t)].name
                      << " = " << get(boost::edge_bundle, graph_t)[*pathIterator].weight << std::endl;
            totalDistance = totalDistance + get(boost::edge_bundle, graph_t)[*pathIterator].weight;

        }

        mat[1][index_tab] = distanceMap[landmark];


        std::cout << "Distance: " << distanceMap[landmark] << std::endl;
     */
    }
}

int main(int argc, char** argv)
{


	string file = "/home/lamure/Documents/developpement/test.graphml";

	Graph_t graph_t;



	ifstream is(file.c_str());
    cout<<"DEBUT de LECTURE "<<endl;
	readGraphMLFile(graph_t, file);
	cout<<"FICHIER LU! "<<endl;

	int N = num_vertices(graph_t);
    vertex_descriptor v1,v2;
    auto weight_map = get(&edge_info::weight, graph_t);

    for (auto ed : boost::make_iterator_range(edges(graph_t)))
        weight_map[ed] = 1.0;



	/* property map iterator pour rechercher des objets qui nous interessent dans le graphe*/



	/* Puis après avoir ajouté des vertex et edges, je peux accéder par exemple à la liste des vertex comme suite: */
	/* Affiche le nom des sommets */


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

	vertex_descriptor noeud_principal, node_landmark;

	vector<std::string> landmark(20);

	thread *threads[landmark.size()];


	landmark[0] ="24482";
	landmark[1] ="131284";
	landmark[2] ="1455";
	landmark[3] ="531";
	landmark[4] ="1501";
	landmark[5] ="52519";
	landmark[6] ="263276";
	landmark[7] ="22773";
	landmark[8] ="12400";
	landmark[9] ="42926";
	landmark[10] ="266084";
	landmark[11] ="11663";
	landmark[12] ="393223";
	landmark[13] ="9549";
	landmark[14] ="35816";
	landmark[15] ="52376";
	landmark[16] ="266117";
	landmark[17] ="56660";
	landmark[18]="52752";
    int timeWindowLow = 1515117900;
    int timeWindowSize = 60;
    int numOfThreads = 8;



    noeud_principal = vertex(1,graph_t);



    std::map<std::string, int> asMap;
    IndexMap index = get(vertex_index,graph_t);
    Graph_t::vertex_descriptor v;
    std::pair<VertexIterator, VertexIterator> vp;
    std::set<int> setofChangedAS;

    int maxTime=0;
    for (vp = vertices(graph_t); vp.first != vp.second; ++vp.first) {
        v= *vp.first;
        asMap[graph_t[v].asn] = index[v];
        if ( (graph_t[v].ctime >= timeWindowLow) && (graph_t[v].ctime < timeWindowLow+timeWindowSize)) {
            setofChangedAS.insert(index[v]);
        }
    }

    cout<<"Num of changed AS:"<<setofChangedAS.size()<<endl;

    std::set<int> setOfLandmarks;
    for(int c = 0; c < landmark.size(); c++){
        setOfLandmarks.insert(index[asMap[landmark[c]]]);
    }
    cout<<"Num of landmarks :"<<setOfLandmarks.size()<<endl;


    std::set<int> setOfLandmarksNeighbors;
    std::pair<AdjacencyIterator, AdjacencyIterator> neighbors;
    for(auto l : setOfLandmarks) {
        neighbors= boost::adjacent_vertices(vertex(l,graph_t), graph_t);
        for(; neighbors.first != neighbors.second; ++neighbors.first) {
            setOfLandmarksNeighbors.insert(index[*neighbors.first]);
        }
    }
    cout<<"Size of setOfLandmarkNeighbors :"<<setOfLandmarksNeighbors.size()<<endl;

    std::set<int> setOfChangedNeighbors;
    for(auto l : setofChangedAS) {
        neighbors= boost::adjacent_vertices(vertex(l,graph_t), graph_t);
        for(; neighbors.first != neighbors.second; ++neighbors.first) {
            setOfChangedNeighbors.insert(index[*neighbors.first]);
        }
    }
    cout<<"Size of setOfChangedNeighbors :"<<setOfChangedNeighbors.size()<<endl;

    // A la fin de cette partie nous avons les données suivante :
    // setOfLandmarks = ensemble des index des Landmarks
    // setOfLandmarksNeighbors = ensemble des index dex voisins des landmarks
    // setOfChangedAS = ensemble des index des AS qui ont change dans la fenetre
    // setofChangedNeighbors = ensemble des index des voisins des AS qui ont change dans la fenetre




    vector<vector<int> > mat(setOfChangedNeighbors.size(),vector<int>(setOfLandmarksNeighbors.size()));


    int numOfElementsPerThread = setOfLandmarksNeighbors.size()/numOfThreads;

    std::vector<int> landmarks;
    int count = 1;
    int threadNum =0;
    for (auto l :setOfLandmarksNeighbors){
        landmarks.push_back(l);
        if (l % numOfElementsPerThread ==0 ){
            threads[threadNum] = new thread(calcul_chemin, graph_t,  landmarks , setOfChangedNeighbors, mat , threadNum*numOfElementsPerThread);
            threadNum ++;
            landmarks.clear();
        }
        count ++;
    }

	for(int c = 0; c < threadNum; c++)
	{
		threads[c]->join();
		delete threads[c];
	}


	for (int i=0; i<2; i++){
		for (int j=0; j<landmark.size(); j++){
			cout << mat[i][j]<<" ";
		}

		cout <<endl;
	}
	std::cout << std::endl;
}

