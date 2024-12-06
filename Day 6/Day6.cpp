#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <utility>

using namespace std;

class GuardPathSimulator
{
private:
    vector<string> grid;
    int rows, cols;
    const vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left

    bool isValidPosition(int r, int c) const
    {
        return r >= 0 && r < rows && c >= 0 && c < cols;
    }

    bool isEdge(int r, int c) const
    {
        return r == 0 || r == rows - 1 || c == 0 || c == cols - 1;
    }

public:
    GuardPathSimulator(const vector<string> &input) : grid(input)
    {
        rows = grid.size();
        cols = grid[0].size();
    }

    pair<int, int> findStart()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == '^')
                {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    int simulatePath()
    {
        auto [startRow, startCol] = findStart();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        int visitedCount = 1;
        int r = startRow, c = startCol, dir = 0;

        while (isValidPosition(r, c) && !isEdge(r, c))
        {
            if (!visited[r][c])
            {
                visited[r][c] = true;
                visitedCount++;
            }

            int nextR = r + directions[dir].first;
            int nextC = c + directions[dir].second;

            if (!isValidPosition(nextR, nextC) || grid[nextR][nextC] == '#')
            {
                dir = (dir + 1) % 4;
            }
            else
            {
                r = nextR;
                c = nextC;
            }
        }

        return visitedCount;
    }

    int findLoopPositions()
    {
        int loopCount = 0;
        auto [startRow, startCol] = findStart();

        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                if (grid[r][c] == '.' && (r != startRow || c != startCol))
                {
                    if (createsLoop(r, c))
                    {
                        loopCount++;
                    }
                }
            }
        }

        return loopCount;
    }

private:
    bool createsLoop(int obstacleRow, int obstacleCol)
    {
        vector<string> tempGrid = grid;
        tempGrid[obstacleRow][obstacleCol] = '#';

        auto [r, c] = findStart();
        int dir = 0;
        set<tuple<int, int, int>> seen;

        while (isValidPosition(r, c) && !isEdge(r, c))
        {
            auto state = make_tuple(r, c, dir);
            if (seen.count(state))
            {
                return true;
            }
            seen.insert(state);

            int nextR = r + directions[dir].first;
            int nextC = c + directions[dir].second;

            if (!isValidPosition(nextR, nextC) || tempGrid[nextR][nextC] == '#')
            {
                dir = (dir + 1) % 4;
            }
            else
            {
                r = nextR;
                c = nextC;
            }
        }

        return false;
    }
};

int main()
{
    ifstream file("Day6.txt");
    vector<string> grid;
    string line;

    while (getline(file, line))
    {
        grid.push_back(line);
    }

    GuardPathSimulator simulator(grid);
    cout << "Part 1: " << simulator.simulatePath() << endl;
    cout << "Part 2: " << simulator.findLoopPositions() << endl;

    return 0;
}