//
//  OCProtobufMaganer.m
//  Protocol-v2.6.0
//
//  Created by Charles on 15/7/11.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#import "OCProtobufMaganer.h"
#import "OCMessageValue.h"
#import "protobuf_manager.h"

static OCProtobufMaganer *protobufManager = nil;

@interface OCProtobufMaganer()
@end

@implementation OCProtobufMaganer
{
    ProtobufManager *_protoMgr;
    BOOL             _isInitialized;
}

+ (instancetype)defaultProtobufMaganer
{
    @synchronized(self){
        if (!protobufManager) {
            protobufManager = [[self alloc] init];
        }
    }
    return protobufManager;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _protoMgr = ProtobufManager::Instance();
        _isInitialized = NO;
    }
    return self;
}

- (BOOL)initializeWithRootPath:(NSString *)rootPath
{
    if (!_protoMgr) {
        return NO;
    }
    
    if (!_protoMgr->Initialize([rootPath UTF8String])) {
        return NO;
    }
    
    _isInitialized = YES;
    
    return YES;
}

- (BOOL) importerWithProto:(NSString *)proto
{
    if (!_isInitialized) {
        return NO;
    }
    
    if (!_protoMgr->ImporterProto([proto UTF8String]))
    {
        return NO;
    }
    
    return YES;
}

- (NSString *)serializeToStringWithMsgName:(NSString *)msgName msgDict:(NSDictionary *)msgDict
{
    if (msgName.length <= 0 || msgDict.count <= 0) {
        return nil;
    }
    
    MessageData *messageData = [OCProtobufMaganer messageDataFromDict:msgDict];
    if (!messageData) {
        return nil;
    }
    
    shared_ptr<MessageData> messageDataPtr(messageData);
    
    string msgString;
    if (!_protoMgr->SerializeToString([msgName UTF8String], *messageData, msgString)) {
        return nil;
    }
    
    return [NSString stringWithUTF8String:msgString.c_str()];
}

- (NSDictionary *)ParseToMessageDictWithMsgName:(NSString *)msgName msgString:(NSString *)msgString
{
    if (msgName.length <=0 || msgString.length <= 0) {
        return nil;
    }
    
    shared_ptr<MessageData> messageData(new MessageData());
    if (!_protoMgr->ParseToMessageData([msgName UTF8String], [msgString UTF8String], *(messageData.get()))) {
        return nil;
    }
    
    return [OCProtobufMaganer dictFromMessageData:messageData.get()];
}

+ (NSDictionary *)dictFromMessageData:(MessageData *)messageData
{
    if (!messageData) {
        return nil;
    }
    
    NSMutableDictionary *mutableDict = [NSMutableDictionary dictionary];
    
    MapMessageValue mapMessageValue = messageData->GetMapMessageValue();
    MapMessageValue::iterator iter = mapMessageValue.begin();
    for (; iter != mapMessageValue.end(); ++iter) {
        
        if (!iter->second.get()) {
            continue;
        }
        
        switch (iter->second->GetType()) {
            case Type_Int32Value:
                {
                    MVInt32 *int32Value = [[MVInt32 alloc] initWithValue:((MessageValue<int32> *)iter->second.get())->GetValue()];
                    [mutableDict setObject:int32Value forKey:[NSString stringWithUTF8String:iter->first.c_str()]];
                }
                break;
            case Type_StringValue:
                {
                    NSString *stringValue = [NSString stringWithUTF8String:(((MessageValue<string> *)iter->second.get())->GetValue()).c_str()];
                    [mutableDict setObject:stringValue forKey:[NSString stringWithUTF8String:iter->first.c_str()]];
                }
                break;
                
            default:
                break;
        }
    }
    
    return mutableDict;
}

+ (MessageData *) messageDataFromDict:(NSDictionary *)dict
{
    if (!dict || [dict count] <= 0) {
        return nil;
    }
    
    NSArray *dictKeys = [dict allKeys];
    if (dictKeys.count <= 0) {
        return nil;
    }
    
    MessageData * messageData = new MessageData();
    for (id key in dictKeys) {
        if (![key isKindOfClass:NSString.class] || [(NSString *)key length] <= 0) {
            continue;
        }
        
        id value = [dict objectForKey:key];
        if ([value isKindOfClass:MVInt32.class]) {
            messageData->SetInt32Value([(NSString *)key UTF8String], [(MVInt32 *)value value]);
        }
        else if ([value isKindOfClass:NSString.class]){
            messageData->SetStringValue([(NSString *)key UTF8String], [(NSString *)value UTF8String]);
        }
    }
    
    return messageData;
}

@end
