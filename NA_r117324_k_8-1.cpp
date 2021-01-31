#include <iostream>

#define ROW 4       // 行
#define COLUMN 4    // 列

double matrix[ROW][COLUMN] = {
        {  1, -2,  3, -1 },
        { -2, -4,  2, -3 },
        {  0, -4,  4, -3 },
        { -3,  2,  4,  0 },
};

double answer[ROW][1] = {
        { 12 },
        {  9 },
        { 15 },
        { -3 },
};

void gauss();
void pivot(int dig);
int max_column_id(int dig);
void exchange_row(int a, int b);

int main() {
    gauss();
    return 0;
}

void gauss() {
    double result[ROW][1];
    for (int diag = 0; diag < COLUMN - 1; diag++) {
        pivot(diag);
        for (int row = diag + 1; row < ROW; row++) {
            double alpha = matrix[row][diag] / matrix[diag][diag];
            for (int col = diag; col < COLUMN; col++) {
                matrix[row][col] = matrix[row][col] - alpha * matrix[diag][col];
            }
            answer[row][0] = answer[row][0] - alpha * answer[diag][0];
        }
    }
    result[ROW - 1][0] = answer[ROW - 1][0] / matrix[ROW - 1][COLUMN - 1];
    for (int diag = ROW - 2; diag >= 0; diag--) {
        double sum = 0;
        for (int i = diag + 1; i < COLUMN; i++) {
            sum += matrix[diag][i] * result[i][0];
        }
        result[diag][0] = (answer[diag][0] - sum) / matrix[diag][diag];
    }
    for (auto & i : result) {
        printf("%5.2lf ", i[0]);
    }
}

void pivot(int dig) {
    int max_id = max_column_id(dig);
    exchange_row(dig, max_id);
}

int max_column_id(int dig) {
    // max.first: 数値, max.second: id
    std::pair<int, int> max = std::make_pair(matrix[dig][dig], dig);
    for (int row = dig + 1; row < ROW; row++) {
        if (max.first < matrix[row][dig]) max = std::make_pair(matrix[row][dig], row);
    }
    return max.second;
}

void exchange_row(int a, int b) {
    for (int col = 0; col < COLUMN; col++) {
        std::swap(matrix[a][col], matrix[b][col]);
    }
    std::swap(answer[a][0], answer[b][0]);
}
