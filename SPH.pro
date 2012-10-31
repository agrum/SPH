TEMPLATE = app
TARGET = SPH
QT += core \
    opengl \
    xml
INCLUDEPATH += /usr/include/GL \
    /home/agrum/Workspace/lemonGL/include
LIBS += -L/usr/include/GL \
	-L/home/agrum/Workspace/lemonGL/lib \
	-llemonGL \
    -lGLEW \
    -lGLU \
    -lGL
HEADERS += src/CIFBox.h \
    src/CIFParticleObj.h \
    src/CIFWidget.h
SOURCES += src/CIFBox.cpp \
    src/CIFParticleObj.cpp \
    src/CIFWidget.cpp \
    main.cpp
FORMS += 
RESOURCES += 
