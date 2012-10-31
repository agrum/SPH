TEMPLATE = app
TARGET = SPH
QT += core \
    opengl \
    xml
INCLUDEPATH += /usr/include/GL
LIBS += -L/usr/include/GL \
    -lGLEW \
    -lGLU \
    -lGL
HEADERS += src/inFire/core/CIFBox.h \
	src/inFire/core/CIFParticleObj.h \
    src/meltingDown/object/CFace.h \
    src/meltingDown/object/CMesh.h \
    src/meltingDown/object/CMeshMngr.h \
    src/meltingDown/object/CObject.h \
    src/meltingDown/object/CVA.h \
    src/meltingDown/texture/CMaterial.h \
    src/meltingDown/texture/CMaterialMngr.h \
    src/meltingDown/CMeltingDown.h \
    src/inFire/core/CIFWidget.h \
    src/meltingDown/mvp/CLight.h \
    src/meltingDown/mvp/CMVP.h \
    src/meltingDown/shader/CProgram.h \
    src/meltingDown/texture/CTexture.h \
    src/warmingUp/utils/CReference.h \
    src/warmingUp/utils/CDom.h \
    src/warmingUp/utils/CLink.h \
    src/warmingUp/utils/CParticle.h \
    src/warmingUp/utils/CTagNames.h \
    src/warmingUp/core/CPopulation.h \
    src/inFire/utils/CTagNames.h \
    src/warmingUp/CWarmingUp.h \
    src/inFire/CInFire.h \
    src/warmingUp/core/CWorld.h \
    src/warmingUp/thread/CComputer.h \
    src/warmingUp/thread/CDocker.h \
    src/warmingUp/thread/CLinker.h \
    src/warmingUp/thread/CPopper.h \
    src/warmingUp/thread/CRoutine.h \
    src/warmingUp/thread/CThread.h \
    src/warmingUp/utils/CList.h \
    src/warmingUp/utils/CMatrix.h
SOURCES += src/inFire/core/CIFBox.cpp \
	src/inFire/core/CIFParticleObj.cpp \
    src/meltingDown/object/CFace.cpp \
    src/meltingDown/object/CMesh.cpp \
    src/meltingDown/object/CMeshMngr.cpp \
    src/meltingDown/object/CObject.cpp \
    src/meltingDown/object/CVA.cpp \
    src/meltingDown/texture/CMaterial.cpp \
    src/meltingDown/texture/CMaterialMngr.cpp \
    src/inFire/core/CIFWidget.cpp \
    src/meltingDown/mvp/CLight.cpp \
    src/meltingDown/mvp/CMVP.cpp \
    src/meltingDown/shader/CProgram.cpp \
    src/meltingDown/texture/CTexture.cpp \
    src/warmingUp/utils/CReference.cpp \
    src/warmingUp/utils/CLink.cpp \
    src/warmingUp/utils/CParticle.cpp \
    src/warmingUp/core/CWorld.cpp \
    src/warmingUp/thread/CComputer.cpp \
    src/warmingUp/thread/CDocker.cpp \
    src/warmingUp/thread/CLinker.cpp \
    src/warmingUp/thread/CPopper.cpp \
    src/warmingUp/thread/CRoutine.cpp \
    src/warmingUp/thread/CThread.cpp \
    src/warmingUp/utils/CMatrix.cpp \
    main.cpp
FORMS += 
RESOURCES += 
