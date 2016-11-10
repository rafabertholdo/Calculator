//
//  CalculatorBrain.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "CalculatorBrain.h"
#import "Operation.h"
#import "PendingBinaryOperationInfo.h"

typedef double (^UnaryBlock)(double);
typedef double (^BinaryBlock)(double,double);

@interface CalculatorBrain()
@property (nonatomic) double accumulator;
@property (nonatomic, strong) NSDictionary *operations;
@property (nonatomic, strong) NSMutableDictionary *variableValues;
@property (nonatomic, strong) PendingBinaryOperationInfo* pending;
@property (nonatomic) BOOL nextOperationAddAccumulatorToExpression;
@property (nonatomic, strong) NSMutableArray* internalProgram;
@end

@implementation CalculatorBrain

-(NSArray*)program{
    return [NSArray arrayWithArray:_internalProgram];
}

-(void)setProgram:(NSArray*)value{
    [self clear];
    for(id item in value){
        if([item isKindOfClass:[NSNumber class]]){
            [self setOperand:[((NSNumber*)item) doubleValue]];
        } else if ([item isKindOfClass:[NSString class]]){
            [self performOperation:item];
        }
    }
}

-(instancetype)init{
    self = [super init];
    if(self){
        _expression = @"";
        _nextOperationAddAccumulatorToExpression = YES;
        _variableValues = [[NSMutableDictionary alloc] init];
        _internalProgram = [[NSMutableArray alloc] init];
        _operations = @{@"π": [[Operation alloc] initWithType:Constant andAssociatedVale: [NSNumber numberWithDouble:M_PI]],
                        @"e": [[Operation alloc] initWithType:Constant andAssociatedVale: [NSNumber numberWithDouble:M_E]] ,
                        @"√": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return sqrt(value);
                        }],
                        @"sin": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return sin(value);
                        }],
                        @"cos": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return cos(value);
                        }],
                        @"tan": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return sin(value);
                        }],
                        @"log": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return log(value);
                        }],
                        @"%": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return value / 100;
                        }],
                        @"x!": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            return tgammaf(++value);
                        }],
                        @"C": [[Operation alloc] initWithType:UnaryOperation andAssociatedVale: ^(double value){
                            [self clear];
                            return 0.0;
                        }],
                        @"+": [[Operation alloc] initWithType:BinaryOperation andAssociatedVale: ^(double value1, double value2){
                            return value1 + value2;
                        }],
                        @"-": [[Operation alloc] initWithType:BinaryOperation andAssociatedVale: ^(double value1, double value2){
                            return value1 - value2;
                        }],
                        @"×": [[Operation alloc] initWithType:BinaryOperation andAssociatedVale: ^(double value1, double value2){
                            return value1 * value2;
                        }],
                        @"÷": [[Operation alloc] initWithType:BinaryOperation andAssociatedVale: ^(double value1, double value2){
                            return value1 / value2;
                        }],
                        @"=": [[Operation alloc] initWithType:Equals andAssociatedVale: nil]};
    }
    return self;
}

-(void)clear{
    self.pending = nil;
    _expression = @"";
    _nextOperationAddAccumulatorToExpression = YES; 
    [_internalProgram removeAllObjects];
}

-(BOOL)isPartialResult{
    return self.pending != nil;
}

-(double)result{
    return _accumulator;
}

-(void)setOperand:(double)operand{
    _accumulator = operand;
    [_internalProgram addObject:[NSNumber numberWithDouble:operand]];
}

-(void)setVariable:(NSString *)variable{
    _variableValues[variable] = [NSNumber numberWithDouble:0.0];
}

-(void)performOperation:(NSString *)symbol{
    [_internalProgram addObject:symbol];
    Operation* operation = _operations[symbol];
    
    switch (operation.operationType) {
        case Constant:
            if(!self.isPartialResult) {
                _expression = symbol;
            }else{
                _expression = [_expression stringByAppendingString:symbol];
            }
            _nextOperationAddAccumulatorToExpression = NO;
            break;
        case UnaryOperation:
            if(!self.isPartialResult) {
                _expression = [NSString stringWithFormat:@"%@(%@)", symbol, _expression];
            }else{
                _expression = [_expression stringByAppendingString:[NSString stringWithFormat:@"%@(%g)", symbol, _accumulator]];
            }
            _nextOperationAddAccumulatorToExpression = NO;
            break;
        case BinaryOperation:
            if(_nextOperationAddAccumulatorToExpression) {
                _expression = [_expression stringByAppendingString:[NSString stringWithFormat:@"%g%@", _accumulator, symbol]];
            }
            else {
                _expression = [_expression stringByAppendingString:[NSString stringWithFormat:@"%@", symbol]];
                _nextOperationAddAccumulatorToExpression = YES;
            }
            break;
        case Equals:
            if(_nextOperationAddAccumulatorToExpression) {
                _expression = [_expression stringByAppendingString:[NSString stringWithFormat:@"%g", _accumulator]];
            }
            _nextOperationAddAccumulatorToExpression = NO;
            break;
    }
    
    
    switch (operation.operationType) {
        case Constant:
            _accumulator = [operation.associatedValue isKindOfClass:[NSNumber class]] ?
            [(NSNumber*)operation.associatedValue doubleValue] : 0;
            break;
        case UnaryOperation:
            _accumulator = ((UnaryBlock)operation.associatedValue)(_accumulator);
            break;
        case BinaryOperation:
            [self performPendingOperation];
            self.pending = [[PendingBinaryOperationInfo alloc] initWithFunction:operation.associatedValue andOperand:_accumulator];
            break;
        case Equals:
            [self performPendingOperation];
            break;
    }
}

-(void)performPendingOperation{
    if(self.pending){
        _accumulator = self.pending.binaryFunction(self.pending.firstOperand, _accumulator);
        self.pending = nil;
    }
}

@end
