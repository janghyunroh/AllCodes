//
#include <iostream>
using namespace std;
using ll = long long;
int N, M;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //greedy
    cin >> N >> M;
    ll sum = 0;
    for(int i = 0; i < N; i++) {
        int a; cin >> a;
        sum += a;
    }
    for(int i = 0; i < M; i++) {
        int b; cin >> b;
        if(b != 0) sum *= b;
    }
    cout << sum;

}