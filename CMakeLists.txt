cmake_minimum_required(VERSION 3.16)

project(Flashcards VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui Qml Network NetworkAuth)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appFlashcards
    main.cpp
)

qt_add_qml_module(appFlashcards
    URI Flashcards
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES authorization/SignInForm.qml
        QML_FILES components/MyButton.qml
        RESOURCES resources.qrc
        QML_FILES
        RESOURCES android/AndroidManifest.xml android/build.gradle android/res/values/libs.xml android/res/xml/qtprovider_paths.xml android/gradle/wrapper/gradle-wrapper.jar android/gradle/wrapper/gradle-wrapper.properties android/gradle.properties android/gradlew android/gradlew.bat
        QML_FILES dashboard/dashboard.qml
        SOURCES
        SOURCES controllers/session.h controllers/session.cpp
        SOURCES services/authservice.h services/authservice.cpp
        SOURCES controllers/logincontroller.h controllers/logincontroller.cpp
        SOURCES
        SOURCES controllers/firebasecontroller.h controllers/firebasecontroller.cpp
        SOURCES services/firebaseservice.h services/firebaseservice.cpp
        SOURCES services/androidauthservice.h services/androidauthservice.cpp
        SOURCES services/authjni.cpp
        QML_FILES components/AppDrawer.qml
        QML_FILES components/AppHeader.qml
        QML_FILES components/+android/AppDrawer.qml
        QML_FILES components/+android/AppHeader.qml
        QML_FILES components/DrawerButton.qml
        QML_FILES dashboard/+android/dashboard.qml
        QML_FILES components/TileSet.qml
        QML_FILES flashcards/FlashcardsDashboard.qml
        SOURCES models/tilesetmodel.h models/tilesetmodel.cpp
        SOURCES models/objects/tilesetobject.h models/objects/tilesetobject.cpp
        RESOURCES
        QML_FILES flashcards/SetCreator.qml
        QML_FILES components/CardInput.qml
        QML_FILES components/CustomInput.qml
        QML_FILES components/MyTextArea.qml
        SOURCES models/objects/cardobject.h models/objects/cardobject.cpp
        SOURCES models/cardmodel.h models/cardmodel.cpp
        QML_FILES components/DeleteDialog.qml
        QML_FILES components/Alert.qml
        QML_FILES flashcards/LearningMode.qml
        QML_FILES flashcards/Card.qml
        QML_FILES flashcards/+android/FlashcardsDashboard.qml
        QML_FILES components/+android/TileSet.qml
        QML_FILES flashcards/+android/SetCreator.qml
        QML_FILES flashcards/+android/LearningMode.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFlashcards PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFlashcards
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android
)

target_link_libraries(appFlashcards
    PRIVATE Qt6::Quick
    Qt6::Network
    Qt6::NetworkAuth
)

include(GNUInstallDirs)
install(TARGETS appFlashcards
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


if(ANDROID)
  include(FetchContent)

  FetchContent_Declare(android_openssl
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/KDAB/android_openssl/archive/refs/heads/master.zip
  )

  FetchContent_MakeAvailable(android_openssl)
  include(${android_openssl_SOURCE_DIR}/android_openssl.cmake)

  add_android_openssl_libraries(appFlashcards)
endif()

