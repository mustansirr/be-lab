#include <iostream>
#include <iomanip>
using namespace std;

struct Item {
    int id;        // item number (1-based)
    double p, w;   // profit and weight
    double ratio;  // p / w
};

int main() {
    int n;
    double W;
    cin >> n >> W;                 // number of items, capacity

    vector<Item> a(n);
    for(int i = 0; i < n; i++) {
        double p, w;
        cin >> p >> w;
        a[i] = { i+1, p, w, p/w }; // store item with ratio
    }

    // Sort items by ratio (profit/weight) decreasing
    sort(a.begin(), a.end(), [](auto &x, auto &y){
        return x.ratio > y.ratio;
    });

    vector<double> frac(n, 0.0); // fractions of items taken
    double maxProfit = 0, cap = W;

    for(auto &it : a) {
        if(cap <= 0) break;
        double take = min(cap, it.w);
        double f = take / it.w;
        frac[it.id - 1] = f;
        maxProfit += f * it.p;
        cap -= take;
    }

    cout << fixed << setprecision(2);
    cout << "Fractions: ";
    for(double f : frac) cout << f << " ";
    cout << "\nMax profit: " << maxProfit << "\n";
    return 0;
}