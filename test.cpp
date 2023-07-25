#include <iostream>
#include <vector>
#include <unordered_map>


using namespace std;

unordered_map<string, bool> memo;

bool canCrossChakravyuhUtil(const vector<int>& enemies, int currentCircle, int power, int a, int b) {
    // Base case: If Abhimanyu is outside the Chakravyuha
    if (currentCircle < 0 || currentCircle >= enemies.size())
        return true;

    // Generate a unique key for the current state
    string key = to_string(currentCircle) + "_" + to_string(power) + "_" + to_string(a);

    // Check if the result for this state is already memoized
    if (memo.find(key) != memo.end())
        return memo[key];

    // Check if Abhimanyu has enough power to fight the enemy in the current circle
    if (power < enemies[currentCircle])
        return false;

    // Try fighting the enemy in the current circle
    if (canCrossChakravyuhUtil(enemies, currentCircle + 1, power - enemies[currentCircle], a, b)) {
        memo[key] = true;
        return true;
    }

    // Check if Abhimanyu can use a boon to skip fighting this enemy
    if (a > 0 && canCrossChakravyuhUtil(enemies, currentCircle + 2, power, a - 1, b)) {
        memo[key] = true;
        return true;
    }

    // Check if Abhimanyu can recharge himself with power
    if (b > 0 && canCrossChakravyuhUtil(enemies, currentCircle, power + b, a, b - 1)) {
        memo[key] = true;
        return true;
    }

    // Check if the current enemy is k3 or k7 and Abhimanyu is at the last circle
    if ((currentCircle == 2 || currentCircle == 6) && power >= (enemies[currentCircle] / 2)) {
        // If he has enough power, consider fighting the enemy while preserving half of their initial power
        if (canCrossChakravyuhUtil(enemies, currentCircle + 1, power - (enemies[currentCircle] / 2), a, b)) {
            memo[key] = true;
            return true;
        }
    }

    memo[key] = false;
    return false;
}

bool canCrossChakravyuh(const vector<int>& enemies, int p, int a, int b) {
    memo.clear(); // Clear the memoization table for each test case
    return canCrossChakravyuhUtil(enemies, 0, p, a, b);
}

int main() {
    vector<int> enemies = {10, 20, 30, 40, 50, 60};
    int p = 210, a = 0, b = 0;
    cout << "Can Cross Chakravyuh: " << (canCrossChakravyuh(enemies, p, a, b) ? "Yes" : "No") << endl;

    return 0;
}
