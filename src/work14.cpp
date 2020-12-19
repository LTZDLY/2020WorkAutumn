#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

template <class T>
T unionFind(map<T, T> m, T x) {
    if (m[x] == x)
        return x;
    else
        m[x] = unionFind(m, m[x]);
    return m[x];
}
/*
template <class T>
bool checkUnionFind(map<T, T> m)
{//若图中所有点不在同一集合，则图不连通，不存在最小生成树 auto it = m.begin();
    T ans = unionFind(m, it->first);
    for (it = m.begin(); it != m.end(); it++) {
        if (unionFind(m, it->second) != ans) return false;
    }
    return true;
}
*/
template <class T>
struct vertex {
    T val;
    vertex(const T& val) : val(val){};
    vertex() : val(){};
    bool operator==(const vertex& v2) const { return (this->val == v2.val); };
    bool operator==(const T& v2) const { return (this->val == v2); };
    bool operator!=(const vertex& v2) { return !(*this == v2); };
    bool operator!=(const T& v2) { return !(*this == v2); };
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
    bool operator!=(const edge& e2) { return !(*this == e2); };
    bool operator<(const edge& e2) const { return (this->val < e2.val); };
    bool operator>(const edge& e2) const { return (this->val > e2.val); };
};

template <class T, class E>
class Graph {
   public:
    void InsertVertex(vertex<T>& v);
    void InsertVertex(const T val);
    void DelVertex(vertex<T>& v);
    void DelVertex(const T val);
    void InsertEdge(vertex<T> v1, vertex<T> v2, E cost);
    void InsertEdge(T v1, T v2, E cost);
    void InsertEdge(edge<T, E> edge);
    void RemoveEdge(vertex<T> v1, vertex<T> v2);
    void RemoveEdge(T v1, T v2);
    void RemoveEdge(edge<T, E> edge);
    void PrintGraph(ostream& os);
    int NumVertices() const { return _vertices.size(); };
    int NumEdges() const { return _edges.size() / 2; }
    bool InGraph(T v);
    bool InGraph(vertex<T> v);
    bool InGraph(T v1, T v2);
    bool InGraph(vertex<T> v1, vertex<T> v2);
    bool InGraph(edge<T, E> edge);
    // bool HasMst();
    Graph<T, E> Prim(vertex<T> v);
    Graph<T, E> Kruskal();

   private:
    vector<vertex<T>> _vertices;
    map<pair<vertex<T>, vertex<T>>, edge<T, E>> _edges;
};

template <class T, class E>
bool Graph<T, E>::InGraph(T v) {
    auto it = find(_vertices.begin(), _vertices.end(), v);
    if (it == _vertices.end()) return false;
    return true;
};
template <class T, class E>
bool Graph<T, E>::InGraph(vertex<T> v) {
    auto it = find(_vertices.begin(), _vertices.end(), v);
    if (it == _vertices.end()) return false;
    return true;
};
template <class T, class E>
bool Graph<T, E>::InGraph(T v1, T v2) {
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    if (it1 != _vertices.end() && it2 != _vertices.end()) {
        auto ite = _edges.find({*it1, *it2});
        if (ite != _edges.end()) return true;
    }
    return false;
};
template <class T, class E>
bool Graph<T, E>::InGraph(vertex<T> v1, vertex<T> v2) {
    auto ite = _edges.find({v1, v2});
    if (ite == _edges.end()) return false;
    return true;
};
template <class T, class E>
bool Graph<T, E>::InGraph(edge<T, E> edge) {
    auto ite = _edges.find({edge.v1, edge.v2});
    if (ite == _edges.end()) return false;
    return true;
};
template <class T, class E>
void Graph<T, E>::InsertVertex(vertex<T>& v) {
    if (InGraph(v)) throw "Error: Vertex already in the graph. ";
    auto it = find(_vertices.begin(), _vertices.end(), v);
    _vertices.push_back(v);
};
template <class T, class E>
void Graph<T, E>::InsertVertex(const T val) {
    if (InGraph(val)) throw "Error: Vertex already in the graph. ";
    vertex<T> vex(val);
    auto it = find(_vertices.begin(), _vertices.end(), vex);
    _vertices.push_back(vex);
};

template <class T, class E>
void Graph<T, E>::DelVertex(vertex<T>& vex) {
    if (!InGraph(vex)) throw "Error: Vertex not found. ";
    auto it = find(_vertices.begin(), _vertices.end(), vex);
    for (auto&& i : _vertices) {
        if (InGraph(vex, i)) RemoveEdge(vex, i);
    }
    vector<vertex<T>> v;
    for (auto&& i : this->_vertices)
        if (i != it) v.push_back(i);
    this->_vertices = v;
};
template <class T, class E>
void Graph<T, E>::DelVertex(const T val) {
    if (!InGraph(val)) throw "Error: Vertex not found. ";
    vertex<T> vex(val);
    auto it = find(_vertices.begin(), _vertices.end(), vex);
    for (auto&& i : _vertices) {
        if (InGraph(vex, i)) RemoveEdge(vex, i);
    }
    vector<vertex<T>> v;
    for (auto&& i : _vertices)
        if (i != *it) v.push_back(i);
    this->_vertices = v;
};

template <class T, class E>
void Graph<T, E>::InsertEdge(vertex<T> v1, vertex<T> v2, E cost) {
    if (!InGraph(v1) || !InGraph(v2)) throw "Error: Vertex not found. ";
    if (InGraph(v1, v2)) throw "Error: Edge already in the graph. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    edge<T, E> e(v1, v2, cost);
    auto ite = _edges.find({*it1, *it2});
    _edges[{v1, v2}] = e;
    _edges[{v2, v1}] = e;
};
template <class T, class E>
void Graph<T, E>::InsertEdge(T v1, T v2, E cost) {
    if (!InGraph(v1) || !InGraph(v2)) throw "Error: Vertex not found. ";
    if (InGraph(v1, v2)) throw "Error: Edge already in the graph. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    edge<T, E> e(*it1, *it2, cost);
    auto ite = _edges.find({*it1, *it2});
    _edges[{*it1, *it2}] = e;
    _edges[{*it2, *it1}] = e;
};
template <class T, class E>
void Graph<T, E>::InsertEdge(edge<T, E> edge) {
    if (InGraph(edge)) throw "Error: Edge already in the graph. ";
    auto it = _edges.find({edge.v1, edge.v2});
    _edges[{edge.v1, edge.v2}] = edge;
    _edges[{edge.v2, edge.v1}] = edge;
};

template <class T, class E>
void Graph<T, E>::RemoveEdge(vertex<T> v1, vertex<T> v2) {
    if (!InGraph(v1, v2)) throw "Error: Edge not found. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    auto ite1 = _edges.find({*it1, *it2});
    _edges.erase(ite1);
    auto ite2 = _edges.find({*it2, *it1});
    _edges.erase(ite2);
};
template <class T, class E>
void Graph<T, E>::RemoveEdge(T v1, T v2) {
    if (!InGraph(v1, v2)) throw "Error: Edge not found. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    auto ite1 = _edges.find({*it1, *it2});
    _edges.erase(ite1);
    auto ite2 = _edges.find({*it2, *it1});
    _edges.erase(ite2);
};
template <class T, class E>
void Graph<T, E>::RemoveEdge(edge<T, E> edge) {
    if (!InGraph(edge)) throw "Error: Edge not found. ";
    auto it1 = _edges.find({edge.v1, edge.v2});
    _edges.erase(it1);
    auto it2 = _edges.find({edge.v2, edge.v1});
    _edges.erase(it2);
};

template <class T, class E>
void Graph<T, E>::PrintGraph(ostream& os) {
    cout << "The Graph has " << NumVertices() << " vertices:" << endl;
    for (auto&& v : _vertices) cout << v.val << ' ';
    cout << endl;
    vector<edge<T, E>> e;
    for (auto&& i : _vertices) {
        for (auto&& j : _vertices) {
            if (i == j) continue;
            auto it = _edges.find({i, j});
            if (it == _edges.end()) continue;
            bool cflag = false;
            for (int k = 0; k < e.size(); k++)
                if (e[k] == _edges[{i, j}]) {
                    cflag = true;
                    break;
                }
            if (cflag) continue;
            os << i.val << "<-(" << _edges[{i, j}].val << ")->" << j.val
               << "    ";
            e.push_back(_edges[{i, j}]);
        }
    }
    os << endl;
}

template <class T, class E>
Graph<T, E> Graph<T, E>::Prim(vertex<T> v) {
    auto it = find(this->_vertices.begin(), this->_vertices.end(), v);
    if (it == this->_vertices.end()) throw "Error: Vertex not found.";
    Graph<T, E> mst;
    mst.InsertVertex(v);
    while (mst.NumVertices() != this->NumVertices()) {
        E min = 999999;
        edge<T, E> emin;
        map<vertex<T>, vertex<T>> ufsets;
        for (auto&& i : this->_vertices) ufsets[i] = i;
        for (auto&& j : mst._vertices) {
            for (auto&& i : this->_vertices) {
                if (i == j) continue;
                auto ite = this->_edges.find({j, i});
                auto itg = mst._edges.find({j, i});
                if (ite == this->_edges.end()) continue;  //如果原图中没有这条边
                if (itg != mst._edges.end()) continue;  //如果生成树中已有这条边
                int temp1 = 1;
                int temp2 = 1;
                for (auto&& k : mst._vertices) {
                    if (k == this->_edges[{j, i}].v1) temp1++;
                    if (k == this->_edges[{j, i}].v2) temp2++;
                }
                if (temp1 > 1 && temp2 > 1) continue;
                auto temp = min;

                if (this->_edges[{j, i}].val < min)
                    min = this->_edges[{j, i}].val;
                if (temp != min) emin = this->_edges[{j, i}];
            }
        }
        if (!mst.InGraph(emin.v1)) mst.InsertVertex(emin.v1);
        if (!mst.InGraph(emin.v2)) mst.InsertVertex(emin.v2);
        mst.InsertEdge(emin);
    }
    if (mst.NumEdges() != this->NumVertices() - 1)
        throw "Error: The graph does not have a minimum spanning tree. ";
    return mst;
}

template <class T, class E>
Graph<T, E> Graph<T, E>::Kruskal() {
    Graph<T, E> mst;
    vector<edge<T, E>> e;
    for (auto&& i : _vertices) {
        for (auto&& j : _vertices) {
            if (i == j) continue;
            auto it = _edges.find({i, j});
            if (it == _edges.end()) continue;
            bool cflag = false;
            for (int k = 0; k < e.size(); k++)
                if (e[k] == _edges[{i, j}]) {
                    cflag = true;
                    break;
                }
            if (cflag) continue;
            e.push_back(_edges[{i, j}]);
        }
    }
    sort(e.begin(), e.end());

    map<vertex<T>, vertex<T>> ufsets;
    for (auto&& i : this->_vertices) ufsets[i] = i;
    for (auto&& i : e) {
        if (unionFind(ufsets, i.v1) == unionFind(ufsets, i.v2)) continue;
        ufsets[unionFind(ufsets, i.v1)] = unionFind(ufsets, i.v2);
        if (!mst.InGraph(i.v1)) mst.InsertVertex(i.v1);
        if (!mst.InGraph(i.v2)) mst.InsertVertex(i.v2);
        mst.InsertEdge(i);
    }
    if (mst.NumEdges() != this->NumVertices() - 1)
        throw "Error: The graph does not have a minimum spanning tree. ";
    return mst;
}
/*
template <class T, class E>
bool Graph<T, E>::HasMst() {
    cout << endl;
    vector<edge<T, E>> e;
    vector<vertex<T>> v;
    //
当且仅当图为连通图，即从图上的任意一点出发都具有到达另一任意点的路径时，图才具有最小生成树
    //
则随机选择一点作为起点进行搜索可到达的所有顶点，结束搜索后若仍具有不可到达的点则代表图不连通
    for (auto&& i : _vertices) {
        for (auto&& j : _vertices) {
            if (i == j) continue;
            auto it = _edges.find({i, j});
            if (it == _edges.end()) continue;
            bool cflag = false;
            for (int k = 0; k < e.size(); k++)
                if (e[k] == _edges[{i, j}]) {
                    cflag = true;
                    break;
                }
            if (cflag) continue;
            e.push_back(_edges[{i, j}]);
            if (find(v.begin(), v.end(), i) != v.end()) v.push_back(i);
            if (find(v.begin(), v.end(), j) != v.end()) v.push_back(j);
        }
    }
    for (auto&& i : _vertices)
        if (find(v.begin(), v.end(), i) != v.end()) return false;
    return true;
}
*/
double str2num(string s) {
    stringstream ss;
    double d = 0.0;
    ss << s;
    ss >> d;
    return d;
}
bool isNum(string str) {
    for (auto&& i : str)
        if (!isdigit(i)) return false;
    return true;
}
void opening() {
    cout << " Direct Communication Road Cost Simulation System " << endl
         << "==============================================================="
         << endl
         << " Please select the action to perform:" << endl
         << "1 --- Create vertex " << endl
         << "2 --- Add edge" << endl
         << "3 --- Remove vertex " << endl
         << "4 --- Delete edge " << endl
         << "5 --- Print Graph " << endl
         << "6 --- Minimum spanning tree generation using prim algorithm."
         << endl
         << "7 --- Minimum spanning tree generation using Kruskal algorithm."
         << endl
         << "8 --- Display minimum spanning tree " << endl
         << "9 --- Exit" << endl;
    return;
}
void addVertex(Graph<string, int>& g) {
    cout << "Please input the number of vertices:";
    int num = 0;
    while (true) {
        string temp;
        cin >> temp;
        if (!isNum(temp))
            cout << "Error: Invalid input detected. Please try again." << endl;
        else {
            num = str2num(temp);
            break;
        }
    }
    cout << "Please enter the name of vertices in turn.";
    for (int i = 0; i < num; i++) {
        string v1 = "";
        cin >> v1;
        g.InsertVertex(v1);
    }
}
void addEdge(Graph<string, int>& g) {
    cout << "Please input the number of edges: ";
    int num = 0;
    while (true) {
        string temp;
        cin >> temp;
        if (!isNum(temp))
            cout << "Error: Invalid input detected. Please try again." << endl;
        else {
            num = str2num(temp);
            break;
        }
    }
    for (int i = 0; i < num; i++) {
        cout << "Please enter two vertices and edge lengths.";
        string v2 = "";
        string v1 = "";
        int cost = 0;
        cin >> v1 >> v2 >> cost;
        g.InsertEdge(v1, v2, cost);
    }
}
void constructPrimMst(Graph<string, int>& g, Graph<string, int>& mst) {
    vertex<string> v;
    string p = "";
    cout << "Please enter the starting vertex: ";
    cin >> p;
    v = p;
    mst = g.Prim(v);
    cout << "This is the Prim minimum spanning tree: " << endl;
    mst.PrintGraph(cout);
}
void constructKruskalMst(Graph<string, int>& g, Graph<string, int>& mst) {
    mst = g.Kruskal();
    cout << "This is the Kruskal minimum spanning tree: " << endl;
    mst.PrintGraph(cout);
}
void delVex(Graph<string, int>& g) {
    string temps;
    cout << "Please input the vertex you want to delete. ";
    cin >> temps;
    g.DelVertex(temps);
}
void delEdge(Graph<string, int>& g) {
    cout << "Please input the edge you want to delete " << endl;
    string temp1;
    string temp2;
    cin >> temp1;
    cin >> temp2;
    g.RemoveEdge(temp1, temp2);
}
bool loop(Graph<string, int>& g, Graph<string, int>& mst) {
    cout << "\nPlease enter a command: ";
    char temp = '\0';
    cin >> temp;
    try {
        switch (temp) {
            case '1':
                // add vertices
                addVertex(g);
                return true;
            case '2':
                // add edges;
                addEdge(g);
                return true;
            case '3':
                // del vertex;
                delVex(g);
                return true;
            case '4':
                // del edge;
                delEdge(g);
                return true;
            case '5':
                // print graph
                g.PrintGraph(cout);
                return true;
            case '6':
                // Constructing minimum spanning tree;
                constructPrimMst(g, mst);
                return true;
            case '7':
                // Constructing minimum spanning tree;
                constructKruskalMst(g, mst);
                return true;
            default:
                return false;
        }
    } catch (const char* e) {
        std::cerr << e << '\n';
        return true;
    }
}

int main() {
    opening();
    Graph<string, int> g;
    Graph<string, int> mst;
    while (loop(g, mst))
        ;

    return 0;
}