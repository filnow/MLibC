#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double lr;
    int n;
    double *w;
    double bias;
} LinearRegression;

typedef struct {
    double *data;
    int rows;
    int cols;
} Matrix;

double dot_product(double *a, double *b, int n) {
    double result = 0;
    for (int i = 0; i < n; i++) {
        result += a[i] * b[i];
    }
    return result;
}

void fit(LinearRegression *lr, Matrix *X, double *y) {

    lr->w = (double *)calloc(X->cols, sizeof(double));

    for (int i = 0; i < lr->n; i++) {

        double *y_pred = (double *)calloc(X->rows, sizeof(double));
        for (int j = 0; j < X->rows; j++) {
            y_pred[j] = dot_product(X->data + j * X->cols, lr->w, X->cols) + lr->bias;
        }
        
        double *dw = (double *)calloc(X->cols, sizeof(double));
        for (int j = 0; j < X->cols; j++) {
            double sum = 0;
            for (int k = 0; k < X->rows; k++) {
                sum += X->data[k * X->cols + j] * (y_pred[k] - y[k]);
            }
            dw[j] = (1.0 / X->rows) * sum;
        }
        
        double db = (1.0 / X->rows) * dot_product(y_pred - y, y_pred - y, X->rows);
        
        for (int j = 0; j < X->cols; j++) {
            lr->w[j] -= lr->lr * dw[j];
        }
        lr->bias -= lr->lr * db;

        free(y_pred);
        free(dw);
    }
}

double pred(LinearRegression *lr, Matrix *X) {
    double result = lr->bias;
    for (int i = 0; i < X->cols; i++) {
        result += X->data[i] * lr->w[i];
    }
    return result;
}

double score(double *y_true, double *y_pred, int n) {
    double u = 0;
    double v = 0;
    double y_true_mean = 0;
    for (int i = 0; i < n; i++) {
        y_true_mean += y_true[i];
    }
    y_true_mean /= n;
    for (int i = 0; i < n; i++) {
        u += pow(y_true[i] - y_pred[i], 2);
        v += pow(y_true[i] - y_true_mean, 2);
    }
    return 1 - (u / v);
}

int main() {

    double X_data[6] = {1, 1, 1, 2, 2, 2};
    double y_data[3] = {1, 2, 3};
    Matrix X = {X_data, 3, 2};
    LinearRegression lr = {0.01, 1000, NULL, 0};
    fit(&lr, &X, y_data);
    printf("%f\n", pred(&lr, &(Matrix){{X_data + 2, 1, 2}})); // should output 3.9999

}
