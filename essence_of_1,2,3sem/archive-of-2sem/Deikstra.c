
/*
 n - число вершин;
 m - число ребер;
 x, y, w;
 начальная вершина;
 get_next_node - следующая вершина с минимальной меткой;
 */

1)
unsigned get_next_node(unsigned Visited[100], unsigned Marks[100], unsigned n) {
    unsigned m = (unsigned) (-1);
    for (i = 0; i < n; i++) {
        if (!Visited[i] && (m == (unsigned) (-1) || (m > Marks[i])))
            m = Marks[i];
    }
    return m;
}
unsigned G[100][100]={{0}}, Visited[100] = {0}, Marks[100];
unsigned i, j, m, n, x, y, w;
scanf("%n %n", &n, &m);
for (i = 0; i < n; i++)
    Marks[i] = (unsigned) (-1);
for (i = 0; i < m: i++) {
    scanf("%n %n %n", &x, &y, &w);
    G[x][y] = G[y][x] = w;
}
scanf("%n", &x);
Marks[x] = 0;
while(get_next_node(Visited, Marks, n) != (unsigned) (-1)) {
    Visited[i] = 1;
    for (j = 0; j < n; j++)
        if (G[i][j] > 0 && !Visited[j] && Marks[i] + G[i][j] < Marks[j])
            Marks[j] = Marks[i] + G[i][j];
}
for (i = 0; i < n; i++)
    printf("%d", (int) Marks[i]);

2)
typedef struct Node Node;
typedef struct List List;

struct Node {
    unsigned mark;
    unsigned visited;
    List * neighbours;
}

struct List {
    Node * item;
    unsigned weight;
    List * next;
}
{
    Node * G;
    ...
    scanf("%u %u", &n, &n);
    G = (Node *) calloc (n * sizeof(Node));
    for (i = 0; i < m;  i++) {
        scanf("%u %u %u", &x, &y, &w);
        G[x], neigb = list_add(G[x], neighbours, &G[y], w);
    
    }
}
unsigned get_next_node(Node * G, unsigned n) {
    unsigned m = (unsigned) (-1);
    for (i = 0; i < n; i++) {
        if (!G[i].visited && (m == (unsigned) (-1) || (m > G[i].mark)))
            m = G[i].mark;
    }
    return m;
}
unsigned i, j, m, n, x, y, w;
while(i = get_next_node(G, n) != (unsigned) (-1)) {
    G[i].visited = 1;
    List * list;
    for (list = G[i].neighbours; list; list = list -> next)
        if (!list -> item -> visited && G[i].mark + list->weight < list->item->mark)
            list->item->mark = G[i].mark + list->weight;
}
for (i = 0; i < n; i++)
    printf("%d", (int) G[i].mark);
for (i = 0; i < n; i++) {
    list_destroy(G[i].neighbours);
    free(G);
}
