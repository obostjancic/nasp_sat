//
// Created by Ognjen on 20.06.2019.
//

#ifndef NASP_SAT_VARIABLE_H
#define NASP_SAT_VARIABLE_H

#include <iostream>
#include <string>

using namespace std;

/**
 * Simple class that represents a variable within a clause. Has properties negated and index.
 */
class Variable{
public:
    Variable();
    Variable(bool negated);
    Variable(bool negated, int index);

    bool is_negated() const;

    void set_negated(bool negated);

    int get_index() const;

    void set_index(int index);

private:
    bool negated;
    int index;
};

/**
 * No parameter constructor
 */
Variable::Variable() {
    this->negated = false;
    this->index = -1;
}

/**
 * One parameter constructor.
 * @param negated - boolean flag which determines is the variable negated in the clause or not
 */
Variable::Variable(bool negated) {
    this->negated = negated;
    this->index = -1;
}

/**
 * One parameter constructor.
 * @param negated - boolean flag which determines is the variable negated in the clause or not
 * @param index - index of this variable (or it's name)
 */
Variable::Variable(bool negated, int index) {
    this->negated = negated;
    this->index = index;
}

/**
 * Getter for negated property
 * @return true if variable is negated, false otherwise
 */
bool Variable::is_negated() const {
    return negated;
}

/**
 * Setter for negated property
 * @param negated - new value of negated property
 */
void Variable::set_negated(bool negated) {
    Variable::negated = negated;
}

/**
 * Getter for index property
 * @return index of the variable
 */
int Variable::get_index() const {
    return index;
}

/**
 * Setter for index property
 * @param index - new value of index property
 */
void Variable::set_index(int index) {
    Variable::index = index;
}

#endif //NASP_SAT_VARIABLE_H
