//
//  PendingBinaryInformationInfoCpp.hpp
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#ifndef PendingBinaryInformationInfoCpp_hpp
#define PendingBinaryInformationInfoCpp_hpp

#include <stdio.h>
#include <functional>
using namespace std;

class PendingBinaryInformationInfoCpp{
public:
    function<double(double,double)> _binaryFunction;
    double _firstOperand;
    
    PendingBinaryInformationInfoCpp(function<double(double,double)> binaryFunction, double operand);
};

#endif /* PendingBinaryInformationInfoCpp_hpp */
