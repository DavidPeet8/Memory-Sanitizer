# Author: davidpeet8
# David Peet

##################### INITIALIZATION #####################

CLIDIR=./src/cli
MCHECKDIR=./src/mcheck
MCHECKSTORAGEDIR=./src/mcheckstorage

######################## PHONY TARGETS #########################

all:
	(cd $(CLIDIR) && $(MAKE))
	cp $(CLIDIR)/mcheck ./build
	cd $(MCHECKSTORAGEDIR) && $(MAKE)
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so ./build 
	cd $(MCHECKDIR) && $(MAKE)
	cp $(MCHECKDIR)/libmcheck.so ./build

debug: 
	cd $(CLIDIR) && $(MAKE) debug
	cp $(CLIDIR)/mcheck ./build
	cd $(MCHECKSTORAGEDIR) && $(MAKE) debug
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so ./build 
	cd $(MCHECKDIR) && $(MAKE) debug
	cp $(MCHECKDIR)/libmcheck.so ./build

compile: 
	cd $(CLIDIR) && $(MAKE) compile
	cp $(CLIDIR)/mcheck ./build
	cd $(MCHECKSTORAGEDIR) && $(MAKE) compile
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so ./build 
	cd $(MCHECKDIR) && $(MAKE) compile
	cp $(MCHECKDIR)/libmcheck.so ./build

link: 
	cd $(CLIDIR) && $(MAKE) link
	cp $(CLIDIR)/mcheck ./build
	cd $(MCHECKSTORAGEDIR) && $(MAKE) link
	cp $(MCHECKSTORAGEDIR)/libmcheckstorage.so ./build 
	cd $(MCHECKDIR) && $(MAKE) link
	cp $(MCHECKDIR)/libmcheck.so ./build

clean:
	cd $(CLIDIR) && $(MAKE) clean
	cd $(MCHECKSTORAGEDIR) && $(MAKE) clean
	cd $(MCHECKDIR) && $(MAKE) clean
	rm ./build/* 
