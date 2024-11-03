#include <iostream>
#include <limits> // Für unendlich große Werte
#include <cstdlib>

using namespace std;

// Kantenstruktur für den Graphen
class Edge {
    public:
        int to; //gibt an zu welchem Konton die Kante geht
        double weight; //gibt das Gewicht dieser Kante an
        Edge* next; //Enthält einen Zeiger auf eine Weitere Kante, wiederum mit dem Zielknoten und dem Gwicht und ggfs. weiteren Zeigern auf Edge
        Edge(int to, double weight) : to(to), weight(weight), next(nullptr) {}
};

class Graph {
    Edge* graph;
    void addEdge(Edge* graph[], int from, int to, double weight)
    {
            Edge* edge = new Edge(to, weight);
            //wenn die Kante die von from aus geht noch nicht exisitiert ist das ein null pointer
            //wenn für den Knoten from bereits eine Kante definiert ist, wird diese Kante in "next"
            //umgeängt
            edge->next = graph[from]; 
            graph[from] = edge; //die neue Kante mit den ggfs. umgehängten Kanten wird den Knoten from zugewiesen.        
    }
    // Funktion zur Suche nach dem Knoten mit der minimalen Distanz
    int findMinDistanceNode(bool* visited, double* distances, int numNodes) {
        double minDistance = numeric_limits<double>::infinity();
        int minNode = -1;

        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                minNode = i;
            }
        }

        return minNode;
    }
        // Dijkstra-Algorithmus
    double dijkstra(Edge* graph[], int numNodes, int start, int goal, int* parent) {
        bool* visited = new bool[numNodes];
        double* distances = new double[numNodes];

        // Initialisieren der Distanzwerte und Besuchszustände
        for (int i = 0; i < numNodes; ++i) {
            visited[i] = false;
            distances[i] = numeric_limits<double>::infinity();
            parent[i] = -1;  // Pfadrekonstruktion: Setze Elternknoten auf -1
        }

        // Startknoten initialisieren
        distances[start] = 0;

        for (int i = 0; i < numNodes; ++i) {
            int currentNode = findMinDistanceNode(visited, distances, numNodes);
            if (currentNode == -1) {
                break; // Keine weiteren erreichbaren Knoten
            }

            visited[currentNode] = true;

            // Nachbarn des aktuellen Knotens überprüfen
            Edge* edge = graph[currentNode];
            while (edge != nullptr) {
                int neighbor = edge->to;
                double newDist = distances[currentNode] + edge->weight;

                // Wenn der neue Pfad kürzer ist, aktualisiere die Distanz und den Elternknoten
                if (newDist < distances[neighbor]) {
                    distances[neighbor] = newDist;
                    parent[neighbor] = currentNode;
                }
                edge = edge->next;
            }
        }

        // Rückgabe der kürzesten Distanz zum Zielknoten
        double result = distances[goal];
        
        delete[] visited;
        delete[] distances;

        return result;
    }

    // Funktion zur Ausgabe des Pfades
    void printPath(int* parent, int currentNode) {
        if (parent[currentNode] == -1) {
            cout << currentNode << " ";
            return;
        }
        printPath(parent, parent[currentNode]);
        cout << currentNode << " ";
    }


};



// Hilfsfunktion, um den Graphen als Adjazenzliste zu initialisieren
void addEdge(Edge* graph[], int from, int to, double weight) {
    Edge* edge = new Edge(to, weight);
    //wenn die Kante die von from aus geht noch nicht exisitiert ist das ein null pointer
    //wenn für den Knoten from bereits eine Kante definiert ist, wird diese Kante in "next"
    //umgeängt
    edge->next = graph[from]; 
    graph[from] = edge; //die neue Kante mit den ggfs. umgehängten Kanten wird den Knoten from zugewiesen.
}

// Funktion zur Suche nach dem Knoten mit der minimalen Distanz
int findMinDistanceNode(bool* visited, double* distances, int numNodes) {
    double minDistance = numeric_limits<double>::infinity();
    int minNode = -1;

    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i] && distances[i] < minDistance) {
            minDistance = distances[i];
            minNode = i;
        }
    }

    return minNode;
}

// Dijkstra-Algorithmus
double dijkstra(Edge* graph[], int numNodes, int start, int goal, int* parent) {
    bool* visited = new bool[numNodes];
    double* distances = new double[numNodes];

    // Initialisieren der Distanzwerte und Besuchszustände
    for (int i = 0; i < numNodes; ++i) {
        visited[i] = false;
        distances[i] = numeric_limits<double>::infinity();
        parent[i] = -1;  // Pfadrekonstruktion: Setze Elternknoten auf -1
    }

    // Startknoten initialisieren
    distances[start] = 0;

    for (int i = 0; i < numNodes; ++i) {
        int currentNode = findMinDistanceNode(visited, distances, numNodes);
        if (currentNode == -1) {
            break; // Keine weiteren erreichbaren Knoten
        }

        visited[currentNode] = true;

        // Nachbarn des aktuellen Knotens überprüfen
        Edge* edge = graph[currentNode];
        while (edge != nullptr) {
            int neighbor = edge->to;
            double newDist = distances[currentNode] + edge->weight;

            // Wenn der neue Pfad kürzer ist, aktualisiere die Distanz und den Elternknoten
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                parent[neighbor] = currentNode;
            }
            edge = edge->next;
        }
    }

    // Rückgabe der kürzesten Distanz zum Zielknoten
    double result = distances[goal];
    
    delete[] visited;
    delete[] distances;

    return result;
}

// Funktion zur Ausgabe des Pfades
void printPath(int* parent, int currentNode) {
    if (parent[currentNode] == -1) {
        cout << currentNode << " ";
        return;
    }
    printPath(parent, parent[currentNode]);
    cout << currentNode << " ";
}

int main() {
    const int numNodes = 4; // A=0, B=1, C=2, D=3
    Edge* graph[numNodes] = { nullptr };

    // Hinzufügen der Kanten
    addEdge(graph, 0, 1, 3.0); // A → B
    addEdge(graph, 1, 3, 8.0); // B → D
    addEdge(graph, 1, 2, 3.0); // B → C
    addEdge(graph, 2, 3, 3.0); // C → D
    addEdge(graph, 0, 3, 12.0); // A → D

    // Knoten "A" ist 0, "D" ist 3
    int start = 0; // A
    int goal = 3;  // D
    int* parent = new int[numNodes];  // Array zur Pfadrekonstruktion

    // Dijkstra-Algorithmus aufrufen
    double shortestDistance = dijkstra(graph, numNodes, start, goal, parent);

    if (shortestDistance == numeric_limits<double>::infinity()) {
        cout << "Kein Pfad gefunden." << endl;
    } else {
        cout << "Kürzeste Entfernung von A nach D: " << shortestDistance << endl;
        cout << "Pfad: ";
        printPath(parent, goal);  // Pfad von A nach D ausgeben
        cout << endl;
    }

    // Speicher freigeben
    delete[] parent;
    for (int i = 0; i < numNodes; ++i) {
        Edge* edge = graph[i];
        while (edge != nullptr) {
            Edge* next = edge->next;
            delete edge;
            edge = next;
        }
    }

    return 0;
}
