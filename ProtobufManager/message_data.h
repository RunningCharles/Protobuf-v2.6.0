//
//  message_data.h
//
//  Created by Charles on 15/7/9.
//  Copyright (c) 2015年 Charles. All rights reserved.
//

#ifndef __message_data__
#define __message_data__

#include <vector>
#include <string>
#include <map>
#include <memory>

#include "message_data_def.h"

using namespace std;

class MessageData;

typedef enum enumMessageValueType
{
    Type_Unknown              = 0,
    Type_Int32Value           = 1,
    Type_Int64Value           = 2,
    Type_UInt32Value          = 3,
    Type_UInt64Value          = 4,
    Type_DoubleValue          = 5,
    Type_FloatValue           = 6,
    Type_BoolValue            = 7,
    Type_EnumValue            = 8,
    Type_StringValue          = 9,
    Type_MessageDataValue     = 10,
    Type_RptInt32Value        = 11,
    Type_RptInt64Value        = 12,
    Type_RptUInt32Value       = 13,
    Type_RptUInt64Value       = 14,
    Type_RptDoubleValue       = 15,
    Type_RptFloatValue        = 16,
    Type_RptBoolValue         = 17,
    Type_RptEnumValue         = 18,
    Type_RptStringValue       = 19,
    Type_RptMessageDataValue  = 20,
}MessageValueType;

class MessageValueBase
{
public:
    MessageValueBase(MessageValueType type);
    ~MessageValueBase();
    MessageValueType GetType();
    
private:
    MessageValueType message_value_type_;
};

template<typename Type>
class MessageValue:public MessageValueBase
{
public:
    MessageValue(MessageValueType type, Type value);
    ~MessageValue();
    Type GetValue();
    
private:
    Type message_value_;
};


typedef map<string, shared_ptr<MessageValueBase>> MapMessageValue;

class MessageData
{
public:
    MessageData();
    MessageData(const MessageData &data);
    ~MessageData();
    
public:
    bool SetInt32Value(const string &key, int32 value);
    bool GetInt32Value(const string &key, int32 &value) const;
    
    bool SetInt64Value(const string &key, int64 value);
    bool GetInt64Value(const string &key, int64 &value) const;
    
    bool SetUInt32Value(const string &key, uint32 value);
    bool GetUInt32Value(const string &key, uint32 &value) const;
    
    bool SetUInt64Value(const string &key, uint64 value);
    bool GetUInt64Value(const string &key, uint64 &value) const;
    
    bool SetDoubleValue(const string &key, double value);
    bool GetDoubleValue(const string &key, double &value) const;
    
    bool SetFloatValue(const string &key, float value);
    bool GetFloatValue(const string &key, float &value) const;
    
    bool SetBoolValue(const string &key, bool value);
    bool GetBoolValue(const string &key, bool &value) const;
    
    bool SetEnumValue(const string &key, int value);
    bool GetEnumValue(const string &key, int &value) const;
    
    bool SetStringValue(const string &key, const string &value);
    bool GetStringValue(const string &key, string &value) const;
    
    bool SetMessageDataValue(const string &key, const MessageData &data);
    bool GetMessageDataValue(const string &key, MessageData &data) const;
    
    bool SetRptInt32Value(const string &key, const vector<int32> &value);
    bool GetRptInt32Value(const string &key, vector<int32> &value) const;
    
    bool SetRptInt64Value(const string &key, const vector<int64> &value);
    bool GetRptInt64Value(const string &key, vector<int64> &value) const;
    
    bool SetRptUInt32Value(const string &key, const vector<uint32> &value);
    bool GetRptUInt32Value(const string &key, vector<uint32> &value) const;
    
    bool SetRptUInt64Value(const string &key, const vector<uint64> &value);
    bool GetRptUInt64Value(const string &key, vector<uint64> &value) const;
    
    bool SetRptDoubleValue(const string &key, const vector<double> &value);
    bool GetRptDoubleValue(const string &key, vector<double> &value) const;
    
    bool SetRptFloatValue(const string &key, const vector<float> &value);
    bool GetRptFloatValue(const string &key, vector<float> &value) const;
    
    bool SetRptBoolValue(const string &key, const vector<bool> &value);
    bool GetRptBoolValue(const string &key, vector<bool> &value) const;
    
    bool SetRptEnumValue(const string &key, const vector<int> &value);
    bool GetRptEnumValue(const string &key, vector<int> &value) const;
    
    bool SetRptStringValue(const string &key, const vector<string> &value);
    bool GetRptStringValue(const string &key, vector<string> &value) const;
    
    bool SetRptMessageData(const string &key, const vector<MessageData> &value);
    bool GetRptMessageData(const string &key, vector<MessageData> &value) const;
    
public:
    MapMessageValue& GetMapMessageValue();
    
private:
    MapMessageValue message_value_map_;
};

#endif /* defined(__message_data__) */
