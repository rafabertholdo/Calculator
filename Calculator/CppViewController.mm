//
//  CppViewController.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "CppViewController.h"
#include "CalculatorBrainCpp.hpp"

@interface CppViewController ()
@property (weak, nonatomic) IBOutlet UILabel *display;
@property (nonatomic) BOOL userIsInTheMiddleOfTyping;
@property (nonatomic) double displayValue;

@end


@implementation CppViewController
@synthesize userIsInTheMiddleOfTyping;

CalculatorBrainCpp _brain;

-(double)displayValue{
    return [_display.text doubleValue];
}

-(void)setDisplayValue:(double)displayValue{
    _display.text = [NSString stringWithFormat:@"%g", displayValue];
}

- (IBAction)touchDigit:(UIButton *)sender {
    NSString* const digit = sender.currentTitle;
    NSString* displayText = self.display.text;
    
    if(self.userIsInTheMiddleOfTyping){
        if(!([digit isEqualToString:@"."] && [_display.text containsString:@"."])){
            self.display.text = [displayText stringByAppendingString:digit];
        }
    }else{
        self.display.text = digit;
    }
    self.userIsInTheMiddleOfTyping = YES;
}


- (IBAction)performOperation:(UIButton *)sender {
    if(userIsInTheMiddleOfTyping){
        _brain.setOperand(self.displayValue);
        userIsInTheMiddleOfTyping = NO;
    }
    
    NSString* const mathematicalSymbol = sender.currentTitle;
    
    _brain.performOperation([mathematicalSymbol UTF8String]);
    self.displayValue = _brain.getResult();
}

@end
