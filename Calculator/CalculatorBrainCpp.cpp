//
//  CalculatorBrainCpp.cpp
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#include "CalculatorBrainCpp.hpp"
#include <math.h>

CalculatorBrainCpp::CalculatorBrainCpp():_internalProgram(){
    _expression = "";
    _internalProgram = vector<string>();
    
    _operations["π"] = make_tuple(OperationType::Constant, [](double a, double b) {
        return M_PI;
    });
    _operations["√"] = make_tuple(OperationType::UnaryOperation, [](double a, double b) {
        return sqrt(a);
    });
    _operations["×"] = make_tuple(OperationType::BinaryOperation, [](double a, double b) {
        return a * b;
    });
    _operations["="] = make_tuple(OperationType::Equals, [](double a, double b) {
        return 0.0;
    });
}

double CalculatorBrainCpp::getResult(){
    return this->_accumulator;
}

string CalculatorBrainCpp::expression(){
    return this->_expression;
}

bool CalculatorBrainCpp::isPartialResult(){
    return this->_partialResult;
}

vector<string> CalculatorBrainCpp::getProgram(){
    return this->_internalProgram;
}

void CalculatorBrainCpp::setProgram(vector<string> program){
    this->_internalProgram = program;
}

void CalculatorBrainCpp::setOperand(const double operand){
    _accumulator = operand;
}

void CalculatorBrainCpp::performOperation(string symbol){
    OperationType operationType;
    function<double(double,double)> func;
    tie(operationType, func) = _operations[symbol];
    switch (operationType) {
        case OperationType::Constant:
            _accumulator = func(0.0,0.0);
            break;
        case OperationType::UnaryOperation:
            _accumulator = func(_accumulator,0.0);
            break;
        case OperationType::BinaryOperation:
            performPendingOperation();
            this->pending = unique_ptr<PendingBinaryInformationInfoCpp>(new PendingBinaryInformationInfoCpp(func, _accumulator));
            break;
        case OperationType::Equals:
            performPendingOperation();
            break;
    }
}

void CalculatorBrainCpp::performPendingOperation(){
    if(pending != nullptr){
        _accumulator = pending->_binaryFunction(pending->_firstOperand, _accumulator);
        pending.reset(nullptr);
    }
}

