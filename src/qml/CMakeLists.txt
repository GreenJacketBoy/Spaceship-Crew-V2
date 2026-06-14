# Note to myself and others learning :
# The URI must be unique, but it should also reflects the project structure
# such that you can trace back the CMakeListFile.txt that directly called
# the one here, with '/' replaced by '.' (From my understanding, it is not
# mandatory, but it "helps tooling"). 
# "src" seem to be omitted from the URI by convention.

# https://doc.qt.io/qt-6/qt-add-qml-module.html

qt_add_qml_module(SpaceshipCrewV2_Module
    URI qml.main
    QML_FILES 
        main.qml
)
