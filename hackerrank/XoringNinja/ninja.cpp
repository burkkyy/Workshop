#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

int sansaXor(vector<int> arr) {
    bitset<32> ans(0);
    int n = arr.size(), num = n;
    int* p = new int[n]();
    p[0] = n;
    cout << p[0] << " ";
    for(int i = 1; i < n; i++){
        num -= 2;
        p[i] += p[i - 1] + num;
        cout << p[i] << " ";
    }
    cout << endl;

    int msb_count = 0;
    for(int i = 0; i < 32; i++){
        msb_count = 0;
        for(int j = 0; j < n; j++){
            bitset<32> b(arr[j]);
            msb_count += b[i] * p[j];
        }
        if(msb_count == 0 || msb_count % 2 == 0){
            ans[i] = 0;
        } else {
            ans[i] = 1;
        }
    }

    delete[] p;
    return (int)ans.to_ulong();
}

/*
 * Complete the 'xoringNinja' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int xoringNinja(vector<int> arr) {
    int a = 0, m = 0x3B9ACA07;
    sansaXor(arr);
    return a;
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string arr_count_temp;
        getline(cin, arr_count_temp);

        int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(arr_count);

        for (int i = 0; i < arr_count; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        int result = xoringNinja(arr);

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

