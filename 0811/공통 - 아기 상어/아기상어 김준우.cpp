#include<iostream>
#include<queue>
using namespace std;

struct node{
  int x;
  int y;
};

int babyS = 2;
int MAP[21][21];
int N, M;
int cnt,eat;
node shark;
int mindist,mx,my;
int visited[21][21] = {0,};

void setInit(){
    mx = 21;
    my = 21;
    mindist = 1000;

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            visited[i][j] = 0;
}

void flood(node a){
    
    queue<node> q;

    MAP[a.x][a.y] = 0;
    q.push(a);
    visited[a.x][a.y] = 1;

    while(!q.empty()){
        node now = q.front();
        q.pop();

        int dx[] = {-1,0,0,1};
        int dy[] = {0,-1,1,0};

        for(int t = 0; t < 4; t++){
        int xdir = now.x + dx[t];
        int ydir = now.y + dy[t];

        if(xdir < 0 || xdir >= N || ydir < 0 || ydir >= N) continue;
        if(MAP[xdir][ydir] > babyS) continue;
        if(visited[xdir][ydir]) continue;

        visited[xdir][ydir] = visited[now.x][now.y] + 1;

        if(MAP[xdir][ydir] != 0 && MAP[xdir][ydir] < babyS){
            
            if(mindist > visited[xdir][ydir]){
                mx = xdir;
                my = ydir;
                mindist = visited[xdir][ydir];
            }
            else if(mindist == visited[xdir][ydir]){
                if(mx == xdir && my > ydir){
                    mx = xdir;
                    my = ydir;
                }
                else if(mx > xdir){
                    mx = xdir;
                    my = ydir;
                }
            }

        }

        q.push({xdir,ydir});
        }
    }
}




int main(){
    cin >> N;


    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++){
        cin >> MAP[i][j];
        if(MAP[i][j] == 9)
            shark = {i,j};
        }

    
    while(true){
            
            setInit();

            flood(shark);

            if(mx != 21 && my != 21){
            shark = {mx,my};
            eat++;
            MAP[mx][my] = 9;

            if(eat == babyS){
            babyS++;
            eat = 0;
            }

            cnt += visited[mx][my] - 1;
            }
            else
                break;
    
    }


    cout << cnt;
}