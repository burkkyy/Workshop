#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'anotherMinimaxProblem' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int get_msb(int n){
	int msb = 0;
	while(n != 0){
		//cout << "stuck msb " << n << endl;
		n = n >> 1;
		msb++;
	}
	return msb;
}

int anotherMinimaxProblem(vector<int> a) {
	vector<int> copy = a;
	sort(copy.begin(), copy.end());
	if(copy[copy.size() - 1] == 0){ return 0; }
	
	int temp, msb;
	vector<int> big;
	int max = get_msb(copy[copy.size() - 1]);

	for(;;){
		big.clear();
		max = get_msb(copy[copy.size() - 1]);
		for(auto i : copy){
			if(get_msb(i) == max){
				big.push_back(i);
			}
		}
		if(big.size() == copy.size()){
			for(int i = 0; i < copy.size(); i++){
				if(get_msb(copy[i]) == max){
					copy[i] -= (1 << (max-1));
				}
			}
		} else {
			break;
		}
	}
	
	long prev_best = 0xFFFFFFFF;
	long best = 0xFFFFFFFF;
	for(auto i : big){
		for(auto j : copy){
			if(i != j && get_msb(j) < max){
				temp = i ^ j;
				if(temp < best){
					best = temp;
				} 
			}
		}
		if(best < prev_best){
			prev_best = best;
		}
	}
	/*
	for(int i = 0; i < a.size(); i++){
		for(int j = i + 1; j < a.size(); j++){
			temp = a[i] ^ a[j];
			if(temp == 32769 || temp == 65568){
				cout << "i: " << a[i] << " i msb: " << get_msb(a[i]) << " j: " << a[j] << " j msb: " << get_msb(a[j]) << endl;
				bitset<32> b(a[i]);
				bitset<32> c(a[j]);
				cout << b << endl;
				cout << c << endl;
			}
		}
	}
	*/
	return prev_best;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = anotherMinimaxProblem(a);
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

