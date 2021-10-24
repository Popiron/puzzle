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
using namespace std;
using namespace std;

const string solution = "123456789ABCDEF0";

struct Node {
	string state;
	string path;
};

struct MancNode {
	string state;
	string path;
	int heuristic;
};

int getInt16(char c) {
	std::stringstream ssX;
	int x;
	ssX << std::hex << c;
	ssX >> x;
	return x;
}

int linearConflictHeuristic(string state) {
	int distance = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			int curr = getInt16(state[4 * i + j]);
			if (curr == 0)
				continue;
			if (i == (curr - 1) / 4)
				for (int k = j + 1; k < 4; k++)
				{
					int next = getInt16(state[4 * i + k]);
					if (next == 0)
						continue;
					if ((next - 1) / 4 == i && curr > next)
						distance += 2;
				}
			if (j == (curr - 1) % 4)
			{
				for (int k = i + 1; k < 4; k++)
				{
					int next = getInt16(state[4 * k + j]);
					if (next == 0)
						continue;
					if ((next - 1) % 4 == j && curr > next)
						distance += 2;
				}
			}
		}
		}
	return distance;
}

int manchDistanceHeuristic(string state) {
	int points = 0;
	for (size_t i = 0; i < solution.length(); i++)
	{
		if (state[i] == '0')
			continue;
		int perfectLoc = solution.find(state[i]);
		int actualLoc = i;
		int colDistance = abs(perfectLoc/4 - actualLoc/4);
		int distance = colDistance + abs(perfectLoc%4 - actualLoc%4);
		points += distance;
	}
	return points;
}

bool winCheck(string state) {
	return (state.compare(solution) == 0);
}

string swap(string state, size_t a, size_t b) {
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

void manchGenerateSuccessor(MancNode curNode, vector<MancNode>& possible_paths) {
	int loc = curNode.state.find('0');

	if (loc > 3) {
		MancNode newNode;
		newNode.state = swap(curNode.state, loc, loc - 4);
		newNode.path = curNode.path;
		newNode.path += 'u';
		newNode.heuristic = newNode.path.size() + manchDistanceHeuristic(newNode.state)+ linearConflictHeuristic(newNode.state);
		possible_paths.push_back(newNode);
	}
	if (loc < 12) {
		MancNode newNode;
		newNode.state = swap(curNode.state, loc, loc + 4);
		newNode.path = curNode.path;
		newNode.path += 'd';
		newNode.heuristic = newNode.path.size() + manchDistanceHeuristic(newNode.state)+ linearConflictHeuristic(newNode.state);

		possible_paths.push_back(newNode);
	}
	if (loc % 4 < 3) {
		MancNode newNode;
		newNode.state = swap(curNode.state, loc, loc + 1);
		newNode.path = curNode.path;
		newNode.path += 'r';
		newNode.heuristic = newNode.path.size() + manchDistanceHeuristic(newNode.state)+ linearConflictHeuristic(newNode.state);

		possible_paths.push_back(newNode);
	}
	if (loc % 4 > 0) {
		MancNode newNode;
		newNode.state = swap(curNode.state, loc, loc - 1);
		newNode.path = curNode.path;
		newNode.path += 'l';
		newNode.heuristic = newNode.path.size() + manchDistanceHeuristic(newNode.state)+ linearConflictHeuristic(newNode.state);

		possible_paths.push_back(newNode);
	}
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
	if (loc % 4 > 0) {
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

struct CompareHeuristic {
	bool operator()(MancNode const& p1, MancNode const& p2)
	{
		return p1.heuristic > p2.heuristic;
	}
};

MancNode aStar(Node startNode) {
	MancNode manchStartNode;
	manchStartNode.state = startNode.state;
	manchStartNode.path = startNode.path;
	manchStartNode.heuristic = manchStartNode.path.size()+ manchDistanceHeuristic(startNode.state) + linearConflictHeuristic(startNode.state);

	priority_queue<MancNode,vector<MancNode>,CompareHeuristic> frontier;
	frontier.push(manchStartNode);

	unordered_map<string, size_t> expanded;

	while (!frontier.empty()) {

		MancNode curNode = frontier.top();
		frontier.pop();

		expanded[curNode.state] = 1;

		vector<MancNode> nextNodes;
		manchGenerateSuccessor(curNode, nextNodes);

		for (size_t i = 0; i < nextNodes.size(); i++) {

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


int main(int argc) {
	Node startNode;
	startNode.state = "DBE87A2C91F65034";
	manchDistanceHeuristic(startNode.state);
	if (winCheck(startNode.state)) {
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
	
	//cout << "IDS" << endl;
	//result = ids(startNode);

	//cout << "path count: " << result.path.length() << endl;
	//cout << "path: " << result.path << endl;

	cout << "A*" << endl;
	MancNode mancResult = aStar(startNode);
	//
	cout << "path count: " << mancResult.path.length() << endl;
	cout << "path: " << mancResult.path << endl;
	return 0;
}
