#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

void read_file(std::unordered_set<std::string> &words) {
	std::ifstream f("words.txt");
	std::string word;
	while(f >> word) words.insert(word);
}

void bfs(const std::unordered_set<std::string> &words, const std::string& target, const std::string& source) {

	std::queue<std::string> q;
	std::unordered_map<std::string, std::string> parent;
	parent[target] = "";
	q.push(target);
	while (!q.empty()) {
        	string w = q.front(); q.pop();
        	string n = w;
        	for (int i = 0; i < 4; ++i) {
            		char orig = n[i];
            		for (char c = 'A'; c <= 'Z'; ++c) {
                		if (c == orig) continue;
                		n[i] = c;
               			if (words.count(n) && !parent.count(n)) {
                    			parent[n] = w;
                    			q.push(n);
                		}
            		}
            		n[i] = orig;
       		}
    	}
	vector<string> path;
    	for (string w = source; !w.empty(); w = parent[w]) path.push_back(w);
    	std::cout << path.size() - 1 << " steps: ";
    	for (size_t i = 0; i < path.size(); ++i) std::cout << (i ? " -> " : "") << path[i];
    	cout << "\n";
}

void update_file(const std::unordered_set<string> &words, const std::string &rm) {

	ofstream on("words.txt");
	
	for (auto &word : words) {
		if (word != rm) on << word << std::endl;
	}
	on.close();
}

int main(int argc, char** argv) {

	const std::string TARGET = "POOP";
	const std::string SOURCE = argv[1];
	std::unordered_set<std::string> words;
	read_file(words);	
	if (SOURCE == "rm") {update_file(words, argv[2]); return 0;}	
	bfs(words, TARGET, SOURCE);
}
