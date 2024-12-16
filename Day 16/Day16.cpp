#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

struct Node
{
    pair<int, int> pos;
    int score;
    int dir;

    bool operator<(const Node &other) const
    {
        return score > other.score;
    }
};

int dijkstra(vector<string> &grid, pair<int, int> startPos, pair<int, int> endPos);

int main()
{
    ifstream file("Day16.txt");
    string line;
    pair<int, int> startPos, endPos;
    vector<string> grid;
    int index = 0;
    while (getline(file, line))
    {
        grid.push_back(line);
        if (line.find("S") != string::npos)
        {
            startPos = {index, line.find("S")};
        }
        if (line.find("E") != string::npos)
        {
            endPos = {index, line.find("E")};
        }
        index++;
    }
    file.close();

    int res_1 = dijkstra(grid, startPos, endPos);
    cout << "Part 1: " << res_1 << endl;

    return 0;
}

int dijkstra(vector<string> &grid, pair<int, int> startPos, pair<int, int> endPos)
{
    priority_queue<Node> heap;
    set<pair<pair<int, int>, int>> visited; // Track position + direction
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    heap.push({startPos, 0, 1}); // Start with direction right

    while (!heap.empty())
    {
        Node current = heap.top();
        heap.pop();

        if (current.pos == endPos)
        {
            return current.score;
        }

        pair<pair<int, int>, int> state = {current.pos, current.dir};
        if (visited.count(state))
            continue;
        visited.insert(state);

        // cout << "POS: " << current.pos.first << " " << current.pos.second << " DIR: " << current.dir << " SCORE: " << current.score << endl;

        for (int i = 0; i < 4; i++)
        {
            pair<int, int> nextPos = {
                current.pos.first + directions[i].first,
                current.pos.second + directions[i].second};

            // Check boundaries first
            if (grid[nextPos.first][nextPos.second] == '#')
            {
                continue;
            }

            int newScore = current.score;
            // Add turn penalty if changing direction
            if (current.dir != i)
            {
                newScore += 1000;
            }
            newScore += 1; // Movement cost

            heap.push({nextPos, newScore, i});
        }
    }
    return -1;
}
