//Boj 9019 - DSLR
/**
 * 레지스터 1개, 0000~9999
 * D : (reg * 2) % 10000
 * S : (reg + 9999) % 10000
 * L : 1234 -> 2341
 * R : 1234 -> 4123
 * 
 * 숫자 A에서 B로 변환하는 최소 연산 횟수
 * 각 추가 연산의 cost가 모두 1로 동일하므로 BFS로 최단 경로 계산 가능
 * --> BFS 사용
 * A의 D, S, L, R 값이 not visited인 경우 갱신하고 경로와 함께 큐에 삽입 
 * 연산을 해야 하는 경우 lazy하게 그때 숫자로 변환하여 계산하고, 실제 저장은 문자열로 진행
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

string Lrotate(string str) {    //O(1)
    string newStr = "0000";
    for(int i = 0; i < 3; i++) {
        newStr[i] = str[i + 1];
    }
    newStr[3] = str[0];
    return newStr;
}

string Rrotate(string str) {    //O(1)
    string newStr = "0000";
    for(int i = 0; i < 3; i++) {
        newStr[i + 1] = str[i];
    }
    newStr[0] = str[3];
    return newStr;
}

int StrToI(string str) {    //O(1)
    int ret = 0;
    int idx = 0;
    while(idx < 4) {
        ret = ret * 10 + ((int)(str[idx] - 48));
        idx++;
    }
    return ret;
}

string IToStr(int num) {    //O(1)
    string ret = "0000";
    int idx = 3;
    while(num > 0 && idx >= 0) {
        char c = (char) ((num % 10) + 48);
        ret[idx] = c;
        idx--;
        num /= 10;
    }
    return ret;
} 

int T;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    //debugging
    // string testStr;
    // int testInt;
    // cout << "---testing---" << '\n';
    // cout << "string : ";
    // cin >> testStr;
    // cout << StrToI(testStr) << '|'  << Lrotate(testStr) << '|' << Rrotate(testStr) << '\n';
    
    // cout << "int : ";
    // cin >> testInt;
    // cout << IToStr(testInt) << '\n';
    

    cin >> T;
    while(T--) {    //O(T)
        bool visited[10000] = {false, };
        string reg_st, reg_tar;
        int A, B; cin >> A >> B;

        //A를 문자열로 변환하여 reg에 저장
        reg_st = IToStr(A);
        //debugging
        //cout << reg_st << '\n';

        //B를 문자열로 변환하여 reg_tar에 저장
        reg_tar = IToStr(B);
        //debugging
        //cout << reg_tar << '\n';

        //BFS 시작
        queue<pair<string, string>> q;
        q.emplace("", reg_st);
        while(q.size()) {   //worst case O(10000)

            auto it = q.front(); q.pop();
            string oper_history = it.first;    //방문 경로 문자열
            string cur_val = it.second;        //현재 reg 값
            //debugging
            //cout << "case - history : " << oper_history << "|cur_val : " << cur_val << '\n';
            
            //숫자 변환 값 - 추후 계산 위함
            int num = StrToI(cur_val);
            visited[num] = true;    //visited 갱신

            //찾은 경우 - 출력 & BFS 종료
            if(cur_val == reg_tar) {
                cout << oper_history << '\n';
                break;
            }

            //못찾은 경우 - 해당 문자열의 D, S, L, R을 각각 추가

            //1. D - 2배 연산
            int numD = (num * 2) % 10000;       //1) 연산
            string next_val = IToStr(numD);     //2) 문자열로 변환
            if(!visited[numD]) {                //3) history와 함께 push
                q.emplace(oper_history + "D", next_val);
            }

            //2. S - 빼기 1 연산
            int numS = (num + 9999) % 10000;    //1) 연산
            next_val = IToStr(numS);            //2) 문자열로 변환
            if(!visited[numS]) {                //3) history와 함께 push
                q.emplace(oper_history + "S", next_val);
            }

            //3. L - 좌회전 연산
            next_val = Lrotate(cur_val);        //1) rotate
            int numL = StrToI(next_val);        //2) 숫자로 변환
            if(!visited[numL]) {                //3) history와 함께 push
                q.emplace(oper_history + "L", next_val);
            }

            //4. R - 우회전 연산
            next_val = Rrotate(cur_val);        //1) rotate
            int numR = StrToI(next_val);        //2) 숫자로 변환
            if(!visited[numR]) {                //3) history와 함께 push
                q.emplace(oper_history + "R", next_val);
            }
        }
    }
}