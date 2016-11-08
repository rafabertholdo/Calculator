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
@property (nonatomic, strong) NSArray* program;

@end


@implementation CppViewController
@synthesize userIsInTheMiddleOfTyping;
@synthesize program;

CalculatorBrainCpp _brain;

-(void)viewDidLoad{
    [super viewDidLoad];
    userIsInTheMiddleOfTyping = NO;
}

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
    [self sync];
}

- (IBAction)saveProgram {
    NSMutableArray *newProgram = [[NSMutableArray alloc] init];
    for(auto& item : _brain.getProgram())
    {
        [newProgram addObject:[NSString stringWithUTF8String:item.c_str()]];
    }
    program = [newProgram copy];
}

- (IBAction)loadProgram {
    if(program){
        std::vector<string> brainProgram;
        for(NSString *item in program){
            brainProgram.push_back([item UTF8String]);
        }
        _brain.setProgram(brainProgram);
        [self sync];
    }
}

-(void)sync{
    self.displayValue = _brain.getResult();
    /*
     self.expression.text = _brain.expression;
     self.expression.text = [self.expression.text stringByAppendingString:_brain.isPartialResult ? @" ...": @" ="];
     */
    
}

@end
