#include <Controller.h>
#include <cmath>

TempController::TempController(TempModel *model, QObject *parent):QObject(parent), model(model){};

void TempController::cTemp_handler(double cT){
    model->setCTemp(cT);
    model->setKTemp(std::round(100 * (cT + 273.16))/100);
    model->setFTemp(std::round(100 * (32 + 9 * cT / 5))/100);
    emit model->fTempChanged();
    emit model->kTempChanged();
}

void TempController::fTemp_handler(double fT){
    model->setFTemp(fT);
    model->setCTemp(std::round(100 * (5 * (fT - 32) / 9))/100);
    model->setKTemp(std::round(100 * (model->getCTemp() + 273.16))/100);
    emit model->cTempChanged();
    emit model->kTempChanged();
}

void TempController::kTemp_handler(double kT){
    model->setKTemp(kT);
    model->setCTemp(std::round(100 * (kT - 273.16))/100);
    model->setFTemp(std::round(100 * ( 32 + 9 * model->getCTemp()  / 5))/100);
    emit model->fTempChanged();
    emit model->cTempChanged();
}
