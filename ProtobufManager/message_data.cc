//
//  message_data.cc
//
//  Created by Charles on 15/7/9.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#include "message_data.h"
#include <sstream>
#include <iostream>

MessageValueBase::MessageValueBase(MessageValueType type)
  :message_value_type_(type)
{
    //cout << "MessageValueBase New, type = " << GetType() << endl;
}

MessageValueBase::~MessageValueBase()
{
    //cout << "MessageValueBase Delete, type = " << GetType() << endl;
}

MessageValueType MessageValueBase::GetType()
{
    return message_value_type_;
}

template <typename Type>
MessageValue<Type>::MessageValue(MessageValueType type, Type value)
  :MessageValueBase(type)
  ,message_value_(value)
{
    //cout << "MessageValue New, type = " << GetType() << endl;
}

template <typename Type>
MessageValue<Type>::~MessageValue()
{
    //cout << "MessageValue Delete, type = " << GetType() << endl;
}

template<typename Type>
Type MessageValue<Type>::GetValue()
{
    return message_value_;
}

MessageData::MessageData()
{
    cout << "MessageData New" << endl;
}

MessageData::MessageData(const MessageData &data)
{
    this->message_value_map_ = data.message_value_map_;
    //cout << "MessageData copy" << endl;
}

MessageData::~MessageData()
{
    message_value_map_.clear();
    //cout << "MessageData Delete" << endl;
}

bool MessageData::SetInt32Value(const string &key, int32 value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<int32>> message_value(new MessageValue<int32>(Type_Int32Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetInt32Value(const string &key, int32 &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_Int32Value)
        {
            value = ((MessageValue<int32>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetInt64Value(const string &key, int64 value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<int64>> message_value(new MessageValue<int64>(Type_Int64Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetInt64Value(const string &key, int64 &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_Int64Value)
        {
            value = ((MessageValue<int64>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetUInt32Value(const string &key, uint32 value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<uint32>> message_value(new MessageValue<uint32>(Type_UInt32Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetUInt32Value(const string &key, uint32 &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_UInt32Value)
        {
            value = ((MessageValue<uint32>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetUInt64Value(const string &key, uint64 value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<uint64>> message_value(new MessageValue<uint64>(Type_UInt64Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetUInt64Value(const string &key, uint64 &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_UInt64Value)
        {
            value = ((MessageValue<uint64>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}


bool MessageData::SetDoubleValue(const string &key, double value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<double>> message_value(new MessageValue<double>(Type_DoubleValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetDoubleValue(const string &key, double &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_DoubleValue)
        {
            value = ((MessageValue<double>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetFloatValue(const string &key, float value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<float>> message_value(new MessageValue<float>(Type_FloatValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetFloatValue(const string &key, float &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_FloatValue)
        {
            value = ((MessageValue<float>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetBoolValue(const string &key, bool value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<bool>> message_value(new MessageValue<bool>(Type_BoolValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetBoolValue(const string &key, bool &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_BoolValue)
        {
            value = ((MessageValue<bool>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetEnumValue(const string &key, int value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<int>> message_value(new MessageValue<int>(Type_EnumValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetEnumValue(const string &key, int &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_EnumValue)
        {
            value = ((MessageValue<int>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetStringValue(const string &key, const string &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<string>> message_value(new MessageValue<string>(Type_StringValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetStringValue(const string &key, string &value) const
{
    if (key.empty()) {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_StringValue)
        {
            value = ((MessageValue<string>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetMessageDataValue(const string &key, const MessageData &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<MessageData>> message_value(new MessageValue<MessageData>(Type_MessageDataValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetMessageDataValue(const string &key, MessageData &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_MessageDataValue)
        {
            value = ((MessageValue<MessageData>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptInt32Value(const string &key, const vector<int32> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<int32>>> message_value(new MessageValue<vector<int32>>(Type_RptInt32Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptInt32Value(const string &key, vector<int32> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptInt32Value)
        {
            value = ((MessageValue<vector<int32>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptInt64Value(const string &key, const vector<int64> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<int64>>> message_value(new MessageValue<vector<int64>>(Type_RptInt64Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptInt64Value(const string &key, vector<int64> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptInt64Value)
        {
            value = ((MessageValue<vector<int64>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptUInt32Value(const string &key, const vector<uint32> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<uint32>>> message_value(new MessageValue<vector<uint32>>(Type_RptUInt32Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptUInt32Value(const string &key, vector<uint32> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptUInt32Value)
        {
            value = ((MessageValue<vector<uint32>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptUInt64Value(const string &key, const vector<uint64> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<uint64>>> message_value(new MessageValue<vector<uint64>>(Type_RptUInt64Value, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptUInt64Value(const string &key, vector<uint64> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptUInt64Value)
        {
            value = ((MessageValue<vector<uint64>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}


bool MessageData::SetRptDoubleValue(const string &key, const vector<double> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<double>>> message_value(new MessageValue<vector<double>>(Type_RptDoubleValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptDoubleValue(const string &key, vector<double> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptDoubleValue)
        {
            value = ((MessageValue<vector<double>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptFloatValue(const string &key, const vector<float> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<float>>> message_value(new MessageValue<vector<float>>(Type_RptFloatValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptFloatValue(const string &key, vector<float> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptFloatValue)
        {
            value = ((MessageValue<vector<float>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptBoolValue(const string &key, const vector<bool> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<bool>>> message_value(new MessageValue<vector<bool>>(Type_RptBoolValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptBoolValue(const string &key, vector<bool> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptBoolValue)
        {
            value = ((MessageValue<vector<bool>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptEnumValue(const string &key, const vector<int> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<int>>> message_value(new MessageValue<vector<int>>(Type_RptEnumValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptEnumValue(const string &key, vector<int> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptEnumValue)
        {
            value = ((MessageValue<vector<int>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptStringValue(const string &key, const vector<string> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<string>>> message_value(new MessageValue<vector<string>>(Type_RptStringValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptStringValue(const string &key, vector<string> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptStringValue)
        {
            value = ((MessageValue<vector<string>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

bool MessageData::SetRptMessageData(const string &key, const vector<MessageData> &value)
{
    if (key.empty())
    {
        return false;
    }
    
    shared_ptr<MessageValue<vector<MessageData>>> message_value(new MessageValue<vector<MessageData>>(Type_RptMessageDataValue, value));
    message_value_map_[key] = message_value;
    
    return true;
}

bool MessageData::GetRptMessageData(const string &key, vector<MessageData> &value) const
{
    if (key.empty())
    {
        return false;
    }
    
    MapMessageValue::const_iterator iter = message_value_map_.find(key);
    if (iter != message_value_map_.end())
    {
        if (iter->second.get() && iter->second->GetType() == Type_RptMessageDataValue)
        {
            value = ((MessageValue<vector<MessageData>>*)iter->second.get())->GetValue();
            return true;
        }
    }
    
    return false;
}

MapMessageValue& MessageData::GetMapMessageValue()
{
    return message_value_map_;
}