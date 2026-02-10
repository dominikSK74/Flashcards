#ifndef SESSION_H
#define SESSION_H

#include <QObject>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged);
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged);
    Q_PROPERTY(QString avatarUrl READ avatarUrl NOTIFY avatarUrlChanged);
public:
    explicit Session(QObject *parent = nullptr);
    void setToken(const QString &token);
    QString token() const;

    void setUsername(const QString &username);
    QString username() const;

    void setAvatarUrl(const QString &avatarUrl);
    QString avatarUrl() const;

signals:
    void tokenChanged();
    void usernameChanged();
    void avatarUrlChanged();

private:
    QString m_token;
    QString m_username;
    QString m_avatarUrl;
};

#endif // SESSION_H
