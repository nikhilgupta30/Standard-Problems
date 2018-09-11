#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll mode = 1000000007;

struct AdjListNode{
    ll dest;
    ll weight;
    struct AdjListNode* next;
};
 
struct AdjList{
    struct AdjListNode *head;  // pointer to head node of list
};
 
struct Graph{
    ll V;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(ll dest, ll weight){
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(ll V){

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for (ll i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
void addEdge(struct Graph* graph, ll src, ll dest, ll weight){

    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
struct MinHeapNode{
    ll  v;
    ll dist;
};
 
struct MinHeap{
    ll size;      // Number of heap nodes present currently
    ll capacity;  // Capacity of min heap
    ll *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(ll v, ll dist){
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
struct MinHeap* createMinHeap(ll capacity){
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (ll *)malloc(capacity * sizeof(ll));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, ll idx){

    ll smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx){

        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
ll isEmpty(struct MinHeap* minHeap){
    return minHeap->size == 0;
}
 
struct MinHeapNode* extractMin(struct MinHeap* minHeap){

    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
void decreaseKey(struct MinHeap* minHeap, ll v, ll dist){

    ll i = minHeap->pos[v];
 
    minHeap->array[i]->dist = dist;
 
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist){

        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        i = (i - 1) / 2;
    }
}
 
bool isInMinHeap(struct MinHeap *minHeap, ll v){

    if (minHeap->pos[v] < minHeap->size)
        return true;
    return false;
}
 
void printArr(ll dist[], ll n){

    printf("Vertex   Distance from Source\n");
    for (ll i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
void dijkstra(struct Graph* graph, ll src){

    ll V = graph->V;// Get the number of vertices in graph
    ll dist[V];      // dist values used to pick minimum weight edge in cut
 
    struct MinHeap* minHeap = createMinHeap(V);
 
    for (ll v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    minHeap->size = V;
 
    while (!isEmpty(minHeap)){

        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        ll u = minHeapNode->v; // Store the extracted vertex number
 
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            ll v = pCrawl->dest;
 
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    printArr(dist, V);
}
 
int main(){
    
    ll V = 9;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);
 
    dijkstra(graph, 0);
 
    return 0;
}
