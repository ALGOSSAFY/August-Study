#include <string>
#include <vector>

using namespace std;

int arr[1001][1001];


int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    
    for(auto i: skill) {
        int type = i[0];
        int x1 = i[1], y1 = i[2]; //시작 좌표
        int x2 = i[3], y2 = i[4]; //끝 좌표
        int degree = i[5];
        if(type == 1) degree = -degree;
        
        arr[x1][y1] += degree;    //시작지점에 값 넣어주기
        arr[x1][y2 + 1] -= degree; //끝나는 지점에 - 해줘서 원래대로
        arr[x2 + 1][y1] -= degree;
        arr[x2 + 1][y2 + 1] += degree;
    }
    
    int a = board.size();
    int b = board[0].size();
    
    //가로방향 prefixsum
    for(int i = 0; i <= a; i++) { 
        for(int j = 0; j < b; j++) {
            arr[i][j+1] += arr[i][j];
        }
    }
        
    //세로방향 prefixsum
    for(int j = 0; j <= b; j++) { 
        for(int i = 0; i < a; i++) {
            arr[i+1][j] += arr[i][j];
        }
    }
    
    
    //원래 배열에서 확인
    for(int i = 0; i < a; i++) {
        for(int j = 0; j < b; j++) {
            if(board[i][j] + arr[i][j] > 0)
                answer++;
        }
    }
    
    return answer;
}
