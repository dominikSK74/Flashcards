#include "services/androidauthservice.h"
#include <QMetaObject>
#include <QString>
#include <QDebug>

static AndroidAuthService* g_googleAuthInstance = nullptr;

// To ma być zawsze dostępne (żeby desktop build nie miał undefined reference)
void AndroidAuthService::setInstanceForJni(AndroidAuthService* inst)
{
    g_googleAuthInstance = inst;
}

#if defined(Q_OS_ANDROID)
#include <jni.h>

extern "C" JNIEXPORT void JNICALL
Java_pl_fc_auth_QtGoogleAuth_nativeOnGoogleIdToken(JNIEnv* env, jclass, jstring token)
{
    const char* utf = env->GetStringUTFChars(token, nullptr);
    QString idToken = QString::fromUtf8(utf);
    env->ReleaseStringUTFChars(token, utf);

    if (g_googleAuthInstance) {
        QMetaObject::invokeMethod(
            g_googleAuthInstance,
            [idToken]() {
                emit g_googleAuthInstance->idTokenReceived(idToken);
            },
            Qt::QueuedConnection
            );
    }
}

extern "C" JNIEXPORT void JNICALL
Java_pl_fc_auth_QtGoogleAuth_nativeOnGoogleError(JNIEnv* env, jclass, jstring message)
{
    const char* utf = env->GetStringUTFChars(message, nullptr);
    QString msg = QString::fromUtf8(utf);
    env->ReleaseStringUTFChars(message, utf);

    if (g_googleAuthInstance) {
        QMetaObject::invokeMethod(
            g_googleAuthInstance,
            [msg]() {
                emit g_googleAuthInstance->signInError(msg);
            },
            Qt::QueuedConnection
            );
    }
}

#endif // Q_OS_ANDROID
