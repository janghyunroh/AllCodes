#include <iostream>
#include <queue>

using namespace std;

vector<pair<int, pair<int, int>>> rooms;
bool convs[1001][1001] = {false, };
bool visited[1001][1001] = {false, };
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int N, M, R, C;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> N >> M >> R >> C;  
    for(int i = 0; i < R; i++) {
        int a, b, p; cin >> a >> b >> p;
        pair<int, int> room = make_pair(a, b);
        rooms.emplace_back(p, room);
    }
    
    for(int i = 0; i < C; i++) {
        int c, d; cin >> c >> d;
        convs[c][d] = true;
    }
    
    //BFS
    priority_queue<pair<int, pair<int, pair<int, int>>>> pq;
    //pq 쓰면 메모리 초과남
    //그냥 queue 쓰고 visited 배열 쓰기
    //근데 각 방마다 cost가 다른데? 
    //q ( 현재까지의 편세권 점수, x, y )
    
    for(auto room : rooms) {
        pq.emplace(0, room);
    }
    
    //BFS 수행
    while(pq.size()) {
        auto it = pq.top(); pq.pop();

        int dist = -it.first;
        int p = it.second.first;
        int convx = it.second.second.first;
        int convy = it.second.second.second;
        
        //편의점을 찾은 경우
        if(convs[convx][convy]) {
            cout << dist;
            return 0;
        }
        
        //
        for(int i = 0; i < 4; i++) {
            int newx = convx + dx[i];
            int newy = convy + dy[i];
            if(newx > 0 && newx <= N && newy > 0 && newy <= M) {
                pair<int, int> next = make_pair(newx, newy);
                pair<int, pair<int, int>> next_room = make_pair(p, next);
                pq.emplace(-(dist + p), next_room);
            }
                
        }        
    }
    
    
}