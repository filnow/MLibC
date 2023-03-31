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

int main() {

    double r_pred[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double r_real[] = {5.0, 3.0, 4.0, 1.0, 2.0};
    
    int n = sizeof(r_pred) / sizeof(r_pred[0]);
    
    double mse = RMSE(r_pred, r_real, n);
    double mae = MAE(r_pred, r_real, n);
    double mre = MRE(r_pred, r_real, n);
    
    printf("MAE: %lf\n", mae);
    printf("RMSE: %lf\n", mse);
    printf("MRE: %lf\n", mre);
    
    return 0;
}
