#include <iostream>
#include <queue>
#include <vector>

using namespace std;


// 1. ���� �Ʊ��� ��ġ���� ���� �� �ִ� �ٸ� ���������� �Ÿ��� ��ǥ ���ؼ� ť�� ���� 
// 2. �Ÿ��� ���� ����� + ���� ���� or ���� ���ʿ� �ִ� ����� ����
// 3. �� ������� ��ġ�� �Ʊ����� ��ġ ����, �̶� �Ÿ�(��) ��� �� ���� ����� �� ���
// 4. ����� ���� �ڽ��� ũ��� ������ �ڽ��� ũ�� 1 Ű���ش�.
// 5. �ٽ� Ž�� ���� => ���̻� ���� �� �ִ°� ���ٸ� ���� 

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
	
	// ���� �Ʊ��� ��ġ���� ���� �� �ִ� �ٸ� ����� ����
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
				//cout <<"�Ծ�" << ny << " " << nx << " " << visited[ny][nx] << "\n";
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

		// ���̻� ���� �� �ִ� ����Ⱑ ������ ����!
		if (pq.size() == 0) break;

		// 3. �� ������� ��ġ�� �Ʊ����� ��ġ ����, �̶� �Ÿ�(��) ��� �� ���� ����� �� ���
		// ũ�Ⱑ �Ȱ����� ������ ���ϰ� ���������� ����.

		Fish target = pq.top();
		y = target.y;
		x = target.x;
		ans += target.dist;
		pq.pop();

		cout << y << " " << x << " " << ans << " " << "\n";
		

		eatFish += 1;
		MAP[y][x] = 0;

		// 4. ����� ���� �ڽ��� ũ��� ������ �ڽ��� ũ�� 1 Ű���ش�.
		if (eatFish == babySize) {
			babySize += 1;
			eatFish = 0;
		}
		
		
	}
	
	cout << ans;

	return 0;
}