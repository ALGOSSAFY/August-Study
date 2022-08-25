#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
/*
  남극 기지
  N개의 탐사기지 존재
  N개 무전기 각 탐사기지에 배치
  두 거리 D -> D이상 통신 가능
  무전기 최소 출력
  크루스칼?
  최소 스패닝 트리의 최대 길이
*/
int n;
pair<double,double> coord[100];
int parents[100] = {0,};
int find_p(int now)
{
  if(parents[now]==now)
    return now;
  return parents[now] = find_p(parents[now]);
  
}
void union_p(int a, int b)
{
  int p_a = find_p(a);
  int p_b = find_p(b);
  if(p_a ==p_b)
    return;
  if(p_a>p_b)
    swap(p_a,p_b);
  parents[p_b] = p_a;
  //작은 놈이 부모로 되게 조정
}
struct graph
{
  int a;
  int b;
  double dist;
};
static bool operator<(const graph a, const graph b)
{
  if(a.dist>b.dist)
    return true;
  return false;
  //작은게 먼저 와야함
}

int main() {
  int c;
  cin>>c;
  for(int tc=1;tc<=c;tc++)
    {
      cin>>n;
      priority_queue<graph,vector<graph>>pq;
      for(int i=0;i<n;i++)
        {
          double x,y;
          cin>>x>>y;
          coord[i] = {x,y};
          parents[i] = i;
        }
      for(int idx= 0;idx<n-1;idx++)
        {
          for(int j=idx+1;j<n;j++)
            {
                double sx = coord[idx].first;
                double sy = coord[idx].second;
                double dx = coord[j].first;
                double dy = coord[j].second;
                
                double dist = sqrt(((sx-dx) * (sx-dx)) + ((sy-dy) * (sy-dy)));
                pq.push({idx,j,dist});

              
            }


          
        }
        double min_dist = -987654321; //연결될때만 갱신한 뒤 출력 
        while(!pq.empty())
          {
            graph now = pq.top();
            pq.pop();
            //가장 짧은놈이 나왔음
            //최소 스패닝 트리의 가장 긴값
            if(find_p(now.a) != find_p(now.b))
            {
              //부모가 다를때 유니온 파인드로 두 그룹을 합침
              union_p(now.a,now.b);
              min_dist = max(min_dist,now.dist);


              
            }

            
          }
          printf("%.2f\n" , round(min_dist*100)/100);

      
    }
  


  
}