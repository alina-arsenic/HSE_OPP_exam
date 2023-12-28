#include "graph.h"

int main() {
    Graph graph;
    std::string letters = "ABCDEFGHIJKLMNOPQRSTYVWXYZ";
    for (int i = 0; i < letters.length(); i++) {
        graph.addVertex({letters[i]});
    }

    srand((unsigned)time(NULL));
    std::cout << "\nPATHS:\n";
    for (int i = 0; i < 50; i++) {
        std::string a = {letters[rand()%letters.length()]};
        std::string b = {letters[rand()%letters.length()]};
        unsigned int n = rand()%50+1;
        if (a != b) graph.addPath(a, b, n);
        std::cout << a << " <--> " << b << "   " << n << "\n";
    }

    Traveler<1u> t1(&graph, "Tap");
    Traveler<2u> t2(&graph, "Tup");
    Traveler<3u> t3(&graph, "Top");
    Traveler<1u> t4(&graph, "Lap");
    Traveler<2u> t5(&graph, "Lup");
    Traveler<3u> t6(&graph, "Lop");
    for (int i = 0; i < 25; i++) {
        t1.travel();
        t2.travel();
        t3.travel();
        t4.travel();
        t5.travel();
        t6.travel();
    }

    std::cout << "\nEverything's fine.\n";
    return 0;
}
