#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

map<char, pair<int, int>> directions = {{'^', {-1, 0}}, {'<', {0, -1}}, {'v', {1, 0}}, {'>', {0, 1}}};

void simulatePart1(vector<string> &grid, char dir, pair<int, int> &pos);
void Part1(vector<string> &grid);

vector<string> resizeGrid(vector<string> grid, pair<int, int> &pos);
void findBlocks(vector<string> &grid, pair<int, int> cur, char dir, set<pair<int, int>> &visited);
void simulatePart2(vector<string> &grid, char dir, pair<int, int> &pos);
void Part2(vector<string> &grid);

int main()
{
    ifstream file("Day15.txt");
    string line;
    vector<string> grid;
    pair<int, int> pos;
    while (getline(file, line))
    {
        if (line == "")
            break;
        grid.push_back(line);
        if (line.find('@') != string::npos)
            pos = {grid.size() - 1, line.find('@')};
    }

    vector<string> newGrid = resizeGrid(grid, pos);

    char dir;
    while (file >> dir)
    {
        // simulatePart1(grid, dir, pos);
        simulatePart2(newGrid, dir, pos);
    }

    file.close();

    // Part1(grid);
    Part2(newGrid);

    return 0;
}

void simulatePart1(vector<string> &grid, char dir, pair<int, int> &pos)
{
    pair<int, int> new_pos = {pos.first + directions[dir].first, pos.second + directions[dir].second};
    if (grid[new_pos.first][new_pos.second] == '#')
        return;

    if (grid[new_pos.first][new_pos.second] == '.')
    {
        swap(grid[pos.first][pos.second], grid[new_pos.first][new_pos.second]);
    }
    else if (grid[new_pos.first][new_pos.second] == 'O')
    {
        // Find connected block
        pair<int, int> cur = {new_pos.first, new_pos.second};
        while (grid[cur.first + directions[dir].first][cur.second + directions[dir].second] == 'O')
        {
            cur.first += directions[dir].first;
            cur.second += directions[dir].second;
        }
        if (grid[cur.first + directions[dir].first][cur.second + directions[dir].second] == '#')
            return;

        grid[cur.first + directions[dir].first][cur.second + directions[dir].second] = 'O';
        grid[new_pos.first][new_pos.second] = '@';
        grid[pos.first][pos.second] = '.';
    }

    pos = new_pos;
}

void Part1(vector<string> &grid)
{
    int res_1 = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 'O')
                res_1 += 100 * i + j;
        }
    }
    cout << "Part 1: " << res_1 << endl;
}

vector<string> resizeGrid(vector<string> grid, pair<int, int> &pos)
{
    vector<string> newGrid;
    for (int i = 0; i < grid.size(); i++)
    {
        string newLine = "";
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '#')
            {
                newLine += grid[i][j];
                newLine += grid[i][j];
            }
            else if (grid[i][j] == 'O')
            {
                newLine += '[';
                newLine += ']';
            }
            else if (grid[i][j] == '@')
            {
                newLine += '@';
                newLine += '.';
                pos = {i, newLine.find('@')};
            }
            else
            {
                newLine += '.';
                newLine += '.';
            }
        }
        newGrid.push_back(newLine);
    }

    return newGrid;
}

void findBlocks(vector<string> &grid, pair<int, int> cur, char dir, set<pair<int, int>> &visited)
{
    pair<int, int> a = {cur.first + directions[dir].first, cur.second + directions[dir].second};
    pair<int, int> b;
    if (grid[a.first][a.second] == ']' || grid[a.first][a.second] == '[')
    {
        visited.insert({a.first, a.second});
        if (grid[a.first][a.second] == '[' && grid[a.first][a.second + 1] == ']' && visited.find({a.first, a.second + 1}) == visited.end())
            b = {a.first, a.second + 1};
        else if (grid[a.first][a.second] == ']' && grid[a.first][a.second - 1] == '[' && visited.find({a.first, a.second - 1}) == visited.end())
            b = {a.first, a.second - 1};
        else
            return;

        visited.insert({b.first, b.second});
        findBlocks(grid, a, dir, visited);
        findBlocks(grid, b, dir, visited);
    }
}

void simulatePart2(vector<string> &grid, char dir, pair<int, int> &pos)
{
    pair<int, int> new_pos = {pos.first + directions[dir].first, pos.second + directions[dir].second};
    if (grid[new_pos.first][new_pos.second] == '#')
        return;

    if (grid[new_pos.first][new_pos.second] == '.')
    {
        swap(grid[pos.first][pos.second], grid[new_pos.first][new_pos.second]);
    }
    else if (dir == '>' || dir == '<')
    {
        // Horizontal movement
        // Find connected block
        pair<int, int> cur = {new_pos.first, new_pos.second};
        while (grid[cur.first + directions[dir].first][cur.second + directions[dir].second] == ']' ||
               grid[cur.first + directions[dir].first][cur.second + directions[dir].second] == '[')
        {
            cur.first += directions[dir].first;
            cur.second += directions[dir].second;
        }

        if (grid[cur.first + directions[dir].first][cur.second + directions[dir].second] == '#')
            return;

        while (grid[cur.first][cur.second] != '@')
        {
            swap(grid[cur.first][cur.second], grid[cur.first + directions[dir].first][cur.second + directions[dir].second]);
            cur.first -= directions[dir].first;
            cur.second -= directions[dir].second;
        }
        swap(grid[pos.first][pos.second], grid[new_pos.first][new_pos.second]);
    }
    else
    {
        // Vertical movement
        // Find connected block
        pair<int, int> cur = {new_pos.first, new_pos.second};
        set<pair<int, int>> visited;
        visited.insert({cur.first, cur.second});
        findBlocks(grid, cur, dir, visited);
        if (grid[cur.first][cur.second] == '[' && grid[cur.first][cur.second + 1] == ']')
        {
            visited.insert({cur.first, cur.second + 1});
            findBlocks(grid, {cur.first, cur.second + 1}, dir, visited);
        }
        else if (grid[cur.first][cur.second] == ']' && grid[cur.first][cur.second - 1] == '[')
        {
            visited.insert({cur.first, cur.second - 1});
            findBlocks(grid, {cur.first, cur.second - 1}, dir, visited);
        }

        vector<pair<int, int>> blocks(visited.begin(), visited.end());
        if (dir == '^')
        {
            for (auto block : blocks)
                if (grid[block.first - 1][block.second] == '#')
                    return;

            sort(blocks.begin(), blocks.end(), [](pair<int, int> a, pair<int, int> b)
                 { return a.first < b.first; });
        }
        else
        {
            for (auto block : blocks)
                if (grid[block.first + 1][block.second] == '#')
                    return;

            sort(blocks.begin(), blocks.end(), [](pair<int, int> a, pair<int, int> b)
                 { return a.first > b.first; });
        }

        for (auto block : blocks)
            swap(grid[block.first][block.second], grid[block.first + directions[dir].first][block.second + directions[dir].second]);

        swap(grid[pos.first][pos.second], grid[new_pos.first][new_pos.second]);
    }

    pos = new_pos;
}

void Part2(vector<string> &grid)
{
    int res_2 = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '[')
                res_2 += 100 * i + j;
        }
    }
    cout << "Part 2: " << res_2 << endl;
}