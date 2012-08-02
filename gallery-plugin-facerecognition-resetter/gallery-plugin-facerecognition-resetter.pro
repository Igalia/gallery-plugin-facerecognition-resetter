! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

TEMPLATE        = lib
QMAKE_LFLAGS   += -Wl,--as-needed
QMAKE_CXXFLAGS += -Werror -Wall -W
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -fvisibility=hidden
QMAKE_CXXFLAGS_DEBUG += -O0 -ggdb
CONFIG         += plugin \
                  meegotouch \
                  gallerycore \
                  quillimagefilter

contains( debug, yes ) {
    message( "Configuring for debug build ..." )
    CONFIG += debug warn_on
} else {
    message( "Configuring for release build ..." )
    CONFIG += release warn_on
    DEFINES += QT_NO_DEBUG_OUTPUT
}

# Relative path definitions for face recognition
DEFINES += GALLERYCORE_DATA_ROOT_DIR=\\\"$${GALLERYCORE_DATA_ROOT_DIR}\\\"
DEFINES += GALLERYCORE_DATA_DATA_DIR=\\\"$${GALLERYCORE_DATA_DATA_DIR}\\\"
DEFINES += FACE_RECOGNITION_DATABASE_FILENAME=\\\"$${FACE_RECOGNITION_DATABASE_FILENAME}\\\"
DEFINES += GALLERYCORE_USER=\\\"$${GALLERYCORE_USER}\\\"
DEFINES += GALLERYCORE_GROUP=\\\"$${GALLERYCORE_GROUP}\\\"
DEFINES += REGULAR_USER=\\\"$${REGULAR_USER}\\\"
DEFINES += REGULAR_GROUP=\\\"$${REGULAR_GROUP}\\\"

PACKAGEVERSION = $$system(head -n 1 ../debian/changelog | grep -o [0-9].[0-9].[0-9])
DEFINES += "PACKAGEVERSION=\\\"$$PACKAGEVERSION\\\""

HEADERS += gallery_plugin_facerecognition_resetter.h \
           gallery_plugin_facerecognition_resetter_p.h \
           gallery_plugin_facerecognition_resetter_widget.h \
           gallery_plugin_facerecognition_resetter_widget_p.h \
           gallery_plugin_facerecognition_resetter_about_widget.h

SOURCES += gallery_plugin_facerecognition_resetter.cpp \
           gallery_plugin_facerecognition_resetter_widget.cpp \
           gallery_plugin_facerecognition_resetter_about_widget.cpp

OTHER_FILES += \
           conf/libgallery_plugin_facerecognition_resetter.css

target.path = /usr/lib/gallery

include($$[QT_INSTALL_DATA]/mkspecs/features/meegotouch_defines.prf)
meegotouch.files = conf/libgallery-plugin-facerecognition-resetter.css
meegotouch.path = $${M_THEME_DIR}/base/meegotouch/libgallery-plugin-facerecognition-resetter/style

editicon.files = data/icon-m-image-edit-facerecognition-resetter.png
editicon.path = /usr/share/themes/base/meegotouch/icons

icon.files = data/icon-l-facerecognition-resetter.png
icon.path = /usr/share/icons/hicolor/64x64/apps/

INSTALLS += target \
            editicon \
            icon \
            meegotouch
