cmake_minimum_required(VERSION 3.5)

project(shop VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(shop
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        loginwithregister.h loginwithregister.cpp loginwithregister.ui
        database.h database.cpp
        resources.qrc
        user.h user.cpp
        accoutpage.h accoutpage.cpp accoutpage.ui
        productlistelement.h productlistelement.cpp productlistelement.ui
        product.h product.cpp
        addproductform.h addproductform.cpp addproductform.ui
        multipictures.h multipictures.cpp multipictures.ui
        productdetailpage.h productdetailpage.cpp productdetailpage.ui
        shoppingcart.h shoppingcart.cpp shoppingcart.ui
        finalizetransaction.h finalizetransaction.cpp finalizetransaction.ui
        editpersonaldataform.h editpersonaldataform.cpp editpersonaldataform.ui
        focuswatcher.h focuswatcher.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET shop APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(shop SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(shop
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(shop PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.shop)
endif()
set_target_properties(shop PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS shop
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(shop)
endif()
