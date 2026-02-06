cmake_minimum_required(VERSION 3.16)

project(Flashcards VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Gui Qml Network NetworkAuth )

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
