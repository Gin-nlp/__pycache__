#include <bits/stdc++.h>

using namespace std;

vector<string> tokenize(string &line)
{
    stringstream stream(line);
    string token;
    vector<string> tokens;
    while (stream >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    vector<string> code = {
        "START 100",
        "READ A",
        "READ B",
        "LOOP   MOVER AREG, A",
        "       MOVER BREG, B",
        "       COMP BREG, ='2'",
        "       BC GT, LOOP",
        "BACK   SUB AREG, B",
        "       COMP AREG, ='5'",
        "       BC LT, BACK",
        "       STOP",
        "A      DS 3",
        "B      DS 1",
        "       END"};

    unordered_map<string, int> symbolTable;
    int lc = 0;

    for (string line : code)
    {
        vector<string> tokens = tokenize(line);
        string label = tokens[0];

        if (label == "START")
        {
            lc = stoi(tokens[1]);
            continue;
        }

        if (label != "READ" && label != "MOVER" && label != "COMP" && label != "BC" && label != "SUB" && label != "STOP" && label != "DS" && label != "END")
        {
            if (tokens.size() > 1 && tokens[1] == "DS")
            {
                int size = stoi(tokens[2]);
                symbolTable[label] = lc;
                lc += size;
                continue;
            }
            else
            {
                symbolTable[label] = lc;
            }
        }
        lc++;
    }

    cout << "Below is the required symbol table ..." << endl;
    for (auto ele : symbolTable)
    {
        cout << ele.first << "\t" << ele.second << endl;
    }

    return 0;
}