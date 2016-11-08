//
//  Veicle.h
//  objectOrientedClass
//
//  Created by Rafael Guilherme Bertholdo on 10/27/16.
//  Copyright © 2016 Rafael Guilherme Bertholdo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Vehicle : NSObject

@property(nonatomic, strong) NSString *name;
@property(nonatomic) Point position;

-(void)moveTo:(Point)newPosition;
-(void)incH:(short)hToInc;
-(void)incV:(short)vToInc;

@end
