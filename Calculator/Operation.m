//
//  Operation.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "Operation.h"

@implementation Operation


-(instancetype)initWithType:(OperationType)type andAssociatedVale:(id)associatedValue{
    self = [super init];
    if(self){
        _operationType = type;
        _associatedValue = associatedValue;
    }
    return self;
}
@end
