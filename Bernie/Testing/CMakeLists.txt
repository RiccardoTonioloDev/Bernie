
cmake_minimum_required(VERSION 3.23)
project(../../Bernie)

set(CMAKE_CXX_STANDARD 14)

include_directories(../Core)
include_directories(../Models)

add_executable(Bernie
        ../Core/RBBSTree.cpp
        ../Core/RBBSTree.h
        ../Models/Account.cpp
        ../Models/Account.h
        ../Models/Contact.cpp
        ../Models/Contact.h
        ../Models/SerializableObjectsEnum.h
        ../Models/CreditCard.cpp
        ../Models/CreditCard.h
        ../Models/CryptoWallet.cpp
        ../Models/CryptoWallet.h
        ../Models/Date.cpp
        ../Models/Date.h
        ../Models/Note.cpp
        ../Models/Note.h
        ../Models/SerializableObject.cpp
        ../Models/SerializableObject.h
        ../Models/Telephone.cpp
        ../Models/Telephone.h
        ../Testing/testingSerialization.cpp)