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
    
    _operations = {
        { "π", make_tuple(OperationType::Constant, [](double , double b) {
            return M_PI;
        })
        } ,
        { "e", make_tuple(OperationType::Constant, [](double , double b) {
            return M_E;
        })
        } ,
        {
            "√", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return sin(a);
            })
        } ,
        {
            "sin", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return sin(a);
            })
        } ,
        {
            "cos", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return cos(a);
            })
        } ,
        {
            "log", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return log(a);
            })
        } ,
        {
            "%", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return a / 100.0;
            })
        } ,
        {
            "x!", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return tgammaf(++a);
            })
        } ,
        {
            "+", make_tuple(OperationType::BinaryOperation, [](double a, double b) {
                return a + b;
            })
        } ,
        {
            "-", make_tuple(OperationType::BinaryOperation, [](double a, double b) {
                return a - b;
            })
        } ,
        {
            "×", make_tuple(OperationType::BinaryOperation, [](double a, double b) {
                return a * b;
            })
        } ,
        {
            "÷", make_tuple(OperationType::BinaryOperation, [](double a, double b) {
                return a / b;
            })
        } ,
        {
            "=",make_tuple(OperationType::Equals, nullptr)
        } ,
        {
            "C", make_tuple(OperationType::UnaryOperation, [](double a, double b) {
                return 0.0;
            })
        }
    };
}

void CalculatorBrainCpp::clear(){
    pending.reset(nullptr);
    _expression = "";
    _internalProgram.clear();
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

void CalculatorBrainCpp::setProgram(vector<string> &program){
    clear();
    for(auto& item : program){
        if(_operations.count(item)){
            performOperation(item);
        }else{
            setOperand(stod(item));
        }
    }
    this->_internalProgram = program;
}

void CalculatorBrainCpp::setOperand(const double operand){
    _accumulator = operand;
    _internalProgram.push_back(to_string(operand));
}

void CalculatorBrainCpp::performOperation(string symbol){
    _internalProgram.push_back(symbol);
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

