#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int sea[20][20] = { 0, };  // 어항(공간)
int sharkSize = 2; // 상어 사이즈
int elapsedTime = 0; // 이동 시간
int y, x; //상어의 위치
int N;
int eatten = 0; // 먹은 횟수

struct Node {
	int Y;
	int X;
};

//대상 지점까지의 최소 거리를 저장하기 위한 구조체
struct Dict {
	Node node;
	int dist;
};

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0, 1, 0, -1 };

struct cmp {
	bool operator() (Dict a, Dict b) {
		if (a.dist < b.dist)
			return false;
		if (a.dist > b.dist)
			return true;

		if (a.node.Y < b.node.Y)
			return false;
		if (a.node.Y > b.node.Y)
			return true;

		if (a.node.X < b.node.X)
			return false;
		if (a.node.X > b.node.X)
			return true;

		return false;
	}
};

//대상 지점까지 최단거리 구하기
int bfs(int dest_y, int dest_x) {
	queue<Node> q;

	int visited[20][20] = { 0, };
	visited[y][x] = 1;

	q.push({ y, x });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();

		
		for (int i = 0; i < 4; i++) {
			int ny = now.Y + dy[i];
			int nx = now.X + dx[i];

			if (ny < 0 || ny >= N || nx < 0 || nx >= N) {
				continue;
			}
			if (visited[ny][nx] >= 1) {
				continue;
			}
			if (sea[ny][nx] > sharkSize) {
				continue;
			}

			visited[ny][nx] = visited[now.Y][now.X] + 1;
			q.push({ ny, nx });

		}

	}	
	
	int dest = visited[dest_y][dest_x];
	return dest - 1;
}


// 물고기를 먹으러 가기 위해 지나야 하는 최소 칸 수 (BFS - 플러드필)
int main() {
	//입력
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> sea[i][j];
			if (sea[i][j] == 9) {
				y = i;
				x = j;
			}
		}
	}


	/* 처리 */
	//while => 먹을 수 있는 물고기가 없을 때까지
	while (true) {

		//먹을 수 있는 물고기 리스트를 담을 우선순위 큐 정의(최단거리, y, x 오름차순 정렬)
		priority_queue<Dict, vector<Dict>, cmp> distlist;
		//1. 먹을 수 있는 물고기 탐색
		// 좌측 상단부 먹을 수 있는 물고기 탐색
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {

				//i, j 칸에 먹을 수 있는 물고기가 있다면
				if (sea[i][j] >= 1 && sea[i][j] < sharkSize) {
				
					//각 물고기까지의 최단 거리 계산
					int sh = bfs(i, j);
					// 먹을 수 없는 물고기가 없을 경우
					if (sh == -1)
						continue;

					distlist.push({ { i, j}, sh });
				}
			}
		}

		/* 이동 */	
		//먹을 수 없는 물고기가 없을 경우 탐색 종료
		if (distlist.size() == 0)
			break;

		//먹어야 할 좌표 꺼내기
		Dict target = distlist.top();
		distlist.pop();

		int t_y = target.node.Y;
		int t_x = target.node.X;
		int shortest = target.dist;

		//상어 위치 갱신
		sea[t_y][t_x] = 9;
		sea[y][x] = 0;
		y = t_y;
		x = t_x;

		// 이동 시간 누적
		elapsedTime = elapsedTime + shortest;
		
		//상어가 먹은 물고기 수 증가
		eatten++;
		//만약 먹은 물고기 수가 상어 사이즈와 같다면 상어 사이즈 +1
		if (eatten == sharkSize) {
			sharkSize++;
			eatten = 0;
		}

	}
	//경과 시간 출력
	cout << elapsedTime;
}
