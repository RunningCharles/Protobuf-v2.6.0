//
//  OCMessageValue.m
//  Protocol-v2.6.0
//
//  Created by Charles on 15/7/11.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#import "OCMessageValue.h"

@implementation MVInt32

- (instancetype) initWithValue:(int32)value
{
    self = [super init];
    if (self) {
        _value = value;
    }
    return self;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"%d", (int)_value];
}

@end