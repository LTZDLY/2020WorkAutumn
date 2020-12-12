#include <iostream>
#include <vector>

int map[23][23] = {{
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
                   }};
int step[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int dir[100][2] = {{}};
int flag = 0;
int len = 0;

void dfs(int now[2], int copymap[23][23], int depth) {
    if (now[0] == 21 && now[1] == 21) {
        flag = 1;
        len = depth;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int next[2];
        next[0] = now[0] + step[i][0];
        next[1] = now[1] + step[i][1];
        if (copymap[next[0]][next[1]] != 0) continue;
        copymap[next[0]][next[1]] = 1;
        dir[depth][0] = next[0];
        dir[depth][1] = next[1];
        dfs(next, copymap, depth + 1);
        copymap[next[0]][next[1]] = 0;
        if (flag == 1) return;
    }
}

void print(int map[23][23], int dd[100][2]) {
    for (int i = 0; i < len; i++) map[dd[i][0]][dd[i][1]] = 1;

    std::string str;
    for (int i = 0; i < 23; i++) {
        for (int j = 0; j < 23; j++) {
            switch (map[i][j]) {
                case -1:
                    str += "＃";
                    break;
                case 0:
                    str += "　";
                    break;
                case 1:
                    str += "１";
                    break;
            }
        }
        str += '\n';
    }
    std::cout << str;
}

int main() {
    // map[1][1],map[21][21]

    print(map, dir);
    std::cout << std::endl;
    int a[2] = {1, 1};
    dir[0][0] = dir[0][1] = 1;
    map[1][1] = 1;
    dfs(a, map, 1);
    map[1][1] = 0;
    print(map, dir);
    std::cout << std::endl;
    std::cout << "(" << dir[0][0] << ", " << dir[0][1] << ")";
    for (int i = 1; i < len; i++) 
        std::cout << " ---> (" << dir[i][0] << ", " << dir[i][1] << ")";
}