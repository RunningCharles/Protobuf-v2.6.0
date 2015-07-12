//
//  OCProtobufMaganer.h
//  Protocol-v2.6.0
//
//  Created by Charles on 15/7/11.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface OCProtobufMaganer : NSObject

+ (instancetype)defaultProtobufMaganer;

- (BOOL)initializeWithRootPath:(NSString *)rootPath;

- (BOOL)importerWithProto:(NSString *)proto;

- (NSString *)serializeToStringWithMsgName:(NSString *)msgName msgDict:(NSDictionary *)msgDict;

- (NSDictionary *)ParseToMessageDictWithMsgName:(NSString *)msgName msgString:(NSString *)msgString;

@end
