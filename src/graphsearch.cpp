#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <utility>

#include <lemon/smart_graph.h>
#include <lemon/dijkstra.h>

std::istream& get_input_handle(const int ac, std::ifstream& fhandle, const char* fname);
bool compare(std::string a, std::string b);
void remove(std::vector<std::string> &v);


std::istream& get_input_handle(const int ac, std::ifstream& fhandle, const char* fname) {
  if (ac == 4) {
    fhandle.open(fname);
    assert(fhandle.is_open());
    return fhandle;
  }
  else {
    return std::cin;
  }
  }

bool compare(std::string a, std::string b) { // comparison function
  return a < b;
}

void remove(std::vector<std::string> &v) // remove extra nodes
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
 
    v.erase(end, v.end());
}

int main (int argc, char** argv) {

  std::string startNode;
  std::string endNode;

  if (argc == 4) {
    startNode = argv[2];
    endNode = argv[3];
  }
  else {
    startNode = argv[1];
    endNode = argv[2];
  }

  struct Arc
  {
    std::string sourceID;
    std::string targetID;
    double cost;
  };

std::map<std::string, int> nodes;
std::vector<Arc> arcs;
std::vector<std::string> temp_nodes;


  std::ifstream fp;
  std::istream& input = get_input_handle(argc, fp, argv[1]); // function figures out if cin or file 
  std::string inp;

    while(std::getline(input, inp)) {
        Arc tempArc;
        std::string node_1;
        std::string node_2;
        int weight;
        std::istringstream iss(inp);

        iss >> node_1 >> node_2 >> weight;
        // ARC -------------------------
        tempArc.sourceID = node_1;
        tempArc.targetID = node_2;
        tempArc.cost = weight;

        arcs.emplace_back(tempArc);
        // NODE(temp) ------------------------
      temp_nodes.emplace_back(node_1);
      temp_nodes.emplace_back(node_2);

    }

    remove(temp_nodes); // gives us vector with all of our nodes

    std::sort(temp_nodes.begin(), temp_nodes.end(), compare); // sort nodes

    for (unsigned int i = 0; i < temp_nodes.size(); i++) {
      nodes.insert( std::pair<std::string,int>(temp_nodes.at(i), i) ); // fill map
    }

  using SptSolver = lemon::Dijkstra<lemon::SmartDigraph, lemon::SmartDigraph::ArcMap<double>>; // remove verbosity

  lemon::SmartDigraph g;
  lemon::SmartDigraph::ArcMap<double> costMap(g);
  lemon::SmartDigraph::NodeMap<std::string> nodeMap(g);

  lemon::SmartDigraph::Node currentNode;
  for (auto nodesIter = nodes.begin(); nodesIter != nodes.end(); ++nodesIter) // fill nodes
  {
    std::string key = nodesIter->first;
    currentNode = g.addNode();
    nodeMap[currentNode] = key;
  }

  lemon::SmartDigraph::Arc currentArc;
  for (auto arcsIter = arcs.begin(); arcsIter != arcs.end(); ++arcsIter) // fill arcs
  {
    int sourceIndex = nodes.at(arcsIter->sourceID);
    int targetIndex = nodes.at(arcsIter->targetID);
 
    lemon::SmartDigraph::Node sourceNode = g.nodeFromId(sourceIndex);
    lemon::SmartDigraph::Node targetNode = g.nodeFromId(targetIndex);
 
    currentArc = g.addArc(sourceNode, targetNode);
    costMap[currentArc] = arcsIter->cost;
  }

lemon::SmartDigraph::Node start = g.nodeFromId( nodes.at(startNode) ); // give start and end locations from command line
lemon::SmartDigraph::Node end = g.nodeFromId( nodes.at(endNode) );

SptSolver spt(g, costMap); // instantiate dijikstras solver

bool validPath = spt.run(start, end); // run solver from start to end node

std::vector<lemon::SmartDigraph::Node> path;
if (validPath) {
for (lemon::SmartDigraph::Node v = end; v != start; v = spt.predNode(v)) // give us total cost of shortest path
{
  if (v != lemon::INVALID && spt.reached(v)) 
  {
     path.push_back(v);
  }
}
path.push_back(start);
}

int costPath;

if (validPath) {
  costPath = spt.dist(end);
}

// print out our cost and path (reverse order since above loop goes from destination to start)
if (startNode == endNode) {
  std::cout << "0: " << startNode << std::endl;
}
else if (validPath) {
  std::cout << costPath << ": ";
    for(auto p = path.rbegin(); p != path.rend(); ++p) {
      std::cout << nodeMap[*p] << " ";
    }
    std::cout << std::endl;
}
else {
  std::cout << "No path exists from " << startNode << " to " << endNode << std::endl;
}
 


    return 0;
}
