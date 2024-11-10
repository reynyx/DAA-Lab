#include <iostream>
#include <vector>
#include <climits>
#include <stdexcept>
#include <string>
using namespace std;

class MatrixDimensionError : public runtime_error {
public:
    explicit MatrixDimensionError(const string& message) : runtime_error(message) {}
};

class MeteoData {
private:
    vector<int> dimensions;
    vector<vector<int> > dp;        // Fixed spacing between angle brackets
    vector<vector<int> > bracket;   // Fixed spacing between angle brackets

    void validateDimensions() {
        // Check for empty dimensions
        if (dimensions.empty()) {
            throw MatrixDimensionError("Dimensions vector cannot be empty");
        }

        // Check for minimum required matrices (at least 2)
        if (dimensions.size() < 3) {
            throw MatrixDimensionError("Need at least 2 matrices (3 dimensions) for chain multiplication");
        }

        // Check for negative dimensions
        for (size_t i = 0; i < dimensions.size(); i++) {  // Traditional for loop instead of range-based
            int dim = dimensions[i];
            if (dim <= 0) {
                throw MatrixDimensionError("Matrix dimensions must be positive integers");
            }
        }

        // Check for integer overflow possibilities
        for (size_t i = 0; i < dimensions.size() - 1; i++) {
            if ((long long)dimensions[i] * dimensions[i + 1] > INT_MAX) {
                throw MatrixDimensionError("Matrix dimensions too large, may cause integer overflow");
            }
        }
    }

    void printParenthesis(int i, int j) {
        if (i == j) {
            cout << "Matrix" << i;
            return;
        }
        cout << "(";
        printParenthesis(i, bracket[i][j]);
        printParenthesis(bracket[i][j] + 1, j);
        cout << ")";
    }

    void initializeTables() {
        try {
            int n = dimensions.size() - 1;
            dp.resize(n, vector<int>(n, 0));        // Using resize instead of initialization
            bracket.resize(n, vector<int>(n, 0));   // Using resize instead of initialization
        } catch (const bad_alloc& e) {
            throw MatrixDimensionError("Memory allocation failed - dimensions too large");
        }
    }

public:
    MeteoData(const vector<int>& dims) {
        // Copy dimensions using push_back instead of initializer list
        dimensions.clear();
        for (size_t i = 0; i < dims.size(); i++) {
            dimensions.push_back(dims[i]);
        }
        
        try {
            validateDimensions();
            initializeTables();
        } catch (const MatrixDimensionError& e) {
            throw;
        } catch (const exception& e) {
            throw MatrixDimensionError("Unexpected error during initialization: " + string(e.what()));
        }
    }

    void findOptimalOrder() {
        try {
            int n = dimensions.size() - 1;

            for (int i = 0; i < n; i++) {
                dp[i][i] = 0;
            }

            for (int l = 2; l <= n; l++) {
                for (int i = 0; i < n - l + 1; i++) {
                    int j = i + l - 1;
                    dp[i][j] = INT_MAX;

                    for (int k = i; k < j; k++) {
                        long long mult1 = (long long)dimensions[i] * dimensions[k + 1];
                        long long mult2 = mult1 * dimensions[j + 1];
                        
                        if (mult2 > INT_MAX) {
                            throw MatrixDimensionError("Computation caused integer overflow");
                        }

                        int cost = dp[i][k] + dp[k + 1][j] + 
                                 dimensions[i] * dimensions[k + 1] * dimensions[j + 1];
                        
                        if (cost < dp[i][j]) {
                            dp[i][j] = cost;
                            bracket[i][j] = k;
                        }
                    }
                }
            }
        } catch (const exception& e) {
            throw MatrixDimensionError("Error during computation: " + string(e.what()));
        }
    }

    void printOptimalParenthesization() {
        try {
            cout << "Optimal Parenthesization: ";
            printParenthesis(0, dimensions.size() - 2);
            cout << "\nMinimum number of multiplications: " << dp[0][dimensions.size() - 2] << endl;
        } catch (const exception& e) {
            throw MatrixDimensionError("Error while printing results: " + string(e.what()));
        }
    }

    vector<int> getDimensions() const {
        return dimensions;
    }
};

#include <iostream>
#include <vector>
#include <climits>
#include <stdexcept>
#include <string>
using namespace std;

// ... [Previous MeteoData class implementation remains the same] ...

void runTests() {
    cout << "\n====== Running Test Cases ======\n";
    
    // ============ POSITIVE TEST CASES ============
    cout << "\n--- Positive Test Cases ---\n\n";

    // #1 - Basic case with 3 matrices
    #define TEST_POSITIVE_1
    #ifdef TEST_POSITIVE_1
    try {
        cout << "Positive Test #1: Basic case with 3 matrices\n";
        vector<int> dims;
        dims.push_back(2);  // 2x3 matrix
        dims.push_back(3);  // 3x4 matrix
        dims.push_back(4);  // 4x5 matrix
        dims.push_back(5);
        MeteoData test(dims);
        test.findOptimalOrder();
        test.printOptimalParenthesization();
        cout << "Test P1 passed: Successfully processed small chain\n\n";
    } catch (const exception& e) {
        cout << "Test P1 failed: " << e.what() << endl << endl;
    }
    #endif

    // #2 - Larger case with 5 matrices
    #define TEST_POSITIVE_2
    #ifdef TEST_POSITIVE_2
    try {
        cout << "Positive Test #2: Larger case with 5 matrices\n";
        vector<int> dims;
        dims.push_back(5);
        dims.push_back(10);
        dims.push_back(3);
        dims.push_back(12);
        dims.push_back(5);
        dims.push_back(50);
        MeteoData test(dims);
        test.findOptimalOrder();
        test.printOptimalParenthesization();
        cout << "Test P2 passed: Successfully processed larger chain\n\n";
    } catch (const exception& e) {
        cout << "Test P2 failed: " << e.what() << endl << endl;
    }
    #endi