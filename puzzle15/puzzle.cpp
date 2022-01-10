#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <set>
#include <unordered_map>
using namespace std;



struct Node {
	string state;
	string path;
};

string win = "xWGCB";

bool checkEquality(string state1, string state2) {
	string oneSideS = state1.substr(0, state1.find('x'));
	string anotherSideS = state1.substr(state1.find('x'), state1.length() - state1.find('x'));

	string oneSide = state2.substr(0, state2.find('x'));
	string anotherSide = state2.substr(state2.find('x'), state2.length() - state2.find('x'));

	if (oneSideS.length() == oneSide.length())
	{
		for (size_t i = 0; i < oneSideS.length(); i++)
		{
			if (oneSideS.find(oneSide[i]) == string::npos)
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool winCheck(string state) {
	return checkEquality(state, win);
}

bool defeatCheck(string state) {
	return checkEquality(state, "WGxBC") || checkEquality(state, "BCxWG") || checkEquality(state, "GCxBW") || checkEquality(state, "BWxGC");;
}

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

bool loopCheck(string path,string state) {
	vector<string> v = split(path, " ");
	for (string s : v) {
		return checkEquality(s, state);
	} 
}

void generateSuccessors(Node curNode, vector<Node>& possible_paths) {
	if (curNode.state.find('G') > curNode.state.find('x') && curNode.state.find('B') > curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'G'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'G');
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'B');
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path,newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
		
	}
	else if (curNode.state.find('G') < curNode.state.find('x') && curNode.state.find('B') < curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'G'), newNode.state.end());
		newNode.state.append("G");
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.append("B");
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	if (curNode.state.find('W') > curNode.state.find('x') && curNode.state.find('B') > curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'W'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'W');
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'B');

		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	else if (curNode.state.find('W') < curNode.state.find('x') && curNode.state.find('B') < curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'W'), newNode.state.end());
		newNode.state.append("W");
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.append("B");
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	if (curNode.state.find('C') > curNode.state.find('x') && curNode.state.find('B') > curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'C'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'C');
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'B');
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	else if (curNode.state.find('C') < curNode.state.find('x') && curNode.state.find('B') < curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'C'), newNode.state.end());
		newNode.state.append("C");
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.append("B");
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	if (curNode.state.find('B') > curNode.state.find('x')) {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.insert(newNode.state.begin(), 1, 'B');
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
	else {
		Node newNode;
		newNode.state = curNode.state;
		newNode.state.erase(remove(newNode.state.begin(), newNode.state.end(), 'B'), newNode.state.end());
		newNode.state.append("B");
		if (!defeatCheck(newNode.state) && !loopCheck(curNode.path, newNode.state)) {
			newNode.path = curNode.path;
			newNode.path += " " + newNode.state;
			possible_paths.push_back(newNode);
		}
	}
}

Node bfs(Node startNode) {
	queue<Node> frontier;
	frontier.push(startNode);
	map<string, int> expanded;	
	while (!frontier.empty()) {
		Node curNode = frontier.front();
		frontier.pop();
		expanded[curNode.state] = 1;
		vector<Node> nextNodes;
		generateSuccessors(curNode, nextNodes);
		for (unsigned int i = 0; i < nextNodes.size(); i++) {
			if (winCheck(nextNodes[i].state)) {
				return nextNodes[i];
			}
			if (expanded.find(nextNodes[i].state) != expanded.end()) {
				continue;
			}
			frontier.push(nextNodes[i]);
		}
	}
}

Node dfs(Node startNode, int maxDepth = 80) {
	stack<Node> frontier;
	frontier.push(startNode);
	map<string, int> expanded;
	while (!frontier.empty()) {
		Node curNode = frontier.top();
		frontier.pop();
		expanded[curNode.state] = curNode.path.length();
		vector<Node> nextNodes;
		if (winCheck(curNode.state)) {
			return curNode;
		}
		generateSuccessors(curNode, nextNodes);
		for (unsigned int i = 0; i < nextNodes.size(); i++) {
			if (nextNodes[i].path.length() > maxDepth) {
				continue;
			}
			if (winCheck(nextNodes[i].state)) {
				return nextNodes[i];
			}
			if (expanded.find(nextNodes[i].state) != expanded.end()
				&& expanded[nextNodes[i].state] < nextNodes[i].path.length()) {
				continue;
			}
			frontier.push(nextNodes[i]);
		}
	}
	return startNode;
}

Node ids(Node startNode) {
	for (unsigned int i = 1; i < 80; i++) {
		Node solved = dfs(startNode, i);
		if (winCheck(solved.state)) {
			return solved;
		}
	}
	return startNode;
}

enum Algo {
	BFS,
	DFS,
	IDS,
};

const string initState = "WGCBx";

int main(int argc) {
	Node startNode;

	startNode.state = initState;
	startNode.path = initState;

	if (winCheck(startNode.state)) {
		cout << "0" << endl;
		return 0;
	}

	if (defeatCheck(startNode.state)) {
		cout << "1" << endl;
		return 0;
	}

	Algo algo = IDS;

	switch (algo)
	{
	case BFS: {
		cout << "BFS" << endl;
		Node result;
		result = bfs(startNode);
		cout << "path count: " << split(result.path," ").size() << endl;
		cout << "path: " << result.path << endl;
		break;
	}
	case DFS: {
		cout << "DFS" << endl;
		Node result;
		result = dfs(startNode);
		cout << "path count: " << split(result.path, " ").size() << endl;
		cout << "path: " << result.path << endl;
		break;
	}

	case IDS: {
		cout << "IDS" << endl;
		Node result;
		result = ids(startNode);
		cout << "path count: " << split(result.path, " ").size() << endl;
		cout << "path: " << result.path << endl;
		break;
	}
		
	default:
		break;
	}

	return 0;
}
