#include <iostream>
#include <queue>
#include <vector>

using namespace std;


// 1. 현재 아기상어 위치에서 먹을 수 있는 다른 물고기까지의 거리와 좌표 구해서 큐에 저장 
// 2. 거리가 가장 가까운 + 가장 위에 or 가장 왼쪽에 있는 물고기 선택
// 3. 그 물고기의 위치로 아기상어의 위치 변경, 이때 거리(초) 기록 및 먹은 물고기 수 기록
// 4. 물고기 수가 자신의 크기와 같으면 자신의 크기 1 키워준다.
// 5. 다시 탐색 시작 => 더이상 먹을 수 있는게 없다면 종료 

struct Fish {
	int y;
	int x;
	int dist;
};

bool operator>(Fish a, Fish b) {
	if (a.dist > b.dist) return true;
	if (a.dist < b.dist) return false;

	if (a.y > b.y) return true;
	if (a.y < b.y) return false;

	if (a.x > b.x) return true;
	if (a.x < b.x) return false;

	return false;
}

int n;
int MAP[21][21];
int babySize = 2;
int eatFish = 0;
priority_queue<Fish, vector<Fish>, greater<Fish>> find_fish(int y, int x) {
	
	// 현재 아기상어 위치에서 먹을 수 있는 다른 물고기 저장
	priority_queue<Fish, vector<Fish>, greater<Fish>> fishes; 

	queue<Fish> q;
	q.push({ y, x, 0 });
	int visited[21][21] = { 0 };
	visited[y][x] = 1;

	int dy[] = {-1, 0, 1, 0};
	int dx[] = {0, 1, 0, -1};

	while (!q.empty()) {
		Fish f = q.front();
		q.pop();
		int fx = f.x;
		int fy = f.y;

		for (int i = 0; i < 4; i++) {
			int ny = fy + dy[i];
			int nx = fx + dx[i];

			if (ny < 0 || ny >= n) continue;
			if (nx < 0 || nx >= n) continue;

			if (MAP[ny][nx] > babySize) continue;
			if (visited[ny][nx] != 0) continue;

			visited[ny][nx] = visited[fy][fx] + 1;
			q.push({ ny, nx, visited[ny][nx] });
			if (MAP[ny][nx] != 0 && MAP[ny][nx] < babySize) {
				fishes.push({ ny, nx, visited[ny][nx]-1 });
				//cout <<"먹어" << ny << " " << nx << " " << visited[ny][nx] << "\n";
			}
			//cout << ny << " " << nx << " " << visited[ny][nx] << "\n";
		}

	}

	return fishes;
}

int main() {
	cin >> n;

	int y, x;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 9) {
				y = i;
				x = j;
				MAP[i][j] = 0;
			}
		}
	}

	//cout << y << x;

	int ans = 0;

	
	while(true) {

		priority_queue<Fish, vector<Fish>, greater<Fish>> pq = find_fish(y, x);

		// 더이상 먹을 수 있는 물고기가 없으면 종료!
		if (pq.size() == 0) break;

		// 3. 그 물고기의 위치로 아기상어의 위치 변경, 이때 거리(초) 기록 및 먹은 물고기 수 기록
		// 크기가 똑같으면 먹지는 못하고 지나갈수만 있음.

		Fish target = pq.top();
		y = target.y;
		x = target.x;
		ans += target.dist;
		pq.pop();

		cout << y << " " << x << " " << ans << " " << "\n";
		

		eatFish += 1;
		MAP[y][x] = 0;

		// 4. 물고기 수가 자신의 크기와 같으면 자신의 크기 1 키워준다.
		if (eatFish == babySize) {
			babySize += 1;
			eatFish = 0;
		}
		
		
	}
	
	cout << ans;

	return 0;
}