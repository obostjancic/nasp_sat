//
// Created by Ognjen on 20.06.2019.
//

#ifndef NASP_SAT_CLAUSE_H
#define NASP_SAT_CLAUSE_H

#include <vector>
#include <iostream>
#include "Variable.h"
#include "Util.h"

using namespace std;

/**
 * Class representing one clause in the formula. Holds a vector of variables.
 */
class Clause{
public:
    Clause();
    Clause(vector<Variable> variables);
    Clause(string clause);

    const vector<Variable> &get_variables() const;

    void set_variables(const vector<Variable> &variables);

    void print();
private:
    vector<Variable> variables;
};

/**
 * Default constructor. Initializes variables to empty array
 */
Clause::Clause() {
    this->variables = vector<Variable>();
}

/**
 * All parameter constructor
 * @param variables - vector of variables to be se in the clause.
 */
Clause::Clause(vector<Variable> variables) {
    this->variables = variables;
}

/**
 * String constructor. Instantiates Clause object from a string (line in the file)
 * @param clause - string representing this clause
 */
Clause::Clause(string clause) : Clause() {
    vector<string> variable_strings = split(clause, ' ');
    for (auto const var_str : variable_strings) {
        if(var_str == "" || var_str == " " || var_str == "0")
            continue;
        if (var_str[0] == '-') {
            int idx = get_index(var_str);
            //cout << "idx " << idx;
            Variable v = Variable(true, idx);
            this->variables.push_back(v);
        }
        else {
            int idx = get_index(var_str);
            //cout << "idx " << idx;
            Variable v = Variable(false, idx);
            this->variables.push_back(v);
        }
    }
}

/**
 * Utility function. Used to print one clause.
 */
void Clause::print() {
    cout << "(";
    for(int i = 0; i < this->variables.size(); i++) {
        if (variables[i].is_negated())
            cout << "!";
        cout << "x" << variables[i].get_index();
        if (i != variables.size() - 1)
            cout << " | ";
    }
    cout << ")";
}

/**
 * Getter for the variables property.
 * @return variables property.
 */
const vector<Variable> &Clause::get_variables() const {
    return variables;
}

/**
 * Setter for the variables property.
 * @param variables - new value of variables property.
 */
void Clause::set_variables(const vector<Variable> &variables) {
    Clause::variables = variables;
}

#endif //NASP_SAT_CLAUSE_H
