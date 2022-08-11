#include <iostream>
#include <string>
using namespace std;

int n;
int maxSum = -2134567890;  // **주의할것! 0으로 하면 안된다 ㅠㅠ 
string str;

int calculate(int a, int b, char op) {
	if (op == '+') return a + b;
	if (op == '-') return a - b;
	if (op == '*') return a * b;
}

void dfs(int idx, int sum) {
	
	// 기저조건
	if (idx > n - 1) {
		if (sum > maxSum) maxSum = sum;
		return;
	}

	char op;
	int tmp;

	// 괄호 추가하지 않는 경우
	if (idx == 0) op = '+';
	else op = str[idx - 1];

	// 이전의 합(sum=0)과 tmp와의 합 누적
	dfs(idx + 2, calculate(sum, str[idx] - '0', op));


	// 괄호 추가하는 경우
	if (idx + 2 < n) {

		int value1 = str[idx] - '0';
		int value2 = str[idx + 2] - '0';

		tmp = calculate(value1, value2, str[idx + 1]);
		// 이전의 합(sum=0)과 tmp와의 합 누적
		dfs(idx + 4, calculate(sum, tmp, op));
	}
}

int main() {
	
	cin >> n;
	cin >> str;

	dfs(0, 0);
	cout << maxSum;
	return 0;
}