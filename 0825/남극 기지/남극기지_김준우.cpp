#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

struct node{
    double x;
    double y;
};

struct edge{
    int a;
    int b;
    double d;
};

int n;
vector<node> v;
vector<edge> v2;
int parent[10001];

int Find(int node){
    if(node == parent[node])
        return node;

    return parent[node] = Find(parent[node]);
}

void Union(int a, int b){
    int pa = Find(a);
    int pb = Find(b);

    if(pa == pb)
        return;

    parent[pb] = pa;
}

double dist(node a, node b){
    double distance = sqrt(pow(b.x-a.x,2) + pow(b.y - a.y,2));

    return distance;
}

bool cmp(edge a, edge b) {
	if (a.d < b.d) return true;
	if (a.d > b.d) return false;

	return false;
}

double kruskal() {

	double sum = 0;
	sort(v2.begin(), v2.end(), cmp);

	for (int i = 0; i < v2.size(); i++) {
		edge now = v2[i];

		if (Find(now.a) == Find(now.b))continue;

		if(sum < now.d)
            sum = now.d;

		Union(now.a, now.b);
	}

	return sum;
}

int main(){

    int T;
    cin >> T;
    for(int tc = 0; tc < T; tc++){
        cin >> n;

        v.clear();
        v2.clear();
      
        for(int i = 0; i < n; i++){
            double x, y;
            cin >> x >> y;

            v.push_back({x,y});
        }

        for (int i = 0; i < n; i++)
		    parent[i] = i;

        for (int i = 0; i < v.size(); i++)
            for (int j = 0; j < v.size(); j++) {
                if (i == j) continue;

                node now = v[i];
                node next = v[j];

                double dst = dist(now, next);

                v2.push_back({ i,j,dst });
        }


        double ans = kruskal();

        printf("%.2f\n" , round(ans*100)/100);
    }
}