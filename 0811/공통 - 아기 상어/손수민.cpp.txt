#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;
/*
  아기 상어
  N * N 크기 공간 - M마리 물고기 아기 상어 1마리
  상어 크기 2 상하좌우 한칸 이동
  한칸 물고기 최대 1마리
  크기마다 좌표 저장 1~6 - 물고기
  먹을 수 있는 물고기 좌표 - 최소거리 저장 - 정렬해서 같으면 가장 위 왼쪽 comp사용
  자신보다 크기 작은 물고기만 먹음
  아기상어 도움 요청 X잡아먹을 수 있는 시간
  큰 물고기 칸은 못지나감
*/
int shark_size = 2;
const int INF = 987654321;
int dr[4] = {-1,0,1,0};
int dc[4] = {0,1,0,-1};
bool cmp(tuple<int,int,int> &a , tuple<int,int,int> &b)
{
  if(get<0>(a) < get<0>(b))
  {
    return true;
  }
  else if(get<0>(a) == get<0>(b))
  {
    if(get<1>(a) < get<1>(b))
    {
      return true;
    }
    else if(get<1>(a) == get<1>(b))
    {
      if(get<2>(a)<get<2>(b))
      {
        return true;
      }
      else
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
}
//BFS 사용

int dist(int shark_r,int shark_c,vector<vector<int>> sea, int food_r,int food_c, int N)
{
  //int result = INF;
  vector<vector<int>>shark_coord(N,vector<int>(N,INF));
  shark_coord[shark_r][shark_c] = 0;
  queue<pair<int,int>>q;
  q.push(make_pair(shark_r,shark_c));
  while(!q.empty())
    {
      int r = q.front().first;
      int c = q.front().second;
      q.pop();
      for(int i=0;i<4;i++)
        {
          int mov_r = r+dr[i];
          int mov_c = c+dc[i];
          if(mov_r>=0 && mov_r <N && mov_c >=0 && mov_c <N)
          {
            if(sea[mov_r][mov_c] <= shark_size && shark_coord[mov_r][mov_c] > (shark_coord[r][c] +1))
            {
              shark_coord[mov_r][mov_c] = shark_coord[r][c]+1;
              q.push(make_pair(mov_r,mov_c));
            }
            
          }
          
        }
      
    }
  return shark_coord[food_r][food_c];
  //INF면 아예 먹이 도달 불가능
}
int calc(vector<vector<int>> sea, pair<int,int> shark,int N)
{
  int result = 0;
  int ate = 0;
  vector<tuple<int,int,int>> feeds;
  //먹이거리, 행좌표, 열좌표
  do{
  feeds.clear();
    for(int r=0;r<N;r++)
      {
        for(int c=0;c<N;c++)
          { 
            if(sea[r][c] != 9 && sea[r][c] != 0 && sea[r][c] <shark_size)
            {
              int distance = dist(shark.first,shark.second, sea,r,c,N);
              //상어 아니고 빈칸 아니고 먹을 수 있음
              //매번 경로 계산해서 feeds에 넣기
              //자기보다 큰 물고기는 못지나감
              if(feeds.size() > 0 && get<0>(feeds.back()) > distance)
              {
                //큰 거리면 아예 안넣음
                feeds.push_back(make_tuple(distance,r,c));
              }
              else if(feeds.size() == 0)
              {
                feeds.push_back(make_tuple(distance,r,c));
              }
              
            }
            
          }
        
      }
    if(feeds.size() !=0)
    {
      sort(feeds.begin(),feeds.end(),cmp);
      if(get<0>(feeds[0]) == INF)
      {
        break;
      }
      result += get<0>(feeds[0]);
      //shark_size +=1;
      ate +=1;
      sea[shark.first][shark.second] = 0;
      if(shark_size == ate)
      {
        ate = 0;
        shark_size++;
      }
      shark.first = get<1>(feeds[0]);
      shark.second = get<2>(feeds[0]);
      //cout<<result<<' '<<shark.first<<' '<<shark.second<<' '<<shark_size<<endl;
      sea[shark.first][shark.second] = 9;
    }
  }while(feeds.size() != 0);
  return result;
}
int main() {
  //vector<pair<int,int>> fishes[7];//(1~6 좌표 저장)
  pair<int,int> shark;
  int N;
  cin>>N;
  vector<vector<int>>sea(N,vector<int>(N,0));
  for(int i=0;i<N;i++)
    {
      for(int j=0;j<N;j++)
        {
          int tmp;
          cin>>tmp;
          if(tmp == 9)
          {
            shark = make_pair(i,j);
          }
          sea[i][j] = tmp;
        }
    }
  cout<<calc(sea,shark,N)<<endl;
}