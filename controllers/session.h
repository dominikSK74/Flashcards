#ifndef SESSION_H
#define SESSION_H

#include <QObject>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged);
    Q_PROPERTY(bool authenticated READ authenticated NOTIFY authenticatedChanged);
public:
    explicit Session(QObject *parent = nullptr);
    void setToken(const QString &token);
    QString token() const;
    bool authenticated() const;

signals:
    void tokenChanged();
    void authenticatedChanged();

private:
    QString m_token;
};

#endif // SESSION_H
