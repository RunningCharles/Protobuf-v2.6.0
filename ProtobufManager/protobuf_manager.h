//
//  protobuf_manager.h
//  protobuf-v2.6.0
//
//  Created by Charles on 15/7/9.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#ifndef __protobuf_v2_6_0__protobuf_manager__
#define __protobuf_v2_6_0__protobuf_manager__

#include <ConditionalMacros.h>
#undef TYPE_BOOL

#include <iostream>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/dynamic_message.h>
#include <google/protobuf/compiler/importer.h>

#include "message_data.h"

using namespace std;
using namespace google::protobuf;
using namespace google::protobuf::io;
using namespace google::protobuf::compiler;

class ProtobufManager:public MultiFileErrorCollector
{
public:
    static ProtobufManager * Instance();
    
private:
    static ProtobufManager *instance;
    
private:
    ProtobufManager();
    ~ProtobufManager();
    
public:
    bool Initialize(const string &root_path);
    bool ImporterProto(const string &proto_file_name);
    bool SerializeToString(const string &msg_name, const MessageData &msg_data, string &msg_string);
    bool ParseToMessageData(const string &msg_name, const string &msg_string, MessageData &msg_data);
    
private:
    bool SetInt32(const Reflection *reflection, const FieldDescriptor* field, const MessageData &msg_data, Message *message);
    bool SetString(const Reflection *reflection, const FieldDescriptor* field, const MessageData &msg_data, Message *message);
    
    bool GetInt32(const Reflection *reflection, const FieldDescriptor* field, Message *message, MessageData &msg_data);
    bool GetString(const Reflection *reflection, const FieldDescriptor* field, Message *message, MessageData &msg_data);
    
// MultiFileErrorCollector
public:
    virtual void AddError(const string& filename, int line, int column, const string& message);

private:
    bool           is_initialized_;
    
private:
    DiskSourceTree        *source_tree_;
    Importer              *importer_;
    DynamicMessageFactory *dynamic_message_factory_;
};

#endif /* defined(__protobuf_v2_6_0__protobuf_manager__) */
