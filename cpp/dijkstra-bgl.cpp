///
/// \file dijkstra-bgl.h
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief Implementation dijkstra with Boost Graph Library
/// \details BGL : https://www.boost.org/doc/libs/1_46_1/libs/graph/doc/adjacency_list.html
///          Dijkstra :https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra
///

#include <cstdlib>
#include <iostream>

#include <boost/graph/graph_utility.hpp> // print_graph
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>

using namespace std;
using namespace boost;


//-----------------------------------------------------------------------------
// Définitions des types pour le graphe
//-----------------------------------------------------------------------------

///
/// \brief Définition du type pour les noeuds graphe
///
struct VertexProperties {
    float d;
    int predecessor;
    VertexProperties() : d(std::numeric_limits<float>::infinity()), predecessor(-1) {}
    VertexProperties(float d, int predecessor) : d(d), predecessor(-1) {}
};

///
/// \brief Définition du type pour les liens graphe
///
struct EdgeProperties {
    int weight;
    EdgeProperties() : weight(0) { }
    EdgeProperties(int weight) : weight(weight) { }
};

struct EdgeInfoPropertyTag {
    typedef edge_property_tag kind;
    static std::size_t const num; // ???
};

std::size_t const EdgeInfoPropertyTag::num = (std::size_t)&EdgeInfoPropertyTag::num;
typedef property<EdgeInfoPropertyTag, EdgeProperties> edge_info_prop_type;

///
/// \brief Type de graphe
///
typedef adjacency_list<
    boost::vecS, boost::vecS, boost::undirectedS,
    VertexProperties,                               // Type vertex
    edge_info_prop_type                             // Type edge
> Graph;

//-----------------------------------------------------------------------------
// En plus
//-----------------------------------------------------------------------------
void test(Graph &g) {
    // Visiter les voisins du sommet 0
    auto neighbours = boost::adjacent_vertices(0, g);
    
    for (auto vd : make_iterator_range(neighbours))
        std::cout << "0 has adjacent vertex " << vd << "\n";

    g[0].d = 42;
    cout<<g[0].d<<endl;

    //cout<<edge(0,2,g).second<<endl;

    EdgeProperties p = get(EdgeInfoPropertyTag(), g, edge(0,2,g).first);
    std::cout << "weight: " << p.weight << std::endl;

    get(EdgeInfoPropertyTag(), g, edge(0,2,g).first).weight = 33;
    std::cout << "weight: " << get(EdgeInfoPropertyTag(), g, edge(0,2,g).first).weight << std::endl;
    
    // Nombre de sommets
    cout<<num_vertices(g)<<endl;
    cout<<num_edges(g)<<endl;

    // Affiche le graphe
    print_graph(g);

}
//-----------------------------------------------------------------------------
// dijkstra
//-----------------------------------------------------------------------------
///
/// \brief Crée une instance de graphe
///
/// \param g : graphe
///
void createInstanceGraph(Graph &g) {
    add_vertex(VertexProperties(std::numeric_limits<float>::infinity(), -1), g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);
    add_vertex(g);

    add_edge(0, 1, EdgeProperties(7), g);
    add_edge(0, 2, EdgeProperties(9), g);
    add_edge(0, 5, EdgeProperties(14), g);
    add_edge(1, 3, EdgeProperties(15), g);
    add_edge(1, 2, EdgeProperties(10), g);
    add_edge(2, 3, EdgeProperties(11), g);
    add_edge(2, 5, EdgeProperties(2), g);
    add_edge(4, 3, EdgeProperties(6), g);
    add_edge(5, 4, EdgeProperties(9), g);
}

///
/// \brief donne le plus petit élément de la liste l
///
/// \param g : graphe
/// \param l : liste de noeud
///
/// \return le plus petit élément de la liste l
///
unsigned int extrait_min(Graph const &g, list<unsigned int> &l) {
    list<unsigned int>::iterator iter = min_element(l.begin(), l.end());
    l.erase(iter);
    return *iter;
}

///
/// \brief *
///
/// \param u : *
/// \param v : *
///
void relacher(Graph &g, unsigned int u, unsigned int v) {
    EdgeProperties p = get(EdgeInfoPropertyTag(), g, edge(u, v, g).first);
    //std::cout << "weight: " << p.weight << std::endl;

    if ((g[u].d + p.weight) < g[v].d ) {
        g[v].d = g[u].d + p.weight;
        g[v].predecessor = u;
    }
}

///
/// \brief algo de dijkstra
///
/// \param g : graphe
///
/// \return le plus court chemin
///
list<unsigned int> dijkstra(Graph &g) {
    g[0].d = 0;             // Sommet de début
    list<unsigned int> F;   // liste des sommets à visiter
    list<unsigned int> E;   // liste des sommets avec longueurs finales de plus court chemin à partir de l’origine s
    for (unsigned int i = 0 ; i < num_vertices(g) ; i++)
        F.push_back(i);

    while (!F.empty()) {
        unsigned int u = extrait_min(g, F);
        E.push_back(u);

        // Visite les voisins du sommet u
        auto neighbours = boost::adjacent_vertices(u, g);
        for (auto v : make_iterator_range(neighbours)) {
            //std::cout << "0 has adjacent vertex " << v << "\n";
            relacher(g, u, v);
        }
    }


    // Lecture du résultat
    list<unsigned int> resultat;
    int x = num_vertices(g) - 1;
    resultat.push_back(x);
    while (0 < x) {
        x = g[x].predecessor;
        resultat.push_back(x);
    }

    return resultat;
}

int main() {
    // Crée un graphe g
    Graph g;

    // Crée un instance de graphe
    createInstanceGraph(g);

    // Affiche le graphe
    cout<<"[+] liste d'adjacence :"<<endl;
    print_graph(g);

    // Appel l'algo dijkstra
    list<unsigned int> r = dijkstra(g);

    // Affiche le plus court chemin
    cout<<endl<<"[+] le plus court chemin :"<<endl;
    for (auto v : r)
        std::cout << v<<" ";
    cout<<endl;

    return EXIT_SUCCESS;
}