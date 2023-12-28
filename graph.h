#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

struct vertex {
    // пара из стоимости и вершины назначения
    typedef std::pair<unsigned int, vertex *> cv;
    std::vector<cv> paths;
    std::string name;
};

class Graph {
public:
    Graph() {};
    ~Graph() {};

    // карта вершин представляет собой map из пары <название вершины, содержание веришны>
    typedef std::map<std::string, vertex> vmap;
    vmap getMap();
    void addVertex(const std::string& name);
    void addPath(const std::string& from, const std::string& to, unsigned int cost);

private:
    vmap map;
};

template<unsigned Type>
class Traveler {
public:
    Traveler(Graph *graph, std::string my_name);
    ~Traveler() {};

    void move_to(std::string position);
    void travel();

private:
    Graph *g;
    std::string name;
    std::string pos;
    std::string log_path;

};

#endif // __GRAPH_H__
