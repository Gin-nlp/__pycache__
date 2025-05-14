#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct MNTEntry
{
    string macroName;
    int startIndex;
    int endIndex;
};

int main()
{
    vector<string> code = {
        "LOAD A",
        "STORE B",
        "MACRO ABC",
        "LOAD p",
        "SUB q",
        "MEND",
        "MACRO ADD1 ARG",
        "LOAD X",
        "STORE ARG",
        "MEND",
        "MACRO ADD5 A1,A2,A3",
        "STORE A2",
        "ADD1 5",
        "ADD1 10",
        "LOAD A1",
        "LOAD A3",
        "MEND",
        "ABC",
        "ADD5 D1,D2,D3",
        "END"};

    vector<string> MDT;
    vector<MNTEntry> MNT;
    bool inMacro = false;
    int currentMDTIndex = 0;
    MNTEntry currentEntry;

    for (int i = 0; i < code.size(); i++)
    {
        string line = code[i];

        if (line.find("MACRO") != string::npos)
        {
            inMacro = true;
            currentEntry.startIndex = currentMDTIndex;
            currentEntry.macroName = line.substr(line.find(" ") + 1);
            continue;
        }

        if (inMacro)
        {
            MDT.push_back(line);
            currentMDTIndex++;

            if (line.find("MEND") != string::npos)
            {
                currentEntry.endIndex = currentMDTIndex - 1;
                MNT.push_back(currentEntry);
                inMacro = false;
            }
        }
    }

    cout << "Macro Definition Table (MDT):" << endl;
    for (int i = 0; i < MDT.size(); i++)
    {
        cout << i << ": " << MDT[i] << endl;
    }

    cout << endl;

    cout << "Macro Name Table (MNT):\n";
    cout << "Index\tMacro Name\t\tStart\tEnd\n";
    for (int i = 0; i < MNT.size(); i++)
    {
        cout << i << "\t" << MNT[i].macroName << "\t\t" << MNT[i].startIndex << "\t" << MNT[i].endIndex << endl;
    }

    return 0;
}
