#include<iostream>
#include <string>
#include <vector>
using namespace std;

int N, M;
int sumarr[1002][1002] = { 0, };
int solution(vector<vector<int>> board, vector<vector<int>> skill) {

    N = board.size(); //세로길이
    M = board[0].size(); //가로길이

    for (int i = 0; i < skill.size(); i++) {
        int type = skill[i][0];
        int y1 = skill[i][1]+1;
        int x1 = skill[i][2]+1;
        int y2 = skill[i][3]+1;
        int x2 = skill[i][4]+1;
        int level = skill[i][5];
        if (type == 1) {
            sumarr[y1][x1] -= level;
            sumarr[y2 + 1][x2 + 1] -= level;
            sumarr[y1][x2 + 1] += level;
            sumarr[y2 + 1][x1] += level;
        }
        else {
            sumarr[y1][x1] += level;
            sumarr[y2 + 1][x2 + 1] += level;
            sumarr[y1][x2 + 1] -= level;
            sumarr[y2 + 1][x1] -= level;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            sumarr[i][j] += sumarr[i - 1][j] + sumarr[i][j - 1] - sumarr[i - 1][j - 1];
        }
    }

    int num = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (board[i][j]+sumarr[i+1][j+1] > 0) {
                num++;
            }
        }
    }
    return num;
}