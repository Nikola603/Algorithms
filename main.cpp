using namespace std;
#include <iostream>
#include <stdio.h>
#include <limits.h>

#define V 9 // Ukupan broj autobuskih stanica.

int counter = 1;
int array[V];
int arrayOfCounters[V];

struct Matrix {
     int numOfRows;
     int numOfCols;
     int** data;
};

void allocateMatrix(Matrix* pMatrix, int numOfRows, int numOfColumns) {
     pMatrix->data = new int* [numOfRows];
     for(int i = 0; i < numOfRows; i++) {
        pMatrix->data[i] = new int [numOfColumns];
     }
     pMatrix->numOfCols = numOfColumns;
     pMatrix->numOfRows = numOfRows;
}

void deallocateMatrix(Matrix* pMatrix) {
     for(int i = 0; i < pMatrix->numOfRows; i++) {
        delete[] pMatrix->data[i];
     }
     delete[] pMatrix->data;
     pMatrix->numOfCols = 0;
     pMatrix->numOfRows = 0;
}

/*  Pomocna funkcija za pronalazenje sledece stanice s minimalnom
    vrednoscu rastojanja od izvorisne stanice na putu do odredisne stanice.  */
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for(int i = 0; i < V; i++) {
        if(sptSet[i] == false && dist[i] <= min) {
            min = dist[i], min_index = i;
        }
    }
    return min_index;
}

/* Kada je popunjen niz parent[], koristi se rekurzivna funkcija
   da bi se zabelezile najkrace putanje do svakog odredista. */
void saveStation(int parent[], int j) {
    if(parent[j] == -1) {
        return;
    }
    saveStation(parent, parent[j]);
    //printf("array[%d]: %d\n", counter, array[counter]);
    array[counter++] = j;
}

void printSolution(int parent[]) {
    int dest;

    Matrix matrix;
    int numberOfColumns = V;
    int numberOfRows = V;

    allocateMatrix(&matrix, numberOfRows, numberOfColumns);

    for(int i = 0; i < V; i++) {
        saveStation(parent, i);
        //printf("\n");
        for(int m = 0; m < counter; m++) {
            matrix.data[i][m] = array[m];
        }
        arrayOfCounters[i] = counter;
        counter = 1;
    }

    while(1) {
        cout << "*--------------------------------------------*" << endl;
        cout << "*---------------GSP Kragujevac---------------*" << endl;
        cout << "*--------------------------------------------*\n" << endl;

        cout << "Source: 0" << endl;

        while(1) {
            cout << "Destination? ";
            cin >> dest;
            if(!(dest >= V || dest < 0)) break;
        }

        cout << "\nShortest path:" << endl;
        for(int j = 0; j < arrayOfCounters[dest]; j++) {
            cout << matrix.data[dest][j];
            if(j < arrayOfCounters[dest]-1) {
                cout << " -> ";
            }
        }

        cout << "\n" <<endl;
        cout << "*--------------------------------------------*" << endl;
        cout << "\n\n" <<endl;

        char ch = getchar();
        if(ch == 'q') break; // Exit the program.
    }

    deallocateMatrix(&matrix);
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];       // Predstavlja niz koji cuva najkrace rastojanje od izvorisne stanice X do odredisne stanice Y.
    bool sptSet[V];    // Predstavlja niz koji govori za koje odredisne stanice je pronadjena najkraca putanja od izvorisne stanice.
    int parent[V];     // Predstavlja niz koji cuva vrhove stabla koji ulaze u najkracu putanju do svakog odredista.

    for(int i = 0; i < V; i++) {
        parent[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    // Pronalazi najkrace putanje do svake odredisne stanice.
    for(int i = 0; i < V-1; i++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for(int j = 0; j < V; j++) {
            if(!sptSet[j] && graph[u][j] && dist[u] + graph[u][j] < dist[j]) {
                parent[j]  = u;
                dist[j] = dist[u] + graph[u][j];
               //printf("\ni:%d j:%d parent[j]:%d dist[j]: %d\n", i, j, parent[j], dist[j]);
            }
        }
    }

    /*
    for(int i = 0; i < V; i++) {
        printf("%d ", parent[i]);
    }
    printf("\n");
    */

    printSolution(parent);
}

int main() {
    // Matrica susedstva, govori koje dve susedne stanice su povezane direktno.
                    //  0  1  2  3  4  5  6  7  8
    int graph[V][V] = {{0, 1, 0, 0, 0, 0, 0, 1, 0}, // 0
                       {1, 0, 1, 0, 0, 0, 0, 1, 0}, // 1
                       {0, 1, 0, 1, 0, 1, 0, 0, 1}, // 2
                       {0, 0, 1, 0, 1, 1, 0, 0, 0}, // 3
                       {0, 0, 0, 1, 0, 1, 0, 0, 0}, // 4
                       {0, 0, 1, 0, 1, 0, 1, 0, 0}, // 5
                       {0, 0, 0, 1, 0, 1, 0, 1, 1}, // 6
                       {1, 1, 0, 0, 0, 0, 1, 0, 1}, // 7
                       {0, 0, 1, 0, 0, 0, 1, 1, 0}  // 8
                      };

    dijkstra(graph, 0);

    return 0;
}
