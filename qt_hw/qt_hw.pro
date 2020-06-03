TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        args.c \
        filter_image.c \
        image_math.c \
        load_image.c \
        main.c \
        process_image.c \
        resize_image.c

HEADERS += \
    args.h \
    image.h \
    image_math.h \
    stb_image.h \
    stb_image_write.h
