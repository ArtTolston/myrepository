#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    vector<double> x, y;
    double tmp1 = 0, tmp2 = 0, tmp3 = 0, sum1 = 0, sum2 = 0, sum = 0, average_of_squares = 0, square_of_average = 0, k = 0, b = 0, k_fault = 0, b_fault = 0;
    int n1 = 0;
    cout << "Vvedite kol-vo znacheniy: ";
    cin >> n1;
    x.resize(n1);
    cout << "Vvedite znacheniya by shift: ";
    for(double& d: x) {
        cin >> d;
    }
    y.resize(n1);
    cout << "Vvedite znacheniya by shift: ";
    for(double& d: y) {
        cin >> d;
    }
    for(int i = 0; i < n1; i++) {
        tmp1 += x[i] * y[i];
    }
    tmp1 /= n1;
    for(int i = 0; i < n1; i++) {
        sum1 += x[i];
        sum2 += y[i];
    }
    sum1 /= n1; // <X>
    sum2 /= n1; // <Y>
    sum = sum1 * sum2;
    for(int i = 0; i < n1; i++) {
        average_of_squares += x[i] * x[i];
    }
    average_of_squares /= n1;
        for(int i = 0; i < n1; i++) {
        square_of_average += x[i];
    }
    square_of_average /= n1;
    square_of_average *= square_of_average;
    k = (tmp1 - sum) / (average_of_squares - square_of_average);
    b = sum2 - k * sum1;

    for(int i = 0; i < n1; i++) {
        tmp3 += y[i] * y[i];
    }
    tmp3 /= n1; // <Y^2>
    sum2 *= sum2; // <Y>^2
    k_fault = sqrt(((tmp3 - sum2) / (average_of_squares - square_of_average)  - k * k) / n1);
    b_fault = k_fault * sqrt(average_of_squares - square_of_average);
    setprecision(5);
    cout << "y = k * x + b" << endl;
    cout << "k = " << k << endl;
    cout << "b = " << b << endl;
    cout << "k_fault = " << k_fault << endl;
    cout << "b_fault = " << b_fault << endl;
    return 0;
}
