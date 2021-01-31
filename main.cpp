#include <iostream>

#define ROW 3       // 行
#define COLUMN 3    // 列

double matrix[ROW][COLUMN] = {
        {  1, -2,  3 },
        {  3, -2,  1 },
        {  2,  2, -2 },
};

double answer[ROW][1] = {
        { -1 },
        { -3 },
        {  6 },
};

void gauss();
void pivot(int col);
int max_column_id(int col);
void exchange_row(int a, int b);

void print_sim();

int main() {
    gauss();
    return 0;
}

void gauss() {
    double result[ROW][1] = { {0}, {0}, {0} };
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

void pivot(int col) {
    int max_id = max_column_id(col);
    exchange_row(col, max_id);
}

int max_column_id(int col) {
    // max.first: 数値, max.second: id
    std::pair<int, int> max = std::make_pair(matrix[0][col], 0);
    for (int row = 1; row < ROW; row++) {
        if (max.first < matrix[row][col]) max = std::make_pair(matrix[row][col], row);
    }
    return max.second;
}

void exchange_row(int a, int b) {
    for (int col = 0; col < COLUMN; col++) {
        std::swap(matrix[a][col], matrix[b][col]);
    }
    std::swap(answer[a][0], answer[b][0]);
}

void print_sim() {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COLUMN; col++) {
            printf("%4.1lf ", matrix[row][col]);
        }
        printf(",%4.1lf\n", answer[row][0]);
    }
}
