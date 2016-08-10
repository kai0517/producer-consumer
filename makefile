# Makefile to build the producer-consumer sample using g++ with C++11 features
# Auther : Wen-Kai, Chang
#
CC=g++
DEBUGFLAGS=-g -std=c++11
RELEASEFLAGS=-std=c++11 
SRCDIR=producer_consumer/
DEBUGDIR=./Debug/
RELEASEDIR=./Release/
DEBUGOBJS=$(DEBUGDIR)main.o $(DEBUGDIR)message.o
RELEASEOBJS=$(RELEASEDIR)main.o $(RELEASEDIR)message.o
OUTPUT=producer_consumer.out
MKDIR_P=mkdir -p

all : debug release

#####################
# Debug build
#####################

debug : debug_dir $(DEBUGDIR)$(OUTPUT)

debug_dir : $(DEBUGDIR)
	
$(DEBUGDIR) : 
	$(MKDIR_P) $(DEBUGDIR)

$(DEBUGDIR)$(OUTPUT) : $(DEBUGOBJS)
	$(CC) $(DEBUGFLAGS) $(DEBUGOBJS) -o $(DEBUGDIR)$(OUTPUT)

$(DEBUGDIR)main.o : $(SRCDIR)main.cpp $(SRCDIR)message.h
	$(CC) $(DEBUGFLAGS) -c $(SRCDIR)main.cpp -o $(DEBUGDIR)main.o

$(DEBUGDIR)message.o : $(SRCDIR)message.cpp $(SRCDIR)message.h
	$(CC) $(DEBUGFLAGS) -c $(SRCDIR)message.cpp -o $(DEBUGDIR)message.o

cleandebug :
	rm -rf $(DEBUGDIR)


#####################
# Release build
#####################

release : release_dir $(RELEASEDIR)$(OUTPUT)

release_dir : $(RELEASEDIR)

$(RELEASEDIR) : 
	$(MKDIR_P) $(RELEASEDIR)

$(RELEASEDIR)$(OUTPUT) : $(RELEASEOBJS)
	$(CC) $(RELEASEFLAGS) $(RELEASEOBJS) -o $(RELEASEDIR)$(OUTPUT)

$(RELEASEDIR)main.o : $(SRCDIR)main.cpp $(SRCDIR)message.h
	$(CC) $(RELEASEFLAGS) -c $(SRCDIR)main.cpp -o $(RELEASEDIR)main.o

$(RELEASEDIR)message.o : $(SRCDIR)message.cpp $(SRCDIR)message.h
	$(CC) $(RELEASEFLAGS) -c $(SRCDIR)message.cpp -o $(RELEASEDIR)message.o
	
cleanrelease :
	rm -rf $(RELEASEDIR)

clean : cleandebug cleanrelease
