QT       += core gui \
            multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    button.cpp \
    card.cpp \
    cardpixmapitem.cpp \
    combination.cpp \
    engine.cpp \
    option.cpp \
    game.cpp \
    main.cpp \
    play.cpp \
    player.cpp \
    setting.cpp \
    welcome.cpp

HEADERS += \
    button.h \
    card.h \
    cardpixmapitem.h \
    combination.h \
    engine.h \
    game.h \
    option.h \
    play.h \
    player.h \
    setting.h \
    welcome.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
