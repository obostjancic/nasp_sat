//
// Created by Ognjen on 21.06.2019.
//

#ifndef NASP_SAT_UTIL_H
#define NASP_SAT_UTIL_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * Utility method. Reads SAT instance in CNF from specified file, changes other parameters.
 * @param filename - Name of the file to be read
 * @param clauses - Lines in the file representing clauses
 * @param var_count - Number of variables in the instance
 * @param clause_count - Number of clauses in the instance
 */
void read(string filename, vector<string> &clauses, int &var_count, int &clause_count) {
    string line;
    ifstream file(filename);
    if (file.is_open()){
        getline(file,line);
        getline(file,line);
        getline(file,line);
        getline(file,line);
        var_count = stoi(line.substr(5, 4));
        clause_count = stoi(line.substr(9, 4));
        while (getline(file,line) )
            clauses.push_back(line);

        file.close();
    }

    else cout << "Unable to open file";
}

/**
 * Utility function. Used to log variables in a formatted way along with their values.
 * @param variables - Assignment of values to variables.
 */
void print(vector<bool> &variables) {
    for(int i = 0; i < variables.size(); i++) {
        cout << " x" << i << " |";
    }
    cout << endl;
    for(int i = 0; i < variables.size(); i++) {
        cout << "  " << variables[i] << " |";
    }
    cout << endl;
}

/**
 * Utility function. Used during the reading on of a file and instantiating a formula object.
 * Implemented because of a bad c++ string support. Splits the given string by a separator character.
 * @param str - string to be split
 * @param separator - char that is used as a separator value
 * @return - vector of substrings.
 */
vector<string> split(string str, char separator) {
    vector<string> res = vector<string>();
    string curr_str = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == separator) {
            res.push_back(curr_str);
            curr_str = "";
        } else
            curr_str += str[i];
    }
    res.push_back(curr_str);
    return res;
}

/**
 * Utility function. Used during the reading on of a file and instantiating a formula object.
 * Gets the index of a variable in the array by the number in file. Negated variables are halnded appropriately here.
 * @param str - string representing one variable
 * @return  - index of the variable
 */
int get_index(string str) {
    if (str[0] != '-')
        return stoi(str) - 1;
    else
        return stoi(str.substr(1, str.size() - 1)) - 1;
}

#endif //NASP_SAT_UTIL_H
