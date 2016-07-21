//Angel Morales
//HW#3
//http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
#include <cstdio>

//Finding the maximum flow using Ford-Fulkerson Algorithm and Breadth-First Search
void maximum_flow(int n, int s, int t, int *capacity, int *flow);


void maximum_flow(int n, int s, int t, int *capacity, int *flow) {
// Breadth-First Search Algorithm
// Declarations and Initializations
    const int infin = 999999;
    bool out = true;
    int *BF;
    BF = new int[n]; //
    int *Apath;
    Apath = new int[n];  // Store the augmenting path
    // Pop ,Push and queued to be used for  Breadth-First Search Algorithm
    int pop, push;
    int *queue = new int[n + 2];
// Breadth-First Search Algorithm Start
    while (out) {
        for (int i = 0; i < n; i++) {
            BF[i] = 0;//Not visited =0
        }
        pop = 0;
        push = 0;
        queue[push] = s;
        push++;
        BF[s] = 1;
        Apath[s] = -1;
        // Unless the queue is empty
        while (pop != push) {
            int x = queue[pop];
            pop++;
            BF[x] = 2;//popped
            int i = x;
            // Search all adjacent nodes
            for (int j = 0; j < n; j++) {     // Explores the vertex if it's connected and unexplored
                if ((BF[j] == 0) && (*(capacity + i * n + j) - *(flow + i * n + j) > 0)) {

                    queue[push] = j;
                    BF[j] = 1; //It's push and visited
                    Apath[j] = i;
                    push++;
                }
            }
        }
        //Check to see if target vertex t is reached
        out = BF[t] == 2;

        // Start of Ford-Fulkerson Algorithm
        int incr = infin;
        // Find minimum residual capacity
        int k;
        for (k = n - 1; Apath[k] >= 0; k = Apath[k])
        {
            if (incr > *(capacity + Apath[k] * n + k) - *(flow + Apath[k] * n + k))
                incr = *(capacity + Apath[k] * n + k) - *(flow + Apath[k] * n + k);
        }
        // Update residual capacities
        for (k = n - 1; Apath[k] >= 0; k = Apath[k])
        {
            *(flow + Apath[k] * n + k) += incr;
            *(flow + k * n + Apath[k]) -= incr;
        }
    }
}

int cap[1000][1000], flow[1000][1000];

int main(void) {
    int i, j, flowsum;
    for (i = 0; i < 1000; i++)
        for (j = 0; j < 1000; j++)
            cap[i][j] = 0;

    for (i = 0; i < 499; i++)
        for (j = i + 1; j < 500; j++)
            cap[i][j] = 2;
    for (i = 1; i < 500; i++)
        cap[i][500 + (i / 2)] = 4;
    for (i = 500; i < 750; i++) {
        cap[i][i - 250] = 3;
        cap[i][750] = 1;
        cap[i][751] = 1;
        cap[i][752] = 5;
    }
    cap[751][753] = 5;
    cap[752][753] = 5;
    cap[753][750] = 20;
    for (i = 754; i < 999; i++) {
        cap[753][i] = 1;
        cap[i][500] = 3;
        cap[i][498] = 5;
        cap[i][1] = 100;
    }
    cap[900][999] = 1;
    cap[910][999] = 1;
    cap[920][999] = 1;
    cap[930][999] = 1;
    cap[940][999] = 1;
    cap[950][999] = 1;
    cap[960][999] = 1;
    cap[970][999] = 1;
    cap[980][999] = 1;
    cap[990][999] = 1;
    printf("prepared capacity matrix, now executing maxflow code\n");
    maximum_flow(1000, 0, 999, &(cap[0][0]), &(flow[0][0]));
    for (i = 0; i <= 999; i++)
        for (j = 0; j <= 999; j++) {
            if (flow[i][j] > cap[i][j]) {
                printf("Capacity violated\n");
                return (0);
            }
        }
    flowsum = 0;
    for (i = 0; i <= 999; i++)
        flowsum += flow[0][i];
    printf("Outflow of  0 is %d, should be 10\n", flowsum);
    flowsum = 0;
    for (i = 0; i <= 999; i++)
        flowsum += flow[i][999];
    printf("Inflow of 999 is %d, should be 10\n", flowsum);

    printf("End Test\n");
    return 0;
}
