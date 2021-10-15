#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <cstdlib>
#include <sstream>
#include <set>
using namespace std;

const string solution = "123456789ABCDEF0";

struct Node {
	string state;
	string path;
};

int manchDistanceHeuristic(string state) {
	int points = 0;
	for (size_t i = 0; i < solution.length(); i++)
	{
		int perfectLoc = solution.find(state[i]);
		int actualLoc = i;
		int distance = abs(perfectLoc - actualLoc) / 4 + abs(perfectLoc - actualLoc) % 4;
		points += distance;
	}
	return points;
}

bool winCheck(Node a) {
	return (a.state.compare(solution) == 0);
}

string swap(string state, unsigned int a, unsigned int b) {
	string newState(state);
	string temp = newState.substr(a, 1);
	newState[a] = newState[b];
	newState[b] = temp[0];
	return newState;
}

bool canBeSolved(string initData) {
		int inv = 0;
		for (int i = 0; i < 16; i++)
		{
			std::stringstream ssX;
			int x;
			ssX << std::hex << initData[i];
			ssX >> x;

			if (x != 0)
				for (int j = 0; j < i; j++)
				{
					std::stringstream ssY;
					int y;
					ssY << std::hex << initData[j];
					ssY >> y;
					if (y > x)
						inv++;
				}
					
		}
		for (int i = 0; i < 16; i++)
		{
			std::stringstream ssX;
			int x;
			ssX << std::hex << initData[i];
			ssX >> x;
			if (x == 0)
				inv += 1 + i / 4;
		}

		return (inv % 2 == 0);
}

void generateSuccessors(Node curNode, vector<Node>& possible_paths) {
	int loc = curNode.state.find("0");
	if (loc > 3) {
		Node newNode;
		newNode.state = swap(curNode.state, loc, loc - 4);
		newNode.path = curNode.path;
		newNode.path += "u";
		possible_paths.push_back(newNode);
	}
	if (loc < 12) {
		Node newNode;
		newNode.state = swap(curNode.state, loc, loc + 4);
		newNode.path = curNode.path;
		newNode.path += "d";
		possible_paths.push_back(newNode);
	}
	if (loc % 4 < 3) {
		Node newNode;
		newNode.state = swap(curNode.state, loc, loc + 1);
		newNode.path = curNode.path;
		newNode.path += "r";
		possible_paths.push_back(newNode);
	}
	if (loc % 4 > 1) {
		Node newNode;
		newNode.state = swap(curNode.state, loc, loc - 1);
		newNode.path = curNode.path;
		newNode.path += "l";
		possible_paths.push_back(newNode);
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
			if (winCheck(nextNodes[i])) {
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
		if (winCheck(curNode)) {
			return curNode;
		}
		generateSuccessors(curNode, nextNodes);
		for (unsigned int i = 0; i < nextNodes.size(); i++) {
			if (nextNodes[i].path.length() > maxDepth) {
				continue;
			}
			if (winCheck(nextNodes[i])) {
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
		if (winCheck(solved)) {
			return solved;
		}
	}
	return startNode;
}


int main(int argc) {
	Node startNode;
	startNode.state = "16245A3709C8DEBF";
	manchDistanceHeuristic(startNode.state);
	if (winCheck(startNode)) {
		cout << "0" << endl;
		return 0;
	}
	if (!canBeSolved(startNode.state)) {
		cout << "No solution" << endl;
		return 0;
	}
	Node result;

	//cout << "BFS" << endl;
	//result = bfs(startNode);
		
	//cout << "DFS" << endl;
	//result = dfs(startNode);
	
	cout << "IDS" << endl;
	result = ids(startNode);

	cout << "path count: " << result.path.length() << endl;
	cout << "path: " << result.path << endl;
	return 0;
}
