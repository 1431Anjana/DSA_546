#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph
{
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

typedef struct Stack
{
    int top;
    unsigned capacity;
    int* array;
} Stack;

Node* createNode(int v)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int n)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = n;

    graph->adjLists = (Node*)malloc(n * sizeof(Node));
    graph->visited = (int*)malloc(n * sizeof(int));

    int i;
    for (i = 0; i < n; i++)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest)
{
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

Stack* createStack(unsigned capacity)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    return stack;
}

int isStackEmpty(Stack* stack)
{
    return (stack->top == -1);
}

int isStackFull(Stack* stack)
{
    return (stack->top == stack->capacity - 1);
}

void push(Stack* stack, int item)
{
    if (isStackFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack)
{
    if (isStackEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}

void dfs(Graph* graph, int startVertex)
{
    Stack* stack = createStack(graph->numVertices);
    graph->visited[startVertex] = 1;
    push(stack, startVertex);

    printf("DFS traversal starting from vertex %d: ", startVertex);

    while (!isStackEmpty(stack))
    {
        int currentVertex = pop(stack);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];

        while (temp)
        {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                push(stack, adjVertex);
            }

            temp = temp->next;
        }
    }

    printf("\n");
}

int main()
{
    int numVertices = 6;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 5);

    int startVertex = 0;
    dfs(graph, startVertex);

    return 0;
}


