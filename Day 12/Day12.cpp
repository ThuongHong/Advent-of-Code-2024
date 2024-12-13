#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>

using namespace std;

int m, n;
vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<string> s;

bool isValid(int i, int j);
pair<int, int> dfs1(vector<string> s, int i, int j, char plant, set<pair<int, int>> &visited);

int getArea(vector<string> s, int i, int j, char plant, set<pair<int, int>> &visited, set<pair<int, int>> &region);
int countSides(vector<string> s, char plant, set<pair<int, int>> &region);

void Part1();
void Part2();

int main()
{
    ifstream file("Day12.txt");
    string line;
    while (getline(file, line))
    {
        s.push_back(line);
    }
    file.close();

    m = s.size();
    n = s[0].size();

    Part1();
    Part2();

    return 0;
}

bool isValid(int i, int j)
{
    return i >= 0 && i < m && j >= 0 && j < n;
}

pair<int, int> dfs1(vector<string> s, int i, int j, char plant, set<pair<int, int>> &visited)
{
    if (!isValid(i, j) || s[i][j] != plant || visited.find({i, j}) != visited.end())
        return {0, 0};

    visited.insert({i, j});
    int area = 1;
    int perimeter = 4;
    for (auto &dir : directions)
    {
        if (isValid(i + dir.first, j + dir.second) && s[i + dir.first][j + dir.second] == plant)
        {
            perimeter--;
        }
    }

    for (auto &dir : directions)
    {

        pair<int, int> search = dfs1(s, i + dir.first, j + dir.second, plant, visited);
        area += search.first;
        perimeter += search.second;
    }
    return {area, perimeter};
}

void Part1()
{
    int res = 0;
    set<pair<int, int>> visited;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited.find({i, j}) == visited.end())
            {
                char plant = s[i][j];
                pair<int, int> search = dfs1(s, i, j, plant, visited);
                res += search.first * search.second;
            }
        }
    }

    cout << "Part 1: " << res << endl;
}

int getArea(vector<string> s, int i, int j, char plant, set<pair<int, int>> &visited, set<pair<int, int>> &region)
{
    if (!isValid(i, j) || s[i][j] != plant || visited.find({i, j}) != visited.end())
        return 0;

    visited.insert({i, j});
    region.insert({i, j});
    int area = 1;

    for (auto &dir : directions)
    {
        area += getArea(s, i + dir.first, j + dir.second, plant, visited, region);
    }

    return area;
}

int countSides(vector<string> s, char plant, set<pair<int, int>> &region)
{
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;

    for (auto &point : region)
    {
        int i = point.first;
        int j = point.second;

        if (!isValid(i - 1, j) || (isValid(i - 1, j) && s[i - 1][j] != plant))
        {
            top++;
            if (region.find({i, j - 1}) != region.end() && (!isValid(i - 1, j - 1) || s[i - 1][j - 1] != plant))
                top--;
        }

        if (!isValid(i + 1, j) || (isValid(i + 1, j) && s[i + 1][j] != plant))
        {
            bottom++;
            if (region.find({i, j - 1}) != region.end() && (!isValid(i + 1, j - 1) || s[i + 1][j - 1] != plant))
                bottom--;
        }

        if (!isValid(i, j - 1) || (isValid(i, j - 1) && s[i][j - 1] != plant))
        {
            left++;
            if (region.find({i - 1, j}) != region.end() && (!isValid(i - 1, j - 1) || s[i - 1][j - 1] != plant))
                left--;
        }

        if (!isValid(i, j + 1) || (isValid(i, j + 1) && s[i][j + 1] != plant))
        {
            right++;
            if (region.find({i - 1, j}) != region.end() && (!isValid(i - 1, j + 1) || s[i - 1][j + 1] != plant))
                right--;
        }
    }

    // cout << "Top: " << top << " Bottom: " << bottom << " Left: " << left << " Right: " << right << endl;
    return top + bottom + left + right;
}

void Part2()
{
    int res = 0;
    set<pair<int, int>> visited;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visited.find({i, j}) == visited.end())
            {
                char plant = s[i][j];
                set<pair<int, int>> region;
                int area = getArea(s, i, j, plant, visited, region);
                int sides = countSides(s, plant, region);
                // cout << "Plant: " << plant << " Area: " << area << " Sides: " << sides << endl;
                res += area * sides;
            }
        }
    }

    cout << "Part 2: " << res << endl;
}