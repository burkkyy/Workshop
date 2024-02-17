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
    long ans = 0, m = 0, n = tickets.size();
    vector<bitset<10>> map;

    for(auto i : tickets){
        for(auto j : i){
            m |= 1 << (j - '0'); 
            if(m == 0x3FF){ ans++; m = 0; break; }
        }
        if(m != 0){ map.push_back(m); m = 0; }
    }
    
    for(int i = 0; i < map.size(); i++){
        for(int j = i + 1; j < map.size(); j++){
            auto c = map[i] | map[j];
            if(c.to_ulong() == 0x3FF){ ans++; }
        }
    }
    for(int i = 1; i <= n - map.size(); i++){ ans += n - i - 1; }
    return ans;
}
/* Brute force method
long winningLotteryTicket(vector<string> tickets) {
    long ans = 0;
    bitset<10> check;
    string con;
    for(int i = 0; i < tickets.size(); i++){
        for(int j = i + 1; j < tickets.size(); j++){
            con = tickets[i] + tickets[j];
            for(auto s : con){
                switch(s){
                    case '0': check.set(0, 1); break;
                    case '1': check.set(1, 1); break;
                    case '2': check.set(2, 1); break;
                    case '3': check.set(3, 1); break;
                    case '4': check.set(4, 1); break;
                    case '5': check.set(5, 1); break;
                    case '6': check.set(6, 1); break;
                    case '7': check.set(7, 1); break;
                    case '8': check.set(8, 1); break;
                    case '9': check.set(9, 1); break;
                }
            }
            if(check.to_ulong() == 1023){ ans++; }
            check.reset();
        }
    }
    return ans;
} */

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
