//
//  CalculatorBrainCpp.hpp
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#ifndef CalculatorBrainCpp_hpp
#define CalculatorBrainCpp_hpp

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <functional>

#include "PendingBinaryInformationInfoCpp.hpp"

using namespace std;

enum class OperationType{
    Constant,
    UnaryOperation,
    BinaryOperation,
    Equals
};

class CalculatorBrainCpp {
    
    class impl;
    unique_ptr<impl> pimpl;

public:
    
    CalculatorBrainCpp();
    ~CalculatorBrainCpp();
    double getResult();
    string getExpression();
    bool isPartialResult();
    vector<string> getProgram();
    void setProgram(const vector<string> &program);
    
    void setOperand(const double operand);
    void performOperation(const string &symbol);
};


#endif /* CalculatorBrainCpp_hpp */
