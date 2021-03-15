QT       += core gui sql axcontainer charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

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
    datadictionary.cpp \
    debt.cpp \
    grade.cpp \
    honor.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    punish.cpp \
    scholarship.cpp \
    studentinfo.cpp \
    user.cpp \
    usercontrol.cpp

HEADERS += \
    datadictionary.h \
    debt.h \
    grade.h \
    honor.h \
    login.h \
    mainwindow.h \
    punish.h \
    scholarship.h \
    studentinfo.h \
    user.h \
    usercontrol.h

FORMS += \
    datadictionary.ui \
    debt.ui \
    grade.ui \
    honor.ui \
    login.ui \
    mainwindow.ui \
    punish.ui \
    scholarship.ui \
    studentinfo.ui \
    user.ui \
    usercontrol.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
