//
//  ViewController.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "ViewController.h"
#import "CalculatorBrain.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *display;
@property (weak, nonatomic) IBOutlet UILabel *expression;
@property (nonatomic) BOOL userIsInTheMiddleOfTyping;
@property (nonatomic) double displayValue;
@property (nonatomic, strong) CalculatorBrain* brain;
@property (nonatomic, strong) NSArray* program;
@end

@implementation ViewController

-(double)displayValue{
    return [_display.text doubleValue];
}

-(void)setDisplayValue:(double)displayValue{
    _display.text = [NSString stringWithFormat:@"%g", displayValue];
}

-(void)viewDidLoad{
    [super viewDidLoad];
    _userIsInTheMiddleOfTyping = NO;
    _brain = [[CalculatorBrain alloc] init];
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
    if(_userIsInTheMiddleOfTyping){
        [_brain setOperand:self.displayValue];
        _userIsInTheMiddleOfTyping = NO;
    }
    
    NSString* const mathematicalSymbol = sender.currentTitle;
    [_brain performOperation:mathematicalSymbol];
    [self sync];
}

- (IBAction)saveProgram {
    _program = _brain.program;
    
}

- (IBAction)loadProgram {
    if(_program){
        _brain.program = _program;
        [self sync];
    }
}

-(void)sync{
    self.displayValue = _brain.result;
    self.expression.text = _brain.expression;
    self.expression.text = [self.expression.text stringByAppendingString:_brain.isPartialResult ? @" ...": @" ="];

}
@end
