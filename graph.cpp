#include "graph.h"

Graph::vmap Graph::getMap() {
    return map;
}

void Graph::addVertex(const std::string &name) {
    auto i = map.find(name);
    if (i == map.end()) {
        vertex v;
        v.name = name;
        map[name] = v;
    }
}

void Graph::addPath(const std::string &from, const std::string &to, unsigned int cost) {
    // если обе такие вершины есть
    if (map.find(from) != map.end() && map.find(to) != map.end()) {
        vertex f = map.find(from)->second;
        vertex t = map.find(to)->second;
        // и если не нашли пути из одной в другую
        int found = 0;
        for (auto i = f.paths.begin(); i < f.paths.end(); i++) {
            if (i->second->name == t.name) {
                found = 1;
                break;
            }
        }
        // то добавляем переданный в функцию
        if (!found) {
            std::pair<int, vertex *> path_f = std::make_pair(cost, &t);
            std::pair<int, vertex *> path_t = std::make_pair(cost, &f);
            f.paths.push_back(path_f);
            t.paths.push_back(path_t);
            map[from] = f;
            map[to] = t;
        }
        
    }
    
}

template<unsigned int Type> Traveler<Type>::Traveler(Graph *graph, std::string my_name) {
    g = graph;
    pos = graph->getMap().begin()->first();
    name = my_name;
    if (Type == 1) {
        log_path = "logs/first.txt";
    } else if (Type == 2) {
        log_path = "logs/second.txt";
    } else {
        log_path = "logs/third.txt";
    }
}

template<unsigned int Type> void Traveler<Type>::move_to(std::string position) {
    pos = position;
    std::ofstream log(log_path);
    log << name << ", " << Type << " type: Teleported to " << pos << "\n"; 
    log.close();
}

template<unsigned int Type> void Traveler<Type>::travel() {
    std::string a = pos;
    unsigned int c;
    vertex *dst;
    vertex my_vertex = g->getMap().find(pos)->second();

    if (Type == 1) {
        srand((unsigned)time(NULL));
        auto i = my_vertex.paths.at(rand() % my_vertex.paths.size());
        dst = i.second;
        c = i.first;
    } else if (Type == 2) {
        dst = my_vertex.paths.begin()->second;
        c = my_vertex.paths.begin()->first;
        for (auto i = my_vertex.paths.begin()+1; i < my_vertex.paths.end(); i++) {
            if (i->first < c) {
                dst = i->second;
                c = i->first;
            }
        }
    } else {
        dst = my_vertex.paths.begin()->second;
        c = my_vertex.paths.begin()->first;
        for (auto i = my_vertex.paths.begin()+1; i < my_vertex.paths.end(); i++) {
            if (i->first > c) {
                dst = i->second;
                c = i->first;
            }
        }
    }

    pos = dst->name;
    std::ofstream log(log_path);
    log << name << ", " << Type << " type: Traveled from " << a << " to " << pos << ". The cost was " << c << "\n"; 
    log.close();
}
