#include <Controller.h>
#include <cmath>

double fixAndParse(QString str){
    return str.toDouble();
}

TempController::TempController(TempModel *model, QObject *parent):QObject(parent), model(model){};

void TempController::cTemp_handler(QString str){
    double cT = fixAndParse(str);
    model->setCTemp(cT);
    model->setKTemp(std::round(100 * (cT + 273.16))/100);
    model->setFTemp(std::round(100 * (32 + 9 * cT / 5))/100);
    emit model->fTempChanged();
    emit model->kTempChanged();
}

void TempController::fTemp_handler(QString str){
    double fT = fixAndParse(str);
    model->setFTemp(fT);
    model->setCTemp(std::round(100 * (5 * (fT - 32) / 9))/100);
    model->setKTemp(std::round(100 * (model->getCTemp() + 273.16))/100);
    emit model->cTempChanged();
    emit model->kTempChanged();
}

void TempController::kTemp_handler(QString str){
    double kT = fixAndParse(str);
    model->setKTemp(kT);
    model->setCTemp(std::round(100 * (kT - 273.16))/100);
    model->setFTemp(std::round(100 * ( 32 + 9 * model->getCTemp()  / 5))/100);
    emit model->fTempChanged();
    emit model->cTempChanged();
}
