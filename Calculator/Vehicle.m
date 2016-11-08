//
//  Veicle.m
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import "Vehicle.h"

@interface Vehicle ()

@end

@implementation Vehicle

@synthesize name;
@synthesize position;

-(instancetype)init{
    self = [super init];
    return self;
}

-(instancetype)initWithName:(NSString*) theName{
    self = [super init];
    if (!self) {
        return nil;
    }
    
    self.name = theName;
    return self;
}

-(void)moveTo:(Point)newPosition{
    self.position = newPosition;
}

-(void)incH:(short)hToInc{
    position.h += hToInc;
}

-(void)incV:(short)vToInc{
    position.v += vToInc;
}

@end
