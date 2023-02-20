#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;



unordered_map<int, vector<int>> dept_prefs = {
    {1, {1, 5, 3, 2, 4}},
    {2, {1, 3, 4, 2, 5}},
    {3, {3, 4, 2, 5, 1}},
    {4, {3, 1, 2, 4, 5}},
    {5, {4, 3, 1, 2, 5}}
};

unordered_map<int, vector<int>> prog_prefs = {
    {1, {3, 1, 2, 5, 4}},
    {2, {4, 3, 1, 5, 2}},
    {3, {2, 5, 4, 1, 3}},
    {4, {4, 5, 2, 1, 3}},
    {5, {3, 2, 1, 5, 1}}
};


unordered_map<int, int> dept_match;
unordered_map<int, int> prog_match;

bool is_free(int prog) {
    return prog_match[prog] == 0;
}

int get_highest_pref(int dept) {
    int highest_pref = -1;
    for (int i = 0; i < dept_prefs[dept].size(); i++) {
        int prog = dept_prefs[dept][i];
        if (is_free(prog) && prog_prefs[prog][0] == dept) {
            highest_pref = prog;
            break;
        }
    }
    return highest_pref;
}



bool prefers_dept(int prog, int dept1, int dept2) {
    for (int i = 0; i < prog_prefs[prog].size(); i++) {
        int dept = prog_prefs[prog][i];
        if (dept == dept1) {
            return true;
        } else if (dept == dept2) {
            return false;
        }
    }
    return false;
}

void match(int dept, int prog) {
    dept_match[dept] = prog;
    prog_match[prog] = dept;
}

void gale_shapley() {
    while (dept_match.size() < dept_prefs.size()) {
        for (auto& it : dept_prefs) {
            int dept = it.first;
            if (dept_match[dept] == 0) {
                int prog = get_highest_pref(dept);
                if (prog != -1) {
                    match(dept, prog);
                } else {
                    for (int i = 0; i < dept_prefs[dept].size(); i++) {
                        int p = dept_prefs[dept][i];
                        int current_dept = prog_match[p];
                        if (prefers_dept(p, dept, current_dept)) {
                            dept_match[current_dept] = 0;
                            match(dept, p);
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    gale_shapley();

    for (auto& it : dept_match) {
    if (it.first != 0 && it.second != 0) {
        cout << "Department #" << it.first << " will get Programmer #" << it.second << endl;
    }
}

    return 0;
}
