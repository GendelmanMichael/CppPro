#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Model.h>
#include <QObject>

class TempController : public QObject{
    Q_OBJECT
public:
    explicit TempController(TempModel* model, QObject *parent = nullptr);
    Q_INVOKABLE void cTemp_handler(double cT);
    Q_INVOKABLE void fTemp_handler(double fT);
    Q_INVOKABLE void kTemp_handler(double kT);

private:
    TempModel* model;
};

#endif // CONTROLLER_H
