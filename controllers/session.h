#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QSettings>

class Session : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ token NOTIFY tokenChanged);
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged);
    Q_PROPERTY(QString avatarUrl READ avatarUrl NOTIFY avatarUrlChanged);
    Q_PROPERTY(bool loggedIn READ loggedIn NOTIFY loggedInChanged)
public:
    explicit Session(QObject *parent = nullptr);
    void setToken(const QString &token);
    QString token() const;

    void setUsername(const QString &username);
    QString username() const;

    void setAvatarUrl(const QString &avatarUrl);
    QString avatarUrl() const;

    bool loggedIn() const;

signals:
    void tokenChanged();
    void usernameChanged();
    void avatarUrlChanged();
    void loggedInChanged();

private:
    QString m_token;
    QString m_username;
    QString m_avatarUrl;
    QSettings m_settings;
};

#endif // SESSION_H
