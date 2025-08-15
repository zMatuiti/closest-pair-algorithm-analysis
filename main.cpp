#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <chrono>
#include <random>

using namespace std;

double calculateDistance(const pair<double, double>& p1, const pair<double, double>& p2) {
    double dx = p1.first - p2.first;
    double dy = p1.second - p2.second;
    return sqrt(dx*dx + dy*dy);
}

double bruteForce(const vector<pair<double, double>>& points) {
    double minDist = numeric_limits<double>::max();
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            minDist = min(minDist, calculateDistance(points[i], points[j]));
        }
    }
    return minDist;
}

// Versión O(n²) de dividir y vencer
double closestPairDC_O2(vector<pair<double, double>> Px) {
    if (Px.size() <= 3) return bruteForce(Px);
    
    size_t mid = Px.size() / 2;
    double midX = Px[mid].first;
    
    vector<pair<double, double>> left(Px.begin(), Px.begin() + mid);
    vector<pair<double, double>> right(Px.begin() + mid, Px.end());
    
    double dLeft = closestPairDC_O2(left);
    double dRight = closestPairDC_O2(right);
    double delta = min(dLeft, dRight);
    
    vector<pair<double, double>> strip;
    for (const auto& p : Px) {
        if (abs(p.first - midX) < delta) strip.push_back(p);
    }
    
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size(); ++j) {
            delta = min(delta, calculateDistance(strip[i], strip[j]));
        }
    }
    
    return delta;
}

vector<pair<double, double>> generateRandomPoints(size_t n) {
    vector<pair<double, double>> points;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 100.0);
    
    for (size_t i = 0; i < n; ++i) {
        points.emplace_back(dis(gen), dis(gen));
    }
    return points;
}

int main() {
    vector<pair<double, double>> points = generateRandomPoints(100);
    
    vector<pair<double, double>> Px = points;
    sort(Px.begin(), Px.end());
    auto start = chrono::high_resolution_clock::now();
    double bf_dist = bruteForce(points);
    auto end = chrono::high_resolution_clock::now();
    auto bf_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    start = chrono::high_resolution_clock::now();
    double dc_dist = closestPairDC_O2(Px);
    end = chrono::high_resolution_clock::now();
    auto dc_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    
    cout << "Fuerza bruta:\n";
    cout << "  Distancia minima: " << bf_dist << "\n";
    cout << "  Tiempo ejecucion: " << bf_time << " microsegundos\n\n";
    
    cout << "Divide y vencer (O(n²)):\n";
    cout << "  Distancia minima: " << dc_dist << "\n";
    cout << "  Tiempo ejecucion: " << dc_time << " microsegundos\n";
    
    return 0;
}