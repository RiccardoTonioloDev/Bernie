
cmake_minimum_required(VERSION 3.23)
project(../Bernie)

set(CMAKE_CXX_STANDARD 14)

include_directories(../Bernie/Core)
include_directories(../Bernie/Models)

add_executable(Bernie
        ../Bernie/Core/RBBSTree2.h
        ../Bernie/Core/RBBSTree2.cpp
        ../Bernie/Models/Account.cpp
        ../Bernie/Models/Account.h
        ../Bernie/Models/Contact.cpp
        ../Bernie/Models/Contact.h
        ../Bernie/Models/CreditCard.cpp
        ../Bernie/Models/CreditCard.h
        ../Bernie/Models/CryptoWallet.cpp
        ../Bernie/Models/CryptoWallet.h
        ../Bernie/Models/Date.cpp
        ../Bernie/Models/Date.h
        ../Bernie/Models/Note.cpp
        ../Bernie/Models/Note.h
        ../Bernie/Models/SerializableObject.cpp
        ../Bernie/Models/SerializableObject.h
        ../Bernie/Models/Telephone.cpp
        ../Bernie/Models/Telephone.h
        TreeTestingFunctions.cpp
        testing.cpp
        SerializationTestingFunctions.cpp SerializationTestingFunctions.h TreeTestingFunctions.h ../Bernie/Core/EncDec_File.cpp ../Bernie/Core/EncDec_File.h EncDec_FileTestingFunctions.cpp EncDec_FileTestingFunctions.h ../Bernie/Models/Vault.cpp ../Bernie/Models/Vault.h VaultTestingFunctions.cpp VaultTestingFunctions.h)

#../Bernie/Core/RBBSTree.cpp
#../Bernie/Core/RBBSTree.h
