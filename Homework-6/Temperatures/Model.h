#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QString>

class TempModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString msg READ getMsg WRITE setMsg NOTIFY msgChanged)
    Q_PROPERTY(double cTemp READ getCTemp WRITE setCTemp NOTIFY cTempChanged)
    Q_PROPERTY(double fTemp READ getFTemp WRITE setFTemp NOTIFY fTempChanged)
    Q_PROPERTY(double kTemp READ getKTemp WRITE setKTemp NOTIFY kTempChanged)

public:
    explicit TempModel(double cT, QObject *parent = nullptr);
    QString getMsg();
    void setMsg(QString val);
    double getCTemp();
    void setCTemp(double val);
    double getFTemp();
    void setFTemp(double val);
    double getKTemp();
    void setKTemp(double val);

signals:
    void msgChanged();
    void cTempChanged();
    void fTempChanged();
    void kTempChanged();

private:
    QString msg;
    double cTemp;
    double fTemp;
    double kTemp;
};

#endif // MODEL_H
