//
//  CalculatorBrain.h
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CalculatorBrain : NSObject
@property (nonatomic, readonly) double result;
@property (nonatomic, readonly) NSString* expression;
@property (nonatomic, readonly) BOOL isPartialResult;
@property (nonatomic, strong) NSArray* program;

-(void)setOperand:(double) operand;
-(void)setVariable:(NSString*) variable;
-(void)performOperation:(NSString*) symbol;

@end
