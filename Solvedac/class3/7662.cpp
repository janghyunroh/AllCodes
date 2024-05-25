//Boj 7662 - 이중 우선순위 큐

/**
 * 우선순위가 가장 높은 데이터와 낮은 데이터 모두 접근 가능 --> deque
 * 우선 순위 deque을 구현하는 것이 목표
 * k ≤ 1,000,000인데 제한 시간 6초
 * 
 * 1. 힙을 사용하는 경우 
 * - 삽입 : 
 * - 제거 - 최대 : O(1)
 *       - 최소 : <-- 얘가 문제네...    
 * 
 * 2. priority queue 2개를 쓰는 경우
 * 
 * max_pq
 * min_pq
 * 
 * 삽입 : 양쪽에 push
 * 삭제 : mode에 맞춰 삭제 후 
 * 
 * 문제점 :  중간 인덱스에 대한 random access가 불가능하므로 별도의 추가 메커니즘이 필요
 * 문제가 되는 부분 : 한쪽에서의 pop이 다른 한 쪽에는 적용되지 못함
 * 
 * 유효성 검증 배열
 * 삽입되었던 모든 원소에 대한 유효성(PQ에 이미 존재하는지)을 저장하는 배열
 * 삽입될 때 alive 배열에도 true를 push
 * 삭제시 false로 만듦
 * 어느 한 쪽에서 pop이 되면 두 pq의 '보이는'(top) invalid 값을 버리기
 * 
 * 
 * 3. Heap 2개를 쓰는 경우
 * 
 * max_heap --> a 삽입
 * min_heap --> -a 삽입
 * 
 * 삽입 : 양쪽에 모두 - O(1)
 * 한쪽 top 삭제 후 해당 element key를 이용해 반대 쪽 원소 삭제 - O(n log n)
 * 
 * 문제점 : C++에선 vector에 대한 heapify를 사용하므로 매 update마다 heapify(O(n))해야 함
 * 
 * ---------------
 * 2번 방법을 이용해 해결
 * 
*/
#include <iostream>
#include <queue>

using ll = long long;
using namespace std;

int T, k;
char oper;



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >>  T;
    while(T--) {
        //초기화
        int cnt = 0;    //삽입된/되었던 모든 원소의 개수 - 모든 history 기록
        priority_queue<pair<ll, int>> max_pq;
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>> > min_pq;
        vector<bool> is_alive;   //모든 history에 대한 유효성 검사
        
        cin >> k;
        for(int i = 0; i < k; i++) {
            cin >> oper;
            if(oper == 'I') {
                ll a; cin >> a;

                // a 삽입
                max_pq.emplace(a, cnt);
                min_pq.emplace(a, cnt);
                is_alive.push_back(true);
                cnt++;
            }
            else if(oper == 'D') {
                int mode; cin >> mode;
                if(max_pq.empty()) continue;
                if(mode == 1) {
                    is_alive[max_pq.top().second] = false;
                    max_pq.pop();
                    while(!max_pq.empty() && !is_alive[max_pq.top().second]) max_pq.pop();
                    while(!min_pq.empty() && !is_alive[min_pq.top().second]) min_pq.pop();
                }
                else {
                    is_alive[min_pq.top().second] = false;
                    min_pq.pop();
                    while(!max_pq.empty() && !is_alive[max_pq.top().second]) max_pq.pop();
                    while(!min_pq.empty() && !is_alive[min_pq.top().second]) min_pq.pop();
                }
            }
        }
        //
        if(max_pq.empty()) cout << "EMPTY" << '\n';
        else cout << max_pq.top().first << ' ' << min_pq.top().first << '\n';
    }
}