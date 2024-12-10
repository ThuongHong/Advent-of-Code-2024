#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

int dfs(vector<string> s, int cur, int i, int j, int m, int n, set<pair<int, int>> &visited, int Part)
{
    if (i < 0 || j < 0 || i >= m || j >= n)
        return 0;

    if (s[i][j] != cur)
        return 0;

    if (s[i][j] == '9')
    {
        if (Part == 2)
            return 1;

        if (visited.find({i, j}) == visited.end())
        {
            visited.insert({i, j});
            return 1;
        }
        return 0;
    }

    int a = dfs(s, cur + 1, i + 1, j, m, n, visited, Part);
    int b = dfs(s, cur + 1, i - 1, j, m, n, visited, Part);
    int c = dfs(s, cur + 1, i, j + 1, m, n, visited, Part);
    int d = dfs(s, cur + 1, i, j - 1, m, n, visited, Part);

    return a + b + c + d;
}

int main()
{
    ifstream file("Day10.txt");
    vector<string> s;
    string line;
    while (getline(file, line))
    {
        s.push_back(line);
    }
    file.close();

    int m = s.size();
    int n = s[0].size();

    int res = 0;
    int Part = 1;
    cout << "Part 1 or 2? ";
    cin >> Part;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s[i][j] == '0')
            {
                set<pair<int, int>> visited;
                res += dfs(s, '0', i, j, m, n, visited, Part);
            }
        }
    }
    cout << res;

    return 0;
}