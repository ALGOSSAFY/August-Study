#include <iostream>

using namespace std;
int N;

int cnt = 0;
int dy[3] = { 0,1,1 };
int dx[3] = { 1,1,0 };
int arr[16][16] = { 0, };
int visited[16][16] = { 0, };

//가로 - 가로 대각선
//세로 - 세로 대각선
//대각선 - 가로(0) 대각선(1) 세로(2)
void dfs(int y, int x, int dir) {
	if (y == N - 1 && x == N - 1) {
		cnt++;
		return;
	}
	if (dir == 0) {
		for (int i = 0; i < 2; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				continue;
			}
			if (arr[ny][nx] == 1) {
				continue;
			}
			if (visited[ny][nx] == 1) {
				continue;
			}
			if (i == 1) {
				if (arr[y + 1][x] == 1 || arr[y][x + 1] == 1) {
					continue;
				}
			}

			visited[ny][nx] = 1;
			dfs(ny, nx, i);
			visited[ny][nx] = 0;
			ny = ny - dy[i];
			nx = nx - dy[i];

		}
	}
	if (dir == 1) {
		for (int i = 0; i < 3; i++) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				continue;
			}
			if (arr[ny][nx] == 1) {
				continue;
			}
			if (visited[ny][nx] == 1) {
				continue;
			}
			if (i == 1) {
				if (arr[y + 1][x] == 1 || arr[y][x + 1] == 1) {
					continue;
				}
			}

			visited[ny][nx] = 1;
			dfs(ny, nx, i);
			visited[ny][nx] = 0;
			ny = ny - dy[i];
			nx = nx - dy[i];

		}
	}
	if (dir == 2) {
		for (int i = 2; i >= 1; i--) {
			int ny = y + dy[i];
			int nx = x + dx[i];

			if (nx < 0 || nx >= N || ny < 0 || ny >= N) {
				continue;
			}
			if (arr[ny][nx] == 1) {
				continue;
			}
			if (visited[ny][nx] == 1) {
				continue;
			}
			if (i == 1) {
				if (arr[y + 1][x] == 1 || arr[y][x + 1] == 1) {
					continue;
				}
			}

			visited[ny][nx] = 1;
			dfs(ny, nx, i);
			visited[ny][nx] = 0;
			ny = ny - dy[i];
			nx = nx - dy[i];

		}
	}
}

int main() {
	cin >> N;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 1, 0);

	cout << cnt;
}
