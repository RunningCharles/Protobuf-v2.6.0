//
//  protobuf_manager.cc
//  protobuf-v2.6.0
//
//  Created by Charles on 15/7/9.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#include "protobuf_manager.h"

ProtobufManager *ProtobufManager::instance = nullptr;
ProtobufManager* ProtobufManager::Instance()
{
    if (instance == nullptr)
    {
        instance = new ProtobufManager();
    }
    return instance;
}

ProtobufManager::ProtobufManager()
  :is_initialized_(false)
  ,source_tree_(nullptr)
  ,importer_(nullptr)
  ,dynamic_message_factory_(nullptr)
{
    
}

ProtobufManager::~ProtobufManager()
{
    if (source_tree_ != nullptr)
    {
        delete source_tree_;
        source_tree_ = nullptr;
    }
    
    if (importer_ != nullptr)
    {
        delete importer_;
        importer_ = nullptr;
    }
    
    if (dynamic_message_factory_ != nullptr)
    {
        delete dynamic_message_factory_;
        dynamic_message_factory_ = nullptr;
    }
}

bool ProtobufManager::Initialize(const string &root_path)
{
    if (!is_initialized_)
    {
        source_tree_ = new DiskSourceTree();
        source_tree_->MapPath("", root_path);
        importer_ = new Importer(source_tree_, this);
        dynamic_message_factory_ = new DynamicMessageFactory();
        
        is_initialized_ = true;
    }
    
    return is_initialized_;
}

bool ProtobufManager::ImporterProto(const string &proto_file_name)
{
    if (!is_initialized_)
    {
        return false;
    }
    
    const FileDescriptor* file_descriptor = importer_->Import(proto_file_name);
    if (file_descriptor == nullptr)
    {
        return false;
    }
    return true;
}

bool ProtobufManager::SerializeToString(const string &msg_name, const MessageData &msg_data, string &msg_string)
{
    if (!is_initialized_)
    {
        return false;
    }
    
    const Descriptor *descriptor = importer_->pool()->FindMessageTypeByName(msg_name);
    if (descriptor == nullptr)
    {
        return false;
    }
    
    DynamicMessageFactory dynamic_message_factory;
    const Message *prototype_msg = dynamic_message_factory.GetPrototype(descriptor);
    if (prototype_msg == nullptr)
    {
        return false;
    }
    
    Message *message = prototype_msg->New();
    const Reflection *reflection = message->GetReflection();
    if (message == nullptr || reflection == nullptr)
    {
        return false;
    }
    
    bool ret = true;
    for (int i = 0; i < descriptor->field_count(); ++i)
    {
        const FieldDescriptor* field = descriptor->field(i);
        switch (FieldDescriptor::TypeToCppType(field->type()))
        {
            case FieldDescriptor::CPPTYPE_INT32:
                ret = this->SetInt32(reflection, field, msg_data, message);
                break;
            case FieldDescriptor::CPPTYPE_STRING:
                ret = this->SetString(reflection, field, msg_data, message);
                break;
                
            default:
                break;
        }
        
        if (!ret)
        {
            break;
        }
    }
    
    string output = "";
    if(!ret || !message->SerializeToString(&output))
    {
        return false;
    }
    
    msg_string = output;
    
    delete message;
    
    return ret;
}

bool ProtobufManager::ParseToMessageData(const string &msg_name, const string &msg_string, MessageData &msg_data)
{
    if (!is_initialized_)
    {
        return false;
    }
    
    const Descriptor *descriptor = importer_->pool()->FindMessageTypeByName(msg_name);
    if (descriptor == nullptr)
    {
        return false;
    }
    
    DynamicMessageFactory dynamic_message_factory;
    const Message *prototype_msg = dynamic_message_factory.GetPrototype(descriptor);
    if (prototype_msg == nullptr)
    {
        return false;
    }
    
    Message *message = prototype_msg->New();
    const Reflection *reflection = message->GetReflection();
    if (message == nullptr || reflection == nullptr)
    {
        return false;
    }
    
    if (!message->ParseFromString(msg_string))
    {
        return false;
    }
    
    bool ret = true;
    for (int i = 0; i < descriptor->field_count(); ++i)
    {
        const FieldDescriptor* field = descriptor->field(i);
        switch (FieldDescriptor::TypeToCppType(field->type()))
        {
            case FieldDescriptor::CPPTYPE_INT32:
                ret = this->GetInt32(reflection, field, message, msg_data);
                break;
            case FieldDescriptor::CPPTYPE_STRING:
                ret = this->GetString(reflection, field, message, msg_data);
                break;
                
            default:
                break;
        }
        
        if (!ret)
        {
            break;
        }
    }
    
    delete message;
    
    return ret;
}

bool ProtobufManager::SetInt32(const Reflection *reflection, const FieldDescriptor *field, const MessageData &msg_data, Message *message)
{
    if (field->is_required() || field ->is_optional())
    {
        int32 int32_value = 0;
        bool has_value = msg_data.GetInt32Value(field->name(), int32_value);
        if (field->is_required() && !has_value)
        {
            return false;
        }
        
        if (has_value)
        {
            reflection->SetInt32(message, field, int32_value);
        }
        return true;
    }
    
    if (field->is_repeated())
    {
        vector<int32> rpt_int32_value;
        bool has_value = msg_data.GetRptInt32Value(field->name(), rpt_int32_value);
        if (has_value)
        {
            vector<int32>::iterator iter = rpt_int32_value.begin();
            for (; iter != rpt_int32_value.end(); ++iter)
            {
                reflection->AddInt32(message, field, *iter);
            }
        }
        return true;
    }
    
    return false;
}

bool ProtobufManager::SetString(const Reflection *reflection, const FieldDescriptor *field, const MessageData &msg_data, Message *message)
{
    if (field->is_required() || field ->is_optional())
    {
        string string_value = "";
        bool has_value = msg_data.GetStringValue(field->name(), string_value);
        if (field->is_required() && !has_value)
        {
            return false;
        }
        
        if (has_value)
        {
            reflection->SetString(message, field, string_value);
        }
        return true;
    }
    
    if (field->is_repeated())
    {
        vector<string> rpt_string_value;
        bool has_value = msg_data.GetRptStringValue(field->name(), rpt_string_value);
        if (has_value)
        {
            vector<string>::iterator iter = rpt_string_value.begin();
            for (; iter != rpt_string_value.end(); ++iter)
            {
                reflection->AddString(message, field, *iter);
            }
        }
        return true;
    }
    
    return false;
}

bool ProtobufManager::GetInt32(const Reflection *reflection, const FieldDescriptor* field, Message *message, MessageData &msg_data)
{
    if (field->is_required() || field->is_optional())
    {
        if (!reflection->HasField(*message, field))
        {
            if (field->is_required())
                return false;
            else
                return true;
        }
        
        int32 int32_value = reflection->GetInt32(*message, field);
        msg_data.SetInt32Value(field->name(), int32_value);
        
        return true;
    }
    
    if (field->is_repeated())
    {
        vector<int32> rpt_int32_value;
        int field_size = reflection->FieldSize(*message, field);
        for (int32 index = 0; index < field_size; ++index)
        {
            int32 int32_value = reflection->GetRepeatedInt32(*message, field, index);
            rpt_int32_value.push_back(int32_value);
        }
        
        if (field_size > 0)
        {
            msg_data.SetRptInt32Value(field->name(), rpt_int32_value);
        }
        
        return true;
    }
    
    return false;
}

bool ProtobufManager::GetString(const Reflection *reflection, const FieldDescriptor* field, Message *message, MessageData &msg_data)
{
    if (field->is_required() || field->is_optional())
    {
        if (!reflection->HasField(*message, field))
        {
            if (field->is_required())
                return false;
            else
                return true;
        }
        
        string string_value = reflection->GetString(*message, field);
        msg_data.SetStringValue(field->name(), string_value);
        
        return true;
    }
    
    if (field->is_repeated())
    {
        vector<string> rpt_string_value;
        int field_size = reflection->FieldSize(*message, field);
        for (int32 index = 0; index < field_size; ++index)
        {
            string string_value = reflection->GetRepeatedString(*message, field, index);
            rpt_string_value.push_back(string_value);
        }
        
        if (field_size > 0)
        {
            msg_data.SetRptStringValue(field->name(), rpt_string_value);
        }
        
        return true;
    }
    
    return false;
}

void ProtobufManager::AddError(const string& filename, int line, int column, const string& message)
{
}