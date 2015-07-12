//
//  TestJsonModel.h
//  Protobuf-v2.6.0
//
//  Created by Charles on 15/7/12.
//  Copyright (c) 2015年 czyhome. All rights reserved.
//

#import "JSONModel.h"

@interface TestJsonModel : JSONModel

@property (strong, nonatomic) NSString *int32_value;
@property (strong, nonatomic) NSString *string_value;
@property (strong, nonatomic) NSArray<Optional>  *rpt_int32_value;
@property (strong, nonatomic) NSArray<Optional>  *rpt_string_value;

@end
