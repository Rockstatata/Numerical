#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Function to calculate forward differences
vector<vector<double>> calculateForwardDifferences(vector<double> y) {
    int n = y.size();
    vector<vector<double>> diffTable(n, vector<double>(n));
    
    // Initialize the first column of the difference table
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    // Calculate forward differences
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diffTable[i][j] = diffTable[i + 1][j - 1] - diffTable[i][j - 1];
        }
    }

    return diffTable;
}

// Function to calculate backward differences
vector<vector<double>> calculateBackwardDifferences(vector<double> y) {
    int n = y.size();
    vector<vector<double>> diffTable(n, vector<double>(n));
    
    // Initialize the first column of the difference table
    for (int i = 0; i < n; i++) {
        diffTable[i][0] = y[i];
    }

    // Calculate backward differences
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            diffTable[i][j] = diffTable[i][j - 1] - diffTable[i - 1][j - 1];
        }
    }

    return diffTable;
}

// Forward interpolation differentiation
double forwardInterpolationDerivative(vector<double> x, vector<double> y, double x0) {
    int n = x.size();
    double h = x[1] - x[0]; // Assumes equal intervals
    vector<vector<double>> forwardDiff = calculateForwardDifferences(y);

    double p = (x0 - x[0]) / h; // Relative position
    double derivative = forwardDiff[0][1] / h; // First term

    // Add higher-order terms (if needed)
    if (n > 2) {
        derivative += (2 * p - 1) * forwardDiff[0][2] / (2 * h);
    }
    return derivative;
}

// Backward interpolation differentiation
double backwardInterpolationDerivative(vector<double> x, vector<double> y, double x0) {
    int n = x.size();
    double h = x[1] - x[0]; // Assumes equal intervals
    vector<vector<double>> backwardDiff = calculateBackwardDifferences(y);

    double p = (x0 - x[n - 1]) / h; // Relative position
    double derivative = backwardDiff[n - 1][1] / h; // First term

    // Add higher-order terms (if needed)
    if (n > 2) {
        derivative += (2 * p + 1) * backwardDiff[n - 1][2] / (2 * h);
    }
    return derivative;
}

int main() {
    int n;
    cout << "Enter the number of data points: ";
    cin >> n;

    vector<double> x(n), y(n);

    cout << "Enter the values of x:\n";
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    cout << "Enter the values of y (f(x)):\n";
    for (int i = 0; i < n; i++) {
        cin >> y[i];
    }

    double x0;
    cout << "Enter the point at which to find the derivative: ";
    cin >> x0;

    if (x0 < x[0] || x0 > x[n - 1]) {
        cout << "Error: x0 must lie within the range of the given data points." << endl;
        return 1;
    }

    cout << fixed << setprecision(6);

    if (x0 <= x[n / 2]) {
        cout << "Using Forward Interpolation:" << endl;
        double result = forwardInterpolationDerivative(x, y, x0);
        cout << "f'(" << x0 << ") = " << result << endl;
    } else {
        cout << "Using Backward Interpolation:" << endl;
        double result = backwardInterpolationDerivative(x, y, x0);
        cout << "f'(" << x0 << ") = " << result << endl;
    }

    return 0;
}
