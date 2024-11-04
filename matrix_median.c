#include <stdio.h>
#include <limits.h>
int countLessEqual(int matrix[][100], int mid, int R, int C) {
	int count = 0;
	for (int i = 0; i < R; i++) {
		int low = 0, high = C - 1;
		while (low <= high) {
			int m = (low + high) / 2;
			if (matrix[i][m] <= mid) {
				low = m + 1;
			} else {
				high = m - 1;
			}
		}
		count += low;
	}
	return count;
}
int findMedian(int matrix[][100], int R, int C) {
	int minVal = matrix[0][0];
	int maxVal = matrix[0][C-1];
	for (int i = 1; i < R; i++) {
		if (matrix[i][0] < minVal) {
			minVal = matrix[i][0];
		}
		if (matrix[i][C-1] > maxVal) {
			maxVal = matrix[i][C-1];
		}
	}
	int desiredCount = (R * C) / 2;
	while (minVal < maxVal) {
		int mid = (minVal + maxVal) / 2;
		int count = countLessEqual(matrix, mid, R, C);
		if (count <= desiredCount) {
			minVal = mid + 1;
		} else {
			maxVal = mid;
		}
	}
	return minVal;
}
int main() {
	int R, C;
	scanf("%d %d", &R, &C);
	int matrix[100][100];
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	int median = findMedian(matrix, R, C);
	printf("%d\n", median);
	return 0;
}
