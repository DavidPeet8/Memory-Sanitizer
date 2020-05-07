# Author: davidpeet8
# David Peet
# Project: Common

##################### INITIALIZATION #####################

# General Vars
COMPILER=g++
COMPILATION_FLAGS=-Werror=vla -Wall -MMD -fPIC
CPPSTANDARD=c++17

# Vars for project objects
SRCDIR=./src
OBJDIR=./obj
OBJECTS=Logger.o commonMethods.o messageManager.o customExceptions.o Args.o
OBJECTPATHS=$(call addprefix, ${OBJDIR}/, ${OBJECTS})
DEPENDSPATHS=${OBJECTPATHS:.o=.d}

.PHONY: clean debug

####################### TARGETS #########################

all: $(OBJECTPATHS)
	@echo finished making ALL

-include ${DEPENDSPATHS}

# Individual File Compilation Target
$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	@echo making $@
	# $@ --> is the name of the makefile target
	# $< is the name of the first prerequisite
	${COMPILER} $< -std=${CPPSTANDARD} -c -o $@ ${COMPILATION_FLAGS}

######################## PHONY TARGETS #########################

debug: COMPILATION_FLAGS+=-g 
debug: ${OBJECTPATHS}

clean:
	rm -f ${OBJDIR}/*


