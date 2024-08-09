#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


void choose3(vector<bool>& used, vector<int>& square, vector<int>& numbers, int s) {
    if (size(square) == 12) {
        return;
    }
    int sTem = s;
    for (int n_1 = 0; n_1 < 16; n_1++) {
        if (used[n_1]) {
            continue;
        }
        if (sTem - numbers[n_1] < 0) {
            continue;
        }
        used[n_1] = true;
        square.push_back(numbers[n_1]);
        sTem -= numbers[n_1];
        for (int n_2 = 0; n_2 < 16; n_2++) {
            if (used[n_2]) {
                continue;
            }
            if (sTem - numbers[n_2] < 0) {
                continue;
            }
            used[n_2] = true;
            square.push_back(numbers[n_2]);
            sTem -= numbers[n_2];
            for (int n_3 = 0; n_3 < 16; n_3++) {
                if (used[n_3]) {
                    continue;
                }
                if (sTem - numbers[n_3] < 0) {
                    continue;
                }
                used[n_3] = true;
                square.push_back(numbers[n_3]);
                sTem -= numbers[n_3];
                for (int i = 0; i < 16; i++) {
                    if (used[i]) {
                        continue;
                    } else {
                        if (numbers[i] == sTem) {
                            square.push_back(numbers[i]);
                            used[i] = true;
                            choose3(used, square, numbers, s);
                            if (size(square) == 12) {
                                auto CheckNum = [&used, &square, &numbers](int value, int k) {
                                    int a = 0;
                                    for (a = 0; a < 16; a++) {
                                        if (used[a]) {
                                            continue;
                                        }
                                        if (value == numbers[a]) {
                                            used[a] = true;
                                            square.push_back(numbers[a]);
                                            break;;
                                        }
                                    }
                                    if (a == 16) {
                                        square.pop_back();
                                        used[k] = false;
                                        return -1;
                                    } else {
                                        return a;
                                    }
                                };
                                int n_13, n_14, n_15, n_16;
                                n_13 = CheckNum(s - square[0] - square[4] - square[8], i);
                                if (n_13 == -1) {
                                    break;
                                }
                                n_14 = CheckNum(s - square[1] - square[5] - square[9], i);
                                if (n_14 == -1) {
                                    used[n_13] = false;
                                    square.pop_back();
                                    break;
                                }
                                n_15 = CheckNum(s - square[2] - square[6] - square[10], i);
                                if (n_15 == -1) {
                                    used[n_13] = false;
                                    square.pop_back();
                                    used[n_14] = false;
                                    square.pop_back();
                                    break;
                                }
                                n_16 = CheckNum(s - square[3] - square[7] - square[11], i);
                                if (n_16 == -1) {
                                    used[n_13] = false;
                                    square.pop_back();
                                    used[n_14] = false;
                                    square.pop_back();
                                    used[n_15] = false;
                                    square.pop_back();
                                    break;
                                }
                            }
                            if (size(square) == 16) {
                                return;
                            }
                            square.pop_back();
                            used[i] = false;
                            break;
                        }
                    }
                }
                used[n_3] = false;
                square.pop_back();
                sTem += numbers[n_3];
            }
            used[n_2] = false;
            square.pop_back();
            sTem += numbers[n_2];
        }
        used[n_1] = false;
        square.pop_back();
        sTem += numbers[n_1];
    }
}

int main() {
    vector<int> numbers(16);
    for (int i = 0; i < 16; i++) {
        cin >> numbers[i];
    }
    vector<bool> used(16);
    vector<int> square(0);
    int s = 0;
    for (int i = 0; i < 16; i++) {
        s += numbers[i];
    }
    if (s % 4 != 0) {
        cout << "NO SOLUTION";
        return 0;
    }
    s = s / 4;
    choose3(used, square, numbers, s);
    if (size(square) != 16) {
        cout << "NO SOLUTION";
    } else {
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 4; i++) {
                cout << square[4*j + i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}