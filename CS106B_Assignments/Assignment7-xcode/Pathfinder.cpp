/*
 * File: Pathfinder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Pathfinder application
 * on Assignment #6.
 */
 
// [TODO: complete this implementation]
// REACT TO EVENTS Fix when nothing close is clicked 

#include <iostream>
#include <string>
#include "console.h"
#include "graphtypes.h"
#include "gpathfinder.h"
#include "tokenscanner.h"
#include "strlib.h"
#include "pqueue.h"
#include <cmath>
#include "path.h"
#include "simpio.h"

using namespace std;

/* Function prototypes */
void quitAction();
SimpleGraph readData(string filename);
void drawNodes(SimpleGraph& graph);
void drawArcs(SimpleGraph& arcs);
void drawMap(SimpleGraph& graph);
void dijkstra(SimpleGraph& graph);;
void startAndFinish(Node*& start, Node*& finish, SimpleGraph& graph);
void readNodes(SimpleGraph& graph, ifstream& infile);
void readArcs(SimpleGraph& graph, ifstream& infile, string line);
Path findShortestPath(Node* start, Node* finish);
void resetGraphics(SimpleGraph& graph);
void kruskal(SimpleGraph& graph);
Set<Arc*> minimumSpanningTree(PriorityQueue<Arc*>& queue, SimpleGraph& graph);
Map<string,Set<Node*> >initialTree(SimpleGraph& graph);
Node* getStart(SimpleGraph& graph);
Node* getFinish(SimpleGraph& graph);
string getFile();
void resetMap(SimpleGraph& graph);

/* Radius of click for the nodes */
const double CLICK_RADIUS = 5;

/* Main program */
int main() {
	initPathfinderGraphics();
	string fileName = getFile();
	SimpleGraph graph = readData(fileName);
	drawMap(graph);
	addButton("Quit", quitAction);
	addButton("Map", resetMap, graph);
	addButton("Dijkstra", dijkstra,graph);
	addButton("Kruskal", kruskal,graph);
	addButton("Reset Graphics", resetGraphics,graph);
	repaintPathfinderDisplay();
	pathfinderEventLoop();
	return 0;
}

/* Sample callback function */
void quitAction() {
   exit(0);
}

/* Asks the user for the file name */
string getFile(){
	string result = getLine("Please enter the name of graph data file: ");
	return result;
}
/* Read the data */
SimpleGraph readData(string filename){
	
	// Graph holding the nodes and arcs
	SimpleGraph graph;
	
	// Infile for reading the data
	ifstream infile;
	infile.open(filename.c_str());
	while(!infile.fail()){
		string line;
		getline(infile, line);
		
		// If the line contains ".jpg" it's the image file
		if(line.find(".jpg") != string::npos){
			graph.imageFile = line;
		}else if (line == "NODES"){
			readNodes(graph, infile);
		}else{
			readArcs(graph,infile, line);
		}
	}
	
	return graph;
}

/* Reads all of the nodes and stores them in the graph */
void readNodes(SimpleGraph& graph, ifstream& infile){
	string line;
	getline(infile, line);
	while (line != "ARCS"){
		
		// Scanner over the city string
		TokenScanner scanner(line);
		scanner.ignoreWhitespace();
		Node* node = new Node;
		
		// The name is the first token
		node->name = scanner.nextToken();
		
		// The x coord. of the city is the first token and the y coord. is the second token
		double x = stringToReal(scanner.nextToken());
		double y = stringToReal(scanner.nextToken());
		GPoint pt(x,y);
		node->loc = pt;
		
		// Add the node to the set in the graph
		graph.nodes += node;
		
		// Add the node to the map in the graph
		graph.nodeMap.put(node->name, node);
		
		// Get the next line
		getline(infile, line);
	}
}

/* Reads all of the graphs and stores them in the graph */
void readArcs(SimpleGraph& graph, ifstream& infile, string line){
	while(!infile.fail()){
	
		TokenScanner scanner(line);
		scanner.ignoreWhitespace();
		
		// Arc in forward directions
		Arc* forwardArc = new Arc;
		
		// The start node is the Node representing 
		forwardArc->start = graph.nodeMap.get(scanner.nextToken());
		forwardArc->finish = graph.nodeMap.get(scanner.nextToken());
		forwardArc->cost = stringToReal(scanner.nextToken());
		graph.arcs += forwardArc;
		
		// Add this arc to the set of arcs from the start
		forwardArc->start->arcs += forwardArc;
		
		// Arc in reverse direction
		Arc* reverseArc = new Arc;
		reverseArc->start = forwardArc->finish;
		reverseArc->finish = forwardArc->start;
		reverseArc->cost = forwardArc->cost;
		graph.arcs += reverseArc;
		
		//Add this arc to the set of arcs from the start
		reverseArc->start->arcs += reverseArc;
		getline(infile, line);
	}
}				

/* Draws the map, nodes and arcs*/
void drawMap(SimpleGraph& graph){
	// Displays the image of the map
	drawPathfinderMap(graph.imageFile);
	drawNodes(graph);
	drawArcs(graph);
}

/* Draws all of the nodes in the graph */
void drawNodes(SimpleGraph& graph){
	foreach(Node* node in graph.nodes){
		drawPathfinderNode(node->loc, "BLACK", node->name);
	}
}

/* Draws all fo the arcs in the graph */
void drawArcs(SimpleGraph& graph){
	foreach(Arc* arc in graph.arcs){
		drawPathfinderArc(arc->start->loc, arc->finish->loc, "BLACK");
	}
}

/* Finds the shortest path between nodes */
void dijkstra(SimpleGraph& graph){
	Node* start = getStart(graph); 
	Node* finish = getFinish(graph);
	Path path = findShortestPath(start, finish);
	for (int i = 0; i < path.size(); i++){
		drawPathfinderArc(path.get(i)->start->loc,path.get(i)->finish->loc, "RED");
	}
	cout << "Your path is: " << path.toString() << endl;
}

/* Returns the starting node */
Node* getStart(SimpleGraph& graph){
	cout << "Select your starting location: " << endl;
	GPoint startpt = getMouseClick();
	Node* start = NULL;
	// Look over all the nodes 
	foreach(Node* node in graph.nodes){
		
		// If a node is close enough to the click set it as the start
		if(abs(node->loc.getX() - startpt.getX()) < CLICK_RADIUS && abs(node->loc.getY() - startpt.getY()) < CLICK_RADIUS){
			start = node;
			cout << "You selected: " << node->name << " as the start." << endl;
			drawPathfinderNode(node->loc, "RED", node->name);
			break;
		}
	}
	// Make sure the user clicked near a node
	while(start == NULL){
		start = getStart(graph);
	}
	return start;
}	

/* Returns the finishing node */
Node* getFinish(SimpleGraph& graph){
	cout << "Select your ending location: " << endl;
	GPoint endpt = getMouseClick();
	Node* finish = NULL;
	foreach(Node* node in graph.nodes){
		
		// If a node is close enough to the click set it as the finish
		if(abs(node->loc.getX() - endpt.getX()) < 5 && abs(node->loc.getY() - endpt.getY()) < 5){
			finish = node;
			cout << "You selected: " << node->name << " as the finish." << endl;
			drawPathfinderNode(node->loc, "RED", node->name);
			break;
		}
	}
	// Make sure the user clicked near a node
	while(finish == NULL){
		finish = getFinish(graph);
	}	
	return finish;
}


/* Finds the shortest path between the nodes start and finish */
Path findShortestPath(Node* start, Node* finish){
	Path path;
	PriorityQueue<Path> queue;
	Map<string, double> fixed;
	while (start != finish){
		if (!fixed.containsKey(start->name)){
			fixed.put(start->name,path.cost());
			foreach(Arc* arc in start->arcs){
				if(!fixed.containsKey(arc->finish->name)){
					path.add(arc);
					queue.enqueue(path, path.cost());
					path.removeAt(path.size() - 1);
				}
			}
		}
		if (queue.isEmpty()){
			path.clear();
			return path;
		}
		path = queue.dequeue();
		start = path.get(path.size() - 1)->finish;
		
	}
	return path;
}

/* Resets the graphics(unhighlights all nodes and arcs) */
void resetGraphics(SimpleGraph& graph){
	// Reset all of the arcs
	foreach(Arc* arc in graph.arcs){
		drawPathfinderArc(arc->start->loc, arc->finish->loc,  "BLACK");
	}
	// Reset all of the nodes
	foreach(Node* node in graph.nodes){
		drawPathfinderNode(node->loc, "BLACK", node->name);
	}
}

/* Finds the minimum spanning tree for a graph */
void kruskal(SimpleGraph& graph){
	PriorityQueue<Arc*> queue;
	
	// Add all the queues to an arc
	foreach(Arc* arc in graph.arcs){
		queue.enqueue(arc, arc->cost);
	}
	Set<Arc*> minimumArcs = minimumSpanningTree(queue,graph);
	foreach(Arc* arc in minimumArcs){
		drawPathfinderArc(arc->start->loc, arc->finish->loc, "RED");
	}
}


/* Returns the arcs that make up the minimum spanning tree */
Set<Arc*> minimumSpanningTree(PriorityQueue<Arc*>& queue, SimpleGraph& graph){
	Set<Arc*> result;
	// Keeps tracks of which all the nodes that a node is connected to
	Map<string,Set<Node*> > nodesMapped = initialTree(graph);
	while (!queue.isEmpty()) {
		Arc* arc = queue.dequeue();
		Node* start = arc->start;
		Node* finish = arc->finish;
		Set<Node*> combinedSet = nodesMapped.get(start->name) + nodesMapped.get(finish->name);
		// The nodes are not part of the spanning tree
		if(!nodesMapped.get(start->name).contains(finish)){
			// Add the arc to the result
			result += arc;
			
			// Update every node in the start's set to be connected
			foreach(Node* node in nodesMapped.get(start->name)){
				string name = node->name;
				nodesMapped.put(name, combinedSet);
			}
			// Update every node in the finish's set to be connected
			foreach(Node* node in nodesMapped.get(finish->name)){
				string name = node->name;
				nodesMapped.put(name, combinedSet);
			}
		}
		
	}
	return result;
}

/* Returns a map for keeping track of which nodes are connected to each other */
Map<string,Set<Node*> > initialTree(SimpleGraph& graph){
	Map<string, Set<Node*> > result;
	foreach(Node* node in graph.nodes){
		Set<Node*> connections;
		connections += node;
		result.put(node->name, connections);
	}
	return result;
}

/* Resets the graph */
void resetMap(SimpleGraph& graph){
	string fileName = getFile();
	graph = readData(fileName);
	drawMap(graph);
}

