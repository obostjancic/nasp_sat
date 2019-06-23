#include <iostream>
#include <fstream>
#include <ctime>
#include "Clause.h"
#include "Formula.h"
#include "Util.h"

using namespace std;

/**
 * Utility function. Makes a random solution. Used as starting point for heuristic algorithms.
 * @param solution - Initially vector containing all false elements. Changed by reference.
 */
void random_solution(vector<bool> &solution) {
    for (int i = 0; i < solution.size(); i++) {
        solution[i] = rand() % 2;
    }
}

/**
 * Utility benchmark function. Throws n random solutions and picks the best one.
 * @param formula - Formula object containing the SAt instance.
 */
void random_solver(Formula &formula) {
    srand(time(NULL));
    int n = formula.get_var_count();
    vector<bool> current_solution(n);
    random_solution(current_solution);
    vector<bool> best_solution = current_solution;
    //cout << formula.num_of_sat_clauses(best_solution) << endl;

    for (int i = 0; i < n; i++) {
        random_solution(current_solution);

        if (formula.num_of_sat_clauses(current_solution) > formula.num_of_sat_clauses(best_solution)) {
            //cout << "Found better solution: " << formula.num_of_sat_clauses(current_solution) << endl;
            best_solution = current_solution;
        }

    }

    cout << formula.num_of_sat_clauses(best_solution) << endl;
}

/**
 * Local search implemented for SAT problem.
 * Starts form a random given solution
 * @param formula - Formula object containing the SAT instance.
 */
void local_search(Formula &formula) {
    int n = formula.get_var_count();

    int MAX_ITER = n*n;
    srand(time(NULL));

    vector<bool> current_solution(n);
    random_solution(current_solution);
    vector<bool> best_solution = current_solution;
    bool found_better_in_pass = false;

    //cout << formula.num_of_sat_clauses(best_solution) << endl;
        for (int i = 0; i < n; i++) {

            if (i == 0)
                found_better_in_pass = false;

            current_solution = best_solution;
            current_solution[i] = !current_solution[i];

            if (formula.num_of_sat_clauses(current_solution) > formula.num_of_sat_clauses(best_solution)) {
                //cout << "Found better solution: " << formula.num_of_sat_clauses(current_solution) << endl;
                best_solution = current_solution;
                found_better_in_pass = true;
            }

            if (i == n - 1 && !found_better_in_pass)
                break;

        }

    cout << formula.num_of_sat_clauses(best_solution) << endl;
}

/**
 * Simulated annealing implemented for SAT problem.
 * Starts form a random given solution
 * Starts with a temperature equal to the number of variables.
 * Lowers temperature by 1/number of variables.
 * @param formula - Formula object containing the SAT instance.
 */
void simmulated_annealing(Formula &formula) {
    int n = formula.get_var_count();

    double T = n;
    double k = 1.0/n;
    double MIN_T = 0.00001;

    vector<bool> current_solution(n);
    random_solution(current_solution);
    vector<bool> best_solution = current_solution;
    //cout << "Initial solution " << formula.num_of_sat_clauses(best_solution) << endl;

    while(T > MIN_T) {
        int i = rand() % n;

        current_solution = best_solution;
        current_solution[i] = !current_solution[i];

        int difference = formula.num_of_sat_clauses(current_solution) - formula.num_of_sat_clauses(best_solution);

        if (difference > 0) {
            //cout << "Found better solution: " << formula.num_of_sat_clauses(current_solution) << endl;
            best_solution = current_solution;
            T *= (1-k);

        } else {
            if((double(rand()) / RAND_MAX) < 1 / (1 + exp(-difference/T))) {
                T *= (1-k);
            }
        }

    }
    cout << formula.num_of_sat_clauses(best_solution) << endl;
}

/**
 * Tabu search implemented for SAT problem.
 * Starts form a random given solution
 * Takes square root of the number of variables as Tabu value. Has maximum of number of variables iterations.
 * @param formula - Formula object containing the SAT instance.
 */
void tabu_search(Formula &formula) {
    int n = formula.get_var_count();

    int TABU = sqrt(n);
    int MAX_ITER = n;
    vector<int> tabu_list(n, 0);

    vector<bool> current_solution(n);
    random_solution(current_solution);
    vector<bool> best_solution = current_solution;
    //cout << formula.num_of_sat_clauses(best_solution) << endl;

    for (int iter = 0; iter < MAX_ITER; iter++) {
        for (int i = 0; i < n; i++) {
            if (tabu_list[i] == 0) {

                current_solution = best_solution;
                current_solution[i] = !current_solution[i];

                if (formula.num_of_sat_clauses(current_solution) > formula.num_of_sat_clauses(best_solution)) {
                    //cout << "Found better solution: " << formula.num_of_sat_clauses(current_solution) << endl;
                    best_solution = current_solution;

                } else {
                    tabu_list[i] = TABU;
                }

            } else {
                tabu_list[i]--;
            }
        }
    }
    cout << formula.num_of_sat_clauses(best_solution) << endl;
}

int main() {
    int var_count, clause_count;
    vector<string> clauses;
    read("uf100-01.cnf", clauses, var_count, clause_count);
    Formula formula = Formula(clauses, var_count, clause_count);
//    f1.print();
    cout << "Random ";
    random_solver(formula);
    cout << "LS ";
    local_search(formula);
    cout << "Tabu ";
    tabu_search(formula);
    cout << "SA ";
    simmulated_annealing(formula);

}

void breakpoint(string s) {
    cout << s << endl;
    int k; cin >> k;
}