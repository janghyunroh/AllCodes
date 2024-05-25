#include <iostream>

using namespace std;

int N, Q;
bool com[200001] = {false, };
int cnt = 0;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;
    for(int i = 0; i < Q; i++) {
        int mode; cin >> mode;
        if(mode == 1) {
            int x; cin >> x;
            if(!com[x]) {
                com[x] = true;
                cnt++;
            }
        }
        else if(mode == 2) {
            int x; cin >> x;
            if(com[x]) {
                com[x] = false;
                cnt--;
            }
        }
        else {
            cout << N - cnt << '\n';
        }
    }
}