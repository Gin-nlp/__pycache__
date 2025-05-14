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

bool isLiteral(const string &token)
{
    return token.size() >= 4 && token.substr(0, 2) == "='";
}

bool isInstruction(const string &word)
{
    return word == "READ" || word == "MOVER" || word == "COMP" ||
           word == "BC" || word == "STOP";
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
    unordered_map<string, int> literalTable;
    vector<string> literalList;
    vector<int> poolTable;
    int lc = 0;

    poolTable.push_back(0);

    for (string line : code)
    {
        vector<string> tokens = tokenize(line);
        string label = tokens[0];

        if (label == "START")
        {
            lc = stoi(tokens[1]);
            continue;
        }

        for (auto token : tokens)
        {
            if (isLiteral(token))
            {
                literalList.push_back(token);
            }
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

        if (tokens[0] == "LTORG" || tokens[0] == "END")
        {
            poolTable.push_back(literalList.size());
        }

        lc++;
    }

    for (auto literal : literalList)
    {
        literalTable[literal] = lc;
        lc++;
    }

    cout << "Below is the required symbol table ..." << endl;
    for (auto ele : symbolTable)
    {
        cout << ele.first << "\t" << ele.second << endl;
    }

    cout << endl;

    cout << "Below is the required symbol table ..." << endl;
    for (auto ele : literalTable)
    {
        cout << ele.first << "\t" << ele.second << endl;
    }

    cout << endl;

    cout << "Below is the required pool table ..." << endl;
    for (auto ele : poolTable)
    {
        cout << ele << " ";
    }

    cout << endl;

    return 0;
}