#include <Controller.h>
#include <cmath>
#include <regex>

TempController::TempController(TempModel *model, QObject *parent):QObject(parent), model(model){};

std::regex doubleRegEx("^-?\\d+(\\.\\d+)?$");

void TempController::cTemp_handler(QString str){
    model->setMsg("");
    std::string stdStr = str.toStdString();

    if(std::regex_match(stdStr, doubleRegEx)){
        double cT = stod(stdStr);
        if(cT >= -273.16){
            model->setCTemp(cT);
            model->setKTemp(std::round(100 * (cT + 273.16))/100);
            model->setFTemp(std::round(100 * (32 + 9 * cT / 5))/100);
            emit model->fTempChanged();
            emit model->kTempChanged();
        }
        else{
            model->setMsg("Incorrect value");
        }
    }
    else{
        model->setMsg("Incorrect format");
    }
    emit model->msgChanged();
}

void TempController::fTemp_handler(QString str){
    model->setMsg("");
    std::string stdStr = str.toStdString();

    if(std::regex_match(stdStr, doubleRegEx)){
        double fT = stod(stdStr);
        if(fT >= -459.67){
            model->setFTemp(fT);
            model->setCTemp(std::round(100 * (5 * (fT - 32) / 9))/100);
            model->setKTemp(std::round(100 * (model->getCTemp() + 273.16))/100);
            emit model->cTempChanged();
            emit model->kTempChanged();
        }
        else{
            model->setMsg("Incorrect value");
        }
    }
    else{
        model->setMsg("Incorrect format");
    }
    emit model->msgChanged();
}

void TempController::kTemp_handler(QString str){
    model->setMsg("");
    std::string stdStr = str.toStdString();

    if(std::regex_match(stdStr, doubleRegEx)){
        double kT = stod(stdStr);
        if(kT >= 0){
            model->setKTemp(kT);
            model->setCTemp(std::round(100 * (kT - 273.16))/100);
            model->setFTemp(std::round(100 * ( 32 + 9 * model->getCTemp()  / 5))/100);
            emit model->fTempChanged();
            emit model->cTempChanged();
        }
        else{
            model->setMsg("Incorrect value");
        }
    }
    else{
        model->setMsg("Incorrect format");
    }
    emit model->msgChanged();
}
