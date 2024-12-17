#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef long long ll;

void Part1(vector<ll> instructions, ll register_A, ll register_B, ll register_C, vector<ll> &output);
void Part2(vector<ll> instructions, ll register_A, ll register_B, ll register_C);

int main()
{
    ll register_A;
    ll register_B;
    ll register_C;
    vector<ll> instructions;

    ifstream file("Day17.txt");
    string temp;

    // Read and parse register A
    getline(file, temp);
    sscanf(temp.c_str(), "Register A: %lld", &register_A);

    // Read and parse register B
    getline(file, temp);
    sscanf(temp.c_str(), "Register B: %lld", &register_B);

    // Read and parse register C
    getline(file, temp);
    sscanf(temp.c_str(), "Register C: %lld", &register_C);

    // Skip empty line
    getline(file, temp);

    // Read and parse instructions
    getline(file, temp);
    stringstream ss(temp.substr(9)); // Skip "Program: "
    while (getline(ss, temp, ','))
    {
        instructions.push_back(stoi(temp));
    }

    file.close();

    // Output the parsed values for verification
    cout << "Register A: " << register_A << endl;
    cout << "Register B: " << register_B << endl;
    cout << "Register C: " << register_C << endl;
    cout << "Instructions: ";
    cout << "\n";
    for (ll i = 0; i < instructions.size(); i++)
    {
        cout << instructions[i] << " ";
    }
    cout << endl;

    vector<ll> output;
    Part1(instructions, register_A, register_B, register_C, output);
    cout << "Part 1: \n";
    for (ll i = 0; i < output.size(); i++)
    {
        cout << output[i] << " ";
    }
    cout << "\n";

    // Part2(instructions, register_A, register_B, register_C);

    return 0;
}

void Part1(vector<ll> instructions, ll register_A, ll register_B, ll register_C, vector<ll> &output)
{
    ll pointer = 0;
    ll opcode, operand;

    while (pointer < instructions.size() - 1)
    {
        opcode = instructions[pointer];
        operand = instructions[pointer + 1];

        bool jump = false;

        ll value;
        switch (operand)
        {
        case 4:
            value = register_A;
            break;
        case 5:
            value = register_B;
            break;
        case 6:
            value = register_C;
            break;
        default:
            value = operand;
            break;
        }

        switch (opcode)
        {
        case 0:
            register_A = register_A / pow(2, value);
            break;
        case 1:
            register_B = register_B ^ operand;
            break;
        case 2:
            register_B = value % 8;
            break;
        case 3:
            if (register_A != 0)
            {
                pointer = operand;
                jump = true;
            }
            break;
        case 4:
            register_B = register_B ^ register_C;
            break;
        case 5:
            output.push_back(value % 8);
            break;
        case 6:
            register_B = register_A / pow(2, value);
            break;
        case 7:
            register_C = register_A / pow(2, value);
            break;
        default:
            break;
        }

        if (!jump)
        {
            pointer += 2;
        }
    }
}

void Part2(vector<ll> instructions, ll register_A, ll register_B, ll register_C)
{
    ll num = 0;
    while (true)
    {
        vector<ll> output;
        Part1(instructions, num, register_B, register_C, output);
        if (output.size() != instructions.size())
        {
            continue;
        }
        else
        {
            for (ll i = 0; i < output.size(); i++)
            {
                if (output[i] != instructions[i])
                {
                    break;
                }
                if (i == output.size() - 1)
                {
                    cout << "Part 2: " << num << endl;
                    return;
                }
            }
        }
        num++;
    }
}