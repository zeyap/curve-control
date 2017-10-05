QT += widgets core gui

HEADERS       = window.h \
    renderarea.h \
    spline.h
SOURCES       = main.cpp window.cpp \
    renderarea.cpp \
    spline.cpp
RESOURCES += basicdrawing.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/painting/basicdrawing
INSTALLS += target


