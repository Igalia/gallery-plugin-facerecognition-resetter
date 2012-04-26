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

# include($$[QT_INSTALL_DATA]/mkspecs/features/meegotouch_defines.prf)
# meegotouch.files = conf/libgallery_plugin_facerecognition_resetter.css
# meegotouch.path = $${M_THEME_DIR}/base/meegotouch/libgallery_plugin_facerecognition_resetter/style

# editicon.files = data/icon-m-image-edit-tilt-shift.png
# editicon.path = /usr/share/themes/base/meegotouch/icons

# icon.files = data/icon-l-tilt-shift.png
# icon.files = /usr/share/icons/hicolor/64x64/apps/

INSTALLS += target # meegotouch editicon icon
