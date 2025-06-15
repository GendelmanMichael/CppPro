#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Model.h>
#include <QObject>
#include <string>
#include <QString>

class TempController : public QObject{
    Q_OBJECT
public:
    explicit TempController(TempModel* model, QObject *parent = nullptr);
    Q_INVOKABLE void cTemp_handler(QString str);
    Q_INVOKABLE void fTemp_handler(QString str);
    Q_INVOKABLE void kTemp_handler(QString str);

private:
    TempModel* model;
};

#endif // CONTROLLER_H
