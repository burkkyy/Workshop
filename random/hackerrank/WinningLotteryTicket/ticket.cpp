#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'winningLotteryTicket' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts STRING_ARRAY tickets as parameter.
 */

long winningLotteryTicket(vector<string> tickets) {
    long long a = 0;
    long m = 0, n = tickets.size();
    vector<long> map(0x400);
    for(auto i : tickets){
        for(auto j : i){
            m |= 1 << (j - '0'); 
            if(m == 0x3FF){ break; }
        } 
        map[m] += 1;
        m = 0;
    }
    a += (map[0x3FF] * (map[0x3FF] + 1)) / 2 - map[0x3FF];
    for(int i = map.size() - 1; i >= 0; i--){
        for(int j = i - 1; j >= 0; j--){
            if((i | j) == 1023){
                a += map[i] * map[j];
            }
        }
    }
    return a;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> tickets(n);

    for (int i = 0; i < n; i++) {
        string tickets_item;
        getline(cin, tickets_item);

        tickets[i] = tickets_item;
    }

    long result = winningLotteryTicket(tickets);

    cout << result << "\n";

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
