#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

void bfs(int n, int source, int amat[][SIZE], int visited[]) {
    int q[SIZE], r=0, f=0, u, v;
    visited[source]=1; q[r]=source;
    while(f<=r){
        u= q[f++];
        for(v=0;v<n;v++){
            if((amat[u][v]==1)&(visited[v]==0)){
                q[++r]=v;
                visited[v]=1;
            }
        }
    }
}

void dfs(int n, int u, int amat[][SIZE], int visited[]) {
    int v;
    // Step 1: Mark the current node as visited
    visited[u] = 1;
    
    // Step 2: Look at all neighbors 'v' of the current node 'u'
    for (v = 0; v < n; v++) {
        // If there is a connection AND the neighbor hasn't been visited
        if (amat[u][v] == 1 && visited[v] == 0) {
            // Visit that neighbor immediately (going deeper)
            dfs(n, v, amat, visited);

            // the child's end will be reached first > then next parent
        }
    }
}

int main() {
    int n, amat[SIZE][SIZE], source, visited[SIZE]={0}, i, j;

    printf("Enter number of vertices:\n"); scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");    // a n square matrix inputed.
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            scanf("%d", &amat[i][j]);   // cols denote where connection are present for A (row 0) on row 1, row 2, (B and C) where connection from A to B is denoted by row[0][1] = 1.

    printf("The adjacency matrix is:\n");
    for(i=0; i<n; i++){
        for(j=0; j<n; j++)
            printf("%d\t", amat[i][j]);
        printf("\n");
    }

    printf("Give the source:\n");
    scanf("%d", &source);
    bfs(n, source, amat, visited);  // Starting from source, the output is visited rows. The source is already visited. The source shows the directions to visit. We follow all directions from source, and show n row's 1-D visited arr

    printf("Showcasing bfs:\n");
    for(i=0;i<n;i++){
        if(visited[i]==0)
            printf("%d is not reachable\n", i);
        else
            printf("%d is reachable\n",i);
    }
    
    for(i=0;i<n;i++)
        visited[i] = 0;    // reset visited arr (to showcase dfs as well)

    dfs(n, source, amat, visited);

    printf("Showcasing dfs: \n");
    for(i=0;i<n;i++){
        if(visited[i]==0)
            printf("%d is not reachable\n", i);
        else
            printf("%d is reachable\n",i);
    }
    
    return 0;
}
