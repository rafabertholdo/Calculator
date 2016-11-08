//
//  CppViewController.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 11/7/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "CppViewController.h"

@interface CppViewController ()
@property (weak, nonatomic) IBOutlet UILabel *display;
@property (nonatomic) BOOL userIsInTheMiddleOfTyping;
@property (nonatomic) double displayValue;

@end


@implementation CppViewController
@synthesize userIsInTheMiddleOfTyping;

-(double)displayValue{
    return [_display.text doubleValue];
}

-(void)setDisplayValue:(double)displayValue{
    _display.text = [NSString stringWithFormat:@"%g", displayValue];
}


- (IBAction)performOperation:(UIButton *)sender {
}

@end
