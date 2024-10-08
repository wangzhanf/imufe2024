QT       += core gui network
#   加载的模块   必选   core， gui  ，如果 开发浏览器  webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# 使用的C++版本，  使用LTS版
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mywidget.cpp

HEADERS += \
    mywidget.h

FORMS += \
    mywidget.ui

#文件列表不建议手工修改 ，  qmake构建工具使用该文件列表
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
