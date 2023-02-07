CONFIG += c++11
QT += core widgets
TARGET = Bernie

OBJECTS_DIR = build/qmake
RCC_DIR = build/qmake/rcc
MOC_DIR = build/qmake/moc
DESTDIR = ./

SOURCES += \
        ../Core/RBBSTree.cpp \
        ../Models/Account.cpp \
        ../Models/Contact.cpp \
        ../Models/CreditCard.cpp \
        ../Models/CryptoWallet.cpp \
        ../Models/Date.cpp \
        ../Models/Note.cpp \
        ../Models/SerializableObject.cpp \
        ../Models/Telephone.cpp \
        ../Core/EncDec_File.cpp \
        ../Models/Vault.cpp \
        TreeTestingFunctions.cpp \
        testing.cpp \
        SerializationTestingFunctions.cpp \
        EncDec_FileTestingFunctions.cpp \
        VaultTestingFunctions.cpp


HEADERS += \
        ../Core/RBBSTree.h \
        ../Models/Account.h \
        ../Models/Contact.h \
        ../Models/CreditCard.h \
        ../Models/CryptoWallet.h \
        ../Models/Date.h \
        ../Models/Note.h \
        ../Models/SerializableObject.h \
        ../Models/Telephone.h \
        SerializationTestingFunctions.h \
        TreeTestingFunctions.h \
        ../Core/EncDec_File.h \
        EncDec_FileTestingFunctions.h \
        ../Models/Vault.h \
        VaultTestingFunctions.h
