#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int get_msb(long n){
    int msb = 0;
    while(n != 0){
        n = n >> 1;
        msb++;
    }
    return msb;
}

/*
 * Complete the 'andProduct' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. LONG_INTEGER a
 *  2. LONG_INTEGER b
 */
long andProduct(long a, long b) {
    if(a == b){ return a & b; }
    int am = get_msb(a), bm = get_msb(b);
    if(am == bm){
        bitset<64> ba(a), bb(b), ans;
        for(int i = ba.size() - 1; i >= 0; i--){
            if(ba[i] == bb[i]){
                ans.set(i, ba[i]);
            } else {
                return (int64_t)ans.to_ulong();
            }
        }
    }
    return 0;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    for (int n_itr = 0; n_itr < n; n_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        long a = stol(first_multiple_input[0]);

        long b = stol(first_multiple_input[1]);

        long result = andProduct(a, b);

        cout << result << "\n";
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

