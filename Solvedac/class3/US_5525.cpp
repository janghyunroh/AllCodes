//Boj 5525 - IOIOI
#include <iostream>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int N, M;
    string S;

    cin >> N;
    cin >> M;
    cin >> S;
    /**
     * S를 순차탐색하며 최대 길이 IOI부분문자열의 길이를 계속 구하며 더함.
     * IOIIOOIOIIIOIOIOIOIOOOIOIOOIOOIOIO
     * ###   ### ### #####   ###     ### 
     * 각 부분 문자열에 Pn은 (L - (2n+1)) / 2 + 1
     * 
     * 1 + 1 + 1 + 2 + 1 + 1 -> 7개
     * 
    */
    
    char formerChar;    
    // false : 'I'
    // true : 'O'
    int i = 0;
    int cnt_of_I = 0;
    int cnt_sum = 0;
    while(i < S.size()) {
        //cout << "current idx : " << i << " | current count : " << cnt_sum << '\n';
        if(i==0) {
            if(S[i] == 'I') cnt_of_I = 1;
        }

        else if(formerChar != S[i]) {
            if(S[i] == 'I') cnt_of_I++;
        }

        else if(formerChar == S[i]) {
            cnt_sum += ( (cnt_of_I - N) > 0 ? (cnt_of_I - N) : 0 );
            if(S[i]=='I') cnt_of_I = 1;
            else cnt_of_I = 0;
        }
        formerChar = S[i];
        i++;
    }
    cout << cnt_sum;
    return 0;

}