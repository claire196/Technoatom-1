TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    Tests/point2d_test.cpp \
    Tests/box2d_test.cpp \
    Tests/ray2d_test.cpp

HEADERS += \
    point2d.hpp \
    Src/box2d.hpp \
    Src/ray2d.hpp \
    Src/vector2d.hpp \
    space.h \
    space.hpp \
    vector2d.hpp \
    box2d.hpp \
    ray2d.hpp \
    gun.h \
    gun.hpp \
    alien.h \
    alien.hpp \
    bullett.h \
    bullett.hpp \
    obstacle.h \
    obstacle.hpp
