//Fazlı Güdül
//Section 2
//student id: 22002785
#ifndef BUILDINGMAP_H
#define BUILDINGMAP_H

#include <string>
#include <vector>
#include <fstream>
#include <utility> 
#include "Stack.h"

class BuildingMap {
public:
    BuildingMap(const std::string& buildingMapFile);
    ~BuildingMap();
    
    void displayAllCubicles() const;
    void displayAdjacentCubicles(int row, int col) const;
    void displayBuildingMap() const;
    void findPaths(int startRow, int startCol, int endRow, int endCol);
    void findPaths(int startRow, int startCol, int endRow, int endCol, int avoidRow, int avoidCol);

private:
    struct PathNode {
        std::vector<std::pair<int, int>> path;
        PathNode* next;
        PathNode(const std::vector<std::pair<int, int>>& pathVal) : path(pathVal), next(nullptr) {}
    };

    PathNode* head = nullptr; 

    void sortedInsert(const std::vector<std::pair<int, int>>& newItem);
    void printPaths() const;
    void clearPaths();
    std::vector<std::vector<int>> map;
    int rows, cols;

    void readMap(const std::string& fileName);
    std::vector<std::pair<int, int>> getAdjacentCubicles(int row, int col) const;
    void dfsPaths(Stack<std::pair<int, int>>& stack, std::vector<std::vector<bool>>& visited, std::vector<std::pair<int, int>>& currentPath, int x, int y, int endRow, int endCol, bool avoid, int avoidRow, int avoidCol);
};

#endif // BUILDINGMAP_H