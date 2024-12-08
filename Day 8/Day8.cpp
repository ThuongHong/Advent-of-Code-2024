#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int part1(unordered_map<char, vector<pair<int, int>>> &antennas, int m, int n, vector<string> s)
{
    int res = 0;
    for (auto &antenna : antennas)
    {
        for (int i = 0; i < antenna.second.size(); i++)
        {
            for (int j = i + 1; j < antenna.second.size(); j++)
            {
                int x1 = 2 * antenna.second[i].first - antenna.second[j].first;
                int y1 = 2 * antenna.second[i].second - antenna.second[j].second;
                int x2 = 2 * antenna.second[j].first - antenna.second[i].first;
                int y2 = 2 * antenna.second[j].second - antenna.second[i].second;

                if (x1 >= 0 && y1 >= 0 && x1 < m && y1 < n && s[x1][y1] != '#')
                {
                    res++;
                    s[x1][y1] = '#';
                }
                if (x2 >= 0 && y2 >= 0 && x2 < m && y2 < n && s[x2][y2] != '#')
                {
                    res++;
                    s[x2][y2] = '#';
                }
            }
        }
    }
    return res;
}

int part2(unordered_map<char, vector<pair<int, int>>> &antennas, int m, int n, vector<string> s)
{
    int res = 0;
    for (auto &antenna : antennas)
    {
        for (int i = 0; i < antenna.second.size(); i++)
        {
            for (int j = i + 1; j < antenna.second.size(); j++)
            {
                int x1 = antenna.second[i].first;
                int y1 = antenna.second[i].second;
                int x2 = antenna.second[j].first;
                int y2 = antenna.second[j].second;

                int dx = x2 - x1;
                int dy = y2 - y1;

                int x = x2;
                int y = y2;

                while (x >= 0 && y >= 0 && x < m && y < n)
                {

                    if (s[x][y] != '#')
                    {
                        res++;
                        s[x][y] = '#';
                    }
                    x += dx;
                    y += dy;
                }
                x = x1;
                y = y1;

                while (x >= 0 && y >= 0 && x < m && y < n)
                {

                    if (s[x][y] != '#')
                    {
                        res++;
                        s[x][y] = '#';
                    }
                    x -= dx;
                    y -= dy;
                }
            }
        }
    }
    return res;
}

int main()
{
    ifstream file("Day8.txt");
    vector<string> s;
    string line;
    while (getline(file, line))
    {
        s.push_back(line);
    }
    file.close();

    int m = s.size();
    int n = s[0].size();
    unordered_map<char, vector<pair<int, int>>> antennas;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (s[i][j] != '.')
                antennas[s[i][j]].push_back({i, j});
        }
    }

    int res1 = part1(antennas, m, n, s);
    int res2 = part2(antennas, m, n, s);

    cout << res1 << "\n";
    cout << res2 << "\n";

    return 0;
}