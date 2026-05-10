#include <stdio.h>
#include <stdlib.h>

#define MAX 5

int graph[MAX][MAX];
int NumberOfVertices;

int visited[MAX] = {0};

void create() {

    int edges;

    printf("Enter Number Of Edges: ");
    scanf("%d", &edges);

    for(int i=0; i<edges; i++) {

        int source, destination;

        printf("Enter Source Vertex: ");
        scanf("%d", &source);

        printf("Enter Destination Vertex: ");
        scanf("%d", &destination);

        graph[source][destination] = 1;
        graph[destination][source] = 1;
    }
}

void addEdge() {

    int source, destination;

    printf("Enter Source Vertex: ");
    scanf("%d", &source);

    printf("Enter Destination Vertex: ");
    scanf("%d", &destination);

    graph[source][destination] = 1;
    graph[destination][source] = 1;

    printf("Edge Added Successfully\n");
}

void printAdjacency() {

    printf("\nAdjacency Matrix:\n");

    for(int i=0; i<NumberOfVertices; i++) {

        for(int j=0; j<NumberOfVertices; j++) {

            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }
}

void listAllVertices() {

    int vertex;

    printf("Enter Vertex: ");
    scanf("%d", &vertex);

    printf("Adjacent Vertices of %d are: ", vertex);

    for(int i=0; i<NumberOfVertices; i++) {

        if(graph[vertex][i] == 1) {

            printf("%d ", i);
        }
    }

    printf("\n");
}

void DFS(int vertex) {

    visited[vertex] = 1;

    printf("%d ", vertex);

    for(int i=0; i<NumberOfVertices; i++) {

        if(graph[vertex][i] == 1 && visited[i] == 0) {

            DFS(i);
        }
    }
}

void BFS(int start) {

    int queue[MAX];

    int front = 0;
    int rear = 0;

    int visited[MAX] = {0};

    visited[start] = 1;

    queue[rear++] = start;

    while(front < rear) {

        int vertex = queue[front++];

        printf("%d ", vertex);

        for(int i=0; i<NumberOfVertices; i++) {

            if(graph[vertex][i] == 1 && visited[i] == 0) {

                visited[i] = 1;

                queue[rear++] = i;
            }
        }
    }
}

int main() {

    printf("Enter Number Of Vertices: ");
    scanf("%d", &NumberOfVertices);

    for(int i=0; i<NumberOfVertices; i++) {

        for(int j=0; j<NumberOfVertices; j++) {

            graph[i][j] = 0;
        }
    }

    while(1) {

        int choice;

        printf("\n----- GRAPH MENU -----");
        printf("\n1. Create Graph");
        printf("\n2. Insert Edge");
        printf("\n3. Print Adjacency Matrix");
        printf("\n4. List Adjacent Vertices");
        printf("\n5. Depth First Search");
        printf("\n6. Breadth First Search");
        printf("\n7. Exit");

        printf("\nEnter Your Choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                create();
                break;

            case 2:
                addEdge();
                break;

            case 3:
                printAdjacency();
                break;

            case 4:
                listAllVertices();
                break;

            case 5: {

                int start;

                for(int i=0; i<MAX; i++) {
                    visited[i] = 0;
                }

                printf("Enter Starting Vertex: ");
                scanf("%d", &start);

                printf("DFS Traversal: ");

                DFS(start);

                printf("\n");

                break;
            }

            case 6: {

                int start;

                printf("Enter Starting Vertex: ");
                scanf("%d", &start);

                printf("BFS Traversal: ");

                BFS(start);

                printf("\n");

                break;
            }

            case 7:
                exit(0);

            default:
                printf("Enter Valid Choice\n");
        }
    }

    return 0;
}