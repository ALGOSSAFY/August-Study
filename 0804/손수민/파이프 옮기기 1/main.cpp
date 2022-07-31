#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> arr(16,vector<int>(16,0));
int n;
int dx[3] = {1,1,0};
int dy[3] = {1,0,1};
int cnt = 0;
//dir = 0 가로 , dir = 1 세로, dir = 2 대각선
void print_pipe()
{
  for(int i=0;i<n;i++)
    {
    for(int j=0;j<n;j++)
      {
        cout<<arr[i][j]<<' ';
      }
      cout<<endl;
    }
  
}


void place(int x, int y, int dir)
{
  //print_pipe();
  if(x==n-1 && y==n-1)
  {
    cnt++;
    return;
    
  }
  int mov_x,mov_y;
  //vector<vector<int>> moving_prev = arr;
  if(dir == 0)
  {
    //가로
    mov_x = x+dx[2];
    mov_y = y+dy[2];
    if(mov_x>=0 && mov_x < n && mov_y>=0 && mov_y<n && arr[mov_x][mov_y] == 0)
    {
      arr[mov_x][mov_y] = 2;
      place(mov_x,mov_y,0);
      arr[mov_x][mov_y] =0;
    }
    

    
  }
  else if(dir == 1)
  {
    //세로
    mov_x = x+dx[1];
    mov_y = y+dy[1];
    if(mov_x>=0 && mov_x < n && mov_y>=0 && mov_y<n && arr[mov_x][mov_y] == 0)
    {
      arr[mov_x][mov_y] = 2;
      place(mov_x,mov_y,1);
      arr[mov_x][mov_y]  =0;
    }
   
    
  }
  else if(dir == 2)
  {
    //대각선
    mov_x = x+dx[2];
    mov_y = y+dy[2];
    if(mov_x>=0 && mov_x < n && mov_y>=0 && mov_y<n && arr[mov_x][mov_y] == 0)
    {
      arr[mov_x][mov_y] = 2;
      place(mov_x,mov_y,0);
      arr[mov_x][mov_y] = 0;
    }
    

    mov_x = x+dx[1];
    mov_y = y+dy[1];
    if(mov_x>=0 && mov_x < n && mov_y>=0 && mov_y<n && arr[mov_x][mov_y] == 0)
    {
      arr[mov_x][mov_y] = 2;
      place(mov_x,mov_y,1);
      arr[mov_x][mov_y] =0;
    }
    
    
    
  }

  bool place_all_flag = true;
    for(int d=0;d<3;d++)
      {
        mov_x = x+dx[d];
        mov_y = y+dy[d];
        if(mov_x>=0 && mov_x <n && mov_y >= 0 && mov_y<n && arr[mov_x][mov_y] == 0)
        {
          arr[mov_x][mov_y] = 2;
        }
        else
        {
          place_all_flag = false;
        }
      }
    if(place_all_flag)
    {
      place(x+1,y+1,2);
    }
    for(int d=0;d<3;d++)
      {
        mov_x = x+dx[d];
        mov_y = y+dy[d];
        if(mov_x>=0 && mov_x <n && mov_y >= 0 && mov_y<n && arr[mov_x][mov_y] == 2)
        {
          arr[mov_x][mov_y] = 0;
        }
      }
}



int main() {
  cin>>n;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      cin>>arr[i][j];
  arr[0][0] = 2;
  arr[0][1] = 2;
  //처음 가로로 되어 있는 상태
  place(0,1,0);
  cout<<cnt<<'\n';
  
}