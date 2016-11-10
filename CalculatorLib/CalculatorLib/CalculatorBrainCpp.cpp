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
    
    _operations = {
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
                    this->clear();
                    return 0.0;
                }
            }
        }
    };
}

void CalculatorBrainCpp::clear(){
    pending.reset(nullptr);
    _expression.clear();
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

void CalculatorBrainCpp::setProgram(const vector<string> &program){
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

void CalculatorBrainCpp::performOperation(const string &symbol){
    if(_operations.count(symbol))
    {
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
}

void CalculatorBrainCpp::performPendingOperation(){
    if(pending != nullptr){
        _accumulator = pending->_binaryFunction(pending->_firstOperand, _accumulator);
        pending.reset(nullptr);
    }
}

