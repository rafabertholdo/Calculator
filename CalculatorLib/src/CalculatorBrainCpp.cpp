//
//  CalculatorBrainCpp.cpp
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#include "CalculatorBrainCpp.hpp"
#include <math.h>
#include <iostream>
#include <sstream>

class CalculatorBrainCpp::impl{
public:
    
    double _accumulator;
    string _expression;
    unique_ptr<PendingBinaryInformationInfoCpp> _pending;
    vector<string> _internalProgram;
    map<string, tuple<OperationType, function<double(double,double)>>> _operations;
    bool _nextOperationAddAccumulatorToExpression;
    
    void performPendingOperation(){
        if(_pending != nullptr){
            _accumulator = _pending->_binaryFunction(_pending->_firstOperand, _accumulator);
            _pending.reset(nullptr);
        }
    }
    
    void clear(){
        _pending.reset(nullptr);
        _expression.clear();
        _nextOperationAddAccumulatorToExpression = true;
        _internalProgram.clear();
    }
};

CalculatorBrainCpp::CalculatorBrainCpp(): pimpl{std::make_unique<impl>()} {
    pimpl->_nextOperationAddAccumulatorToExpression = true;
    pimpl->_operations = {
        {
            "π", { OperationType::Constant,
                [](auto, auto ) {
                    return M_PI;
                }
            }
        } ,
        {
            "e", { OperationType::Constant,
                [](auto,auto) {
                    return M_E;
                }
            }
        } ,
        {
            "√", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return sin(a);
                }
            }
        } ,
        {
            "sin", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return sin(a);
                }
            }
        } ,
        {
            "cos", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return cos(a);
                }
            }
        } ,
        {
            "log", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return log(a);
                }
            }
        } ,
        {
            "%", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return a / 100.0;
                }
            }
        } ,
        {
            "x!", { OperationType::UnaryOperation,
                [](auto a,auto) {
                    return tgammaf(++a);
                }
            }
        } ,
        {
            "+", { OperationType::BinaryOperation,
                [](auto a,auto b) {
                    return a + b;
                }
            }
        } ,
        {
            "-", { OperationType::BinaryOperation,
                [](auto a,auto b) {
                    return a - b;
                }
            }
        } ,
        {
            "×", { OperationType::BinaryOperation,
                [](auto a,auto b) {
                    return a * b;
                }
            }
        } ,
        {
            "÷", { OperationType::BinaryOperation,
                [](auto a,auto b) {
                    return a / b;
                }
            }
        } ,
        {
            "=", { OperationType::Equals, nullptr}
        } ,
        {
            "C", { OperationType::UnaryOperation,
                [this](auto,auto) {
                    pimpl->clear();
                    return 0.0;
                }
            }
        }
    };
}

CalculatorBrainCpp::~CalculatorBrainCpp(){
    
}

double CalculatorBrainCpp::getResult(){
    return pimpl->_accumulator;
}

string CalculatorBrainCpp::getExpression(){
    return pimpl->_expression;
}

bool CalculatorBrainCpp::isPartialResult(){
    return pimpl->_pending != nullptr;
}

vector<string> CalculatorBrainCpp::getProgram(){
    return pimpl->_internalProgram;
}

void CalculatorBrainCpp::setProgram(const vector<string> &program){
    pimpl->clear();
    for(auto& item : program){
        if(pimpl->_operations.count(item)){
            performOperation(item);
        }else{
            setOperand(stod(item));
        }
    }
    pimpl->_internalProgram = program;
}

void CalculatorBrainCpp::setOperand(const double operand){
    pimpl->_accumulator = operand;
    pimpl->_internalProgram.push_back(to_string(operand));
}

void CalculatorBrainCpp::performOperation(const string &symbol){
    if(pimpl->_operations.count(symbol))
    {
        pimpl->_internalProgram.push_back(symbol);
        OperationType operationType;
        function<double(double,double)> func;
        tie(operationType, func) = pimpl->_operations[symbol];
        switch (operationType) {
            case OperationType::Constant:
                //process expression
                if(!isPartialResult()) {
                    pimpl->_expression = symbol;
                }else{
                    pimpl->_expression = pimpl->_expression + symbol;
                }
                pimpl->_nextOperationAddAccumulatorToExpression = false;
                
                //process unary function
                pimpl->_accumulator = func(0.0,0.0);
                break;
            case OperationType::UnaryOperation:
            {
                //Process expression
                if(pimpl->_expression.empty()) {
                    stringstream format;
                    format << symbol << "(" << pimpl->_accumulator << ")";
                    pimpl->_expression = format.str();
                }else{
                    stringstream format;
                    format << symbol << "(" << pimpl->_expression << ")";
                    pimpl->_expression = format.str();
                }
                pimpl->_nextOperationAddAccumulatorToExpression = false;
                
                //process unary function
                pimpl->_accumulator = func(pimpl->_accumulator,0.0);
                break;
            }
            case OperationType::BinaryOperation:
            {
                //process expression
                if(pimpl->_nextOperationAddAccumulatorToExpression) {
                    stringstream format;
                    format << pimpl->_accumulator << symbol;
                    pimpl->_expression = pimpl->_expression + format.str();
                }
                else {
                    pimpl->_expression = pimpl->_expression  + symbol;
                    pimpl->_nextOperationAddAccumulatorToExpression = true;
                }
                
                //process binary function
                pimpl->performPendingOperation();
                pimpl->_pending = unique_ptr<PendingBinaryInformationInfoCpp>(new PendingBinaryInformationInfoCpp(func, pimpl->_accumulator));
                break;
            }
            case OperationType::Equals:
            {
                //process expression
                if(pimpl->_nextOperationAddAccumulatorToExpression) {
                    stringstream format;
                    format << pimpl->_expression << pimpl->_accumulator;
                    pimpl->_expression = format.str();
                }
                pimpl->_nextOperationAddAccumulatorToExpression = false;
                
                //process equals
                pimpl->performPendingOperation();
                break;
            }
                
        }
    }
}
