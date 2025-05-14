#include <bits/stdc++.h>
using namespace std;

int prec(const string &op)
{
    if (op == "^")
        return 4;
    if (op == "*" || op == "/")
        return 3;
    if (op == "+" || op == "-")
        return 2;
    if (op == "=")
        return 1;
    return 0;
}

bool isOp(const string &tok)
{
    return tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "^" || tok == "=";
}

vector<string> tokenize(const string &s)
{
    vector<string> out;
    for (int i = 0; i < s.size();)
    {
        if (isspace(s[i]))
        {
            i++;
            continue;
        }
        if (isalpha(s[i]) || isdigit(s[i]) || s[i] == '.')
        {
            string t;
            while (i < s.size() && (isalnum(s[i]) || s[i] == '.'))
            {
                t.push_back(s[i++]);
            }
            out.push_back(t);
        }
        else
        {
            out.push_back(string(1, s[i]));
            i++;
        }
    }
    return out;
}

vector<string> infixToPostfix(const vector<string> &in)
{
    vector<string> out;
    stack<string> st;
    for (auto &tok : in)
    {
        if (!isOp(tok) && tok != "(" && tok != ")")
        {
            out.push_back(tok);
        }
        else if (isOp(tok))
        {
            while (!st.empty() && isOp(st.top()) &&
                   ((tok != "^" && prec(st.top()) >= prec(tok)) ||
                    (tok == "^" && prec(st.top()) > prec(tok))))
            {
                out.push_back(st.top());
                st.pop();
            }
            st.push(tok);
        }
        else if (tok == "(")
        {
            st.push(tok);
        }
        else if (tok == ")")
        {
            while (!st.empty() && st.top() != "(")
            {
                out.push_back(st.top());
                st.pop();
            }
            if (!st.empty())
                st.pop();
        }
    }
    while (!st.empty())
    {
        out.push_back(st.top());
        st.pop();
    }
    return out;
}

int main()
{
    string line;
    getline(cin, line);
    auto toks = tokenize(line);

    int eq = -1;
    for (int i = 0; i < toks.size(); ++i)
        if (toks[i] == "=")
        {
            eq = i;
            break;
        }

    if (eq < 1)
    {
        cerr << "Invalid input\n";
        return 1;
    }

    string lhs = toks[0];
    vector<string> rhsTokens(toks.begin() + eq + 1, toks.end());

    auto post = infixToPostfix(rhsTokens);

    stack<string> st;
    int tmpCnt = 1;
    vector<string> code;
    for (auto &tok : post)
    {
        if (!isOp(tok))
        {
            st.push(tok);
        }
        else
        {
            string b = st.top();
            st.pop();
            string a = st.top();
            st.pop();
            string tmp = "t" + to_string(tmpCnt++);
            code.push_back(tmp + " = " + a + " " + tok + " " + b);
            st.push(tmp);
        }
    }

    string result = st.top();
    code.push_back(lhs + " = " + result);

    for (auto &l : code)
    {
        cout << l << "\n";
    }
    return 0;
}
