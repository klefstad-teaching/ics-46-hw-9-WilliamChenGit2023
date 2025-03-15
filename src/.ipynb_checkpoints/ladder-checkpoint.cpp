#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <cmath>
#include "ladder.h"
using namespace std;

void error(string word1, string word2, string msg){
	cout << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
	return true;
}
bool is_adjacent(const string& word1, const string& word2){
	if(word1 == word2) return true;
	int n1 = word1.size();
	int n2 = word2.size();
	int diff = abs(n1-n2);
	if(diff >= 2) return false; 
	else if(diff == 1){
		bool skipped = false;
		int i1 = 0;
		int i2 = 0;
		while(i1 < n1 && i2 < n2){
			if(word1[i1]!=word2[i2]){
				if(skipped) return false;
				else{
					skipped = true;
					if(n1>n2) i1++;
					else i2++;
				}
			}
			else{
				i1++;
				i2++;
			}
		}
		return true;
	}
	else{
		bool changed = false;
		for(int i = 0; i < n1; i++){
			if(word1[i]!=word2[i]){
				if(changed) return false;
				else changed = true;
			}
		}
		return true;
	}
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
	queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                if (word == end_word) {
                    return new_ladder;
                }
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {}; 
	
}

void load_words(set<string> & word_list, const string& file_name){
	ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file: " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder){
	if(ladder.size() == 0) cout << "No word ladder found.\n";
	else{
		cout << "Word ladder found: ";
		for(string s: ladder){
			cout << s << " ";
		}
		cout << "\n";
	}
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}