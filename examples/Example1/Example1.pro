QT -= gui


#add library, we add the code straight with the application, as it uses MPL licence you are allowed to do this.
include($$PWD/../../StellarQtSDK.pri)


#add openssl library, for other platforms you will have to link the proper library.
windows {
    LIBS += -L$$PWD/../OpenSSL/Win_x64/bin -llibssl-1_1-x64
    LIBS += -L$$PWD/../OpenSSL/Win_x64/bin -llibcrypto-1_1-x64
    #INCLUDEPATH += $PWD/../OpenSSL/Win_x64/include/
    #DEPENDPATH += $PWD/../OpenSSL/Win_x64/include/
}


CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target





