<h1 align="center">Bernie</h1>
<h2 align="center">A friendly digital assistant to secure your data</h2>
<p align="center">
    <img src="src/Savings/Assets/App_Logo.png" style="width:auto;height:200px">
</p>
<hr/>

## Why and what is it?
Bernie is the project that me and my friend decided to make as the course project for the Object Oriented Programming course for the year 2022/2023 at the University of Padua.
Basically it's a password and data manager, where your stored data (not only passwords but even contacts, crypto wallets, credit cards, and notes as well), will be encrypted with the master password you used to generate your database.

> **Keep in mind:** the encryption method is the Vigenère cipher. It's not so much secure nowdays, but we decided to utilize it since this program is a proof of concept to show how it works, and since we weren't allowed to use third party libraries for the crypto stuff. If you want to make the system more secure, you only need to change the `loadToFile` and the `loadFromFile` methods in the `src/Core/EncDec_File` class, with your favourite symmetric encryption algorithm.

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

## Documentation
There are two technical sheets (one from me and one from my partner) about the project (written in italian), inside the `Docs` folder (there are the pdfs and the docx versions).
You can even find the UML for the model, the minimal UML for the GUI, and the storyboard used to design the GUI.

## Notes
You will find that there are already some databases. They are just there as an example, to try the project out.
- The ones with the "_correct" suffix, will work correctly if you will use their names (without the "_correct") as the passwords;
  - Like for example: prova1_correct, will be decrypted by the password "prova1";
- The ones with the "_fail" suffix, won't work anyway (they are manually corrupted files, to show that the program can spot manual corruption of files).

## Evaluation
```
Evaluation: 3/3 with honors
Mandatory constraints:
+ Satisfied

Object orientation:
+ Nesting
+ Modularity (the logic model is detached from the GUI)
+ Extensibility and evolvability, polymorphism
+ Efficiency and robustness

Functionality:
+ Numerous features related to the chosen theme
+ Implementation and use of a not trivial data structure (red and black binary search tree)
+ Extensive use of polymorphism, in an appropriate manner
+ Documented use of a good development methodology (for example unit tests)

GUI:
+ Views of different data types in an appropriate manner
+ Usable and intuitive
+ Robust and handles scaling
+ Use of colors and styles
+ Use of images and icons

Report:
+ Adequate

Suggestions for improvements:
None.
```