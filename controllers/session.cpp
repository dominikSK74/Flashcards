#include "session.h"
#include <QDir>

Session::Session(QObject *parent)
    : QObject{parent}, m_settings(QSettings("userdata.ini", QSettings::IniFormat))
{
    if(!(m_settings.value("token").toString().isEmpty())){
        setToken(m_settings.value("token").toString());
        setUsername(m_settings.value("username").toString());
        setAvatarUrl(m_settings.value("avatarUrl").toString());
    }
}

void Session::setToken(const QString &token) {
    m_token = token;
    QSettings settings("userdata.ini", QSettings::IniFormat);
    settings.setValue("token", token);
}

QString Session::token() const {
    return m_token;
}

void Session::setUsername(const QString &username) {
    m_username = username;
    QSettings settings("userdata.ini", QSettings::IniFormat);
    settings.setValue("username", username);
    emit usernameChanged();
}

QString Session::username() const {
    return m_username;
}

void Session::setAvatarUrl(const QString &avatarUrl) {
    m_avatarUrl = avatarUrl;
    QSettings settings("userdata.ini", QSettings::IniFormat);
    settings.setValue("avatarUrl", avatarUrl);
    emit avatarUrlChanged();
}

QString Session::avatarUrl() const {
    return m_avatarUrl;
}

bool Session::loggedIn() const { return !m_token.isEmpty(); }
