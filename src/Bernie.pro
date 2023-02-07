QT += core widgets
CONFIG += c++11
TARGET = Bernie

RESOURCES += resources.qrc

INCLUDEPATH += src/
OBJECTS_DIR = build/qmake
RCC_DIR = build/qmake/rcc
MOC_DIR = build/qmake/moc
DESTDIR = ./

SOURCES += \
        ./Core/RBBSTree.cpp \
        ./Models/Account.cpp \
        ./Models/Contact.cpp \
        ./Models/CreditCard.cpp \
        ./Models/CreditCard.h \
        ./Models/CryptoWallet.cpp \
        ./Models/Date.cpp \
        ./Models/Note.cpp \
        ./Models/SerializableObject.cpp \
        ./Models/Telephone.cpp \
        ./Core/EncDec_File.cpp \
        ./Models/Vault.cpp \
        main.cpp \
        Views/MainWindow.cpp \
        Views/LandingPage.cpp \
        Views/CreateDBPage.cpp \
        Views/SelectDBPage.cpp \
        Views/HomePage.cpp \
        Views/Visitors/VisitorListItem.cpp \
        Views/Visitors/ListCardItem.cpp \
        Views/Visitors/SerializableObjectsVisitor.cpp \
        Views/DBSelectedPage.cpp \
        Views/Components/MenuButton.cpp \
        Views/TypeSelectionPage.cpp \
        Views/Components/TypeSelectionButton.cpp \
        Views/Visitors/VisitorManageItem.cpp \
        Views/SerializableObjectPages/PagesInterface.cpp \
        Views/SerializableObjectPages/AccountPage.cpp \
        Views/SerializableObjectPages/NotePage.cpp \
        Views/SerializableObjectPages/CryptoWalletPage.cpp \
        Views/SerializableObjectPages/CreditCardPage.cpp \
        Views/Components/DateComponent.cpp \
        Views/SerializableObjectPages/ContactPage.cpp \
        Views/SelectDBToRemove.cpp \
        Views/DBSelectedToRemovePage.cpp \

HEADERS += \
        ./Core/RBBSTree.h \
        ./Models/Account.h \
        ./Models/Contact.h \
        ./Models/CreditCard.h \
        ./Models/CryptoWallet.h \
        ./Models/Date.h \
        ./Models/Note.h \
        ./Models/SerializableObject.h \
        ./Models/Telephone.h \
        ./Core/EncDec_File.h \
        ./Models/Vault.h \
        Views/MainWindow.h \
        Views/LandingPage.h \
        Views/CreateDBPage.h \
        Views/SelectDBPage.h \
        Views/HomePage.h \
        Views/Visitors/VisitorListItem.h \
        Views/Visitors/SerializableObjectsVisitor.h \
        Views/Visitors/ListCardItem.h \
        Views/DBSelectedPage.h \
        Views/Components/MenuButton.h \
        Views/TypeSelectionPage.h \
        Views/Components/TypeSelectionButton.h \
        Views/Visitors/VisitorManageItem.h \
        Views/SerializableObjectPages/PagesInterface.h \
        Views/SerializableObjectPages/AccountPage.h \
        Views/SerializableObjectPages/NotePage.h \
        Views/SerializableObjectPages/CryptoWalletPage.h \
        Views/SerializableObjectPages/CreditCardPage.h \
        Views/Components/DateComponent.h \
        Views/SerializableObjectPages/ContactPage.h \
        Views/SelectDBToRemove.h \
        Views/DBSelectedToRemovePage.h
