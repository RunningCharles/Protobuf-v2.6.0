//
//  OCMessageValue.h
//  Protocol-v2.6.0
//
//  Created by Charles on 15/7/11.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "message_data_def.h"

@interface MVInt32 : NSObject

@property (assign, nonatomic) int32 value;

- (instancetype) initWithValue:(int32)value;

@end

