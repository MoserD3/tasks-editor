
HEADERS += \
    db-filter.h \
    db.h \
    editor.h \
    factory.h \
    ka-model.h \
    lst-model.h \
    resource.h \
    settings.h \
    tasks-editor.h \
    tasks-model.h \
    val3.h

SOURCES += \
    db.cpp \
    editor.cpp \
    ka-model.cpp \
    lst-model.cpp \
    main.cpp \
    settings.cpp \
    tasks-editor.cpp \
    tasks-model.cpp

FORMS += \
    editor.ui \
    settings.ui \
    tasks-editor.ui

HEADERS += \
    tasks/apo.h \
    tasks/call-adr.h \
    tasks/flags.h \
    tasks/free-access.h \
    tasks/freq-pk.h \
    tasks/kpr2.h \
    tasks/ku-params.h \
    tasks/ms-freq.h \
    tasks/ok-freq.h \
    tasks/orc.h \
    tasks/regions.h \
    tasks/rko.h \
    tasks/self-noise.h \
    tasks/tmi.h \
    tasks/turnoff-ms.h \
    tasks/vm-count.h

SOURCES += \
    tasks/apo.cpp \
    tasks/call-adr.cpp \
    tasks/flags.cpp \
    tasks/free-access.cpp \
    tasks/freq-pk.cpp \
    tasks/kpr2.cpp \
    tasks/ku-params.cpp \
    tasks/ms-freq.cpp \
    tasks/ok-freq.cpp \
    tasks/orc.cpp \
    tasks/regions.cpp \
    tasks/rko.cpp \
    tasks/self-noise.cpp \
    tasks/tmi.cpp \
    tasks/turnoff-ms.cpp \
    tasks/vm-count.cpp

FORMS += \
    tasks/apo.ui \
    tasks/call-adr.ui \
    tasks/flags.ui \
    tasks/free-access.ui \
    tasks/freq-pk.ui \
    tasks/kpr2.ui \
    tasks/ku-params.ui \
    tasks/ms-freq.ui \
    tasks/ok-freq.ui \
    tasks/orc.ui \
    tasks/regions.ui \
    tasks/rko.ui \
    tasks/self-noise.ui \
    tasks/tmi.ui \
    tasks/turnoff-ms.ui \
    tasks/vm-count.ui

TRANSLATIONS += tasks-editor_ru.ts

RESOURCES += tasks-editor.qrc
