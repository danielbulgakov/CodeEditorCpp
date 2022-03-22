#pragma once

class TDataValue{
public:
    virtual TDataValue* GetCopy() = 0;
    ~TDataValue(){};

};

typedef TDataValue* PTDataValue;