cmake_minimum_required(VERSION 3.22)
project(Bernie)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6Widgets REQUIRED)

add_executable(Bernie
        ./Core/RBBSTree.h
        ./Core/RBBSTree.cpp
        ./Models/Account.cpp
        ./Models/Account.h
        ./Models/Contact.cpp
        ./Models/Contact.h
        ./Models/CreditCard.cpp
        ./Models/CreditCard.h
        ./Models/CryptoWallet.cpp
        ./Models/CryptoWallet.h
        ./Models/Date.cpp
        ./Models/Date.h
        ./Models/Note.cpp
        ./Models/Note.h
        ./Models/SerializableObject.cpp
        ./Models/SerializableObject.h
        ./Models/Telephone.cpp
        ./Models/Telephone.h
        ./Core/EncDec_File.cpp
        ./Core/EncDec_File.h
        ./Models/Vault.cpp
        ./Models/Vault.h
        main.cpp
        resources.qrc
        Views/MainWindow.cpp
        Views/MainWindow.h
        Views/LandingPage.cpp
        Views/LandingPage.h
        Views/CreateDBPage.cpp
        Views/CreateDBPage.h
        Views/SelectDBPage.cpp
        Views/SelectDBPage.h
        Views/HomePage.cpp
        Views/HomePage.h
        Views/Visitors/VisitorListItem.cpp
        Views/Visitors/VisitorListItem.h
        Views/Visitors/SerializableObjectsVisitor.h
        Views/Visitors/ListCardItem.cpp Views/Visitors/ListCardItem.h Views/Visitors/SerializableObjectsVisitor.cpp Views/DBSelectedPage.cpp Views/DBSelectedPage.h Views/Components/MenuButton.cpp Views/Components/MenuButton.h Views/TypeSelectionPage.cpp Views/TypeSelectionPage.h Views/Components/TypeSelectionButton.cpp Views/Components/TypeSelectionButton.h Views/Visitors/VisitorManageItem.cpp Views/Visitors/VisitorManageItem.h Views/SerializableObjectPages/PagesInterface.h Views/SerializableObjectPages/PagesInterface.cpp Views/SerializableObjectPages/AccountPage.cpp Views/SerializableObjectPages/AccountPage.h)

target_link_libraries(Bernie Qt6::Widgets)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
