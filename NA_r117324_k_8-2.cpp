#include <iostream>
#include <cmath>

#define N 100
const double ALPHA = 0.5;

double a[N + 1], b[N + 1], c[N + 1], l[N + 1], d[N + 1], z[N + 1], x[N + 1], y[N + 1];

void input_a_b_c();
void input_y();
void solve_l_d();
void solve_z();
void solve_x();

int main() {
    input_a_b_c();
    input_y();
    solve_l_d();
    solve_z();
    solve_x();
    for (int i = 1; i <= N; i++) {
        printf("%2.2lf ", x[i]);
    }
}

void input_a_b_c() {
    for (int i = 1; i <= N; i++) {
        a[i] = 1 + 2 * ALPHA;
        b[i + 1] = -1 * ALPHA;
        if (i == N) break;
        c[i] = -1 * ALPHA;
    }
}

void input_y() {
    for (int i = 1; i <= N; i++) {
        double buf = 2 * (double)i / N - 1;
        y[i] = 1 - std::abs(buf);
    }
}

void solve_l_d() {
    d[1] = a[1];
    for (int i = 1; i < N; i++) {
        l[i + 1] = b[i + 1] / d[i];
        d[i + 1] = a[i + 1] - l[i + 1] * c[i];
    }
}

void solve_z() {
    z[1] = y[1];
    for (int i = 2; i <= N; i++) {
        z[i] = y[i] - l[i] * z[i - 1];
    }
}

void solve_x() {
    x[N] = z[N] / d[N];
    for (int i = N - 1; i >= 1; i--) {
        x[i] = (z[i] - c[i] * x[i + 1]) / d[i];
    }
}
