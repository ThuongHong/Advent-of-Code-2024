#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int N = 71;

struct Node
{
    int x, y, dist;
};

vector<vector<char>> grid(N, vector<char>(N, '.'));

int bfs(vector<vector<char>> grid);

int main()
{
    cout << "Day 18!" << endl;
    ifstream file("Day18.txt");
    string line;
    int x, y, cnt = 1024;

    while (getline(file, line))
    {
        if (sscanf(line.c_str(), "%d,%d", &x, &y) == 2)
        {
            if (x >= 0 && x < N && y >= 0 && y < N)
            {
                grid[x][y] = '#';
            }
        }
        if (bfs(grid) == -1)
        {
            cout << "No path found!" << endl;
            cout << "The byte block: " << x << "," << y << endl;
            return 0;
        }
    }

    file.close();

    // cout << "Shortest path: " << bfs(grid) << endl;

    return 0;
}

int bfs(vector<vector<char>> grid)
{
    vector<vector<bool>> visited(N, vector<bool>(N, false));
    queue<Node> q;

    Node src = {0, 0, 0};
    q.push(src);
    visited[src.x][src.y] = true;

    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        int x = node.x;
        int y = node.y;
        int dist = node.dist;

        if (x == N - 1 && y == N - 1)
            return dist;

        for (auto &dir : dirs)
        {
            int newX = x + dir.first;
            int newY = y + dir.second;

            if (newX >= 0 && newX < N && newY >= 0 && newY < N && !visited[newX][newY] && grid[newX][newY] != '#')
            {
                visited[newX][newY] = true;
                q.push({newX, newY, dist + 1});
            }
        }
    }

    return -1;
}