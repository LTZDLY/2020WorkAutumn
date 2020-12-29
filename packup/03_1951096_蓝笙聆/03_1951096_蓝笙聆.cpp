#include <iostream>
#include <string>
#include <vector>

class Maze {
   private:
    int _step[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};  //枚举的每一个方向
    std::vector<std::vector<std::vector<int>>> _maps;  //保存多个地图
    std::vector<std::vector<std::pair<int, int>>> _dir_all;  //保存多个路径
    std::vector<std::pair<int, int>> _dirv;                  //一个路径
    int _map = 0;      //选择的第几个地图
    int _row = 0;      //行
    int _start_x = 1;  //起点横坐标
    int _start_y = 1;  //起点纵坐标
    int _end_x = 0;    //终点横坐标
    int _end_y = 0;    //终点纵坐标
    int _col = 0;      //列

   public:
    Maze();
    std::vector<std::vector<int>> Copy();       //拷贝一份棋盘
    void Dfs(int now_x, int now_y, int depth);  //深度优先搜索主体
    void PrintAns(std::ostream& os);            //输出路径与地图
    void PrintMaps(std::ostream& os);           //输出所有的原始地图
    void SelectMap(int id);                     //选择地图
    int GetStartX() const { return this->_start_x; }    //返回起点横坐标
    int GetStartY() const { return this->_start_y; }    //返回起点纵坐标
    int GetMaps() const { return this->_maps.size(); }  //返回地图总数
};
Maze::Maze() {
    _maps.push_back({{-1, -1, -1, -1, -1},
                     {-1, 0, 0, 0, -1},
                     {-1, 0, 0, 0, -1},
                     {-1, 0, 0, 0, -1},
                     {-1, -1, -1, -1, -1}});
    _maps.push_back({{
                         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     },
                     {
                         -1, 0, 0,  0, 0,  0, 0, 0, 0, 0, -1, 0,
                         -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, -1,
                     },
                     {
                         -1, 0, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0,
                         -1, 0, -1, 0,  -1, 0, -1, 0, -1, -1, -1,
                     },
                     {
                         -1, 0, 0,  0, -1, 0, -1, 0, 0, 0, 0,  0,
                         0,  0, -1, 0, 0,  0, -1, 0, 0, 0, -1,
                     },
                     {
                         -1, 0,  -1, -1, -1, -1, -1, -1, -1, 0, -1, -1,
                         -1, -1, -1, 0,  -1, 0,  -1, 0,  -1, 0, -1,
                     },
                     {
                         -1, 0, 0,  0, 0,  0, 0,  0, -1, 0, -1, 0,
                         0,  0, -1, 0, -1, 0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, -1, -1, 0, -1, 0,  -1, 0,  -1, 0,  -1, 0,
                         -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1,
                     },
                     {
                         -1, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0,  0,
                         0,  0, 0, 0, 0,  0, 0,  0, 0,  0, -1,
                     },
                     {
                         -1, -1, -1, 0, -1, 0,  -1, 0,  -1, -1, -1, -1,
                         -1, 0,  -1, 0, -1, -1, -1, -1, -1, 0,  -1,
                     },
                     {
                         -1, 0, 0,  0, -1, 0, -1, 0, 0,  0, 0,  0,
                         -1, 0, -1, 0, 0,  0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, 0,  -1, 0, -1, -1, -1, -1, -1, 0,  -1, -1,
                         -1, -1, -1, 0, -1, 0,  -1, 0,  -1, -1, -1,
                     },
                     {
                         -1, 0, -1, 0, 0,  0, 0,  0, -1, 0, 0,  0,
                         0,  0, -1, 0, -1, 0, -1, 0, 0,  0, -1,
                     },
                     {
                         -1, -1, -1, 0, -1, 0, -1, 0, -1, -1, -1, -1,
                         -1, 0,  -1, 0, -1, 0, -1, 0, -1, -1, -1,
                     },
                     {
                         -1, 0, 0,  0, -1, 0, -1, 0, 0, 0, -1, 0,
                         0,  0, -1, 0, -1, 0, 0,  0, 0, 0, -1,
                     },
                     {
                         -1, 0, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0,
                         -1, 0, -1, -1, -1, 0, -1, 0,  -1, -1, -1,
                     },
                     {
                         -1, 0, 0,  0, -1, 0, -1, 0, -1, 0, 0,  0,
                         -1, 0, -1, 0, 0,  0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, 0,  -1, 0, -1, 0, -1, 0, -1, 0, -1, 0,
                         -1, -1, -1, 0, -1, 0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, 0, -1, 0, -1, 0, 0,  0, -1, 0, -1, 0,
                         -1, 0, 0,  0, -1, 0, -1, 0, 0,  0, -1,
                     },
                     {
                         -1, -1, -1, -1, -1, 0, -1, 0, -1, 0, -1, -1,
                         -1, -1, -1, -1, -1, 0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0,  0,
                         -1, 0, 0, 0, 0, 0, -1, 0, -1, 0, -1,
                     },
                     {
                         -1, -1, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0,
                         -1, 0,  -1, -1, -1, 0, -1, 0, -1, -1, -1,
                     },
                     {
                         -1, 0, 0, 0, 0,  0, -1, 0, -1, 0, 0,  0,
                         -1, 0, 0, 0, -1, 0, -1, 0, 0,  0, -1,
                     },
                     {
                         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                         -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                     }});
    _maps.push_back(
        {{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
          -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
         {-1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1},
         {-1, -1, -1, 0,  -1, 0,  -1, -1, -1, 0, -1,
          0,  -1, -1, -1, 0,  -1, -1, -1, 0,  -1},
         {-1, 0, 0, 0, -1, 0, -1, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, 0, -1},
         {-1, 0,  -1, -1, -1, 0,  -1, 0,  -1, 0, -1,
          0,  -1, -1, -1, 0,  -1, 0,  -1, 0,  -1},
         {-1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1},
         {-1, -1, -1, -1, -1, 0,  -1, 0,  -1, -1, -1,
          -1, -1, -1, -1, 0,  -1, -1, -1, 0,  -1},
         {-1, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1},
         {-1, -1, -1, 0,  -1, -1, -1, 0,  -1, -1, -1,
          0,  -1, -1, -1, 0,  -1, -1, -1, 0,  -1},
         {-1, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1, 0, -1},
         {-1, -1, -1, -1, -1, 0,  -1, -1, -1, 0, -1,
          -1, -1, 0,  -1, 0,  -1, -1, -1, 0,  -1},
         {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
         {-1, -1, -1, 0,  -1, -1, -1, 0,  -1, 0, -1,
          -1, -1, 0,  -1, -1, -1, -1, -1, 0,  -1},
         {-1, 0,  0, 0,  0, 0,  -1, 0, -1, 0, -1,
          0,  -1, 0, -1, 0, -1, 0,  0, 0,  -1},
         {-1, 0,  -1, -1, -1, -1, -1, -1, -1, 0, -1,
          0,  -1, -1, -1, 0,  -1, -1, -1, 0,  -1},
         {-1, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, -1},
         {-1, 0,  -1, -1, -1, 0,  -1, -1, -1, -1, -1,
          0,  -1, 0,  -1, -1, -1, -1, -1, 0,  -1},
         {-1, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, -1},
         {-1, 0,  -1, -1, -1, 0,  -1, 0,  -1, -1, -1,
          0,  -1, 0,  -1, 0,  -1, 0,  -1, 0,  -1},
         {-1, 0, -1, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, -1},
         {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
          -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}});
    _dirv.push_back({this->_start_x, this->_start_y});
}
void Maze::SelectMap(int id) {
    if (id < 0 || id > this->_maps.size()) throw "Error: ";
    this->_map = id;
    this->_row = this->_maps[id].size();
    this->_col = this->_maps[id][0].size();
    int _start_x = 1;
    int _start_y = 1;
    this->_end_x = this->_col - 2;
    this->_end_y = this->_row - 2;
}

std::vector<std::vector<int>> Maze::Copy() {
    std::vector<std::vector<int>> copy(_col, std::vector<int>(_row));
    for (int i = 0; i < _col; i++)
        for (int j = 0; j < _row; j++) copy[i][j] = _maps[_map][i][j];
    return copy;
}
void Maze::Dfs(int now_x, int now_y, int depth) {
    if (now_x == _end_x && now_y == _end_y) {  //如果到达终点
        std::vector<std::pair<int, int>> ans;
        for (int i = 0; i < depth; i++) {
            ans.push_back(_dirv[i]);
        }
        _dir_all.push_back(ans);  //将路径保存并结束该层搜索
        return;
    }
    _maps[_map][now_x][now_y] = 1;  //标记该点已被访问
    for (int i = 0; i < 4; i++) {
        int next_x = now_x + _step[i][0];
        int next_y = now_y + _step[i][1];  //枚举4个方向
        if (_maps[_map][next_x][next_y] != 0)
            continue;                  //若该点不可到达则下一个方向
        if (_dirv.size() < depth + 1)  //将该点坐标暂存
            _dirv.push_back({next_x, next_y});
        else
            _dirv[depth] = {next_x, next_y};
        Dfs(next_x, next_y, depth + 1);  //传入该点坐标递归进行搜索
    }
    _maps[_map][now_x][now_y] = 0;  //取消该点标记
}

void Maze::PrintMaps(std::ostream& os) {
    for (int k = 0; k < _maps.size(); k++) {
        os << k + 1 << ": " << std::endl;
        std::string str;
        for (int i = 0; i < _maps[k].size(); i++) {
            for (int j = 0; j < _maps[k][0].size(); j++) {
                switch (_maps[k][i][j]) {
                    case -1:
                        str += "＃";
                        break;
                    case 0:
                        str += "　";
                        break;
                }
            }
            str += "\n";
        }
        os << str;
    }
}

void Maze::PrintAns(std::ostream& os) {
    std::cout << "There is " << _dir_all.size() << " paths to the end."
              << std::endl;
    for (int i = 0; i < _dir_all.size(); i++) {
        int step = 0;
        auto copy = Copy();
        for (int j = 0; j < _dir_all[i].size(); j++) {
            copy[_dir_all[i][j].first][_dir_all[i][j].second] = step % 10 + 1;
            step++;
        }
        std::string str;
        for (int k = 0; k < _col; k++) {
            for (int j = 0; j < _row; j++) {
                switch (copy[k][j]) {
                    case -1:
                        str += "＃";
                        break;
                    case 0:
                        str += "　";
                        break;
                    case 1:
                        str += "１";
                        break;
                    case 2:
                        str += "２";
                        break;
                    case 3:
                        str += "３";
                        break;
                    case 4:
                        str += "４";
                        break;
                    case 5:
                        str += "５";
                        break;
                    case 6:
                        str += "６";
                        break;
                    case 7:
                        str += "７";
                        break;
                    case 8:
                        str += "８";
                        break;
                    case 9:
                        str += "９";
                        break;
                    case 10:
                        str += "０";
                        break;
                }
            }
            str += '\n';
        }
        os << str;
        os << "(" << _dir_all[i][0].first << ", " << _dir_all[i][0].second
           << ")";
        for (int j = 1; j < _dir_all[i].size(); j++)
            os << " ---> (" << _dir_all[i][j].first << ", "
               << _dir_all[i][j].second << ")";
        os << std::endl << std::endl;
    }
}

void opening(Maze& m) {
    std::cout << "Maze Game" << std::endl
              << "Automatically generate mazes first." << std::endl
              << "Here are " << m.GetMaps() << " maps to choose from"
              << std::endl;
    m.PrintMaps(std::cout);
    std::cout << std::endl;
    std::cout << "Now select a map for testing by enter its id.";
    int temp = 0;
    while (true) {
        std::cin >> temp;
        try {
            m.SelectMap(temp - 1);
            break;
        } catch (const char* e) {
            std::cerr << e << std::endl;
        }
    }
    return;
}
void solution(Maze& m) { m.Dfs(m.GetStartX(), m.GetStartY(), 1); }

void ending(Maze& m) {
    m.PrintAns(std::cout);  //对地图和走过的路径进行打印
}

bool loop(){
    Maze m;
    opening(m);
    solution(m);
    ending(m);

    std::cout << "Again? (y for yes, n for no)";
    char c;
    std::cin >> c;
    if (c == 'y')
        return true;
    else
        return false;
}

int main() {
    while (loop())
        ;
    std::cout << "Thanks for using it. See you next time! " << std::endl;
    return 0;
}