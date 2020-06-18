TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        args.c \
        filter_image.c \
        harris_image.c \
        load_image.c \
        main.c \
        matrix.c \
        panorama_image.c \
        process_image.c \
        resize_image.c \
        test.c

HEADERS += \
    args.h \
    image.h \
    image_math.h \
    matrix.h \
    stb_image.h \
    stb_image_write.h \
    test.h
