#include <Model.h>

TempModel::TempModel(double cT, QObject *parent) : QObject(parent){
    this->cTemp = cT;
    this->kTemp = cT + 273.16;
    this->fTemp = 32 + 9*cT/5;
}

double TempModel::getCTemp(){
    return this->cTemp;
}

double TempModel::getFTemp(){
    return this->fTemp;
}

double TempModel::getKTemp(){
    return this->kTemp;
}

void TempModel::setCTemp(double val){
    this->cTemp = val;
}

void TempModel::setFTemp(double val){
    this->fTemp = val;
}

void TempModel::setKTemp(double val){
    this->kTemp = val;
}
