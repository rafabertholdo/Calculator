//
//  Operation.h
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,OperationType) {
    Constant,
    UnaryOperation,
    BinaryOperation,
    Equals
};

@interface Operation : NSObject

@property (nonatomic) OperationType operationType;
@property (nonatomic, strong) id associatedValue;

-(instancetype)initWithType:(OperationType)type andAssociatedVale:(id)associatedValue;
@end
