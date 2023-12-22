cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(RaspberryPiApp LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick LinguistTools QuickControls2 )

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

qt_add_executable(RaspberryPiApp src/main.cpp
    ImagesResources.qrc
    translations.qrc
)

qt_add_translations(RaspberryPiApp
    RESOURCE_PREFIX /qt/qml/translated/i18n
    TS_FILES
        i18n/base.ts
        i18n/qml_en.ts
        i18n/qml_fr.ts
)

qt_add_resources(RaspberryPiApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

qt_add_resources(RaspberryPiApp "ImagesResources"
    PREFIX "/"
    FILES
        "assets/svgIcons/edit.svg"
        "assets/svgIcons/payments.svg"
        "assets/svgIcons/shopping_cart.svg"
        "assets/svgIcons/fr_flag.svg"
        "assets/svgIcons/en_flag.svg"
)

set(TS_FILES
        i18n/base.ts
        i18n/qml_en.ts
        i18n/qml_fr.ts
)

target_link_libraries(RaspberryPiApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS RaspberryPiApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")

