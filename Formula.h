//
// Created by Ognjen on 20.06.2019.
//

#ifndef NASP_SAT_FORMULA_H
#define NASP_SAT_FORMULA_H

#include <vector>
#include <iostream>
#include <string>
#include "Clause.h"

/**
 * Class representing a SAT instance. Used as a wrapper to hold clauses and number of variables.
 */
class Formula {
public:
    Formula();
    Formula(vector<string> clauses, unsigned int var_count, unsigned int clause_count);

    int num_of_sat_clauses(const vector<bool> &variables) const;
    int clause_count() const { return this->clauses.size();}
    int get_var_count() { return this->var_count;}
    bool evaluate(const vector<bool> &variables) const;
    void print();
private:
    bool evaluate_clause(const Clause& clause, const vector<bool> &variables) const;

    vector<Clause> clauses;
    int var_count;
};

/**
 * Default constructor
 */
Formula::Formula() {
    this->clauses = vector<Clause>();
    this->var_count = 0;
}

/**
 * All parameter constructor
 * @param clauses - vector of strings representing clauses in formula
 * @param var_count - number or variables
 * @param clause_count  - number of clauses
 */
Formula::Formula(vector<string> clauses, unsigned int var_count, unsigned int clause_count) : Formula(){
    this->var_count = var_count;
    for(auto const &clause_str : clauses)
        this->clauses.push_back(Clause(clause_str));

}

/**
 * Evaluates the passed "solution"
 * @param variables - one assignment of values to variables for the SAT problem
 * @return number of clauses that are satisfied by this assignment of values to variables
 */
int Formula::num_of_sat_clauses(const vector<bool> &variables) const {
    int counter = 0;
    for (auto const &clause : this->clauses)
        if(evaluate_clause(clause, variables))
            counter++;
    return counter;
}

/**
 * Evaluates the formula with given assignment of values to variables
 * @param variables - one assignment of values to variables for the SAT problem
 * @return true if formula is satisfied, false otherwise
 */
bool Formula::evaluate(const vector<bool> &variables) const {
    return this->num_of_sat_clauses(variables) == this->clause_count();
}

/**
 * Utility function. Used to log the formula to the console.
 */
void Formula::print() {
    for(int i = 0; i < this->clauses.size(); i++) {
        clauses[i].print();
        if (i != clauses.size() - 1)
            cout << " & " << endl;
    }
    cout << endl;
}

/**
 * Evaluates the passed clause with given assignment of values to variables.
 * @param clause - Clause in the formula to be evaluated
 * @param variables - one assignment of values to variables.
 * @return true if the clause is satisfied, false otherwise
 */
bool Formula::evaluate_clause(const Clause &clause, const vector<bool> &variables) const {
    for (auto const var : clause.get_variables()) {
        bool value = variables[var.get_index()];
        if (value && !var.is_negated() || !value && var.is_negated()) {
            return true;
        }

    }
    return false;
}


#endif //NASP_SAT_FORMULA_H
