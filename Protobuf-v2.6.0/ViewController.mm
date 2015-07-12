//
//  ViewController.m
//  Protobuf-v2.6.0
//
//  Created by Charles on 15/7/12.
//  Copyright (c) 2015年 czyhome. All rights reserved.
//

#import "ViewController.h"
#import "OCProtobufMaganer.h"
#import "OCMessageValue.h"
#import "TestJsonModel.h"

#include <ConditionalMacros.h>
#undef TYPE_BOOL

#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;

#import "ProtoTest.pb.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UILabel *json1MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *json10MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *jsonSizeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoStatic1MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoStatic10MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoStaticSizeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoDynamic1MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoDynamic10MTimeLabel;
@property (weak, nonatomic) IBOutlet UILabel *protoDynamicSizeLabel;

@end

@implementation ViewController
{
    NSTimer *_timer;
    NSInteger _StringSize;
    NSTimeInterval _startTime;
    NSTimeInterval _1wSpentTime;
    NSTimeInterval _10wSpentTime;
    NSInteger _index;
    NSInteger _startType;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)onJsonStartAction:(id)sender {
    
    NSThread *jsonThread = [[NSThread alloc] initWithTarget:self selector:@selector(jsonThreadRun) object:nil];
    [jsonThread setName:@"jsonThread"];
    [jsonThread start];
    
    _startType = 1;
    _timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];
}

- (IBAction)onProtoStaticStartAction:(id)sender {
    NSThread *protoStaticThread = [[NSThread alloc] initWithTarget:self selector:@selector(protoStaticThreadRun) object:nil];
    [protoStaticThread setName:@"protoStaticThread"];
    [protoStaticThread start];
    
    _startType = 2;
    _timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];
}

- (IBAction)onProtoDynamicStartAction:(id)sender {
    NSThread *protoDynamicThread = [[NSThread alloc] initWithTarget:self selector:@selector(protoDynamicThreadRun) object:nil];
    [protoDynamicThread setName:@"protoDynamicThread"];
    [protoDynamicThread start];
    
    _startType = 3;
    _timer = [NSTimer scheduledTimerWithTimeInterval:0.05 target:self selector:@selector(onTimer:) userInfo:nil repeats:YES];
}

- (void)jsonThreadRun
{
    NSMutableDictionary *dictIn = [NSMutableDictionary dictionary];
    
    NSMutableArray *int32Array = [NSMutableArray array];
    NSMutableArray *stringArray = [NSMutableArray array];
    for (int i = 0; i < 100; ++i) {
        [int32Array addObject:[NSString stringWithFormat:@"%d", i]];
        [stringArray addObject:@"qwertyuiopasdfghjklzxcvbnm"];
    }
    
    [dictIn setObject:@"10000" forKey:@"int32_value"];
    [dictIn setObject:@"qwertyuiopasdfghjklzxcvbnm" forKey:@"string_value"];
    
    TestJsonModel *jsonModelIn = [[TestJsonModel alloc] initWithDictionary:dictIn error:nil];
    
    _StringSize = 0;
    NSInteger maxRoopTimes = 1000000;
    
    _startTime = [[NSDate date] timeIntervalSince1970];
    for (_index = 0; _index < maxRoopTimes; ++_index) {
        
        NSString *jsonString = [jsonModelIn toJSONString];
        
        TestJsonModel *jsonModelOut = [[TestJsonModel alloc] initWithString:jsonString error:nil];
        
        if (_index == 0) {
            _StringSize = jsonString.length;
        }
        
        if (_index % 50 == 0) {
            _10wSpentTime = [[NSDate date] timeIntervalSince1970] - _startTime;
            if (_index <= maxRoopTimes/10) {
                _1wSpentTime = _10wSpentTime;
            }
        }
    }
    
    [_timer invalidate];
}

- (void)protoStaticThreadRun
{
    ProtoTest protoTestIn;
    protoTestIn.set_int32_value(10000);
    protoTestIn.set_string_value("qwertyuiopasdfghjklzxcvbnm");
    
    _StringSize = 0;
    NSInteger maxRoopTimes = 1000000;
    
    _startTime = [[NSDate date] timeIntervalSince1970];
    for (_index = 0; _index < maxRoopTimes; ++_index) {
        
        string protoString;
        protoTestIn.SerializeToString(&protoString);
        
        ProtoTest protoTestOut;
        
        protoTestOut.ParseFromString(protoString);
        
        if (_index == 0) {
            _StringSize = protoString.size();
        }
        
        if (_index % 50 == 0) {
            _10wSpentTime = [[NSDate date] timeIntervalSince1970] - _startTime;
            if (_index <= maxRoopTimes/10) {
                _1wSpentTime = _10wSpentTime;
            }
        }
    }
    
    [_timer invalidate];
}

- (void)protoDynamicThreadRun
{
    
    DiskSourceTree *source_tree = new DiskSourceTree();
    source_tree->MapPath("", [[[NSBundle mainBundle] bundlePath] UTF8String]);
    Importer *importer = new Importer(source_tree, nullptr);
    DynamicMessageFactory *dynamic_message_factory = new DynamicMessageFactory();
    importer->Import("ProtoTest.proto");
    const Descriptor *descriptor = importer->pool()->FindMessageTypeByName("ProtoTest");
    const FieldDescriptor *int32_field = descriptor->FindFieldByName("int32_value");
    const FieldDescriptor *string_field = descriptor->FindFieldByName("string_value");
    const Message *prototype_msg = dynamic_message_factory->GetPrototype(descriptor);
    Message *message_in = prototype_msg->New();
    Message *message_out = prototype_msg->New();
    const Reflection *reflection = message_in->GetReflection();
    
    reflection->SetInt32(message_in, int32_field, 10000);
    reflection->SetString(message_in, string_field, "qwertyuiopasdfghjklzxcvbnm");

    _StringSize = 0;
    NSInteger maxRoopTimes = 1000000;
    
    _startTime = [[NSDate date] timeIntervalSince1970];
    for (_index = 0; _index < maxRoopTimes; ++_index) {
        
        string protoString = "";
        message_in->SerializeToString(&protoString);
        message_out->ParseFromString(protoString);
        
        if (_index == 0) {
            _StringSize = protoString.size();
        }
        
        if (_index % 50 == 0) {
            _10wSpentTime = [[NSDate date] timeIntervalSince1970] - _startTime;
            if (_index <= maxRoopTimes/10) {
                _1wSpentTime = _10wSpentTime;
            }
        }
    }
    
    delete message_in;
    delete message_out;
    
    [_timer invalidate];
}

- (void)onTimer:(NSTimer *)timer
{
    if (_startType == 1) {
        _jsonSizeLabel.text = [NSString stringWithFormat:@"%ld", (long)_StringSize];
        _json1MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_1wSpentTime * 1000)];
        _json10MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_10wSpentTime * 1000)];
    }
    
    if (_startType == 2) {
        _protoStaticSizeLabel.text = [NSString stringWithFormat:@"%ld", (long)_StringSize];
        _protoStatic1MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_1wSpentTime * 1000)];
        _protoStatic10MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_10wSpentTime * 1000)];
    }
    
    if (_startType == 3) {
        _protoDynamicSizeLabel.text = [NSString stringWithFormat:@"%ld", (long)_StringSize];
        _protoDynamic1MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_1wSpentTime * 1000)];
        _protoDynamic10MTimeLabel.text = [NSString stringWithFormat:@"%ld", (long)(_10wSpentTime * 1000)];
    }
}

- (void) test
{
    OCProtobufMaganer *protoMgr = [OCProtobufMaganer defaultProtobufMaganer];
    if (![protoMgr initializeWithRootPath:[[NSBundle mainBundle] bundlePath]]) {
        return;
    }
    
    if (![protoMgr importerWithProto:@"test.proto"]) {
        return;
    }
    
    NSMutableDictionary *msgDictIn = [NSMutableDictionary dictionary];
    [msgDictIn setObject:[[MVInt32 alloc]initWithValue:100] forKey:@"int32_value"];
    [msgDictIn setObject:@"101" forKey:@"string_value"];
    
    NSString *msgString = [protoMgr serializeToStringWithMsgName:@"test" msgDict:msgDictIn];
    if (msgString.length <= 0) {
        return;
    }
    
    NSDictionary *msgDictOut = [protoMgr ParseToMessageDictWithMsgName:@"test" msgString:msgString];
    if (msgDictOut.count <= 0) {
        return;
    }
}

@end
