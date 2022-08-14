#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
int map[10][10] = {
    0,
};
int visited[7] = {0,};
const int INF = 987654321;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int n, m;
int min_result = 987654321;
int island_num;
int min_connected[7][7] = {0,};
//연결하고 2차원 BFS를 통해서 또 탐색이 필요함




bool calc_range(int x, int y) {
  if (x >= 0 && x < n && y >= 0 && y < m)
    return true;
  return false;
}
void print_island(int ma[10][10]) {
  cout << "\nprinting::\n";
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < m; c++) {
      cout << ma[r][c] << ' ';
    }
    cout << '\n';
  }
}
int  bridge_coord(int x, int y, int d) 
{
  //해당 x,y좌표에서 d방향으로 갈 수 있는 섬으로 섬과 섬의 거리를 갱신
  int found = 0;
  int mov_x = x + dx[d];
  int mov_y = y + dy[d];
  int start = map[x][y];
  int end;
  while (calc_range(mov_x, mov_y) && map[mov_x][mov_y] == 0)   {
    //최대한 가보기
    mov_x += dx[d];
    mov_y += dy[d];
  }
  //해당 시점에서 범위 벗어나는 것이 가능 
  //벗어나지 않고 섬이어야 함
  if (calc_range(mov_x,mov_y)&&(abs(mov_x - x) + abs(mov_y - y)) > 2) {
    //다리 생성조건만족
    if (map[mov_x][mov_y] != map[x][y] && map[mov_x][mov_y])     {
      //다른 섬임
      found = (abs(mov_x-x) + abs(mov_y-y))-1;
      end = map[mov_x][mov_y];
    }
  }
  if(found)
  {
    min_connected[start][end] = min(min_connected[start][end],found);
    min_connected[end][start] = min(min_connected[end][start],found);
  }
  return found;
}


int seperate_island() {
  int island_num = 7;
  //섬 6개 이슈 처리
  //섬을 6부터 역으로 카운팅함
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (map[i][j] && map[i][j] < island_num) 
      {
      if(island_num>2)
      {
        island_num--;
        queue<pair<int, int>> q;
        q.push({i, j});
        // visited필요 없음 바꿀거기 때문에
        map[i][j] = island_num;
        while (!q.empty()) {
          int x, y;
          tie(x, y) = q.front();
          q.pop();
          for (int d = 0; d < 4; d++) {
            int mov_x = x + dx[d];
            int mov_y = y + dy[d];
            if (calc_range(mov_x, mov_y) && map[mov_x][mov_y] == 1) {
              map[mov_x][mov_y] = island_num;
              q.push({mov_x, mov_y});
            }
          }
        }
        // print_island();
      }
      else
      {
        island_num--;
      }






        
      }
    }
  }
  return island_num;
}
bool chk_finished(int visited_2D[7][7])
{
  int start = island_num;
  //다리 설치한 후 BFS 수행해서 다 갔는지 체크
  int visited[7] = {0,};
  int cnt = 0;
  for(int i=0;i<island_num;i++)
    visited[i] = 1;
  queue<int>q;
  for(int i=1;i<7;i++)
    {
    for(int j=1;j<7;j++)
      {
        if(visited_2D[i][j] == 1)
        {
          visited[i]  =1;
          q.push(i);
          cnt++;
          break;
        }
        
      }
      if(!q.empty())
      {
        break;
      }
      
    }
  while(!q.empty())
    {
      int now = q.front();
      q.pop();
      for(int i=1;i<7;i++)
        {
          if(visited_2D[now][i] == 1 && !visited[i])
          {
            visited[i] = 1;
            cnt++;
            q.push(i);
          }
        }


      
    }
  return cnt == (7-island_num);
}
void select_bridge( int start,int end,int bridge_num,int visited_2D[7][7])
{
  //매번 다리 놓고 체크
    if(chk_finished(visited_2D))
    {
      min_result = min(min_result,bridge_num);
      return;
    }
  
    for(int i=start;i<7;i++)
    {
        if(i>start)
        {
          end = start;
        }
    for(int j=end;j<7;j++)
      {    
        if(!visited_2D[i][j] && !visited_2D[j][i] && min_connected[i][j] != INF)
        {
          visited_2D[i][j] = 1;
          visited_2D[j][i] = 1;
          //print_grid(visited_2D);
          select_bridge(i,j+1,bridge_num+min_connected[i][j],visited_2D);
          visited_2D[j][i] = 0;
          visited_2D[i][j] = 0;
        }

        
      }



      
    }

  
}





int main() {
  cin >> n >> m;
  cin.tie(NULL);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> map[i][j];
  island_num = seperate_island(); //섬분리 완료
  //cout<<island_num<<endl;
  //print_island(map);

  for(int i=0;i<7;i++)
    for(int j=0;j<7;j++)
      min_connected[i][j] = INF;

  for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
      for(int d=0;d<4;d++)
        if(map[i][j])
          bridge_coord(i,j,d);


  // for(int i=1;i<7;i++)
  //   {
  //   for(int j=1;j<7;j++)
  //     cout<<min_connected[i][j]<<' ';
  //   cout<<endl;

      
  //   }

  
  int visited_2D[7][7] = {0,};
  for(int i=0;i<island_num;i++)
    visited[i] = 1;
  visited[island_num] = 1;
  select_bridge(island_num,island_num,0,visited_2D);



  
  if(min_result == 987654321)
    cout<<"-1\n";
  else
    cout<<min_result<<'\n';

  //cout<<chk_finished(map);
  //print_island(map);  
}