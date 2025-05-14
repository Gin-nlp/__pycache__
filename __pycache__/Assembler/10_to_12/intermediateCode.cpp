#include <bits/stdc++.h>
using namespace std;

vector<string> tokenize(string &line)
{
    stringstream stream(line);
    string token;
    vector<string> tokens;
    while (stream >> token)
        tokens.push_back(token);
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

    map<string, string> opcode = {
        {"READ", "01"}, {"MOVER", "04"}, {"COMP", "06"}, {"BC", "07"}, {"SUB", "05"}, {"STOP", "00"}};
    map<string, string> regcode = {
        {"AREG", "1"}, {"BREG", "2"}, {"CREG", "3"}, {"DREG", "4"}};
    map<string, string> condition = {
        {"LT", "1"}, {"LE", "2"}, {"EQ", "3"}, {"GT", "4"}, {"GE", "5"}, {"ANY", "6"}};

    int lc = 0;
    vector<string> intermediate;

    for (string line : code)
    {
        vector<string> tokens = tokenize(line);
        if (tokens.empty())
            continue;

        string label = tokens[0];

        if (label == "START")
        {
            lc = stoi(tokens[1]);
            intermediate.push_back("(AD,01) (C," + tokens[1] + ")");
            continue;
        }

        if (label == "END")
        {
            intermediate.push_back("(AD,02)");
            break;
        }

        string ic = "";
        int tok_index = 0;

        string instr = tokens[tok_index];
        ic += "(IS," + opcode[instr] + ")";

        if (instr == "BC")
        {
            string cond = tokens[tok_index + 1];
            ic += " (" + condition[cond.substr(0, 2)] + ")";
            ic += " (S," + tokens[tok_index + 2] + ")";
        }
        else if (instr != "STOP" && instr != "READ")
        {
            string reg = tokens[tok_index + 1];
            reg = reg.substr(0, reg.find(','));
            // ic += " (" + regcode[reg] + ")";
            string operand = tokens[tok_index + 2];
            if (operand[0] == '=')
                ic += " (L," + operand + ")";
            else
                ic += " (S," + operand + ")";
        }
        else if (instr == "READ")
        {
            string op = tokens[tok_index + 1];
            ic += " (S," + op + ")";
        }

        intermediate.push_back(ic);
        lc++;
    }

    cout << "Intermediate Code:\n";
    for (auto &line : intermediate)
        cout << line << endl;

    return 0;
}
