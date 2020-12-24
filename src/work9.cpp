#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

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

void SplitString(const string& s, vector<string>& v, const string& c) {
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (string::npos != pos2) {
        if (pos2 != pos1) v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length()) v.push_back(s.substr(pos1));
}  //�ָ��ı�����

struct Course {
    string id;           //�γ̱��
    string name;         //�γ�����
    int lesson;          //��ʱ
    int term;            //����ѧ�ڣ�0Ϊ����
    vector<string> pre;  //���޿γ�
    void input(string s);
    friend std::ostream& operator<<(std::ostream& output, const Course& D);
    bool operator==(const Course& v2) const { return (this->id == v2.id); };
    bool operator==(const string& v2) const { return (this->id == v2); };
    bool operator!=(const Course& v2) { return !(*this == v2); };
    bool operator!=(const string& v2) { return !(*this == v2); };
    bool operator<(const Course& v2) const { return (this->id < v2.id); };
};

void Course::input(string s) {
    vector<string> text;
    SplitString(s, text, " ");
    if (text.size() < 4) throw "Error: invalue input detected. ";
    if (!isNum(text[2]) || !isNum(text[3]))
        throw "Error: invalue input detected. ";
    this->id = text[0];
    this->name = text[1];
    this->lesson = (int)str2num(text[2]);
    this->term = (int)str2num(text[3]);
    for (int i = 4; i < text.size(); i++) pre.push_back(text[i]);
}

std::ostream& operator<<(std::ostream& output, const Course& D) {
    output << D.id << '\t' << D.name;
    for (int i = D.name.size() - 1; i < 23; i++) output << ' ';
    output << D.lesson << '\t' << D.term << '\t';
    for (auto&& i : D.pre) output << i << " ";
    output << '\n';
    return output;
}

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
        return (this->v1 == e2.v1 && this->v2 == e2.v2);
    };
    bool operator!=(const edge& e2) { return !(*this == e2); };
    bool operator<(const edge& e2) const { return (this->val < e2.val); };
    bool operator>(const edge& e2) const { return (this->val > e2.val); };
};

template <class T, class E>
class Graph {
   public:
    //������Ԫ����
    friend vector<vector<vertex<Course>>> Topological(Graph<Course, int> g);
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
    int NumEdges() const { return _edges.size(); }
    bool InGraph(T v);
    bool InGraph(vertex<T> v);
    bool InGraph(T v1, T v2);
    bool InGraph(vertex<T> v1, vertex<T> v2);
    bool InGraph(edge<T, E> edge);

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
        if (i != *it) v.push_back(i);
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
    _edges[{v1, v2}] = e;
};
template <class T, class E>
void Graph<T, E>::InsertEdge(T v1, T v2, E cost) {
    if (!InGraph(v1) || !InGraph(v2)) throw "Error: Vertex not found. ";
    if (InGraph(v1, v2)) throw "Error: Edge already in the graph. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    edge<T, E> e(*it1, *it2, cost);
    _edges[{*it1, *it2}] = e;
};
template <class T, class E>
void Graph<T, E>::InsertEdge(edge<T, E> edge) {
    if (InGraph(edge)) throw "Error: Edge already in the graph. ";
    _edges[{edge.v1, edge.v2}] = edge;
};

template <class T, class E>
void Graph<T, E>::RemoveEdge(vertex<T> v1, vertex<T> v2) {
    if (!InGraph(v1, v2)) throw "Error: Edge not found. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    auto ite1 = _edges.find({*it1, *it2});
    _edges.erase(ite1);
};
template <class T, class E>
void Graph<T, E>::RemoveEdge(T v1, T v2) {
    if (!InGraph(v1, v2)) throw "Error: Edge not found. ";
    auto it1 = find(_vertices.begin(), _vertices.end(), v1);
    auto it2 = find(_vertices.begin(), _vertices.end(), v2);
    auto ite1 = _edges.find({*it1, *it2});
    _edges.erase(ite1);
};
template <class T, class E>
void Graph<T, E>::RemoveEdge(edge<T, E> edge) {
    if (!InGraph(edge)) throw "Error: Edge not found. ";
    auto it1 = _edges.find({edge.v1, edge.v2});
    _edges.erase(it1);
};

template <class T, class E>
void Graph<T, E>::PrintGraph(ostream& os) {
    cout << "The Graph has " << NumVertices() << " vertices:" << endl;
    for (auto&& v : _vertices) cout << v.val << ' ';
    cout << endl;
    for (auto&& i : _vertices) {
        for (auto&& j : _vertices) {
            if (i == j) continue;
            auto it = _edges.find({i, j});
            if (it == _edges.end()) continue;
            os << i.val << "-(" << _edges[{i, j}].val << ")->" << j.val
               << "    ";
        }
    }
    os << endl;
}

vector<vector<vertex<Course>>> Topological(Graph<Course, int> g) {
    Graph<Course, int> a = g;  //����ͼ
    vector<vector<vertex<Course>>>
        v;  //�ö�ά�����γ̱���ά�ֱ����ѧ�ڣ��γ�
    int t = 1;  //��ǰѧ��
    while (a.NumVertices() != 0) {
        vector<vertex<Course>> temp;  //�洢��ǰ����Ϊ0���޶���ѧ�ڿ��εĿγ�
        for (auto&& j : a._vertices) {
            if (j.val.term != 0 && j.val.term != t)
                continue;  //����ÿγ����޶�ѧ�ڿγ��Ҳ��Ǹ�ѧ�ڵĿγ������
            bool bflag = false;
            for (auto&& i : a._vertices) {
                if (i == j) continue;
                auto it = a._edges.find({i, j});
                if (it == a._edges.end()) continue;  //��������ڸñ�
                bflag = true;  //������ڸñߣ���j����Ȳ�Ϊ0������
                break;
            }
            if (bflag) continue;
            temp.push_back(j);  // j�����Ϊ0�����
        }
        int time = 0;
        vector<vertex<Course>>
            ntemp;  //�洢�ڲ���ѧʱ��ǰ���µ�ǰ����Ϊ0���޶���ѧ�ڿ��εĿγ�
        for (auto&& i : temp) {
            if (i.val.term == 0) {  //�����޶��γ�
                time += i.val.lesson;
                if (time > 20) continue;  //ѧʱ���˾��ϵ��¸�ѧ����ѧ
                ntemp.push_back(i);
                a.DelVertex(i);
            } else {  //���޶��γ̣�����ѧʱ����Ҳ��ѧ
                ntemp.push_back(i);
                a.DelVertex(i);
            }
        }
        v.push_back(ntemp);  //����ѧ�ڿγ�����
        t++;                 //ѧ����++
    }
    return v;
}

void opening() {
    cout << "Course Scheduling Software" << endl;
    return;
}
void reading(Graph<Course, int>& g) {
    cout << "Enter the location of the timetable file." << endl;
    string temp;
    ifstream in;
    while (true) {
        cin >> temp;
        in = ifstream(temp);
        if (in) break;                                       // �и��ļ�
        cout << "No such file, please try again. " << endl;  // �޸��ļ�
    }
    string line;
    while (getline(in, line)) {  // line�в�����ÿ�еĻ��з�
        map<string, Course>
            course;  //ʹ��map�ݴ�ÿ�ſγ�id��γ̵Ķ�Ӧ��ϵ�Ա㻭ͼ
        if (line.size() == 0) continue;
        Course c;
        c.input(line);
        cout << c;
        course[c.id] = c;
        g.InsertVertex(c);
        if (c.pre.size() != 0)
            for (auto&& i : c.pre) {
                auto it = course.find(i);
                if (it != course.end()) g.InsertEdge(course[i], c, 0);
            }
    }
}

void scheduling(Graph<Course, int>& g) {
    cout << "Enter the path and name to save the timetable." << endl;
    string temp;
    cin >> temp;
    ofstream out(temp);
    auto v = Topological(g);
    /*
     cout << endl << endl;
     for (auto&& i : v) {
             for (auto&& j : i) cout << j.val;
             cout << endl;
     }
    */
    //��ʼ����ά������Ϊ�γ̱�������ά�ֱ��ʾѧ�ڡ����ڡ��ڼ��ڿ�
    vector<vector<vector<string>>> schedule(
        v.size(), vector<vector<string>>(5, vector<string>(4, "��")));
    for (int i = 0; i < v.size(); i++) {  //��ÿ��ѧ��
        for (auto&& k : v[i]) {           //��ÿ��ѧ�ڵ�ÿ�ſγ�
            for (int j = 0; j < 2; j++) {  //�����еĿ�ʱö�ٺ���Ŀ�ʱ����
                if (k.val.lesson == 6) {
                    if (schedule[i][j][0] == "��" &&
                        schedule[i][j + 2][2] == "��") {
                        schedule[i][j][0] = k.val.name;
                        schedule[i][j + 2][2] = k.val.name;
                        break;
                    } else if (schedule[i][j][2] == "��" &&
                               schedule[i][j + 3][0] == "��") {
                        schedule[i][j][2] = k.val.name;
                        schedule[i][j + 3][0] = k.val.name;
                        break;
                    }
                } else if (k.val.lesson == 5) {
                    if (schedule[i][j][0] == "��" &&
                        schedule[i][j + 2][3] == "��") {
                        schedule[i][j][0] = k.val.name;
                        schedule[i][j + 2][3] = k.val.name;
                        break;
                    } else if (schedule[i][j][1] == "��" &&
                               schedule[i][j + 2][2] == "��") {
                        schedule[i][j][1] = k.val.name;
                        schedule[i][j + 2][2] = k.val.name;
                        break;
                    } else if (schedule[i][j][2] == "��" &&
                               schedule[i][j + 3][1] == "��") {
                        schedule[i][j][2] = k.val.name;
                        schedule[i][j + 3][1] = k.val.name;
                        break;
                    } else if (schedule[i][j][3] == "��" &&
                               schedule[i][j + 3][0] == "��") {
                        schedule[i][j][3] = k.val.name;
                        schedule[i][j + 3][0] = k.val.name;
                        break;
                    }
                } else if (k.val.lesson == 4) {
                    if (schedule[i][j][1] == "��" &&
                        schedule[i][j + 2][3] == "��") {
                        schedule[i][j][1] = k.val.name;
                        schedule[i][j + 2][3] = k.val.name;
                        break;
                    } else if (schedule[i][j][3] == "��" &&
                               schedule[i][j + 3][1] == "��") {
                        schedule[i][j][3] = k.val.name;
                        schedule[i][j + 3][1] = k.val.name;
                        break;
                    }
                } else if (k.val.lesson == 3) {
                    if (schedule[i][j][0] == "��") {
                        schedule[i][j][0] = k.val.name;
                        break;
                    } else if (schedule[i][j][2] == "��") {
                        schedule[i][j][2] = k.val.name;
                        break;
                    }
                } else if (k.val.lesson == 2) {
                    if (schedule[i][j][1] == "��") {
                        schedule[i][j][1] = k.val.name;
                        break;
                    } else if (schedule[i][j][3] == "��") {
                        schedule[i][j][3] = k.val.name;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < schedule.size(); i++) {
        cout << endl
             << "��" << i + 1 << "ѧ�ڿα�" << endl
             << "����һ              ���ڶ�              ������              "
                "������              ������"
             << endl;
        out << endl
            << "��" << i + 1 << "ѧ�ڿα�" << endl
            << "����һ              ���ڶ�              ������              "
               "������              ������"
            << endl;
        for (int k = 0; k < 4; k++) {
            if (k == 0 || k == 2)
                for (int num = 0; num < 3; num++) {
                    for (int j = 0; j < 5; j++) {
                        cout << schedule[i][j][k], out << schedule[i][j][k];
                        for (int u = schedule[i][j][k].size() - 1; u < 19; u++)
                            cout << ' ', out << ' ';
                    }
                    cout << endl, out << endl;
                }
            else
                for (int num = 0; num < 2; num++) {
                    for (int j = 0; j < 5; j++) {
                        cout << schedule[i][j][k], out << schedule[i][j][k];
                        for (int u = schedule[i][j][k].size() - 1; u < 19; u++)
                            cout << ' ', out << ' ';
                    }
                    cout << endl, out << endl;
                }
        }
    }
}

int main() {
    opening();
    Graph<Course, int> g;
    reading(g);
    scheduling(g);
    return 0;
}