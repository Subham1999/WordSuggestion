#ifndef INCLUDE
	#include <vector>
	#include <string>
	#include <fstream>
	#include <map>
	#include <set>
	#include <algorithm>
	using namespace std;
#endif
class WordSuggestor{
	int min(int x, int y){
		return (x < y) ? x : y;
	}
	int edt_distance(string str1, string str2){
	 	int m = (int)str1.length();
	 	int n = (int)str2.length();
	    int dp[m + 1][n + 1];
	    for (int i = 0; i <= m; i++) { 
	        for (int j = 0; j <= n; j++) { 
	            if (i == 0) 
	                dp[i][j] = j;
	            else if (j == 0) 
	                dp[i][j] = i;
	            else if (str1[i - 1] == str2[j - 1]) 
	                dp[i][j] = dp[i - 1][j - 1]; 
	            else
	                dp[i][j] = 1 + min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
	        } 
	    }
	    return dp[m][n]; 
	} 
	vector<string> util_for_suggestion(const vector<pair<string, int>>& dictonary, const string word){
		vector<pair<string, pair<int, int>>> temp;
		for(pair<string, int> each : dictonary){
			int dist = edt_distance(each.first, word);
			temp.push_back({each.first, {dist, each.second}});
		}
		sort(temp.begin(), temp.end(), [](pair<string, pair<int, int>> one, pair<string, pair<int, int>> two){
			return (one.second.first < two.second.first) || \
			(one.second.first == two.second.first && one.second.second > two.second.second);
		});
		vector<string> result;
		for(int i = 0; i < (int)temp.size(); i++){
			result.push_back(temp[i].first);
		}
		return result;
	}
public:
	WordSuggestor(){}
	void suggestMe(const vector<pair<string, int>> dictonary, const string word){
		vector<string> result = util_for_suggestion(dictonary, word);
		for(string each : result){
			cout << each << endl;
		}
		return;
	}
};