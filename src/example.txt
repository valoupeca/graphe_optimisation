//============================================================================
// Name        : example.cpp
// Author      : Lamure
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/filesystem.hpp>
#include <libs/graph/src/graphml.cpp>
#include <boost/config.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>



/*
int main(int argc, char* argv[])
{

		/*std::ifstream inFile;
	    inFile.open("", std::ifstream::in);*/

	/*	typedef adjacency_list<vecS, vecS, directedS,property<vertex_name_t,std::string> > BoostGraphType;
	    typedef dynamic_properties BoostDynamicProperties;

	    std::string file = "/home/lamure/Documents/developpement/table.gml";
	    std::ifstream is(file.c_str());
	    if (!is.is_open())
	    {
	        std::cout << "loading file '" << file << "'failed." << std::endl;
	        throw "Could not load file.";
	    }

	    BoostGraphType g;
	    BoostDynamicProperties dp ;
	    const std::string vn = "vertex_name";
	    dp.property(vn,get(vertex_name,g));
	    read_graphml(is, g, dp);
*/

	    /*std::ifstream t(file.c_str());
	    if (!t.is_open())
	    {
	       std::cout << "loading file failed." << std::endl;
	       throw "Could not load file.";
	    }

	    typedef boost::adjacency_list<boost::hash_setS, boost::vecS, boost::undirectedS> Graph;
	    Graph g;
	    boost::dynamic_properties dp;



	    struct graph_exception : public std::exception {
	      virtual ~graph_exception() throw();
	      virtual const char* what() const throw() = 0;
	    };

	    try{
 	    boost::read_graphml(t,g,dp);
	    }
	         catch(const boost::property_tree::xml_parser::xml_parser_error& ex){
	           std::cout<<argv[1]<<" failed, reading "<<argv[2]<<std::endl;
	           boost::read_graphml(t,g,dp);
	         }
*/
	/*	return 0;
}
*/
