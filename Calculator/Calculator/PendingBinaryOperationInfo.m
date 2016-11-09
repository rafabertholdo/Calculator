//
//  PendingBinaryOperationInfo.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "PendingBinaryOperationInfo.h"

@implementation PendingBinaryOperationInfo

-(instancetype)initWithFunction:(id)function andOperand:(double)operand{
    self = [super init];
    if(self) {
        _binaryFunction = function;
        _firstOperand = operand;
    }
    
    return self;
}
@end
