QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    passager.cpp \
    qstream.cpp \
    table.cpp \
    trip.cpp \
    trip_dialog.cpp

HEADERS += \
    file_dialog.h \
    mainwindow.h \
    passager.h \
    qstream.h \
    table.h \
    trip.h \
    trip_dialog.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
