#include <stdio.h>
int queue[MAX], front = -1, rear = -1;
void enqueue(int v) {
	if (rear == MAX - 1) {
		printf("Queue Overflow\n");
		return;
	}
	if (front == -1) {
		front = 0;
	}
	queue[++rear] = v;
}
int dequeue() {
	if (front == -1 || front > rear) {
		printf("Queue Underflow\n");
		return -1;
	}
	return queue[front++];
}
int isQueueEmpty() {
	return front == -1 || front > rear;
}
void BFS(int startVertex) {
	int currentVertex;
	GNODE temp;
	visited[startVertex] = 1;
	enqueue(startVertex);
	while (!isQueueEmpty()) {
		currentVertex = dequeue();
		printf("%d\n", currentVertex);
		temp = graph[currentVertex];
		while (temp != NULL) {
			int adjVertex = temp->vertex;
			if (!visited[adjVertex]) {
				visited[adjVertex] = 1;
				enqueue(adjVertex);
			}
			temp = temp->next;
		}
	}
}
int main() {
	int n, E, s, d, i;
	GNODE p, q;
	for (i = 0; i < MAX; i++) {
		graph[i] = NULL;
		visited[i] = 0;
	}
	printf("Enter no of vertices: ");
	scanf("%d", &n);
	printf("Enter no of edges: ");
	scanf("%d", &E);
	for (i = 1; i <= E; i++) {
		printf("Enter source: ");
		scanf("%d", &s);
		printf("Enter destination: ");
		scanf("%d", &d);
		q = (GNODE)malloc(sizeof(struct node));
		q->vertex = d;
		q->next = NULL;
		if (graph[s] == NULL) {
			graph[s] = q;
		} else {
			p = graph[s];
			while (p->next != NULL) {
			p = p->next;
			}
			p->next = q;
		}
	}
	int startVertex;
	printf("Enter Start Vertex for BFS: ");
	scanf("%d", &startVertex);
	printf("BFS of graph: \n");
	BFS(startVertex);
	return 0;
}
