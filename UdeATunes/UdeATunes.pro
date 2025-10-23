TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    cancion.cpp \
    Usuario.cpp\
    Artista.cpp\
    Anuncio.cpp\
    SistemaAnuncios.cpp\
    listacanciones.cpp \
    listafavoritos.cpp \
        main.cpp\
    sistema.cpp

HEADERS += \
    album.h \
    cancion.h \
    creditos.h \
    Usuario.h\
    Artista.h\
    Anuncio.h\
    SistemaAnuncios.h\
    listacanciones.h \
    listafavoritos.h \
    sistema.h
