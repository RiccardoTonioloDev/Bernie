
cmake_minimum_required(VERSION 3.23)
project(..)

set(CMAKE_CXX_STANDARD 14)

# Enable AddressSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

# Enable UndefinedBehaviorSanitizer
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

include_directories(../Core)
include_directories(../Models)

add_executable(Bernie
        ../Core/RBBSTree.h
        ../Core/RBBSTree.cpp
        ../Models/Account.cpp
        ../Models/Account.h
        ../Models/Contact.cpp
        ../Models/Contact.h
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
        TreeTestingFunctions.cpp
        testing.cpp
        SerializationTestingFunctions.cpp SerializationTestingFunctions.h TreeTestingFunctions.h ../Core/EncDec_File.cpp ../Core/EncDec_File.h EncDec_FileTestingFunctions.cpp EncDec_FileTestingFunctions.h ../Models/Vault.cpp ../Models/Vault.h VaultTestingFunctions.cpp VaultTestingFunctions.h)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})