//Boj 1389 - 케빈 베이컨의 6단계 법칙
/**
 * all to all shortest path 후 (플로이드 워셜)
 * 각 점 별로 최단 거리의 합 계산하여 
 * 최소인 번호(동일한 경우 번호가 작은 사람)
*/
#include <iostream>
#include <algorithm>
#define INF 100000
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int dist[101][101];
    int N, M;
    cin >> N >> M;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            if(i==j) dist[i][j] = 0;
            else dist[i][j] = INF;
        }
    }
    
    for(int i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        dist[a][b] = 1;
        dist[b][a] = 1;
    }

    //Floyd Warshall
    for(int k = 1; k <= N; k++) {
        for(int i = 1; i <= N; i++) {
            for(int j = 1; j <= N; j++) {
                dist[i][j] = min(dist[i][k] + dist[k][j], dist[i][j]);
            }
        }
    }
    //debugging
    // for(int i = 1; i <= N; i++) {
    //     for(int j = 1; j <= N; j++) cout << dist[i][j] << ' ';
    //     cout << '\n';
    // }

    //
    int min_ = INF, min_idx = 1;
    for(int i = 1; i <= N; i++) {
        int sum = 0;
        for(int j = 1; j <= N; j++) sum += dist[i][j];
        //cout << i << '|' << sum << '\n';
        
        if(min_ > sum) {
            min_ = sum;
            min_idx = i;
        }
    }
    cout << min_idx;
}
