#include "session.h"

Session::Session(QObject *parent)
    : QObject{parent}
{

}

void Session::setToken(const QString &token) {
    m_token = token;
}

bool Session::authenticated() const {
    return !(m_token.isEmpty());
}

QString Session::token() const {
    return m_token;
}
