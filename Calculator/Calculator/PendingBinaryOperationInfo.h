//
//  PendingBinaryOperationInfo.h
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface PendingBinaryOperationInfo : NSObject

@property (nonatomic,strong) double (^binaryFunction)(double,double);
@property (nonatomic) double firstOperand;

-(instancetype)initWithFunction:(id)function andOperand:(double)operand;
@end
