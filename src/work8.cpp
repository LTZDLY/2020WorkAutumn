#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

template <class T>
struct vertex {
    T val;
    vertex(const T& val) : val(val){};
    vertex() : val(){};
    bool operator==(const vertex& v2) const { return (this->val == v2.val); };
    bool operator==(const T& v2) const { return (this->val == v2); };
    bool operator<(const vertex& v2) const { return (this->val < v2.val); };
    bool operator>(const vertex& v2) const { return (this->val > v2.val); };
    void operator=(const vertex& v2) { this->val = v2.val; };
    void operator=(const T& v2) { this->val = v2; };
};
template <class T, class E>
struct edge {
    E val;
    vertex<T> v1;
    vertex<T> v2;
    edge(const vertex<T> v1, const vertex<T> v2, const E val)
        : v1(v1), v2(v2), val(val){};
    edge() : v1(), v2(), val(){};
    bool operator==(const edge& e2) {
        return ((this->v1 == e2.v1 && this->v2 == e2.v2) ||
                (this->v1 == e2.v2 && this->v2 == e2.v1));
    };
    bool operator<(const edge& e2) const { return (this->val < e2.val); };
    bool operator>(const edge& e2) const { return (this->val > e2.val); };
};

template <class T, class E>
class Graph {
   public:
    void insertVertex(vertex<T>& v);
    void insertVertex(const T val);
    void insertEdge(vertex<T> v1, vertex<T> v2, E cost);
    void insertEdge(T v1, T v2, E cost);
    void insertEdge(edge<T, E> edge);
    void printGraph(ostream& os);
    bool inGraph(vertex<T> v);
    vector<vertex<T>> vertices;
    map<pair<vertex<T>, vertex<T>>, edge<T, E>> edges;
};

template <class T, class E>
bool Graph<T, E>::inGraph(vertex<T> v) {
    auto it = find(vertices.begin(), vertices.end(), v);
    if (it == vertices.end())
        return false;
    else
        return true;
};
template <class T, class E>
void Graph<T, E>::insertVertex(vertex<T>& v) {
    auto it = find(vertices.begin(), vertices.end(), v);
    if (it == vertices.end()) {
        vertices.push_back(v);
    } else
        throw "error";
};
template <class T, class E>
void Graph<T, E>::insertVertex(const T val) {
    vertex<T> vertex(val);
    auto it = find(vertices.begin(), vertices.end(), vertex);
    if (it == vertices.end()) {
        vertices.push_back(vertex);
    } else
        throw "error";
};
template <class T, class E>
void Graph<T, E>::insertEdge(vertex<T> v1, vertex<T> v2, E cost) {
    auto it1 = find(vertices.begin(), vertices.end(), v1);
    auto it2 = find(vertices.begin(), vertices.end(), v2);
    if (it1 != vertices.end() && it2 != vertices.end()) {
        edge<T, E> e(v1, v2, cost);
        auto ite = edges.find({*it1, *it2});
        if (ite == edges.end()) {
            edges[{v1, v2}] = e;
            edges[{v2, v1}] = e;
        } else
            throw "error";
    } else
        throw "error";
};
template <class T, class E>
void Graph<T, E>::insertEdge(T v1, T v2, E cost) {
    auto it1 = find(vertices.begin(), vertices.end(), v1);
    auto it2 = find(vertices.begin(), vertices.end(), v2);
    if (it1 != vertices.end() && it2 != vertices.end()) {
        edge<T, E> e(*it1, *it2, cost);
        auto ite = edges.find({*it1, *it2});
        if (ite == edges.end()) {
            edges[{*it1, *it2}] = e;
            edges[{*it2, *it1}] = e;
        } else
            throw "error";
    } else
        throw "error";
};

template <class T, class E>
void Graph<T, E>::insertEdge(edge<T, E> edge) {
    auto it = edges.find({edge.v1, edge.v2});
    if (it == edges.end()) {
        edges[{edge.v1, edge.v2}] = edge;
        edges[{edge.v2, edge.v1}] = edge;
    } else
        throw "error";
};
template <class T, class E>
void Graph<T, E>::printGraph(ostream& os) {
    vector<edge<T, E>> e;
    for (auto&& i : vertices) {
        for (auto&& j : vertices) {
            if (i == j) continue;
            auto it = edges.find({i, j});
            if (it == edges.end()) continue;
            bool cflag = false;
            for (int k = 0; k < e.size(); k++)
                if (e[k] == edges[{i, j}]) {
                    cflag = true;
                    break;
                }
            if (cflag) continue;
            os << i.val << "<-(" << edges[{i, j}].val << ")->" << j.val
               << "    ";
            e.push_back(edges[{i, j}]);
        }
    }
    os << endl;
}

template <class T, class E>
Graph<T, E> Prim(Graph<T, E> g, vertex<T> v) {
    auto it = find(g.vertices.begin(), g.vertices.end(), v);
    if (it == g.vertices.end()) throw "error";
    Graph<T, E> mst;
    mst.insertVertex(v);
    while (mst.vertices.size() != g.vertices.size()) {
        E min = 999999;
        edge<T, E> emin;
        for (auto&& j : mst.vertices) {
            for (auto&& i : g.vertices) {
                if (i == j) continue;
                auto ite = g.edges.find({j, i});
                auto itg = mst.edges.find({j, i});
                if (ite == g.edges.end()) continue;
                if (itg != mst.edges.end()) continue;
                bool bflag = false;
                int temp1 = 1;
                int temp2 = 1;
                for (auto&& k : mst.vertices) {
                    if (k == g.edges[{j, i}].v1) temp1++;
                    if (k == g.edges[{j, i}].v2) temp2++;
                }
                if (temp1 >= 2 && temp2 >= 2) continue;
                auto temp = min;

                if (g.edges[{j, i}].val < min) min = g.edges[{j, i}].val;
                if (temp != min) emin = g.edges[{j, i}];
            }
        }
        if (!mst.inGraph(emin.v1)) mst.insertVertex(emin.v1);
        if (!mst.inGraph(emin.v2)) mst.insertVertex(emin.v2);
        mst.insertEdge(emin);
    }
    return mst;
}

bool loop(Graph<string, int>& g, Graph<string, int>& mst) {
    cout << "\nPlease enter a command: ";
    char temp = '\0';
    cin >> temp;
    int num = 0;
    string p = "";
    string v1 = "";
    string v2 = "";
    vertex<string> v;
    int cost = 0;
    switch (temp) {
        case '1':
            // add vertices
            cout << "Please input the number of vertices:";
            cin >> num;
            cout << "Please enter the name of vertices in turn.";
            for (int i = 0; i < num; i++) {
                cin >> v1;
                g.insertVertex(v1);
            }
            return true;
        case '2':
            // add edges;
            cout << "Please input the number of edges: ";
            cin >> num;
            for (int i = 0; i < num; i++) {
                cout << "Please enter two vertices and edge lengths.";
                cin >> v1 >> v2 >> cost;
                g.insertEdge(v1, v2, cost);
            }
            return true;
        case '3':
            // Constructing minimum spanning tree;
            cout << "Please enter the starting vertex: ";
            cin >> p;
            v = p;
            mst = Prim(g, v);
            return true;
        case '4':
            // change name;
            cout << "This is the minimum spanning tree: " << endl;
            mst.printGraph(cout);
            return true;
        default:
            return false;
    }
}

int main() {
    cout << "**             Power grid cost simulation system             **"
         << endl
         << "==============================================================="
         << endl
         << "**           Please select the action to perform:            **"
         << endl
         << "**             1 --- Create vertex                           **"
         << endl
         << "**             2 --- Add edge                                **"
         << endl
         << "**             3 --- Constructing minimum spanning tree      **"
         << endl
         << "**             4 --- Display minimum spanning tree           **"
         << endl
         << "**             5 --- Exit                                    **"
         << endl;
    Graph<string, int> g;
    Graph<string, int> mst;
    while (loop(g, mst))
        ;

    return 0;
}