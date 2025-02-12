
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int queue[MAX], front = -1, rear = -1;
int stack[MAX], top = -1;
int visited[MAX];

void enqueue(int vertex) {
    if (rear == MAX - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = vertex;
}

int dequeue() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

void push(int vertex) {
    if (top == MAX - 1) return;
    stack[++top] = vertex;
}

int pop() {
    if (top == -1) return -1;
    return stack[top--];
}

void BFS(int adj[][9], int start, int n) {
    int i, vertex;
    enqueue(start);
    visited[start] = 1;

    printf("BFS Order: ");
    while ((vertex = dequeue()) != -1) {
        printf("%d ", vertex);

        for (i = 0; i < n; i++) {
            if (adj[vertex][i] && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

void DFS(int adj[][9], int start, int n) {
    int i, vertex;
    push(start);
    visited[start] = 1;

    printf("DFS Order: ");
    while ((vertex = pop()) != -1) {
        printf("%d ", vertex);

        for (i = n - 1; i >= 0; i--) {
            if (adj[vertex][i] && !visited[i]) {
                push(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int n = 9;
    int adj[9][9] = {0};
    int v, e, i, j, s, d;

    printf("\nEnter no of vertices: ");
    scanf("%d", &v);
    printf("\nEnter no of edges: ");
    scanf("%d", &e);

    for (i = 0; i < e; i++) {
        printf("Enter source & destination: ");
        scanf("%d %d", &s, &d);
        adj[s][d] = adj[d][s] = 1;
    }

    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < MAX; i++) visited[i] = 0;
    BFS(adj, 0, n);

    for (i = 0; i < MAX; i++) visited[i] = 0;
    DFS(adj, 0, n);

    return 0;
}

