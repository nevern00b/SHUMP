SHUMP
=====

Procedurally Generated Shmup - Philadelphia Game Lab

Setup instructions:

The first step is to clone the git repo onto your local computer. If you use git bash, do the command: git clone https://github.com/nevern00b/SHUMP. This creates a folder "SHUMP" with the project inside.

In order to keep the codebase clean, we are using premake to auto generate the project files for visual studio, Xcode, and other IDEs that people want to use.

To build the project, go to the premake folder and double-click the batch script for type of project you want. It will generate a build folder in the root directory. Go in there and open the project.

Right now we only support Visual Studio 2013 (32 and 64 bit). All the libraries in the external folder are compiled for VS2013. Premake can only generate up to VS2010, but that's ok. Just open the project in VS2013 and the solution will be converted. 

In the near future, we will get the project working for Xcode and other other IDEs. Premake can create projects for many different setups, it's just a matter of compiling the libraries on these different platforms.

The purpose of the .gitignore file is to prevent the build folder from being included in the git repo. Therefore do not add any code to the build folder! Put all code in the src folder. For example, if you are adding a class in Visual Studio, you can't use "Add Class" because it will force you to add the class to the build folder. Instead, you have to use "Add New Item" for both the .cpp and .h file, and make sure to change the location to the src folder. 

We're going to replace tabs with spaces in the code. To set this up in visual studio, go to Tools->Options->Text Editor->All Languages->Tabs. Select Insert Spaces. Change tab size and indent size to 4.