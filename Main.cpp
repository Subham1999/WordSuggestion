#include <iostream>
#include <fstream>
#include "WordSuggestor.cpp"
using namespace std;

pair<string, int> process_line(string line){
	int start = 0;
	string word;
	int frequency;
	int length = (int)line.length();
	for(int i = 0; i < (int)line.length(); i++){
		if(line[i] == ','){
			word = line.substr(start, i - start);
		} else if(line[i] == ' '){
			start = i + 1;
		}
	}
	frequency = stoi(line.substr(start, length - start));
	return {word, frequency};
}

void show_suggestion(const vector<pair<string, int>>& dictonary, const string word){
	WordSuggestor* suggestor = new WordSuggestor();
	suggestor->suggestMe(dictonary, word);
}
int main(int argc, char const *argv[]){
	ifstream infile(argv[1]);
	string word = argv[2];
	if(infile.is_open() and infile.good()){
		string line = "";
        vector<pair<string, int>> input;
        while (getline(infile, line)){			// input from file is taken
            input.push_back(process_line(line));
        }
        show_suggestion(input, word);
        infile.close();
	}
	return 0;
}