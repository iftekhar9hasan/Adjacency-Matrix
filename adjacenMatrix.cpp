#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

int main() {
    const int INF = -999;

    vector<string> vertices;
    map<string, int> vertexMap;
    vector<vector<int>> matrix;

    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cerr << "Failed to open input file." << endl;
        return 1;
    }

    string line;
    bool isFirstLine = true;

    while (getline(inputFile, line)) {
        if (isFirstLine) {
            stringstream ss(line);
            string vertex;
            while (ss >> vertex) {
                vertices.push_back(vertex);
                vertexMap[vertex] = vertices.size() - 1;
            }

            matrix.resize(vertices.size(), vector<int>(vertices.size(), INF));
            isFirstLine = false;
        }
        else {
            stringstream ss(line);
            string from, to, weightStr;

            if (getline(ss, from, ',') && getline(ss, to, ',') && getline(ss, weightStr)) {
                from = trim(from);
                to = trim(to);
                weightStr = trim(weightStr);

                int weight = stoi(weightStr);

                if (vertexMap.find(from) != vertexMap.end() && vertexMap.find(to) != vertexMap.end()) {
                    int row = vertexMap[from];
                    int col = vertexMap[to];
                    matrix[row][col] = weight;
                }
            }
        }
    }
    inputFile.close();

    cout << "Vertices: { ";
    for (const auto& vertex : vertices) {
        cout << "'" << vertex << "' ";
    }
    cout << "}" << endl;

    cout << "\nmatrix=" << endl;
    for (size_t i = 0; i < matrix.size(); ++i) {
        cout << "+";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << "-----+";
        }
        cout << endl;

        cout << "|";
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            cout << setw(5) << matrix[i][j] << "|";
        }
        cout << endl;
    }

    cout << "+";
    for (size_t j = 0; j < matrix[0].size(); ++j) {
        cout << "-----+";
    }
    cout << endl;

    return 0;
}
