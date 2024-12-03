#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void readFile(string filename, vector<int> &v1, vector<int> &v2, map<int, int> &m)
{
    ifstream file("Day1.txt");

    while (!file.eof())
    {
        int x, y;
        file >> x >> y;
        v1.push_back(x);
        v2.push_back(y);
        m[y]++;
    }

    file.close();
}

void partOne(vector<int> &v1, vector<int> &v2)
{
    long long res = 0;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    for (int i = 0; i < v1.size(); i++)
    {
        res += abs(v1[i] - v2[i]);
    }
    cout << res;
}

void partTwo(vector<int> &v1, map<int, int> &m)
{
    long long res = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        res += m[v1[i]] * v1[i];
    }
    cout << res;
}

int main()
{
    vector<int> v1, v2;
    map<int, int> m;
    readFile("Day1.txt", v1, v2, m);

    // Part 1
    partOne(v1, v2);

    // Part 2
    partTwo(v1, m);

    return 0;
}