#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> code = {
        "LOAD A",
        "MACRO ABC",
        "LOAD p",
        "SUB q",
        "MEND",
        "STORE B",
        "MULT D",
        "MACRO ADD1 ARG",
        "LOAD X",
        "STORE ARG",
        "MEND",
        "LOAD B",
        "MACRO ADD5 A1, A2, A3",
        "STORE A2",
        "ADD1 5",
        "ADD1 10",
        "LOAD A1",
        "LOAD A3",
        "MEND",
        "ADD1 t",
        "ABC",
        "ADD5 D1, D2, D3",
        "END"};

    bool insideMacro = false;

    cout << "Intermediate Code:\n";
    for (const string &line : code)
    {
        if (line.find("MACRO") != string::npos)
        {
            insideMacro = true;
            continue;
        }
        else if (line.find("MEND") != string::npos)
        {
            insideMacro = false;
            continue;
        }

        if (!insideMacro)
        {
            cout << line << endl;
        }
    }

    return 0;
}
