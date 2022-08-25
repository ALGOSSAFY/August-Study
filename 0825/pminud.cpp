#include<iostream>
using namespace std;

int N;
int num[11];
int op[4];
int max_sum = -987654321;
int min_sum = 987654321;

void backtracking(int cnt, int now_sum) {
    if (cnt == N) {
        if (now_sum < min_sum) {
            min_sum = now_sum;
        }
        if (now_sum > max_sum) {
            max_sum = now_sum;
        }
        return;
    }

    if (op[0]) {
        op[0]--;
        backtracking(cnt + 1, now_sum + num[cnt]);
        op[0]++;
    }
    if (op[1]) {
        op[1]--;
        backtracking(cnt + 1, now_sum - num[cnt]);
        op[1]++;
    }
    if (op[2]) {
        op[2]--;
        backtracking(cnt + 1, now_sum * num[cnt]);
        op[2]++;
    }
    if (op[3]) {
        op[3]--;
        backtracking(cnt + 1, now_sum / num[cnt]);
        op[3]++;
    }
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }
    for (int i = 0; i < 4; i++) {
        cin >> op[i];
    }
    backtracking(1,num[0]);
    cout << max_sum << endl << min_sum;
}