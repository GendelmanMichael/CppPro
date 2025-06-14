#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class TempModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cTemp READ getCTemp WRITE setCTemp NOTIFY cTempChanged)
    Q_PROPERTY(double fTemp READ getFTemp WRITE setFTemp NOTIFY fTempChanged)
    Q_PROPERTY(double kTemp READ getKTemp WRITE setKTemp NOTIFY kTempChanged)

public:
    explicit TempModel(double cT, QObject *parent = nullptr);
    double getCTemp();
    void setCTemp(double val);
    double getFTemp();
    void setFTemp(double val);
    double getKTemp();
    void setKTemp(double val);

signals:
    void cTempChanged();
    void fTempChanged();
    void kTempChanged();

private:
    double cTemp;
    double fTemp;
    double kTemp;
};

#endif // MODEL_H
