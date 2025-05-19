//   plugin advmath_1_module for woflang paerser/interpreter 

// Include standard libraries
#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <Eigen/Dense> // Include Eigen library for matrix operations
#include <fftw3.h> // FFTW library for Fourier transformations
#include <functional>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <tuple>
#include <memory>
#include <map>
#include <unordered_map>
#include <random> // swap for better random.
#include <utility>


// Define namespace to keep things organized
namespace AdvancedMath {
    using namespace Eigen; // Use Eigen namespace for matrix operations

    // Matrix Operations
    MatrixXd matrixMultiply(const MatrixXd& A, const MatrixXd& B) {
        return A * B; // Matrix multiplication using Eigen
    }

    MatrixXd matrixTranspose(const MatrixXd& A) {
        return A.transpose(); // Matrix transpose using Eigen
    }

    MatrixXd matrixInverse(const MatrixXd& A) {
        return A.inverse(); // Matrix inversion using Eigen
    }

    std::pair<VectorXd, MatrixXd> matrixEigen(const MatrixXd& A) {
        SelfAdjointEigenSolver<MatrixXd> eigensolver(A);
        if (eigensolver.info() != Success) {
            std::cerr << "Eigenvalue calculation failed!" << std::endl;
            exit(1);
        }
        return std::make_pair(eigensolver.eigenvalues(), eigensolver.eigenvectors());
    }

    double matrixDeterminant(const MatrixXd& A) {
        return A.determinant(); // Matrix determinant using Eigen
    }

    // Linear Algebra Operations
    std::pair<MatrixXd, MatrixXd> luDecomposition(const MatrixXd& A) {
        FullPivLU<MatrixXd> lu_decomp(A);
        return std::make_pair(lu_decomp.matrixLU().triangularView<Lower>(), lu_decomp.matrixLU().triangularView<Upper>());
    }

    std::pair<MatrixXd, MatrixXd> qrDecomposition(const MatrixXd& A) {
        HouseholderQR<MatrixXd> qr_decomp(A);
        return std::make_pair(qr_decomp.householderQ(), qr_decomp.matrixQR().triangularView<Upper>());
    }

    std::tuple<MatrixXd, VectorXd, MatrixXd> svdDecomposition(const MatrixXd& A) {
        JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV);
        return std::make_tuple(svd.matrixU(), svd.singularValues(), svd.matrixV());
    }

    VectorXd leastSquaresSolver(const MatrixXd& A, const VectorXd& b) {
        return A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b);
    }

    Vector3d vectorCrossProduct(const Vector3d& a, const Vector3d& b) {
        return a.cross(b); // Vector cross product using Eigen
    }

    // Fourier Transformations
    void fft(const std::vector<double>& in, std::vector<std::complex<double>>& out) {
        fftw_complex* in_fftw = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * in.size()));
        fftw_complex* out_fftw = reinterpret_cast<fftw_complex*>(fftw_malloc(sizeof(fftw_complex) * in.size()));

        for (size_t i = 0; i < in.size(); ++i) {
            in_fftw[i][0] = in[i]; // Real part
            in_fftw[i][1] = 0.0; // Imaginary part
        }

        fftw_plan plan = fftw_plan_dft_1d(in.size(), in_fftw, out_fftw, FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(plan);

        out.resize(in.size());
        for (size_t i = 0; i < in.size(); ++i) {
            out[i] = std::complex<double>(out_fftw[i][0], out_fftw[i][1]);
        }

        fftw_destroy_plan(plan);
        fftw_free(in_fftw);
        fftw_free(out_fftw);
    }

        //  Calculus Functions
                //      Numerical Integration: Compute integrals numerically using methods like Simpson's rule or trapezoidal rule.
                // Simpson's Rule Numerical Integration
                    double simpsonsRule(const std::vector<double>& x, const std::vector<double>& y) {
                    int n = x.size() - 1;
                if (n % 2 != 0) {
                            std::cerr << "Simpson's rule requires an even number of intervals!" << std::endl;
                            return 0.0;
                }

                    double h = (x.back() - x.front()) / n;
                    double sum = y[0] + y[n];

                        for (int i = 1; i < n; i += 2) {
                                    sum += 4 * y[i];
                                    }
                        for (int i = 2; i < n - 1; i += 2) {
                                    sum += 2 * y[i];
                                    }

                    return sum * h / 3.0;
                }

        // Trapezoidal Rule Numerical Integration
        double trapezoidalRule(const std::vector<double>& x, const std::vector<double>& y) {
            int n = x.size() - 1;
            double h = (x.back() - x.front()) / n;
            double sum = 0.5 * (y[0] + y[n]);

            for (int i = 1; i < n; ++i) {
                sum += y[i];
            }

            return sum * h;
        }

        // Example usage function
        void calc(const std::vector<double>& x, const std::vector<double>& y, bool useSimpsons) {
            double result;
            if (useSimpsons) {
                result = simpsonsRule(x, y);
                std::cout << "Integral using Simpson's Rule: " << result << std::endl;
            } else {
            result = trapezoidalRule(x, y);
                std::cout << "Integral using Trapezoidal Rule: " << result << std::endl;
            }
        }

        int main() {
            std::vector<double> x = {0, 1, 2, 3, 4}; // Example x-values
            std::vector<double> y = {0, 1, 4, 9, 16}; // Example y-values: f(x) = x^2

            calc(x, y, true);  // Use Simpson's Rule
            calc(x, y, false); // Use Trapezoidal Rule

            return 0;
        }

            //  Differentiation: Compute derivatives numerically or symbolically.
// Forward Difference Method for Numerical Differentiation
double forwardDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i >= x.size() - 1) {
        std::cerr << "Index out of bounds for forward difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i + 1] - x[i];
    return (y[i + 1] - y[i]) / h;
}

// Backward Difference Method for Numerical Differentiation
double backwardDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i <= 0) {
        std::cerr << "Index out of bounds for backward difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i] - x[i - 1];
    return (y[i] - y[i - 1]) / h;
}

// Central Difference Method for Numerical Differentiation
double centralDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i <= 0 || i >= x.size() - 1) {
        std::cerr << "Index out of bounds for central difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i + 1] - x[i - 1];
    return (y[i + 1] - y[i - 1]) / h;
}

// Function to compute numerical derivatives
void computeDerivatives(const std::vector<double>& x, const std::vector<double>& y, std::vector<double>& derivatives, const std::string& method = "central") {
    derivatives.resize(x.size());
    
    for (int i = 0; i < x.size(); ++i) {
        if (method == "forward") {
            if (i < x.size() - 1) {
                derivatives[i] = forwardDifference(x, y, i);
            } else {
                derivatives[i] = NAN; // Forward difference not possible for last element
            }
        } else if (method == "backward") {
            if (i > 0) {
                derivatives[i] = backwardDifference(x, y, i);
            } else {
                derivatives[i] = NAN; // Backward difference not possible for first element
            }
        } else if (method == "central") {
            if (i > 0 && i < x.size() - 1) {
                derivatives[i] = centralDifference(x, y, i);
            } else if (i == 0) {
                derivatives[i] = forwardDifference(x, y, i); // Use forward for first element
            } else if (i == x.size() - 1) {
                derivatives[i] = backwardDifference(x, y, i); // Use backward for last element
            }
        } else {
            std::cerr << "Unknown differentiation method: " << method << std::endl;
            return;
        }
    }
}

// Example usage
int main() {
    std::vector<double> x = {0, 1, 2, 3, 4};  // Example x-values
    std::vector<double> y = {0, 1, 4, 9, 16}; // Example y-values: f(x) = x^2

    std::vector<double> derivatives;

    // Compute derivatives using central difference method
    computeDerivatives(x, y, derivatives, "central");
    std::cout << "Derivatives using Central Difference:" << std::endl;
    for (const auto& d : derivatives) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Compute derivatives using forward difference method
    computeDerivatives(x, y, derivatives, "forward");
    std::cout << "Derivatives using Forward Difference:" << std::endl;
    for (const auto& d : derivatives) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    // Compute derivatives using backward difference method
    computeDerivatives(x, y, derivatives, "backward");
    std::cout << "Derivatives using Backward Difference:" << std::endl;
    for (const auto& d : derivatives) {
        std::cout << d << " ";
    }
    std::cout << std::endl;

    return 0;
}

            //      Differentiation: Compute derivatives numerically or symbolically.
// Define a structure to hold complex calculations if needed (placeholder)
struct calc_complex {
    double real;
    double imag;
};

// Numerical Differentiation Methods for Real Functions
double forwardDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i >= x.size() - 1) {
        std::cerr << "Index out of bounds for forward difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i + 1] - x[i];
    return (y[i + 1] - y[i]) / h;
}

double backwardDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i <= 0) {
        std::cerr << "Index out of bounds for backward difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i] - x[i - 1];
    return (y[i] - y[i - 1]) / h;
}

double centralDifference(const std::vector<double>& x, const std::vector<double>& y, int i) {
    if (i <= 0 || i >= x.size() - 1) {
        std::cerr << "Index out of bounds for central difference calculation!" << std::endl;
        return 0.0;
    }
    double h = x[i + 1] - x[i - 1];
    return (y[i + 1] - y[i - 1]) / h;
}

// Placeholder function for symbolic differentiation (requires a symbolic math library)
std::string symbolicDifferentiation(const std::string& expression) {
    // In a real implementation, this function would parse the expression and compute its derivative symbolically.
    // Placeholder: Return a dummy derivative.
    return "d/dx (" + expression + ")";
}

// General differentiation function to compute derivatives (numerically or symbolically)
void calc(const std::vector<double>& x, const std::vector<double>& y, std::vector<std::complex<double>>& derivatives, bool useSymbolic = false) {
    if (useSymbolic) {
        // If symbolic differentiation is requested, process each function expression symbolically
        for (const auto& expr : x) {  // Assuming 'x' holds expressions as strings if symbolic
            std::string symbolic_result = symbolicDifferentiation(std::to_string(expr));
            std::cout << "Symbolic Derivative of " << expr << ": " << symbolic_result << std::endl;
        }
    } else {
        // Compute numerical derivatives
        derivatives.resize(x.size());
        for (int i = 0; i < x.size(); ++i) {
            if (i > 0 && i < x.size() - 1) {
                derivatives[i] = centralDifference(x, y, i);
            } else if (i == 0) {
                derivatives[i] = forwardDifference(x, y, i);
            } else if (i == x.size() - 1) {
                derivatives[i] = backwardDifference(x, y, i);
            }
        }
    }
}

// Example usage
int main() {
    std::vector<double> x = {0, 1, 2, 3, 4};  // Example x-values
    std::vector<double> y = {0, 1, 4, 9, 16}; // Example y-values: f(x) = x^2

    std::vector<std::complex<double>> derivatives;

    // Compute derivatives numerically
    calc(x, y, derivatives, false);

    std::cout << "Numerical Derivatives:" << std::endl;
    for (const auto& d : derivatives) {
        std::cout << d.real() << " + " << d.imag() << "i" << std::endl;
    }

    // Example symbolic differentiation (output as placeholder)
    std::vector<double> expressions = {2.0}; // Placeholder for expressions if using symbolic math
    calc(expressions, y, derivatives, true);

    return 0;
}

            //      Gradient and Hessian Calculations: Compute the gradient or Hessian matrix of a function
// Function to calculate the numerical gradient of a scalar function f at a point x
std::vector<double> computeGradient(const std::function<double(const std::vector<double>&)>& f, const std::vector<double>& x, double h = 1e-5) {
    int n = x.size();
    std::vector<double> gradient(n);
    
    for (int i = 0; i < n; ++i) {
        std::vector<double> x_forward = x;
        std::vector<double> x_backward = x;

        x_forward[i] += h;
        x_backward[i] -= h;

        gradient[i] = (f(x_forward) - f(x_backward)) / (2 * h);  // Central difference
    }

    return gradient;
}

// Function to calculate the numerical Hessian matrix of a scalar function f at a point x
Eigen::MatrixXd computeHessian(const std::function<double(const std::vector<double>&)>& f, const std::vector<double>& x, double h = 1e-5) {
    int n = x.size();
    Eigen::MatrixXd hessian(n, n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::vector<double> x_forward_i = x;
            std::vector<double> x_backward_i = x;
            std::vector<double> x_forward_j = x;
            std::vector<double> x_backward_j = x;
            std::vector<double> x_forward_ij = x;
            std::vector<double> x_backward_ij = x;

            if (i == j) {
                x_forward_i[i] += h;
                x_backward_i[i] -= h;

                hessian(i, j) = (f(x_forward_i) - 2 * f(x) + f(x_backward_i)) / (h * h);  // Second derivative wrt xi
            } else {
                x_forward_ij[i] += h; x_forward_ij[j] += h;
                x_backward_ij[i] -= h; x_backward_ij[j] -= h;
                x_forward_i[i] += h; x_backward_i[i] -= h;
                x_forward_j[j] += h; x_backward_j[j] -= h;

                hessian(i, j) = (f(x_forward_ij) - f(x_forward_i) - f(x_forward_j) + f(x)) / (h * h);  // Mixed partial derivative
            }
        }
    }

    return hessian;
}

// Function to calculate both Gradient and Hessian of a scalar function
void calc(const std::function<double(const std::vector<double>&)>& f, const std::vector<double>& x, std::vector<double>& gradient, Eigen::MatrixXd& hessian) {
    gradient = computeGradient(f, x);
    hessian = computeHessian(f, x);
}

// Example usage function
int main() {
    auto func = [](const std::vector<double>& x) -> double {
        return x[0] * x[0] + x[1] * x[1] + x[2] * x[2];  // Example function: f(x, y, z) = x^2 + y^2 + z^2
    };

    std::vector<double> x = {1.0, 2.0, 3.0};  // Point at which to calculate gradient and Hessian
    std::vector<double> gradient;
    Eigen::MatrixXd hessian;

    calc(func, x, gradient, hessian);

    // Output results
    std::cout << "Gradient:" << std::endl;
    for (double grad : gradient) {
        std::cout << grad << " ";
    }
    std::cout << std::endl;

    std::cout << "Hessian:" << std::endl;
    std::cout << hessian << std::endl;

    return 0;
}

            //      Graph Theory Functions

// Function to add an edge to an adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
    adjList[v].push_back({u, weight});
}

// Dijkstra's Algorithm for Shortest Paths
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for Shortest Paths
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// Depth-First Search (DFS)
void dfs(const std::vector<std::vector<int>>& adjList, int start, std::vector<bool>& visited) {
    visited[start] = true;
    std::cout << start << " ";
    
    for (int v : adjList[start]) {
        if (!visited[v]) {
            dfs(adjList, v, visited);
        }
    }
}

// Breadth-First Search (BFS)
void bfs(const std::vector<std::vector<int>>& adjList, int start) {
    int n = adjList.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << u << " ";
        
        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Kruskal's Algorithm for Minimum Spanning Tree (MST)
struct Edge {
    int u, v;
    double weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int find(int u, std::vector<int>& parent) {
    if (parent[u] != u) {
        parent[u] = find(parent[u], parent);
    }
    return parent[u];
}

void unite(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);
    
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

std::vector<Edge> kruskal(int n, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end());
    std::vector<Edge> mst;
    std::vector<int> parent(n), rank(n, 0);
    
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
    
    for (const auto& edge : edges) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            mst.push_back(edge);
            unite(edge.u, edge.v, parent, rank);
        }
    }
    
    return mst;
}

// Prim's Algorithm for Minimum Spanning Tree (MST)
std::vector<double> prim(const std::vector<std::vector<std::pair<int, double>>>& adjList) {
    int n = adjList.size();
    std::vector<double> key(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);
    
    key[0] = 0;
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        int u = pq.top().second; pq.pop();
        inMST[u] = true;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }
    
    return key;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in graph
    
    // Example graph with weighted edges
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Example edges for Bellman-Ford and Kruskal
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    std::vector<Edge> edgesKruskal = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Run Dijkstra's algorithm
    std::vector<double> dist = dijkstra(adjList, 0);
    std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    for (double d : dist) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    
    // Run Bellman-Ford algorithm
    try {
        std::vector<double> distBF = bellmanFord(edges, n, 0);
        std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        for (double d : distBF) {
            std::cout << d << " ";
        }
        std::cout << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    
    // Run Depth-First Search (DFS)
    std::cout << "DFS traversal from node 0:" << std::endl;
    std::vector<bool> visited(n, false);
    dfs(adjList, 0, visited);
    std::cout << std::endl;
    
    // Run Breadth-First Search (BFS)
    std::cout << "BFS traversal from node 0:" << std::endl;
    bfs(adjList, 0);
    std::cout << std::endl;
    
    // Run Kruskal's algorithm
    std::vector<Edge> mstKruskal = kruskal(n, edgesKruskal);
    std::cout << "Edges in the MST using Kruskal's algorithm:" << std::endl;
    for (const auto& edge : mstKruskal) {
        std::cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ") ";
    }
    std::cout << std::endl;
    
    // Run Prim's algorithm
    std::vector<double> mstPrim = prim(adjList);
    std::cout << "Minimum spanning tree using Prim's algorithm:" << std::endl;
    for (double k : mstPrim) {
        std::cout << k << " ";
    }
    std::cout << std::endl;
    
    return 0;
}

   //  Shortest Path Algorithms:

// Define a struct for complex numbers if needed
struct calc_complex {
    double real;
    double imag;
};

// Function to add an edge to the graph's adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
}

// Dijkstra's Algorithm for finding the shortest paths from a source node
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for finding shortest paths and detecting negative-weight cycles
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// General function to calculate shortest paths using Dijkstra's or Bellman-Ford algorithms
void calc(const std::vector<std::tuple<int, int, double>>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int start, bool useDijkstra) {
    std::vector<double> shortestPaths;

    if (useDijkstra) {
        shortestPaths = dijkstra(adjList, start);
        std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    } else {
        try {
            shortestPaths = bellmanFord(edges, adjList.size(), start);
            std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    for (double d : shortestPaths) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Create an edge list for Bellman-Ford algorithm
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Run shortest path calculations
    calc(edges, adjList, 0, true);  // Use Dijkstra's algorithm
    calc(edges, adjList, 0, false); // Use Bellman-Ford algorithm
    
    return 0;
}

// Define a struct for complex numbers if needed
struct calc_complex {
    double real;
    double imag;
};

// Function to add an edge to the graph's adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
}

// Dijkstra's Algorithm for finding the shortest paths from a source node
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for finding shortest paths and detecting negative-weight cycles
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// General function to calculate shortest paths using Dijkstra's or Bellman-Ford algorithms
void calc(const std::vector<std::tuple<int, int, double>>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int start, bool useDijkstra) {
    std::vector<double> shortestPaths;

    if (useDijkstra) {
        shortestPaths = dijkstra(adjList, start);
        std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    } else {
        try {
            shortestPaths = bellmanFord(edges, adjList.size(), start);
            std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    for (double d : shortestPaths) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Create an edge list for Bellman-Ford algorithm
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Run shortest path calculations
    calc(edges, adjList, 0, true);  // Use Dijkstra's algorithm
    calc(edges, adjList, 0, false); // Use Bellman-Ford algorithm
    
    return 0;
}

// Define a struct for complex numbers if needed
struct calc_complex {
    double real;
    double imag;
};

// Function to add an edge to the graph's adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
}

// Dijkstra's Algorithm for finding the shortest paths from a source node
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for finding shortest paths and detecting negative-weight cycles
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// General function to calculate shortest paths using Dijkstra's or Bellman-Ford algorithms
void calc(const std::vector<std::tuple<int, int, double>>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int start, bool useDijkstra) {
    std::vector<double> shortestPaths;

    if (useDijkstra) {
        shortestPaths = dijkstra(adjList, start);
        std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    } else {
        try {
            shortestPaths = bellmanFord(edges, adjList.size(), start);
            std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    for (double d : shortestPaths) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Create an edge list for Bellman-Ford algorithm
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Run shortest path calculations
    calc(edges, adjList, 0, true);  // Use Dijkstra's algorithm
    calc(edges, adjList, 0, false); // Use Bellman-Ford algorithm
    
    return 0;
}

// Define a struct for complex numbers if needed
struct calc_complex {
    double real;
    double imag;
};

// Function to add an edge to the graph's adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
}

// Dijkstra's Algorithm for finding the shortest paths from a source node
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for finding shortest paths and detecting negative-weight cycles
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// General function to calculate shortest paths using Dijkstra's or Bellman-Ford algorithms
void calc(const std::vector<std::tuple<int, int, double>>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int start, bool useDijkstra) {
    std::vector<double> shortestPaths;

    if (useDijkstra) {
        shortestPaths = dijkstra(adjList, start);
        std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    } else {
        try {
            shortestPaths = bellmanFord(edges, adjList.size(), start);
            std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    for (double d : shortestPaths) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Create an edge list for Bellman-Ford algorithm
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Run shortest path calculations
    calc(edges, adjList, 0, true);  // Use Dijkstra's algorithm
    calc(edges, adjList, 0, false); // Use Bellman-Ford algorithm
    
    return 0;
}

            //      Shortest Path Algorithms: Dijkstra's or Bellman-Ford algorithms for finding shortest paths in graphs.

// Define complex number handling structure (if needed for extended functionality)
struct calc_complex {
    double real;
    double imag;
};

// Function to add an edge to an adjacency list
void addEdge(std::vector<std::vector<std::pair<int, double>>>& adjList, int u, int v, double weight) {
    adjList[u].push_back({v, weight});
}

// Dijkstra's Algorithm for finding shortest paths from a source node
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& adjList, int start) {
    int n = adjList.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    using P = std::pair<double, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [currentDist, u] = pq.top(); pq.pop();
        if (currentDist > dist[u]) continue;
        
        for (const auto& [v, weight] : adjList[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Bellman-Ford Algorithm for finding shortest paths and detecting negative-weight cycles
std::vector<double> bellmanFord(const std::vector<std::tuple<int, int, double>>& edges, int n, int start) {
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[start] = 0;
    
    for (int i = 1; i < n; ++i) {
        for (const auto& [u, v, weight] : edges) {
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    
    // Check for negative-weight cycles
    for (const auto& [u, v, weight] : edges) {
        if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
            throw std::runtime_error("Graph contains a negative-weight cycle");
        }
    }
    
    return dist;
}

// General function to calculate shortest paths using Dijkstra's or Bellman-Ford algorithms
void calc(const std::vector<std::tuple<int, int, double>>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int start, bool useDijkstra, std::vector<double>& out) {
    if (useDijkstra) {
        out = dijkstra(adjList, start);
        std::cout << "Shortest distances using Dijkstra's algorithm:" << std::endl;
    } else {
        try {
            out = bellmanFord(edges, adjList.size(), start);
            std::cout << "Shortest distances using Bellman-Ford algorithm:" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    for (double d : out) {
        std::cout << d << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    addEdge(adjList, 0, 1, 2);
    addEdge(adjList, 0, 2, 4);
    addEdge(adjList, 1, 2, 1);
    addEdge(adjList, 1, 3, 7);
    addEdge(adjList, 2, 4, 3);
    addEdge(adjList, 3, 4, 1);
    
    // Create an edge list for Bellman-Ford algorithm
    std::vector<std::tuple<int, int, double>> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};
    
    // Output vector for shortest paths
    std::vector<double> shortestPaths;
    
    // Run shortest path calculations
    calc(edges, adjList, 0, true, shortestPaths);  // Use Dijkstra's algorithm
    calc(edges, adjList, 0, false, shortestPaths); // Use Bellman-Ford algorithm
    
    return 0;
}

             //      Graph Search Algorithms: Depth-first search (DFS), breadth-first search (BFS).

// Placeholder structure for complex calculations (not required for basic DFS and BFS)
struct calc_complex {
    double real;
    double imag;
};

// Depth-First Search (DFS) using an iterative approach
void depthFirstSearch(const std::vector<std::vector<int>>& adjList, int start) {
    int n = adjList.size();
    std::vector<bool> visited(n, false); // To keep track of visited nodes
    std::stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            std::cout << u << " ";
            visited[u] = true;
        }

        // Push all adjacent vertices of u to the stack
        for (int v : adjList[u]) {
            if (!visited[v]) {
                s.push(v);
            }
        }
    }
}

// Breadth-First Search (BFS) using a queue
void breadthFirstSearch(const std::vector<std::vector<int>>& adjList, int start) {
    int n = adjList.size();
    std::vector<bool> visited(n, false); // To keep track of visited nodes
    std::queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        std::cout << u << " ";

        // Enqueue all adjacent vertices of u
        for (int v : adjList[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// General function to perform graph search using either DFS or BFS
void calc(const std::vector<std::vector<int>>& adjList, int start, bool useDFS) {
    if (useDFS) {
        std::cout << "Depth-First Search (DFS) traversal starting from node " << start << ":" << std::endl;
        depthFirstSearch(adjList, start);
    } else {
        std::cout << "Breadth-First Search (BFS) traversal starting from node " << start << ":" << std::endl;
        breadthFirstSearch(adjList, start);
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph
    
    // Create an adjacency list for the graph
    std::vector<std::vector<int>> adjList(n);
    adjList[0] = {1, 2};  // Node 0 is connected to Node 1 and Node 2
    adjList[1] = {0, 3};  // Node 1 is connected to Node 0 and Node 3
    adjList[2] = {0, 4};  // Node 2 is connected to Node 0 and Node 4
    adjList[3] = {1};     // Node 3 is connected to Node 1
    adjList[4] = {2};     // Node 4 is connected to Node 2
    
    // Perform DFS and BFS starting from node 0
    calc(adjList, 0, true);  // Use DFS
    calc(adjList, 0, false); // Use BFS
    
    return 0;
}

            //      Minimum Spanning Tree: Kruskal’s or Prim’s algorithm.

// Struct to represent an edge
struct Edge {
    int u, v;       // The two nodes this edge connects
    double weight;  // The weight of this edge

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Helper function to find the root of a node in a union-find structure
int find(int u, std::vector<int>& parent) {
    if (parent[u] != u) {
        parent[u] = find(parent[u], parent);  // Path compression
    }
    return parent[u];
}

// Helper function to unite two sets in a union-find structure
void unite(int u, int v, std::vector<int>& parent, std::vector<int>& rank) {
    int rootU = find(u, parent);
    int rootV = find(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal's Algorithm for Minimum Spanning Tree
std::vector<Edge> kruskal(int n, std::vector<Edge>& edges) {
    std::sort(edges.begin(), edges.end());  // Sort edges by weight
    std::vector<Edge> mst;  // Store edges that form the MST
    std::vector<int> parent(n), rank(n, 0);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;  // Each node is its own parent initially
    }

    for (const auto& edge : edges) {
        if (find(edge.u, parent) != find(edge.v, parent)) {
            mst.push_back(edge);
            unite(edge.u, edge.v, parent, rank);
        }
    }

    return mst;
}

// Prim's Algorithm for Minimum Spanning Tree
std::vector<Edge> prim(const std::vector<std::vector<std::pair<int, double>>>& adjList) {
    int n = adjList.size();
    std::vector<double> key(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> inMST(n, false);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;

    key[0] = 0;
    pq.push({0, 0});

    std::vector<Edge> mst;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (const auto& [v, weight] : adjList[u]) {
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({key[v], v});
                parent[v] = u;
            }
        }
    }

    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1) {
            mst.push_back({parent[v], v, key[v]});
        }
    }

    return mst;
}

// General function to calculate Minimum Spanning Tree using Kruskal's or Prim's algorithms
void calc(const std::vector<Edge>& edges, const std::vector<std::vector<std::pair<int, double>>>& adjList, int n, bool useKruskal, std::vector<Edge>& mst) {
    if (useKruskal) {
        mst = kruskal(n, const_cast<std::vector<Edge>&>(edges));
        std::cout << "Edges in the MST using Kruskal's algorithm:" << std::endl;
    } else {
        mst = prim(adjList);
        std::cout << "Edges in the MST using Prim's algorithm:" << std::endl;
    }

    for (const auto& edge : mst) {
        std::cout << "(" << edge.u << ", " << edge.v << ", " << edge.weight << ")" << std::endl;
    }
}

// Example usage function
int main() {
    int n = 5; // Number of nodes in the graph

    // Example edges for Kruskal's algorithm
    std::vector<Edge> edges = {{0, 1, 2}, {0, 2, 4}, {1, 2, 1}, {1, 3, 7}, {2, 4, 3}, {3, 4, 1}};

    // Create an adjacency list for Prim's algorithm
    std::vector<std::vector<std::pair<int, double>>> adjList(n);
    adjList[0].push_back({1, 2});
    adjList[0].push_back({2, 4});
    adjList[1].push_back({0, 2});
    adjList[1].push_back({2, 1});
    adjList[1].push_back({3, 7});
    adjList[2].push_back({0, 4});
    adjList[2].push_back({1, 1});
    adjList[2].push_back({4, 3});
    adjList[3].push_back({1, 7});
    adjList[3].push_back({4, 1});
    adjList[4].push_back({2, 3});
    adjList[4].push_back({3, 1});

    // Output vector for MST
    std::vector<Edge> mst;

    // Run MST calculations
    calc(edges, adjList, n, true, mst);  // Use Kruskal's algorithm
    calc(edges, adjList, n, false, mst); // Use Prim's algorithm

    return 0;
}

    //  Advanced Trigonometry and Geometry

// Struct to represent a point in 2D or 3D space
struct Point {
    double x, y, z = 0; // 2D points have z = 0 by default
};

// Function to convert degrees to radians
inline double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Spherical Trigonometry: Calculate the great-circle distance between two points on a sphere
double sphericalDistance(const Point& p1, const Point& p2, double radius) {
    double lat1 = toRadians(p1.x);
    double lon1 = toRadians(p1.y);
    double lat2 = toRadians(p2.x);
    double lon2 = toRadians(p2.y);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return radius * c;
}

// Geometric Transformations: Rotate a 2D point around the origin
Point rotate2D(const Point& p, double angleDegrees) {
    double angle = toRadians(angleDegrees);
    double cosAngle = cos(angle);
    double sinAngle = sin(angle);
    return {p.x * cosAngle - p.y * sinAngle, p.x * sinAngle + p.y * cosAngle};
}

// Geometric Transformations: Translate a 2D or 3D point
Point translate(const Point& p, const Point& translationVector) {
    return {p.x + translationVector.x, p.y + translationVector.y, p.z + translationVector.z};
}

// Geometric Transformations: Scale a 2D or 3D point
Point scale(const Point& p, double scaleFactor) {
    return {p.x * scaleFactor, p.y * scaleFactor, p.z * scaleFactor};
}

// Convex Hull Algorithms: Andrew's monotone chain algorithm for convex hull in 2D
std::vector<Point> convexHull(std::vector<Point> points) {
    if (points.size() <= 1) return points;

    // Sort points lexicographically
    std::sort(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return std::tie(p1.x, p1.y) < std::tie(p2.x, p2.y);
    });

    std::vector<Point> hull;

    // Lower hull
    for (const auto& pt : points) {
        while (hull.size() >= 2 && (hull[hull.size() - 1].x - hull[hull.size() - 2].x) * (pt.y - hull[hull.size() - 2].y) - 
               (hull[hull.size() - 1].y - hull[hull.size() - 2].y) * (pt.x - hull[hull.size() - 2].x) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pt);
    }

    // Upper hull
    size_t t = hull.size() + 1;
    for (int i = points.size() - 1; i >= 0; i--) {
        const auto& pt = points[i];
        while (hull.size() >= t && (hull[hull.size() - 1].x - hull[hull.size() - 2].x) * (pt.y - hull[hull.size() - 2].y) - 
               (hull[hull.size() - 1].y - hull[hull.size() - 2].y) * (pt.x - hull[hull.size() - 2].x) <= 0) {
            hull.pop_back();
        }
        hull.push_back(pt);
    }

    hull.pop_back(); // Remove the last point because it is the same as the first one

    return hull;
}

// General function to perform advanced trigonometry and geometry calculations
void calc(const std::vector<Point>& in, std::vector<Point>& out, int operationType, double param = 0) {
    out.clear();
    switch (operationType) {
        case 1: { // Spherical Distance Calculation
            double radius = param; // Assuming param is radius
            if (in.size() >= 2) {
                double distance = sphericalDistance(in[0], in[1], radius);
                std::cout << "Great-circle distance: " << distance << std::endl;
            }
            break;
        }
        case 2: { // Rotate 2D Points
            double angleDegrees = param; // Assuming param is angle in degrees
            for (const auto& p : in) {
                out.push_back(rotate2D(p, angleDegrees));
            }
            std::cout << "Points after rotation:" << std::endl;
            break;
        }
        case 3: { // Translate Points
            if (in.size() >= 2) {
                Point translationVector = in[1]; // Second point represents translation vector
                for (const auto& p : in) {
                    out.push_back(translate(p, translationVector));
                }
                std::cout << "Points after translation:" << std::endl;
            }
            break;
        }
        case 4: { // Scale Points
            double scaleFactor = param; // Assuming param is scale factor
            for (const auto& p : in) {
                out.push_back(scale(p, scaleFactor));
            }
            std::cout << "Points after scaling:" << std::endl;
            break;
        }
        case 5: { // Convex Hull Calculation
            out = convexHull(in);
            std::cout << "Convex Hull Points:" << std::endl;
            break;
        }
        default:
            std::cout << "Invalid operation type!" << std::endl;
    }

    for (const auto& p : out) {
        std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }
}

// Example usage function
int main() {
    std::vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {3, 0}, {0, 3}, {3, 3}};
    std::vector<Point> out;

    // Spherical distance calculation (Example points are not on a sphere, this is just to demonstrate functionality)
    calc({{40.7486, -73.9864}, {51.5074, -0.1278}}, out, 1, 6371.0); // Distance between New York and London on Earth's surface

    // Rotate points 45 degrees around the origin
    calc(points, out, 2, 45);

    // Translate points by (1, 1, 0)
    calc({{0, 0}, {1, 1}}, out, 3);

    // Scale points by a factor of 2
    calc(points, out, 4, 2);

    // Calculate the convex hull of points
    calc(points, out, 5);

    return 0;
}

            //      Spherical Trigonometry: Functions for solving triangles on a sphere.

const double PI = 3.141592653589793;
const double EARTH_RADIUS_KM = 6371.0;  // Average radius of the Earth in kilometers

// Function to convert degrees to radians
inline double toRadians(double degrees) {
    return degrees * PI / 180.0;
}

// Function to calculate the great-circle distance between two points on a sphere using the haversine formula
double haversineDistance(double lat1, double lon1, double lat2, double lon2, double radius = EARTH_RADIUS_KM) {
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return radius * c;
}

// Function to calculate the spherical excess of a triangle on a sphere
double sphericalExcess(double A, double B, double C) {
    return A + B + C - PI;  // Angles are in radians; result in radians
}

// Function to calculate an angle in a spherical triangle using the law of cosines for spherical trigonometry
double sphericalAngle(double a, double b, double c) {
    return acos((cos(a) - cos(b) * cos(c)) / (sin(b) * sin(c)));
}

// General function to perform spherical trigonometry calculations
void calc(const std::vector<double>& in, std::vector<std::complex<double>>& out) {
    if (in.size() < 4) {
        std::cerr << "Insufficient input data!" << std::endl;
        return;
    }

    double lat1 = in[0];
    double lon1 = in[1];
    double lat2 = in[2];
    double lon2 = in[3];

    // Calculate great-circle distance between two points on the Earth's surface
    double distance = haversineDistance(lat1, lon1, lat2, lon2);
    std::cout << "Great-circle distance: " << distance << " km" << std::endl;

    // Example of calculating spherical angles in a triangle (requires more input)
    if (in.size() >= 7) {
        double a = in[4];  // Side length in radians
        double b = in[5];  // Side length in radians
        double c = in[6];  // Side length in radians

        double angleA = sphericalAngle(a, b, c);
        double angleB = sphericalAngle(b, c, a);
        double angleC = sphericalAngle(c, a, b);

        std::cout << "Spherical Triangle Angles: A = " << angleA * 180.0 / PI
                  << "°, B = " << angleB * 180.0 / PI
                  << "°, C = " << angleC * 180.0 / PI << "°" << std::endl;
    }
}

// Example usage function
int main() {
    std::vector<double> inputData = {40.7486, -73.9864, 51.5074, -0.1278, 1.0, 1.0, 1.0};  // Example lat/lon in degrees + sides in radians

    std::vector<std::complex<double>> outputData;
    calc(inputData, outputData);

    return 0;
}

            //      Geometric Transformations: Functions for rotation, translation, and scaling in 2D or 3D.

// Struct to represent a point in 2D or 3D space
struct Point {
    double x, y, z = 0;  // 2D points have z = 0 by default
};

// Function to convert degrees to radians
inline double toRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

// Geometric Transformation: Rotate a 2D point around the origin
Point rotate2D(const Point& p, double angleDegrees) {
    double angle = toRadians(angleDegrees);
    double cosAngle = cos(angle);
    double sinAngle = sin(angle);
    return {p.x * cosAngle - p.y * sinAngle, p.x * sinAngle + p.y * cosAngle};
}

// Geometric Transformation: Rotate a 3D point around the Z-axis
Point rotate3D(const Point& p, double angleDegrees, char axis) {
    double angle = toRadians(angleDegrees);
    double cosAngle = cos(angle);
    double sinAngle = sin(angle);
    Point rotatedPoint = p;

    switch (axis) {
        case 'x':  // Rotate around the X-axis
            rotatedPoint.y = p.y * cosAngle - p.z * sinAngle;
            rotatedPoint.z = p.y * sinAngle + p.z * cosAngle;
            break;
        case 'y':  // Rotate around the Y-axis
            rotatedPoint.x = p.x * cosAngle + p.z * sinAngle;
            rotatedPoint.z = -p.x * sinAngle + p.z * cosAngle;
            break;
        case 'z':  // Rotate around the Z-axis
            rotatedPoint.x = p.x * cosAngle - p.y * sinAngle;
            rotatedPoint.y = p.x * sinAngle + p.y * cosAngle;
            break;
        default:
            std::cerr << "Invalid axis! Choose 'x', 'y', or 'z'." << std::endl;
    }

    return rotatedPoint;
}

// Geometric Transformation: Translate a 2D or 3D point
Point translate(const Point& p, const Point& translationVector) {
    return {p.x + translationVector.x, p.y + translationVector.y, p.z + translationVector.z};
}

// Geometric Transformation: Scale a 2D or 3D point
Point scale(const Point& p, double scaleFactor) {
    return {p.x * scaleFactor, p.y * scaleFactor, p.z * scaleFactor};
}

// General function to perform geometric transformations
void calc(const std::vector<Point>& in, std::vector<Point>& out, int transformationType, double param = 0, char axis = 'z') {
    out.clear();
    switch (transformationType) {
        case 1: { // Rotate 2D Points
            double angleDegrees = param;  // Assuming param is angle in degrees
            for (const auto& p : in) {
                out.push_back(rotate2D(p, angleDegrees));
            }
            std::cout << "Points after 2D rotation:" << std::endl;
            break;
        }
        case 2: { // Rotate 3D Points
            double angleDegrees = param;  // Assuming param is angle in degrees
            for (const auto& p : in) {
                out.push_back(rotate3D(p, angleDegrees, axis));
            }
            std::cout << "Points after 3D rotation around " << axis << "-axis:" << std::endl;
            break;
        }
        case 3: { // Translate Points
            if (in.size() >= 1) {
                Point translationVector = {param, param, param};  // Example translation vector; modify as needed
                for (const auto& p : in) {
                    out.push_back(translate(p, translationVector));
                }
                std::cout << "Points after translation:" << std::endl;
            }
            break;
        }
        case 4: { // Scale Points
            double scaleFactor = param;  // Assuming param is scale factor
            for (const auto& p : in) {
                out.push_back(scale(p, scaleFactor));
            }
            std::cout << "Points after scaling:" << std::endl;
            break;
        }
        default:
            std::cout << "Invalid transformation type!" << std::endl;
    }

    for (const auto& p : out) {
        std::cout << "(" << p.x << ", " << p.y << ", " << p.z << ")" << std::endl;
    }
}

// Example usage function
int main() {
    std::vector<Point> points = {{1, 1}, {2, 2}, {3, 3}};
    std::vector<Point> out;

    // Rotate points 45 degrees around the origin in 2D
    calc(points, out, 1, 45);

    // Rotate points 30 degrees around the Z-axis in 3D
    calc(points, out, 2, 30, 'z');

    // Translate points by (1, 1, 1)
    calc(points, out, 3, 1);

    // Scale points by a factor of 2
    calc(points, out, 4, 2);

    return 0;
}

            //      Convex Hull Algorithms: Determine the convex hull of a set of points.

// Struct to represent a point in 2D space
struct Point {
    double x, y;

    // Comparison operator to sort points lexicographically
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

// Function to compute the cross product of two vectors (p1p2 and p1p3)
double crossProduct(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

// Convex Hull Algorithm: Andrew's monotone chain algorithm
std::vector<Point> convexHull(std::vector<Point>& points) {
    if (points.size() <= 1) return points;

    // Sort the points lexicographically (by x, then by y)
    std::sort(points.begin(), points.end());

    std::vector<Point> hull;

    // Build the lower hull
    for (const auto& p : points) {
        while (hull.size() >= 2 && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Build the upper hull
    size_t t = hull.size() + 1;
    for (int i = points.size() - 1; i >= 0; i--) {
        const auto& p = points[i];
        while (hull.size() >= t && crossProduct(hull[hull.size() - 2], hull[hull.size() - 1], p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    hull.pop_back();  // Remove the last point since it's the same as the first point in the hull

    return hull;
}

// General function to determine the convex hull of a set of points
void calc(const std::vector<Point>& in, std::vector<Point>& out) {
    // Copy the input points to a local vector to sort and compute the convex hull
    std::vector<Point> points = in;

    // Compute the convex hull
    out = convexHull(points);

    std::cout << "Convex Hull Points:" << std::endl;
    for (const auto& p : out) {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }
}

// Example usage function
int main() {
    // Example set of points
    std::vector<Point> points = {{0, 3}, {1, 1}, {2, 2}, {4, 4}, {0, 0}, {1, 2}, {3, 1}, {3, 3}};
    std::vector<Point> hull;

    // Calculate the convex hull
    calc(points, hull);

    return 0;
}

    //  Symbolic Computation



// Base class for symbolic expressions
class Expression {
public:
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Expression> differentiate(const std::string& var) const = 0;
    virtual ~Expression() = default;
};

// Variable class
class Variable : public Expression {
    std::string name;

public:
    Variable(const std::string& name) : name(name) {}

    std::string toString() const override {
        return name;
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        if (name == var)
            return std::make_unique<Constant>(1);
        else
            return std::make_unique<Constant>(0);
    }
};

// Constant class
class Constant : public Expression {
    double value;

public:
    Constant(double value) : value(value) {}

    std::string toString() const override {
        return std::to_string(value);
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Constant>(0);
    }
};

// Sum class
class Sum : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Sum(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " + " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Sum>(left->differentiate(var), right->differentiate(var));
    }
};

// Product class
class Product : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Product(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " * " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        // Product rule: (f * g)' = f' * g + f * g'
        return std::make_unique<Sum>(
            std::make_unique<Product>(left->differentiate(var), right->clone()),
            std::make_unique<Product>(left->clone(), right->differentiate(var))
        );
    }

    std::unique_ptr<Expression> clone() const {
        return std::make_unique<Product>(left->clone(), right->clone());
    }
};

// General function to perform symbolic computation
void calc(const std::string& expr, const std::string& var) {
    // Example: Parse the expression manually (as a simple example)
    std::unique_ptr<Expression> x = std::make_unique<Variable>(var);
    std::unique_ptr<Expression> expr1 = std::make_unique<Product>(
        std::make_unique<Constant>(3),
        x->clone()
    );  // 3*x

    std::unique_ptr<Expression> expr2 = std::make_unique<Sum>(
        std::make_unique<Constant>(2),
        expr1->clone()
    );  // 2 + 3*x

    std::cout << "Expression: " << expr2->toString() << std::endl;

    auto derivative = expr2->differentiate(var);
    std::cout << "Derivative wrt " << var << ": " << derivative->toString() << std::endl;
}

// Example usage function
int main() {
    calc("2 + 3*x", "x");
    return 0;
}

            //       Symbolic Differentiation and Integration: Perform calculus operations symbolically.

// Base class for symbolic expressions
class Expression {
public:
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Expression> differentiate(const std::string& var) const = 0;
    virtual std::unique_ptr<Expression> integrate(const std::string& var) const = 0;
    virtual ~Expression() = default;
};

// Variable class
class Variable : public Expression {
    std::string name;

public:
    Variable(const std::string& name) : name(name) {}

    std::string toString() const override {
        return name;
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        if (name == var)
            return std::make_unique<Constant>(1);
        else
            return std::make_unique<Constant>(0);
    }

    std::unique_ptr<Expression> integrate(const std::string& var) const override {
        if (name == var)
            return std::make_unique<Power>(std::make_unique<Variable>(name), 2.0, 0.5); // ∫x dx = x^2 / 2
        else
            return std::make_unique<Product>(std::make_unique<Variable>(name), std::make_unique<Variable>(var)); // ∫a dx = ax
    }
};

// Constant class
class Constant : public Expression {
    double value;

public:
    Constant(double value) : value(value) {}

    std::string toString() const override {
        return std::to_string(value);
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Constant>(0);
    }

    std::unique_ptr<Expression> integrate(const std::string& var) const override {
        return std::make_unique<Product>(std::make_unique<Constant>(value), std::make_unique<Variable>(var)); // ∫c dx = cx
    }
};

// Sum class
class Sum : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Sum(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " + " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Sum>(left->differentiate(var), right->differentiate(var));
    }

    std::unique_ptr<Expression> integrate(const std::string& var) const override {
        return std::make_unique<Sum>(left->integrate(var), right->integrate(var));
    }
};

// Product class
class Product : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Product(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " * " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        // Product rule: (f * g)' = f' * g + f * g'
        return std::make_unique<Sum>(
            std::make_unique<Product>(left->differentiate(var), right->clone()),
            std::make_unique<Product>(left->clone(), right->differentiate(var))
        );
    }

    std::unique_ptr<Expression> integrate(const std::string& var) const override {
        // Basic symbolic integration is not handled in this example for products
        throw std::runtime_error("Integration of products is not implemented in this basic example.");
    }

    std::unique_ptr<Expression> clone() const {
        return std::make_unique<Product>(left->clone(), right->clone());
    }
};

// Power class
class Power : public Expression {
    std::unique_ptr<Expression> base;
    double exponent;

public:
    Power(std::unique_ptr<Expression> base, double exponent) : base(std::move(base)), exponent(exponent) {}

    std::string toString() const override {
        return "(" + base->toString() + "^" + std::to_string(exponent) + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        if (exponent == 0) {
            return std::make_unique<Constant>(0);
        } else if (exponent == 1) {
            return base->differentiate(var);
        } else {
            // Power rule: (x^n)' = n * x^(n-1)
            return std::make_unique<Product>(
                std::make_unique<Constant>(exponent),
                std::make_unique<Power>(base->clone(), exponent - 1)
            );
        }
    }

    std::unique_ptr<Expression> integrate(const std::string& var) const override {
        if (exponent == -1) {
            throw std::runtime_error("Integration of x^-1 is not implemented. Consider natural logarithm.");
        } else {
            // ∫x^n dx = (x^(n+1))/(n+1) for n != -1
            return std::make_unique<Power>(base->clone(), exponent + 1);
        }
    }

    std::unique_ptr<Expression> clone() const {
        return std::make_unique<Power>(base->clone(), exponent);
    }
};

// General function to perform symbolic differentiation and integration
void calc(const std::string& expr, const std::string& var) {
    // Example: Parse the expression manually (as a simple example)
    std::unique_ptr<Expression> x = std::make_unique<Variable>(var);
    std::unique_ptr<Expression> expr1 = std::make_unique<Power>(x->clone(), 3.0);  // x^3

    std::cout << "Expression: " << expr1->toString() << std::endl;

    auto derivative = expr1->differentiate(var);
    std::cout << "Derivative wrt " << var << ": " << derivative->toString() << std::endl;

    try {
        auto integral = expr1->integrate(var);
        std::cout << "Indefinite Integral wrt " << var << ": " << integral->toString() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Integration Error: " << e.what() << std::endl;
    }
}

// Example usage function
int main() {
    calc("x^3", "x");
    return 0;
}

    //  Simplification of Algebraic Expressions: Simplify or expand algebraic expressions.

// Base class for symbolic expressions
class Expression {
public:
    virtual std::string toString() const = 0;
    virtual std::unique_ptr<Expression> differentiate(const std::string& var) const = 0;
    virtual std::unique_ptr<Expression> simplify() const = 0;
    virtual ~Expression() = default;
};

// Variable class
class Variable : public Expression {
    std::string name;

public:
    Variable(const std::string& name) : name(name) {}

    std::string toString() const override {
        return name;
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        if (name == var)
            return std::make_unique<Constant>(1);
        else
            return std::make_unique<Constant>(0);
    }

    std::unique_ptr<Expression> simplify() const override {
        return std::make_unique<Variable>(name);
    }
};

// Constant class
class Constant : public Expression {
    double value;

public:
    Constant(double value) : value(value) {}

    std::string toString() const override {
        return std::to_string(value);
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Constant>(0);
    }

    std::unique_ptr<Expression> simplify() const override {
        return std::make_unique<Constant>(value);
    }

    double getValue() const {
        return value;
    }
};

// Sum class
class Sum : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Sum(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " + " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        return std::make_unique<Sum>(left->differentiate(var), right->differentiate(var));
    }

    std::unique_ptr<Expression> simplify() const override {
        auto leftSimplified = left->simplify();
        auto rightSimplified = right->simplify();

        // If both sides are constants, add them
        Constant* leftConst = dynamic_cast<Constant*>(leftSimplified.get());
        Constant* rightConst = dynamic_cast<Constant*>(rightSimplified.get());

        if (leftConst && rightConst) {
            return std::make_unique<Constant>(leftConst->getValue() + rightConst->getValue());
        }

        // Simplify further if either side is 0
        if (leftConst && leftConst->getValue() == 0) {
            return rightSimplified;
        }

        if (rightConst && rightConst->getValue() == 0) {
            return leftSimplified;
        }

        // If no simplification is possible, return the sum of the simplified expressions
        return std::make_unique<Sum>(std::move(leftSimplified), std::move(rightSimplified));
    }
};

// Product class
class Product : public Expression {
    std::unique_ptr<Expression> left, right;

public:
    Product(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right)
        : left(std::move(left)), right(std::move(right)) {}

    std::string toString() const override {
        return "(" + left->toString() + " * " + right->toString() + ")";
    }

    std::unique_ptr<Expression> differentiate(const std::string& var) const override {
        // Product rule: (f * g)' = f' * g + f * g'
        return std::make_unique<Sum>(
            std::make_unique<Product>(left->differentiate(var), right->clone()),
            std::make_unique<Product>(left->clone(), right->differentiate(var))
        );
    }

    std::unique_ptr<Expression> simplify() const override {
        auto leftSimplified = left->simplify();
        auto rightSimplified = right->simplify();

        // If both sides are constants, multiply them
        Constant* leftConst = dynamic_cast<Constant*>(leftSimplified.get());
        Constant* rightConst = dynamic_cast<Constant*>(rightSimplified.get());

        if (leftConst && rightConst) {
            return std::make_unique<Constant>(leftConst->getValue() * rightConst->getValue());
        }

        // Simplify further if either side is 1 or 0
        if (leftConst) {
            if (leftConst->getValue() == 0) {
                return std::make_unique<Constant>(0);
            } else if (leftConst->getValue() == 1) {
                return rightSimplified;
            }
        }

        if (rightConst) {
            if (rightConst->getValue() == 0) {
                return std::make_unique<Constant>(0);
            } else if (rightConst->getValue() == 1) {
                return leftSimplified;
            }
        }

        // If no simplification is possible, return the product of the simplified expressions
        return std::make_unique<Product>(std::move(leftSimplified), std::move(rightSimplified));
    }

    std::unique_ptr<Expression> clone() const {
        return std::make_unique<Product>(left->clone(), right->clone());
    }
};

// General function to perform symbolic simplification
void calc(const std::string& expr, const std::string& var) {
    // Example: Parse the expression manually (as a simple example)
    std::unique_ptr<Expression> x = std::make_unique<Variable>(var);
    std::unique_ptr<Expression> expr1 = std::make_unique<Product>(
        std::make_unique<Sum>(
            std::make_unique<Constant>(2),
            x->clone()
        ),
        std::make_unique<Sum>(
            x->clone(),
            std::make_unique<Constant>(3)
        )
    );  // (2 + x) * (x + 3)

    std::cout << "Expression: " << expr1->toString() << std::endl;

    auto simplifiedExpr = expr1->simplify();
    std::cout << "Simplified Expression: " << simplifiedExpr->toString() << std::endl;
}

// Example usage function
int main() {
    calc("(2 + x) * (x + 3)", "x");
    return 0;
}

    //   Complex Number Operations

// Function to compute the power of a complex number (z^n)
std::complex<double> complexExponentiation(const std::complex<double>& z, double n) {
    return std::pow(z, n);
}

// Function to compute the logarithm of a complex number (log(z))
std::complex<double> complexLogarithm(const std::complex<double>& z) {
    return std::log(z);
}

// Function to compute the sine of a complex number (sin(z))
std::complex<double> complexSine(const std::complex<double>& z) {
    return std::sin(z);
}

// Function to compute the cosine of a complex number (cos(z))
std::complex<double> complexCosine(const std::complex<double>& z) {
    return std::cos(z);
}

// General function to perform complex number operations
void calc(const std::vector<std::complex<double>>& in, std::vector<std::complex<double>>& out, int operationType, double param = 1.0) {
    out.clear();
    for (const auto& z : in) {
        switch (operationType) {
            case 1: { // Complex Exponentiation
                out.push_back(complexExponentiation(z, param));
                std::cout << "Exponentiation (z^" << param << "): " << out.back() << std::endl;
                break;
            }
            case 2: { // Complex Logarithm
                out.push_back(complexLogarithm(z));
                std::cout << "Logarithm (log(z)): " << out.back() << std::endl;
                break;
            }
            case 3: { // Complex Sine
                out.push_back(complexSine(z));
                std::cout << "Sine (sin(z)): " << out.back() << std::endl;
                break;
            }
            case 4: { // Complex Cosine
                out.push_back(complexCosine(z));
                std::cout << "Cosine (cos(z)): " << out.back() << std::endl;
                break;
            }
            default:
                std::cerr << "Invalid operation type!" << std::endl;
                break;
        }
    }
}

// Example usage function
int main() {
    std::vector<std::complex<double>> complexNumbers = {{1.0, 1.0}, {2.0, -3.0}, {-1.0, 2.0}};
    std::vector<std::complex<double>> results;

    // Complex exponentiation (raising each complex number to the power of 2)
    calc(complexNumbers, results, 1, 2.0);

    // Complex logarithm of each number
    calc(complexNumbers, results, 2);

    // Complex sine of each number
    calc(complexNumbers, results, 3);

    // Complex cosine of each number
    calc(complexNumbers, results, 4);

    return 0;
}

            //      Complex Exponentiation: Compute powers of complex numbers.

// Function to compute the power of a complex number (z^n)
std::complex<double> complexExponentiation(const std::complex<double>& z, const std::complex<double>& n) {
    return std::pow(z, n);
}

// General function to perform complex exponentiation
void calc(const std::vector<std::complex<double>>& in, std::vector<std::complex<double>>& out, const std::complex<double>& exponent) {
    out.clear();
    for (const auto& z : in) {
        std::complex<double> result = complexExponentiation(z, exponent);
        out.push_back(result);
        std::cout << "Exponentiation (" << z << "^" << exponent << "): " << result << std::endl;
    }
}

// Example usage function
int main() {
    // Define a vector of complex numbers
    std::vector<std::complex<double>> complexNumbers = {{1.0, 1.0}, {2.0, -3.0}, {-1.0, 2.0}};
    std::vector<std::complex<double>> results;

    // Define an exponent as a complex number
    std::complex<double> exponent(2.0, 1.0);

    // Compute the exponentiation of each complex number by the given exponent
    calc(complexNumbers, results, exponent);

    return 0;
}

            //      Complex Logarithm: Compute logarithms of complex numbers.

// Function to compute the logarithm of a complex number (log(z))
std::complex<double> complexLogarithm(const std::complex<double>& z) {
    return std::log(z);
}

// General function to perform complex logarithm calculations
void calc(const std::vector<std::complex<double>>& in, std::vector<std::complex<double>>& out) {
    out.clear();
    for (const auto& z : in) {
        std::complex<double> result = complexLogarithm(z);
        out.push_back(result);
        std::cout << "Logarithm (log(" << z << ")): " << result << std::endl;
    }
}

// Example usage function
int main() {
    // Define a vector of complex numbers
    std::vector<std::complex<double>> complexNumbers = {{1.0, 1.0}, {2.0, -3.0}, {-1.0, 2.0}};
    std::vector<std::complex<double>> results;

    // Compute the logarithm of each complex number
    calc(complexNumbers, results);

    return 0;
}

            //      Complex Trigonometric Functions: Functions like complex sine, cosine, etc.

// Function to compute the sine of a complex number (sin(z))
std::complex<double> complexSine(const std::complex<double>& z) {
    return std::sin(z);
}

// Function to compute the cosine of a complex number (cos(z))
std::complex<double> complexCosine(const std::complex<double>& z) {
    return std::cos(z);
}

// Function to compute the tangent of a complex number (tan(z))
std::complex<double> complexTangent(const std::complex<double>& z) {
    return std::tan(z);
}

// General function to perform complex trigonometric calculations
void calc(const std::vector<std::complex<double>>& in, std::vector<std::complex<double>>& out, int operationType) {
    out.clear();
    for (const auto& z : in) {
        std::complex<double> result;
        switch (operationType) {
            case 1: // Complex Sine
                result = complexSine(z);
                out.push_back(result);
                std::cout << "Sine (sin(" << z << ")): " << result << std::endl;
                break;
            case 2: // Complex Cosine
                result = complexCosine(z);
                out.push_back(result);
                std::cout << "Cosine (cos(" << z << ")): " << result << std::endl;
                break;
            case 3: // Complex Tangent
                result = complexTangent(z);
                out.push_back(result);
                std::cout << "Tangent (tan(" << z << ")): " << result << std::endl;
                break;
            default:
                std::cerr << "Invalid operation type!" << std::endl;
                break;
        }
    }
}

// Example usage function
int main() {
    // Define a vector of complex numbers
    std::vector<std::complex<double>> complexNumbers = {{1.0, 1.0}, {2.0, -3.0}, {-1.0, 2.0}};
    std::vector<std::complex<double>> results;

    // Compute the sine of each complex number
    calc(complexNumbers, results, 1);

    // Compute the cosine of each complex number
    calc(complexNumbers, results, 2);

    // Compute the tangent of each complex number
    calc(complexNumbers, results, 3);

    return 0;
}

    //  Cryptographic Functions


// Function to perform modular exponentiation (base^exp % mod)
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {  // If exp is odd, multiply base with the result
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // exp = exp / 2
        base = (base * base) % mod;  // Change base to base^2
    }
    return result;
}

// Function to check if a number is prime using the Miller-Rabin primality test
bool isPrime(long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    auto millerTest = [n](long long d, long long a) {
        long long x = modularExponentiation(a, d, n);
        if (x == 1 || x == n - 1)
            return true;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            if (x == 1) return false;
            if (x == n - 1) return true;
        }
        return false;
    };

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        if (!millerTest(d, a))
            return false;
    }
    return true;
}

// Function to generate a random prime number in a given range
long long generateRandomPrime(long long lower, long long upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(lower, upper);

    long long prime;
    do {
        prime = dis(gen);
    } while (!isPrime(prime));
    return prime;
}

// General function to perform cryptographic calculations
void calc(long long base, long long exp, long long mod) {
    // Perform modular exponentiation
    long long modExpResult = modularExponentiation(base, exp, mod);
    std::cout << "Modular Exponentiation (" << base << "^" << exp << " % " << mod << "): " << modExpResult << std::endl;

    // Check if a number is prime
    long long numberToCheck = 97;  // Example number
    bool primeCheck = isPrime(numberToCheck);
    std::cout << "Is " << numberToCheck << " a prime number? " << (primeCheck ? "Yes" : "No") << std::endl;

    // Generate a random prime number in a range
    long long randomPrime = generateRandomPrime(100, 200);
    std::cout << "Generated random prime: " << randomPrime << std::endl;
}

// Example usage function
int main() {
    long long base = 2, exp = 10, mod = 1000;
    calc(base, exp, mod);
    return 0;
}

            //      Modular Exponentiation: Compute large powers modulo a number, useful in cryptography.

// Function to perform modular exponentiation (base^exp % mod)
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;  // Update base if it is more than or equal to mod

    while (exp > 0) {
        // If exp is odd, multiply base with result
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }

        // Now exp must be even, so we divide it by 2
        exp = exp >> 1;  // exp = exp / 2
        base = (base * base) % mod;  // Change base to base^2
    }

    return result;
}

// General function to perform modular exponentiation
void calc(long long base, long long exp, long long mod, long long& result) {
    // Perform modular exponentiation
    result = modularExponentiation(base, exp, mod);
    std::cout << "Modular Exponentiation (" << base << "^" << exp << " % " << mod << "): " << result << std::endl;
}

// Example usage function
int main() {
    long long base = 2;
    long long exp = 10;
    long long mod = 1000;
    long long result;

    // Compute modular exponentiation
    calc(base, exp, mod, result);

    return 0;
}

            //      Prime Testing and Generation: Functions for checking primality or generating primes.

// Function to perform modular exponentiation (base^exp % mod)
long long modularExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Miller-Rabin primality test function
bool isPrime(long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    long long d = n - 1;
    while (d % 2 == 0)
        d /= 2;

    auto millerTest = [n](long long d, long long a) {
        long long x = modularExponentiation(a, d, n);
        if (x == 1 || x == n - 1)
            return true;
        while (d != n - 1) {
            x = (x * x) % n;
            d *= 2;
            if (x == 1) return false;
            if (x == n - 1) return true;
        }
        return false;
    };

    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (n - 4);
        if (!millerTest(d, a))
            return false;
    }
    return true;
}

// Function to generate a random prime number in a given range
long long generateRandomPrime(long long lower, long long upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(lower, upper);

    long long prime;
    do {
        prime = dis(gen);
    } while (!isPrime(prime));
    return prime;
}

// General function to perform prime testing and generation
void calc(long long number, long long lower, long long upper) {
    // Prime testing
    bool primeCheck = isPrime(number);
    std::cout << "Is " << number << " a prime number? " << (primeCheck ? "Yes" : "No") << std::endl;

    // Prime generation
    long long randomPrime = generateRandomPrime(lower, upper);
    std::cout << "Generated random prime between " << lower << " and " << upper << ": " << randomPrime << std::endl;
}

// Example usage function
int main() {
    long long number = 97;  // Example number to check for primality
    long long lower = 100;  // Lower bound for prime generation
    long long upper = 200;  // Upper bound for prime generation

    // Perform prime testing and generation
    calc(number, lower, upper);

    return 0;
}

    //      Discrete Mathematics Functions

// Function to compute factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to compute permutations (nPr)
unsigned long long permutations(int n, int r) {
    if (n < r) return 0;
    return factorial(n) / factorial(n - r);
}

// Function to compute combinations (nCr)
unsigned long long combinations(int n, int r) {
    if (n < r) return 0;
    return factorial(n) / (factorial(r) * factorial(n - r));
}

// Simple graph coloring using a greedy algorithm
std::vector<int> greedyGraphColoring(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> result(n, -1);  // Store color of each vertex
    std::vector<bool> availableColors(n, false);  // Track available colors

    // Assign the first color to the first vertex
    result[0] = 0;

    // Assign colors to the rest of the vertices
    for (int u = 1; u < n; u++) {
        // Mark colors of adjacent vertices as unavailable
        for (int i : graph[u]) {
            if (result[i] != -1) {
                availableColors[result[i]] = true;
            }
        }

        // Find the first available color
        int color;
        for (color = 0; color < n; color++) {
            if (!availableColors[color]) {
                break;
            }
        }

        result[u] = color;  // Assign the found color

        // Reset the available colors for the next iteration
        for (int i : graph[u]) {
            if (result[i] != -1) {
                availableColors[result[i]] = false;
            }
        }
    }

    return result;
}

// General function to perform discrete mathematics functions
void calc(int n, int r, const std::vector<std::vector<int>>& graph) {
    // Compute permutations (nPr)
    unsigned long long perm = permutations(n, r);
    std::cout << "Permutations (" << n << "P" << r << "): " << perm << std::endl;

    // Compute combinations (nCr)
    unsigned long long comb = combinations(n, r);
    std::cout << "Combinations (" << n << "C" << r << "): " << comb << std::endl;

    // Perform graph coloring
    auto coloringResult = greedyGraphColoring(graph);
    std::cout << "Graph Coloring (vertex colors): ";
    for (int color : coloringResult) {
        std::cout << color << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    int n = 5;  // Example number of items
    int r = 3;  // Example number of selections

    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},     // Vertex 0 is connected to vertices 1 and 2
        {0, 2, 3},  // Vertex 1 is connected to vertices 0, 2, and 3
        {0, 1, 3},  // Vertex 2 is connected to vertices 0, 1, and 3
        {1, 2, 4},  // Vertex 3 is connected to vertices 1, 2, and 4
        {3}         // Vertex 4 is connected to vertex 3
    };

    // Perform discrete mathematics functions
    calc(n, r, graph);

    return 0;
}

            //  Combinatorial Functions:

// Function to compute factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to compute permutations (nPr)
unsigned long long permutations(int n, int r) {
    if (n < r) return 0;  // If r > n, permutations are not possible
    return factorial(n) / factorial(n - r);
}

// Function to compute combinations (nCr)
unsigned long long combinations(int n, int r) {
    if (n < r) return 0;  // If r > n, combinations are not possible
    return factorial(n) / (factorial(r) * factorial(n - r));
}

// Function to compute binomial coefficients (nCr) using Pascal's Triangle method
unsigned long long binomialCoefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    std::vector<unsigned long long> C(k + 1, 0);
    C[0] = 1;  // nC0 is always 1

    for (int i = 1; i <= n; i++) {
        for (int j = std::min(i, k); j > 0; j--) {
            C[j] = C[j] + C[j - 1];
        }
    }

    return C[k];
}

// General function to perform combinatorial calculations
void calc(int n, int r) {
    // Compute permutations (nPr)
    unsigned long long perm = permutations(n, r);
    std::cout << "Permutations (" << n << "P" << r << "): " << perm << std::endl;

    // Compute combinations (nCr)
    unsigned long long comb = combinations(n, r);
    std::cout << "Combinations (" << n << "C" << r << "): " << comb << std::endl;

    // Compute binomial coefficients (nCr) using Pascal's Triangle method
    unsigned long long binomCoeff = binomialCoefficient(n, r);
    std::cout << "Binomial Coefficient (" << n << "C" << r << ") using Pascal's Triangle: " << binomCoeff << std::endl;
}

// Example usage function
int main() {
    int n = 5;  // Example number of items
    int r = 3;  // Example number of selections

    // Perform combinatorial calculations
    calc(n, r);

    return 0;
}

            //      Combinatorial Functions: Calculate permutations, combinations, and binomial coefficients.

// Function to compute factorial of a number
unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to compute permutations (nPr)
unsigned long long permutations(int n, int r) {
    if (n < r) return 0;  // If r > n, permutations are not possible
    return factorial(n) / factorial(n - r);
}

// Function to compute combinations (nCr)
unsigned long long combinations(int n, int r) {
    if (n < r) return 0;  // If r > n, combinations are not possible
    return factorial(n) / (factorial(r) * factorial(n - r));
}

// Function to compute binomial coefficients (nCr) using Pascal's Triangle method
unsigned long long binomialCoefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    std::vector<unsigned long long> C(k + 1, 0);
    C[0] = 1;  // nC0 is always 1

    for (int i = 1; i <= n; i++) {
        for (int j = std::min(i, k); j > 0; j--) {
            C[j] = C[j] + C[j - 1];
        }
    }

    return C[k];
}

// General function to perform combinatorial calculations
void calc(int n, int r, std::vector<unsigned long long>& results) {
    results.clear();

    // Compute permutations (nPr)
    unsigned long long perm = permutations(n, r);
    results.push_back(perm);
    std::cout << "Permutations (" << n << "P" << r << "): " << perm << std::endl;

    // Compute combinations (nCr)
    unsigned long long comb = combinations(n, r);
    results.push_back(comb);
    std::cout << "Combinations (" << n << "C" << r << "): " << comb << std::endl;

    // Compute binomial coefficients (nCr) using Pascal's Triangle method
    unsigned long long binomCoeff = binomialCoefficient(n, r);
    results.push_back(binomCoeff);
    std::cout << "Binomial Coefficient (" << n << "C" << r << ") using Pascal's Triangle: " << binomCoeff << std::endl;
}

// Example usage function
int main() {
    int n = 5;  // Example number of items
    int r = 3;  // Example number of selections
    std::vector<unsigned long long> results;

    // Perform combinatorial calculations
    calc(n, r, results);

    return 0;
}

                //      Graph Coloring: Functions for coloring graphs with minimal colors

// Function to perform greedy graph coloring
std::vector<int> greedyGraphColoring(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();  // Number of vertices
    std::vector<int> result(n, -1);  // Store color of each vertex
    std::vector<bool> availableColors(n, false);  // Track available colors for vertices

    // Assign the first color to the first vertex
    result[0] = 0;

    // Assign colors to the remaining vertices
    for (int u = 1; u < n; u++) {
        // Mark colors of adjacent vertices as unavailable
        for (int i : graph[u]) {
            if (result[i] != -1) {
                availableColors[result[i]] = true;
            }
        }

        // Find the first available color
        int color;
        for (color = 0; color < n; color++) {
            if (!availableColors[color]) {
                break;
            }
        }

        result[u] = color;  // Assign the found color

        // Reset the available colors for the next iteration
        for (int i : graph[u]) {
            if (result[i] != -1) {
                availableColors[result[i]] = false;
            }
        }
    }

    return result;
}

// General function to perform graph coloring
void calc(const std::vector<std::vector<int>>& graph, std::vector<int>& coloringResult) {
    // Perform graph coloring
    coloringResult = greedyGraphColoring(graph);
    std::cout << "Graph Coloring (vertex colors): ";
    for (int color : coloringResult) {
        std::cout << color << " ";
    }
    std::cout << std::endl;
}

// Example usage function
int main() {
    // Example graph represented as an adjacency list
    std::vector<std::vector<int>> graph = {
        {1, 2},     // Vertex 0 is connected to vertices 1 and 2
        {0, 2, 3},  // Vertex 1 is connected to vertices 0, 2, and 3
        {0, 1, 3},  // Vertex 2 is connected to vertices 0, 1, and 3
        {1, 2, 4},  // Vertex 3 is connected to vertices 1, 2, and 4
        {3}         // Vertex 4 is connected to vertex 3
    };

    std::vector<int> coloringResult;

    // Perform graph coloring
    calc(graph, coloringResult);

    return 0;
}

// Function to approximate the derivative of a function at a given point using central difference
double numericalDifferentiation(const std::vector<double>& x, const std::vector<double>& y, double point) {
    size_t n = x.size();
    double derivative = 0.0;
    
    // Find closest index to the given point
    size_t index = 0;
    for (size_t i = 1; i < n; i++) {
        if (std::abs(x[i] - point) < std::abs(x[index] - point)) {
            index = i;
        }
    }

    // Use central difference for the internal points
    if (index > 0 && index < n - 1) {
        derivative = (y[index + 1] - y[index - 1]) / (x[index + 1] - x[index - 1]);
    }
    // Use forward difference for the first point
    else if (index == 0) {
        derivative = (y[1] - y[0]) / (x[1] - x[0]);
    }
    // Use backward difference for the last point
    else if (index == n - 1) {
        derivative = (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]);
    }

    return derivative;
}

// Function to approximate the integral of a function over an interval using the trapezoidal rule
double numericalIntegration(const std::vector<double>& x, const std::vector<double>& y) {
    size_t n = x.size();
    double integral = 0.0;

    for (size_t i = 0; i < n - 1; i++) {
        double dx = x[i + 1] - x[i];
        double avg_y = (y[i + 1] + y[i]) / 2.0;
        integral += dx * avg_y;
    }

    return integral;
}

// Dijkstra's Algorithm to find the shortest path from a source vertex
std::vector<double> dijkstra(const std::vector<std::vector<std::pair<int, double>>>& graph, int source) {
    int n = graph.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    dist[source] = 0.0;

    // Min-heap priority queue
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0.0, source});

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (const auto& [v, weight] : graph[u]) {
            double distance = currentDist + weight;
            if (distance < dist[v]) {
                dist[v] = distance;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// General function to perform various calculations
void calc(const std::vector<double>& in, std::vector<std::complex<double>>& out) {
    // Example data for differentiation and integration
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y = {1, 2, 0, 2, 1}; // Example function values

    // Perform numerical differentiation at point x = 2
    double point = 2.0;
    double derivative = numericalDifferentiation(x, y, point);
    std::cout << "Numerical Differentiation at x = " << point << ": " << derivative << std::endl;

    // Perform numerical integration over the interval
    double integral = numericalIntegration(x, y);
    std::cout << "Numerical Integration over the interval: " << integral << std::endl;

    // Example graph for Dijkstra's algorithm
    std::vector<std::vector<std::pair<int, double>>> graph = {
        {{1, 1.0}, {2, 4.0}},  // Edges from vertex 0 to 1 (weight 1.0) and to 2 (weight 4.0)
        {{2, 2.0}, {3, 5.0}},  // Edges from vertex 1 to 2 (weight 2.0) and to 3 (weight 5.0)
        {{3, 1.0}},            // Edge from vertex 2 to 3 (weight 1.0)
        {}                     // No edges from vertex 3
    };

    // Perform Dijkstra's algorithm from source vertex 0
    std::vector<double> shortestPaths = dijkstra(graph, 0);
    std::cout << "Shortest paths from vertex 0:" << std::endl;
    for (size_t i = 0; i < shortestPaths.size(); ++i) {
        std::cout << "Vertex " << i << ": " << shortestPaths[i] << std::endl;
    }
}

// Example usage function
int main() {
    std::vector<double> inputData;  // Placeholder for any input data if needed
    std::vector<std::complex<double>> outputData;

    // Perform various calculations
    calc(inputData, outputData);

    return 0;
}

// Main function to demonstrate module usage

int main() {
}
    // Example usage of matrix operations
    Eigen::MatrixXd A(2, 2);
    A << 1, 2, 3, 4;

    Eigen::MatrixXd B = AdvancedMath::matrixTranspose(A);
    std::cout << "Matrix B (Transpose of A):\n" << B << std::endl;

    Eigen::MatrixXd C = AdvancedMath::matrixMultiply(A, B);
    std::cout << "Matrix C (A * B):\n" << C << std::endl;

    Eigen::MatrixXd D = AdvancedMath::matrixInverse(A);
    std::cout << "Matrix D (Inverse of A):\n" << D << std::endl;

    return 0;
}

//    Make sure to link the Eigen and FFTW libraries when compiling.
//    For example, with g++, you might use:
//    ```g++ main.cpp -o math_module -I /path/to/eigen -lfftw3```
