#include <iostream>
#include <vector>
#include <queue>

using namespace std;
/*
  캐슬 디펜스
  게임 진행되는 곳 N*M 격자판
  각 칸에 포함된 적의 수 최대 하나
  N번행 바로 아래 모든 칸 성
  궁수 3명 배치
  모든 궁수 동시 공격
  궁수 거리 D이하인 적 중에서 가장 가까운 적
  여럿일 경우 가장 왼쪽 적 공격 -> 같은 적 여러 궁수 공격 가능
  궁수 공격후 적 -> 아래로 한칸 이동
  성 있는칸 이동할 경우 게임에서 제외
  모든 적 격자판 제외 게임 끝남
  궁수 공격 제거 적의 최대 수

  1. 궁수 배치 -> dfs -> 해당 벡러 리스트 바로 시뮬레이션 함수
  2. 적 제거 -> 시뮬레이션
*/

vector<vector<int>> map (16,vector<int>(16,0));
int visited[16] = {0,};
int N,M;
int range;
int max_cnt = -1;
vector<int> path;
bool game_finished(vector<vector<int>> chk)
{
  bool result = true;
  for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
      if(chk[i][j] == 1)
        return false;

  return result;

  
}
int calc_dist(int x,int y ,int a,int b)
{
  return abs(x-a) + abs(y-b);
  
}

void simul(vector<vector<int>> deployed)
{
  int tmp_cnt = 0;
  while(!game_finished(deployed))
    {
      queue<pair<int,int>> atk_q;
      //1. 궁수 공격
      for(int c=0;c<M;c++)
        {
          if(deployed[N][c] == 3)
          {
            //궁수 발견후 열 별로 적있는 곳 사거리 계산후
            //가장 짧은 사거리에 공격
            //열이 왼쪽부터 봐서 왼쪽에 있는 가까운 적 공격 가능
            int max_range =987654321;
            int atk_x,atk_y;
            for(int e_c = 0; e_c<M;e_c++)
              {
                for(int e_r = 0;e_r<N;e_r++)
                  {
                    if(deployed[e_r][e_c] == 1)
                    {
                      //적이 존재함
                      int dist = calc_dist(N,c,e_r,e_c);
                      if(dist<=range)
                      {
                        //공격 가능
                        if(dist<max_range)
                        {
                          //최소 사거리 충족
                          max_range = dist;
                          atk_x = e_r;
                          atk_y = e_c;
                          
                        }
                      }
                    }
                  }
              }
              if(max_range != 987654321)
              {
                //공격 가능
                //큐 넣는 것이 시간초과 뜨면 벡터 복사해서 하는 방법 모색 
                atk_q.push(make_pair(atk_x,atk_y));
                
              }
            
          }

          
        }
        //2. 적 제거
        while(!atk_q.empty())
          {
            pair<int,int> pos = atk_q.front();
            atk_q.pop();
            int x = pos.first;
            int y = pos.second;
            if(deployed[x][y] == 1)
            {
              tmp_cnt++;
              deployed[x][y] = 0;
            }

            
          }

        //3. 적 이동
        //밑에 있는 놈부터 이동해야지 안겹침
        for(int e_r = N-1;e_r>=0;e_r--)
          {
            for(int e_c = 0;e_c<M;e_c++)
              {
                if(deployed[e_r][e_c] == 1)
                {
                  int mov_e_r = e_r+1;
                  deployed[e_r][e_c] =0;
                  if(mov_e_r < N)
                    deployed[mov_e_r][e_c] = 1;
                  
                }

                
              }
            
          }
      
    }
  //2.결산
  max_cnt = max(tmp_cnt,max_cnt);
}
void print_map()
{
  cout<<endl<<"printing::"<<endl;
  for(int i=0;i<=N;i++)
    {
      for(int j=0;j<M;j++)
        {
          cout<<map[i][j]<<' ';
        }
        cout<<endl;
    }

  
}

void dfs(int num,int depth)
{
  if(num == 3)
  {
    //print_map();
    simul(map);
    return;
  }
  if(depth == M)
    return;
  for(int i=depth;i<M;i++)
    {
      if(!visited[i])
      {
        visited[i] = 1;
        map[N][i] = 3;//archer
        
        dfs(num+1,i+1);
        map[N][i] = 0;
        visited[i] = 0;
      }
      
    }

  
}

int main() {
  cin>>N>>M;
  cin>>range;
  for(int i=0;i<N;i++)
    {
      for(int j=0;j<M;j++)
      {
        cin>>map[i][j];
      }
    }
    dfs(0,0);
  cout<<max_cnt;
  
}