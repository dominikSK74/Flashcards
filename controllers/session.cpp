#include "session.h"

Session::Session(QObject *parent)
    : QObject{parent}
{

}

void Session::setToken(const QString &token) {
    m_token = token;
}

QString Session::token() const {
    return m_token;
}

void Session::setUsername(const QString &username) {
    m_username = username;
    emit usernameChanged();
}

QString Session::username() const {
    return m_username;
}

void Session::setAvatarUrl(const QString &avatarUrl) {
    m_avatarUrl = avatarUrl;
    emit avatarUrlChanged();
}

QString Session::avatarUrl() const {
    return m_avatarUrl;
}
