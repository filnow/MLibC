#include <stdio.h>
#include <math.h>
//Math.h not linked in the compiler

int MAE(double r_pred[], double r_real[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = r_pred[i] - r_real[i];
        sum += fabs(diff);
    }
    return sum / n;
}

int RMSE(double r_pred[], double r_real[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = r_pred[i] - r_real[i];
        sum += diff * diff;
    }
    return sqrt(sum / n);
}

int MRE(double r_pred[], double r_real[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = r_pred[i] - r_real[i];
        sum += diff / r_real[i];
    }
    return sum / n;
}