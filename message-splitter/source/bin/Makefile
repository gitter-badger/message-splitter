# Created by Ahmet Hakan Karaaslan

# Project Configurations
PROJECT_NAME="SendLongMessage"
PROJECT_AUTHOR="Rancho"
PROJECT_DESCRIPTION="SendLongMessage"
PROJECT_EXECUTABLE="slm.so"
			   
# Linux Compiler Configurations
LINUX_COMPILER=g++-4.6 -m32
LINUX_GCC=gcc-4.6 -m32

# (Linux) Compiler Configurations
L_FLAGS=
L_COMPILER_FLAGS=-c $(FRAMEWORK_BUILD_FLAGS) -I../include -I../src/SDK -DSAMPGDK_AMALGAMATION
L_LINKER_FLAGS=
# (Source Files)
SRC_FOLDER=../src
SOURCES=	main.cpp \
			SDK/amxplugin.cpp \
			sysChat.cpp


# (Object Files)
OBJECTS=$(foreach source, $(SOURCES), ./objects/$(source).o)
OBJECT_DIRS=SDK 

# (Lets Begin)
all: CREATE_OBJECT_DIRECTORIES linux

# Preparing for compiling.
CREATE_OBJECT_DIRECTORIES:
	@mkdir -p ./objects
	@$(foreach dir, $(OBJECT_DIRS), $(shell mkdir -p ./objects/$(dir)))
	
	
# (Linux Compilers)

linux: LINUX_COMPILE LINUX_LINK

LINUX_COMPILE:
	@echo "Compiling..."
	@$(foreach source, $(SOURCES), $(shell $(LINUX_COMPILER) $(L_FLAGS) $(L_COMPILER_FLAGS) $(FRAMEWORK_VER_FLAGS) $(SRC_FOLDER)/$(source) -o ./objects/$(source).o &> results.txt ))
	@$(LINUX_GCC) -I../include -I$(SRC_FOLDER)/SDK/ $(SRC_FOLDER)/SDK/sampgdk.c -c -o objects/sampgdk.o	
	@echo "Compiled."
	
LINUX_LINK:
	@echo "Linking..."
	@$(LINUX_COMPILER) $(OBJECTS) objects/sampgdk.o $(L_FLAGS) $(L_LINKER_FLAGS) -shared -o $(PROJECT_EXECUTABLE)
	@echo "Linked."
	
clean:
	@rm -f -r ./objects
	@rm -f $(PROJECT_EXECUTABLE)

