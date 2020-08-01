# Author: davidpeet8
# David Peet

##################### INITIALIZATION #####################

CLIDIR=./src/cli
MCHECKDIR=./src/mcheck
MCHECKSTORAGEDIR=./src/mcheckstorage
INSTALL_DIR= ~/mylibs/
BUILD_DIR=./build
BIN_DIR=~/bin

######################## PHONY TARGETS #########################

all: makeBuildDir makeLibsDir
	cd $(CLIDIR) && $(MAKE)
	cp $(CLIDIR)/mcheck $(BUILD_DIR)
	cp $(CLIDIR)/mcheck $(BIN_DIR)
	cd $(MCHECKSTORAGEDIR) && $(MAKE)
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(BUILD_DIR)
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(INSTALL_DIR)
	cd $(MCHECKDIR) && $(MAKE)
	cp $(MCHECKDIR)/libmcheck.so $(BUILD_DIR)
	cp $(MCHECKDIR)/libmcheck.so $(INSTALL_DIR) 

debug: 
	cd $(CLIDIR) && $(MAKE) debug
	cp $(CLIDIR)/mcheck $(BUILD_DIR)
	cp $(CLIDIR)/mcheck $(BIN_DIR)
	cd $(MCHECKSTORAGEDIR) && $(MAKE) debug
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(BUILD_DIR)
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(INSTALL_DIR) 
	cd $(MCHECKDIR) && $(MAKE) debug
	cp $(MCHECKDIR)/libmcheck.so $(BUILD_DIR)
	cp $(MCHECKDIR)/libmcheck.so $(INSTALL_DIR) 

compile: 
	cd $(CLIDIR) && $(MAKE) compile
	cd $(MCHECKSTORAGEDIR) && $(MAKE) compile
	cd $(MCHECKDIR) && $(MAKE) compile

link: 
	cd $(CLIDIR) && $(MAKE) link
	cp $(CLIDIR)/mcheck $(BUILD_DIR)
	cp $(CLIDIR)/mcheck $(BIN_DIR)
	cd $(MCHECKSTORAGEDIR) && $(MAKE) link
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(BUILD_DIR)
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so $(INSTALL_DIR) 
	cd $(MCHECKDIR) && $(MAKE) link
	cp $(MCHECKDIR)/libmcheck.so $(BUILD_DIR)
	cp $(MCHECKDIR)/libmcheck.so $(INSTALL_DIR) 

clean:
	cd $(CLIDIR) && $(MAKE) clean
	cd $(MCHECKSTORAGEDIR) && $(MAKE) clean
	cd $(MCHECKDIR) && $(MAKE) clean
	rm -f $(BUILD_DIR)/* 

install:
	cp $(BUILD_DIR)/*.so $(INSTALL_DIR)

makeBuildDir:
	mkdir -p build

makeLibsDir:
	mkdir -p ~/mylibs