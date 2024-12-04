#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int Horizontal(const vector<string> &a, int i, int j)
{
    int cnt = 0;
    if (j + 3 < a[0].size() && a[i][j] == 'X' && a[i][j + 1] == 'M' && a[i][j + 2] == 'A' && a[i][j + 3] == 'S')
    {
        cnt++;
    }
    if (j - 3 >= 0 && a[i][j] == 'X' && a[i][j - 1] == 'M' && a[i][j - 2] == 'A' && a[i][j - 3] == 'S')
    {
        cnt++;
    }
    return cnt;
}

int Vertical(const vector<string> &a, int i, int j)
{
    int cnt = 0;
    if (i + 3 < a.size() && a[i][j] == 'X' && a[i + 1][j] == 'M' && a[i + 2][j] == 'A' && a[i + 3][j] == 'S')
    {
        cnt++;
    }
    if (i - 3 >= 0 && a[i][j] == 'X' && a[i - 1][j] == 'M' && a[i - 2][j] == 'A' && a[i - 3][j] == 'S')
    {
        cnt++;
    }
    return cnt;
}

int Diagonal(const vector<string> &a, int i, int j)
{
    int cnt = 0;
    if (i + 3 < a.size() && j + 3 < a[0].size() && a[i][j] == 'X' && a[i + 1][j + 1] == 'M' && a[i + 2][j + 2] == 'A' && a[i + 3][j + 3] == 'S')
    {
        cnt++;
    }
    if (i - 3 >= 0 && j - 3 >= 0 && a[i][j] == 'X' && a[i - 1][j - 1] == 'M' && a[i - 2][j - 2] == 'A' && a[i - 3][j - 3] == 'S')
    {
        cnt++;
    }
    if (i + 3 < a.size() && j - 3 >= 0 && a[i][j] == 'X' && a[i + 1][j - 1] == 'M' && a[i + 2][j - 2] == 'A' && a[i + 3][j - 3] == 'S')
    {
        cnt++;
    }
    if (i - 3 >= 0 && j + 3 < a[0].size() && a[i][j] == 'X' && a[i - 1][j + 1] == 'M' && a[i - 2][j + 2] == 'A' && a[i - 3][j + 3] == 'S')
    {
        cnt++;
    }
    return cnt;
}

int Special(const vector<string> &a, int i, int j)
{
    if (a[i][j] != 'A' || i - 1 < 0 || i + 1 >= a.size() || j - 1 < 0 || j + 1 >= a[0].size())
    {
        return 0;
    }

    int cnt = 0;
    int lu_i = i - 1, lu_j = j - 1;
    int ru_i = i - 1, ru_j = j + 1;
    int ld_i = i + 1, ld_j = j - 1;
    int rd_i = i + 1, rd_j = j + 1;

    if (a[lu_i][lu_j] == 'M' && a[rd_i][rd_j] == 'S' &&
        a[ru_i][ru_j] == 'M' && a[ld_i][ld_j] == 'S')
    {
        cnt++;
    }

    if (a[lu_i][lu_j] == 'S' && a[rd_i][rd_j] == 'M' &&
        a[ru_i][ru_j] == 'S' && a[ld_i][ld_j] == 'M')
    {
        cnt++;
    }

    if (a[lu_i][lu_j] == 'M' && a[rd_i][rd_j] == 'S' &&
        a[ru_i][ru_j] == 'S' && a[ld_i][ld_j] == 'M')
    {
        cnt++;
    }

    if (a[lu_i][lu_j] == 'S' && a[rd_i][rd_j] == 'M' &&
        a[ru_i][ru_j] == 'M' && a[ld_i][ld_j] == 'S')
    {
        cnt++;
    }

    return cnt;
}

int main()
{
    ifstream file("Day4.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    vector<string> a;
    while (getline(file, line))
    {
        a.push_back(line);
    }

    file.close();

    long long resPart1 = 0, resPart2 = 0;
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            resPart1 += Horizontal(a, i, j) + Vertical(a, i, j) + Diagonal(a, i, j);

            resPart2 += Special(a, i, j);
        }
    }

    cout << resPart1 << endl;
    cout << resPart2 << endl;

    return 0;
}