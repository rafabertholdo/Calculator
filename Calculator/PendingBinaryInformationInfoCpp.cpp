//
//  PendingBinaryInformationInfoCpp.cpp
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#include "PendingBinaryInformationInfoCpp.hpp"

PendingBinaryInformationInfoCpp::PendingBinaryInformationInfoCpp(function<double(double,double)>binaryFunction, double firstOperand):_binaryFunction(binaryFunction), _firstOperand(firstOperand)
{
    
}
