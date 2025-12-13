#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

const int INF = numeric_limits<int>::max();

struct ProgramOptions {
    int vertices = 0;        
    bool isWeighted = true;    
    bool isDirected = true;    
    bool showHelp = false;    
    int maxWeight = 15;        
};

void showHelp() {
    cout << "=== ПАРАМЕТРЫ КОМАНДНОЙ СТРОКИ ===" << endl;
    cout << "Использование: program [параметры]" << endl;
    cout << endl;
    cout << "Параметры:" << endl;
    cout << "  -n <число>     Количество вершин графа (обязательный параметр)" << endl;
    cout << "  -t <тип>       Тип графа: 'weighted' (взвешенный) или 'unweighted' (невзвешенный)" << endl;
    cout << "  -o <ориентация> Ориентация: 'directed' (ориентированный) или 'undirected' (неориентированный)" << endl;
    cout << "  -w <число>     Максимальный вес ребра (только для взвешенных графов)" << endl;
    cout << "  -h             Показать эту справку" << endl;
    cout << endl;
    cout << "Примеры:" << endl;
    cout << "  program.exe -n 10 -t weighted -o directed -w 20" << endl;
    cout << "  program.exe -n 5 -t unweighted -o undirected" << endl;
    cout << "  program.exe -h" << endl;
    cout << endl;
    cout << "При запуске без параметров активируется интерактивный режим." << endl;
}

ProgramOptions parseArguments(int argc, char* argv[]) {
    ProgramOptions options;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            options.vertices = atoi(argv[i + 1]);
            i++;
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "weighted") == 0) {
                options.isWeighted = true;
            } else if (strcmp(argv[i + 1], "unweighted") == 0) {
                options.isWeighted = false;
            } else {
                cerr << "Ошибка: неизвестный тип графа: " << argv[i + 1] << endl;
                cerr << "Допустимые значения: weighted, unweighted" << endl;
                exit(1);
            }
            i++;
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            if (strcmp(argv[i + 1], "directed") == 0) {
                options.isDirected = true;
            } else if (strcmp(argv[i + 1], "undirected") == 0) {
                options.isDirected = false;
            } else {
                cerr << "Ошибка: неизвестная ориентация: " << argv[i + 1] << endl;
                cerr << "Допустимые значения: directed, undirected" << endl;
                exit(1);
            }
            i++;
        } else if (strcmp(argv[i], "-w") == 0 && i + 1 < argc) {
            options.maxWeight = atoi(argv[i + 1]);
            if (options.maxWeight <= 0) {
                cerr << "Ошибка: максимальный вес должен быть положительным" << endl;
                exit(1);
            }
            i++;
        } else if (strcmp(argv[i], "-h") == 0) {
            options.showHelp = true;
        } else {
            cerr << "Ошибка: неизвестный параметр: " << argv[i] << endl;
            cerr << "Используйте -h для просмотра справки" << endl;
            exit(1);
        }
    }
    
    return options;
}

vector<vector<int>> createGraph(const ProgramOptions& options) {
    int n = options.vertices;
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n; 
        int weight = options.isWeighted ? (1 + rand() % options.maxWeight) : 1;
        graph[i][j] = weight;
        if (!options.isDirected) {
            graph[j][i] = weight;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && rand() % 3 == 1) {
                int weight = options.isWeighted ? (1 + rand() % options.maxWeight) : 1;
                graph[i][j] = weight;
                if (!options.isDirected) {
                    graph[j][i] = weight;
                }
            }
        }
    }
    
    return graph;
}

void printAdjacencyMatrix(const vector<vector<int>>& graph, const ProgramOptions& options) {
    int n = graph.size();
    
    cout << "Матрица смежности ";
    if (options.isDirected) {
        cout << "ориентированного ";
    } else {
        cout << "неориентированного ";
    }
    if (options.isWeighted) {
        cout << "взвешенного ";
    } else {
        cout << "невзвешенного ";
    }
    cout << "графа:" << endl;
    
    cout << "   ";
    for (int i = 0; i < n; i++) {
        cout << setw(3) << i;
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << setw(2) << i << ":";
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 0 && i != j) {
                cout << setw(3) << "-";
            } else {
                cout << setw(3) << graph[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> floydWarshall(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] > 0) {
                dist[i][j] = graph[i][j];
            }
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    return dist;
}

void printShortestDistances(const vector<vector<int>>& dist) {
    int n = dist.size();
    
    cout << "Матрица кратчайших расстояний (-1 означает недостижимость):" << endl << endl;
    
    cout << "|    |";
    for (int j = 0; j < n; j++) {
        cout << setw(3) << j << " |";
    }
    cout << endl;
    
    cout << "|";
    for (int j = 0; j <= n; j++) {
        cout << "----|";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "| " << setw(2) << i << " |";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) {
                cout << setw(3) << -1 << " |";
            } else {
                cout << setw(3) << dist[i][j] << " |";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void calculateGraphProperties(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<int> eccentricity(n, 0);
    
    for (int i = 0; i < n; i++) {
        int maxDist = 0;
        bool hasUnreachable = false;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if (dist[i][j] == INF) {
                    hasUnreachable = true;
                } else if (dist[i][j] > maxDist) {
                    maxDist = dist[i][j];
                }
            }
        }
        
        if (hasUnreachable) {
            eccentricity[i] = INF;
        } else {
            eccentricity[i] = maxDist;
        }
    }
    
    int radius = INF;
    int diameter = 0;
    
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] != INF) {
            if (eccentricity[i] < radius) {
                radius = eccentricity[i];
            }
            if (eccentricity[i] > diameter) {
                diameter = eccentricity[i];
            }
        }
    }
    
    if (radius == INF) {
        radius = -1;
    }
    if (diameter == 0) {
        diameter = -1;
    }
    
    vector<int> centralVertices;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == radius) {
            centralVertices.push_back(i);
        }
    }
    
    vector<int> peripheralVertices;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == diameter) {
            peripheralVertices.push_back(i);
        }
    }
    
    cout << "=== СВОЙСТВА ГРАФА ===" << endl;
    
    cout << "Эксцентриситеты вершин:" << endl;
    for (int i = 0; i < n; i++) {
        if (eccentricity[i] == INF) {
            cout << "Вершина " << i << ": недостижимы некоторые вершины (∞)" << endl;
        } else {
            cout << "Вершина " << i << ": " << eccentricity[i] << endl;
        }
    }
    cout << endl;
    
    if (radius == -1 || diameter == -1) {
        cout << "Граф не является сильно связным. Радиус и диаметр не определены." << endl;
    } else {
        cout << "Радиус графа: " << radius << endl;
        cout << "Диаметр графа: " << diameter << endl;
    }
    
    if (!centralVertices.empty()) {
        cout << "Центральные вершины: ";
        for (size_t i = 0; i < centralVertices.size(); i++) {
            cout << centralVertices[i];
            if (i < centralVertices.size() - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    
    if (!peripheralVertices.empty()) {
        cout << "Периферийные вершины: ";
        for (size_t i = 0; i < peripheralVertices.size(); i++) {
            cout << peripheralVertices[i];
            if (i < peripheralVertices.size() - 1) {
                cout << " ";
            }
        }
        cout << endl << endl;
    }
}

ProgramOptions interactiveInput() {
    ProgramOptions options;
    
    cout << "=== ИНТЕРАКТИВНЫЙ РЕЖИМ ===" << endl;
    cout << "Введите количество вершин в графе: ";
    cin >> options.vertices;
    
    if (options.vertices <= 0) {
        cout << "Ошибка: количество вершин должно быть положительным!" << endl;
        exit(1);
    }
    
    char choice;
    cout << "Граф взвешенный? (y/n, по умолчанию y): ";
    cin >> choice;
    if (choice == 'n' || choice == 'N') {
        options.isWeighted = false;
    }
    
    if (options.isWeighted) {
        cout << "Введите максимальный вес ребра (по умолчанию 15): ";
        string weightInput;
        cin >> weightInput;
        if (!weightInput.empty()) {
            options.maxWeight = stoi(weightInput);
        }
    }
    
    cout << "Граф ориентированный? (y/n, по умолчанию y): ";
    cin >> choice;
    if (choice == 'n' || choice == 'N') {
        options.isDirected = false;
    }
    
    return options;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    
    ProgramOptions options;
    
    if (argc > 1) {
        options = parseArguments(argc, argv);
        
        if (options.showHelp) {
            showHelp();
            return 0;
        }
        
        if (options.vertices == 0) {
            cout << "Ошибка: не указано количество вершин!" << endl;
            cout << "Используйте параметр -n <число>" << endl;
            cout << "Для справки используйте: " << argv[0] << " -h" << endl;
            return 1;
        }
    } else {
        options = interactiveInput();
    }
    
    cout << endl;
    cout << "=== ПАРАМЕТРЫ ПРОГРАММЫ ===" << endl;
    cout << "Количество вершин: " << options.vertices << endl;
    cout << "Тип графа: " << (options.isWeighted ? "взвешенный" : "невзвешенный") << endl;
    if (options.isWeighted) {
        cout << "Максимальный вес ребра: " << options.maxWeight << endl;
    }
    cout << "Ориентация: " << (options.isDirected ? "ориентированный" : "неориентированный") << endl;
    cout << endl;
    
    cout << "Создание графа из " << options.vertices << " вершин..." << endl;
    auto graph = createGraph(options);
    
    printAdjacencyMatrix(graph, options);
    
    auto distMatrix = floydWarshall(graph);
    
    printShortestDistances(distMatrix);
    
    calculateGraphProperties(distMatrix);
    
    return 0;
}