QT       += core gui widgets network

TARGET = obs
TEMPLATE = app

INCLUDEPATH += ../libobs obs-frontend-api ../dependencies2015/win64/include

HEADERS += \
    adv-audio-control.hpp \
    audio-encoders.hpp \
    crash-report.hpp \
    display-helpers.hpp \
    double-slider.hpp \
    focus-list.hpp \
    hotkey-edit.hpp \
    item-widget-helpers.hpp \
    locked-checkbox.hpp \
    menu-button.hpp \
    mute-checkbox.hpp \
    obs-app.hpp \
    platform.hpp \
    properties-view.hpp \
    properties-view.moc.hpp \
    qt-display.hpp \
    qt-wrappers.hpp \
    remote-text.hpp \
    slider-absoluteset-style.hpp \
    source-label.hpp \
    source-list-widget.hpp \
    vertical-scroll-area.hpp \
    visibility-checkbox.hpp \
    visibility-item-widget.hpp \
    volume-control.hpp \
    window-basic-adv-audio.hpp \
    window-basic-auto-config.hpp \
    window-basic-filters.hpp \
    window-basic-interaction.hpp \
    window-basic-main.hpp \
    window-basic-main-outputs.hpp \
    window-basic-preview.hpp \
    window-basic-properties.hpp \
    window-basic-settings.hpp \
    window-basic-source-select.hpp \
    window-basic-stats.hpp \
    window-basic-status-bar.hpp \
    window-basic-transform.hpp \
    window-license-agreement.hpp \
    window-log-reply.hpp \
    window-main.hpp \
    window-namedialog.hpp \
    window-projector.hpp \
    window-remux.hpp \
    interface.h

SOURCES += \
    adv-audio-control.cpp \
    api-interface.cpp \
    audio-encoders.cpp \
    crash-report.cpp \
    double-slider.cpp \
    focus-list.cpp \
    hotkey-edit.cpp \
    item-widget-helpers.cpp \
    locked-checkbox.cpp \
    menu-button.cpp \
    obs-app.cpp \
    platform-windows.cpp \
    platform-x11.cpp \
    properties-view.cpp \
    qt-display.cpp \
    qt-wrappers.cpp \
    remote-text.cpp \
    slider-absoluteset-style.cpp \
    source-label.cpp \
    source-list-widget.cpp \
    vertical-scroll-area.cpp \
    visibility-checkbox.cpp \
    visibility-item-widget.cpp \
    volume-control.cpp \
    window-basic-adv-audio.cpp \
    window-basic-auto-config.cpp \
    window-basic-auto-config-test.cpp \
    window-basic-filters.cpp \
    window-basic-interaction.cpp \
    window-basic-main.cpp \
    window-basic-main-dropfiles.cpp \
    window-basic-main-outputs.cpp \
    window-basic-main-profiles.cpp \
    window-basic-main-scene-collections.cpp \
    window-basic-main-transitions.cpp \
    window-basic-preview.cpp \
    window-basic-properties.cpp \
    window-basic-settings.cpp \
    window-basic-source-select.cpp \
    window-basic-stats.cpp \
    window-basic-status-bar.cpp \
    window-basic-transform.cpp \
    window-license-agreement.cpp \
    window-log-reply.cpp \
    window-namedialog.cpp \
    window-projector.cpp \
    window-remux.cpp \
    interface.cpp

RESOURCES += \
    forms/obs.qrc

FORMS += \
    forms/AutoConfigFinishPage.ui \
    forms/AutoConfigStartPage.ui \
    forms/AutoConfigStreamPage.ui \
    forms/AutoConfigTestPage.ui \
    forms/AutoConfigVideoPage.ui \
    forms/NameDialog.ui \
    forms/OBSBasic.ui \
    forms/OBSBasicFilters.ui \
    forms/OBSBasicInteraction.ui \
    forms/OBSBasicSettings.ui \
    forms/OBSBasicSourceSelect.ui \
    forms/OBSBasicTransform.ui \
    forms/OBSLicenseAgreement.ui \
    forms/OBSLogReply.ui \
    forms/OBSRemux.ui \
    forms/OBSUpdate.ui
