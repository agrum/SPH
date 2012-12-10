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

OTHER_FILES += \
    shaders/illumination.fs \
    shaders/opaque.vs \
    shaders/opaque.fs \
    shaders/illumination.vs \
    shaders/particle/velocityUpdate.vs \
    shaders/particle/velocityUpdate.fs \
    shaders/particle/positionUpdate.vs \
    shaders/particle/positionUpdate.fs \
    shaders/particle/particleDraw.vs \
    shaders/particle/particleDraw.fs \
    shaders/particle/dttComputation.vs \
    shaders/particle/dttComputation.fs \
    meshes/sphere.obj \
    meshes/sphere.mtl \
    meshes/cube.obj \
    meshes/cube.mtl \
    meshes/img/white.jpg
