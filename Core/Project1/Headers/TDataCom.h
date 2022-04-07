#pragma once

enum DataErrors{
    DataOk = 0,
    DataError = -1
};

class TDataCom{
protected:
    int RetCode;
    void SetRetCode(int _RetCode) {this->RetCode = _RetCode;};
    TDataCom():RetCode(DataOk){};
    virtual ~TDataCom() = default;
    int GetRetCode(){
        int tmp = RetCode;
        RetCode = DataOk;
        return tmp;
    };
};
