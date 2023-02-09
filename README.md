<h1 align="center">Bernie</h1>
<h2 align="center">A friendly digital assistant to secure your data</h2>
<p align="center">
    <img src="src/Savings/Assets/App_Logo.png" style="width:auto;height:200px">
</p>
<hr/>

## Why and what is it?
Bernie is the project that me and my friend decided to make as the course project for the Object Oriented Programming course for the year 2022/2023 at the University of Padua.
Basically it's a password and data manager, where your stored data (not only passwords but even contacts, crypto wallets, credit cards, and notes as well), will be encrypted with the master password you used to generate your database.

**Keep in mind:** the encryption method is the Vigenère cipher. It's not so much secure nowdays, but we decided to utilize it since this program is a proof of concept to show how it works. If you want to make the system more secure, you only need to change the `loadToFile` and the `loadFromFile` methods in the `src/Core/EncDec_File` class, with your favourite symmetric encryption algorithm.

## Disclaimer
I made the project public to inspire anyone who needed it. I take no responsibility for your use of the code within.
The project is licensed under the open source MIT licence.

## Requirements
To compile Bernie you need:
- A version of C++11 or higher;
- QMake (3.1 or higher) or CMake (3.22 or higher) (depending on the OS);
- The Qt framework, version 6.2.4 or higher.

## Building
To build the project you need to:
- Enter in the `src` directory with the terminal;
- Use the following command:
  - If you are on MacOS use: `cmake CMakeLists.txt`;
  - If you are on any Linux distro use: `qmake`;
- Use the following command (indipendently on the OS you are using): `make`;
- Now that you executable is compiled, use `./Bernie` to execute it.

## Testing
You can use the same exact commands you used for building, to build the automated tests I made.

All you have to do is going into the `src/Testing` folder, and then use the commands outlined before.

## Notes
You will find that there are already some databases. They are just there as an example, to try the project out.
- The ones with the "_correct" suffix, will work correctly if you will use their names (without the "_correct") as the passwords;
  - Like for example: prova1_correct, will be decrypted by the password "prova1";
- The ones with the "_fail" suffix, won't work anyway (they are manually corrupted files, to show that the program can spot manual corruption of files).