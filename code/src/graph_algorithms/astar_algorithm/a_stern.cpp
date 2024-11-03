#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

// Struktur für Kanten im Graphen
struct Edge {
    int to;
    double cost;
    Edge* next;

    Edge(int to, double cost) : to(to), cost(cost), next(nullptr) {}
};

// Struktur für Knoten im Graphen
struct Node {
    int id;
    double g;  // bisherige Kosten vom Start
    double h;  // heuristische Kosten (Schätzung)
    double f;  // Gesamtkosten g + h
    Node* parent;  // Zeiger auf den Elternknoten im Pfad
    Node* next;    // Zeiger auf den nächsten Knoten in der offenen Liste

    Node(int id, double g, double h, Node* parent = nullptr) : id(id), g(g), h(h), f(g + h), parent(parent), next(nullptr) {}
};

// Manuelle Implementierung der Liste der offenen Knoten
struct OpenList {
    Node* head;

    OpenList() : head(nullptr) {}

    // Fügt einen Knoten in die Liste sortiert nach den f-Kosten ein
    void insert(Node* node) {
        if (!head || node->f < head->f) {
            node->next = head;
            head = node;
        } else {
            Node* current = head;
            while (current->next && current->next->f < node->f) {
                current = current->next;
            }
            node->next = current->next;
            current->next = node;
        }
    }

    // Nimmt den ersten Knoten aus der Liste
    Node* pop() {
        if (!head) return nullptr;
        Node* node = head;
        head = head->next;
        return node;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

// Berechnung der euklidischen Distanz als Heuristik
double euclideanDistance(int node1, int node2, const double positions[][2]) {
    double dx = positions[node1][0] - positions[node2][0];
    double dy = positions[node1][1] - positions[node2][1];
    return sqrt(dx * dx + dy * dy);
}

// A*-Algorithmus ohne STL
int* aStar(int start, int goal, Edge* graph[], const double positions[][2], int numNodes) {
    OpenList openList;
    double* gScore = new double[numNodes]; // Array für g-Werte
    for (int i = 0; i < numNodes; ++i) {
        gScore[i] = INFINITY;
    }
    gScore[start] = 0;

    Node* startNode = new Node(start, 0, euclideanDistance(start, goal, positions));
    openList.insert(startNode);

    while (!openList.isEmpty()) {
        Node* current = openList.pop();
        if (current->id == goal) {
            // Pfad zurückverfolgen
            int* path = new int[numNodes];
            int index = 0;
            while (current) {
                path[index++] = current->id;
                current = current->parent;
            }
            delete[] gScore;
            return path;
        }

        Edge* edge = graph[current->id];
        while (edge) {
            int neighborId = edge->to;
            double tentative_g = current->g + edge->cost;

            if (tentative_g < gScore[neighborId]) {
                gScore[neighborId] = tentative_g;
                double h = euclideanDistance(neighborId, goal, positions);
                Node* neighborNode = new Node(neighborId, tentative_g, h, current);
                openList.insert(neighborNode);
            }
            edge = edge->next;
        }
    }

    delete[] gScore;
    return nullptr;
}

int main() {
    const int numNodes = 4;

    // Beispielgraph als Adjazenzliste
    Edge* graph[numNodes];
    for (int i = 0; i < numNodes; ++i) {
        graph[i] = nullptr;
    }

    // Kanten des Graphen manuell hinzufügen
    graph[0] = new Edge(1, 1.0);
    graph[0]->next = new Edge(2, 4.0);

    graph[1] = new Edge(0, 1.0);
    graph[1]->next = new Edge(2, 2.0);
    graph[1]->next->next = new Edge(3, 5.0);

    graph[2] = new Edge(0, 4.0);
    graph[2]->next = new Edge(1, 2.0);
    graph[2]->next->next = new Edge(3, 1.0);

    graph[3] = new Edge(1, 5.0);
    graph[3]->next = new Edge(2, 1.0);

    // Knotenpositionen für die Heuristik
    double positions[numNodes][2] = {
        {0, 0},  // Knoten 0
        {1, 1},  // Knoten 1
        {2, 2},  // Knoten 2
        {3, 3}   // Knoten 3
    };

    int start = 0;
    int goal = 3;

    // A*-Algorithmus aufrufen
    int* path = aStar(start, goal, graph, positions, numNodes);

    // Pfad ausgeben
    if (path) {
        cout << "Gefundener Pfad: ";
        for (int i = 0; path[i] != goal; ++i) {
            cout << path[i] << " -> ";
        }
        cout << goal << endl;
        delete[] path;
    } else {
        cout << "Kein Pfad gefunden." << endl;
    }

    // Speicher freigeben
    for (int i = 0; i < numNodes; ++i) {
        Edge* edge = graph[i];
        while (edge) {
            Edge* next = edge->next;
            delete edge;
            edge = next;
        }
    }

    return 0;
}
