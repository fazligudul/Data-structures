//Fazlı Güdül
//Section 2
//student id: 22002785
#include "BuildingMap.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

BuildingMap::BuildingMap(const string& buildingMapFile) {
    readMap(buildingMapFile);
    cout << rows << " rows and " << cols << " columns have been read." << endl;
}

BuildingMap::~BuildingMap() {
    clearPaths();
}

void BuildingMap::readMap(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        throw runtime_error("Unable to open file");
    }
    file >> rows >> cols;
    map.resize(rows, vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        string line;
        file >> line;
        for (int j = 0; j < cols; ++j) {
            map[i][j] = line[j] - '0';
        }
    }
    file.close();
}

void BuildingMap::displayAllCubicles() const {
    cout << "The cubicles in the building are:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "(" << i << "," << j << ")";
            if (j < cols - 1){
                cout << ",";
            }
        }
        cout << endl;
    }
}

void BuildingMap::displayAdjacentCubicles(int row, int col) const {
    auto adj = getAdjacentCubicles(row, col);
    cout << "The cubicles adjacent to (" << row << "," << col << ") are:" << endl;
    cout << "(" << row << "," << col << ") -> ";
    for (const auto& p : adj) {
        cout << "(" << p.first << "," << p.second << ")";
        if (&p != &adj.back()){
            cout << ",";
        }
    }
    cout << endl;
}

void BuildingMap::displayBuildingMap() const {
    cout << "The building map is as follows:" << endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            auto adj = getAdjacentCubicles(i, j);
            cout << "(" << i << "," << j << ") -> ";
            for (const auto& p : adj) {
            cout << "(" << p.first << "," << p.second << ")";
                if (&p != &adj.back()){
                    cout << ",";
                }
            }
            cout << endl; 
        }
    }
}

void BuildingMap::findPaths(int startRow, int startCol, int endRow, int endCol) {
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") are:" << endl;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    Stack<pair<int, int>> stack;
    vector<pair<int, int>> path;
    dfsPaths(stack, visited, path, startRow, startCol, endRow, endCol, false, -1, -1);
    printPaths();
    clearPaths();
}

void BuildingMap::findPaths(int startRow, int startCol, int endRow, int endCol, int avoidRow, int avoidCol) {
    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," << endCol << ") avoiding (" << avoidRow << "," << avoidCol << ") are:" << endl;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    Stack<pair<int, int>> stack;
    vector<pair<int, int>> path;
    dfsPaths(stack, visited, path, startRow, startCol, endRow, endCol, true, avoidRow, avoidCol);
    printPaths();
    clearPaths();
}

vector<pair<int, int>> BuildingMap::getAdjacentCubicles(int row, int col) const {
    vector<pair<int, int>> adj;
    if (row > 0 && !(map[row-1][col] & 2)){
        adj.emplace_back(row-1, col); 
    }
    if (row < rows - 1 && !(map[row][col] & 2)) {
        adj.emplace_back(row+1, col);
    }
    if (col > 0 && !(map[row][col] & 1)){
        adj.emplace_back(row, col-1); 
    }
    if (col < cols - 1 && !(map[row][col+1] & 1)){
        adj.emplace_back(row, col+1); 
    }
    sort(adj.begin(), adj.end());
    return adj;
}

void BuildingMap::dfsPaths(Stack<pair<int, int>>& stack, vector<vector<bool>>& visited, vector<pair<int, int>>& currentPath, int x, int y, int endRow, int endCol, bool avoid, int avoidRow, int avoidCol) {
    stack.push({x, y});
    currentPath.push_back({x, y});
    visited[x][y] = true;

    if ( y == endCol && x == endRow ) {
        sortedInsert(currentPath);
        currentPath.pop_back();
        stack.pop();
        visited[x][y] = false;
        return;
    }

    auto adj = getAdjacentCubicles(x, y);
    for (const auto& [nx, ny] : adj) {
        if (!visited[nx][ny] && !(avoid && nx == avoidRow && ny == avoidCol)) {
            dfsPaths(stack, visited, currentPath, nx, ny, endRow, endCol, avoid, avoidRow, avoidCol);
        }
    }

    visited[x][y] = false;
    currentPath.pop_back();
    stack.pop();
}

void BuildingMap::sortedInsert(const vector<pair<int, int>>& newItem) {
    PathNode* newNode = new PathNode(newItem);
    PathNode** ptr = &head;

    while (*ptr != nullptr && (*ptr)->path < newItem) {
        ptr = &((*ptr)->next);
    }
    newNode->next = *ptr;
    *ptr = newNode;
}

void BuildingMap::printPaths() const {
    if (!head) {
        cout << "None" << endl;
        return;
    }

    for (PathNode* current = head; current != nullptr; current = current->next) {
        for (const auto& p : current->path) {
            cout << "(" << p.first << "," << p.second << ")";
            if (&p != &current->path.back()){
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void BuildingMap::clearPaths() {
    while (head != nullptr) {
        PathNode* temp = head;
        head = head->next;
        delete temp;
    }
}
