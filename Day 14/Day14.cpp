#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const int ROW = 103;
const int COL = 101;

vector<vector<int>> grid(ROW, vector<int>(COL, 0));

void preProcess(vector<vector<int>> &grid, int x, int y, int v_x, int v_y, int seconds);
void processPart1(vector<vector<int>> &grid);

int main()
{
    ifstream file("Day14.txt");
    string line;
    while (getline(file, line))
    {
        int x, y;
        int v_x, v_y;

        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &x, &y, &v_x, &v_y);

        preProcess(grid, x, y, v_x, v_y, 100);
    }

    processPart1(grid);

    return 0;
}

void preProcess(vector<vector<int>> &grid, int x, int y, int v_x, int v_y, int seconds)
{
    int final_x = (x + (seconds * v_x) % COL + COL) % COL;
    int final_y = (y + (seconds * v_y) % ROW + ROW) % ROW;
    grid[final_y][final_x] += 1;
}

void processPart1(vector<vector<int>> &grid)
{
    long long res_1 = 0;
    int batches[4]{};

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (i == ROW / 2 || j == COL / 2)
                continue;

            if (i < ROW / 2 && j < COL / 2)
                batches[0] += grid[i][j];

            else if (i < ROW / 2 && j > COL / 2)
                batches[1] += grid[i][j];

            else if (i > ROW / 2 && j < COL / 2)
                batches[2] += grid[i][j];

            else if (i > ROW / 2 && j > COL / 2)
                batches[3] += grid[i][j];
        }
    }

    res_1 = batches[0] * batches[1] * batches[2] * batches[3];

    cout << "Part 1: " << res_1 << endl;
}
