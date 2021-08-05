#/**
#* MIT License
#*
#* Copyright (c) 2019 Infineon Technologies AG
#*
#* Permission is hereby granted, free of charge, to any person obtaining a copy
#* of this software and associated documentation files (the "Software"), to deal
#* in the Software without restriction, including without limitation the rights
#* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#* copies of the Software, and to permit persons to whom the Software is
#* furnished to do so, subject to the following conditions:
#*
#* The above copyright notice and this permission notice shall be included in all
#* copies or substantial portions of the Software.
#*
#* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#* SOFTWARE
#
#*/

SRCEXT = c
INCEXT = h
SRCDIR = lib/interface lib/common 
APPDIR = sample
INCDIR = include
BINDIR = bin

CC = gcc
CFLAGS = -Wall   
#LDFLAGS = -lwiringPi
DEBUG = 

INCSSRC := $(shell find $(INCSDIR) -name '*.$(INCEXT)')
INCSDIR := $(patsubst %,%/$(INCDIR),$(SRCDIR))

OBJSSRC := $(shell find $(SRCDIR) -name '*.$(SRCEXT)')
OBJECTS := $(patsubst %.$(SRCEXT),%.o,$(OBJSSRC))

APPSSRC := $(shell find $(APPDIR) -name '*.$(SRCEXT)')
APPSOBJ := $(patsubst %.$(SRCEXT),%.o,$(APPSSRC))
APPS := $(patsubst %.$(SRCEXT),%,$(APPSSRC))

INCSDIR := $(addprefix -I,$(INCSDIR))
CFLAGS += -c $(DEBUG) $(INCSDIR) 

all : $(APPS)

$(APPS): %: $(OBJECTS) $(INCSSRC) %.o
	@echo "******* Linking $@ "
	@$(CC) $(LDFLAGS) $@.o $(OBJECTS) -o $@
	@mkdir -p bin
	@cp $@ bin/.

$(OBJECTS): %.o: %.$(SRCEXT) $(INCSSRC)
	@echo "+++++++ Generating dependencies for $< "
	@$(CC) $(CFLAGS) $< -o $@

%.o: %.$(SRCEXT) $(INCSSRC)
	@echo "------- Generating application objects for $< "
	@$(CC) $(CFLAGS) $< -o $@

.Phony : clean 
clean :
	@echo "Removing *.o from $(SRCDIR)" 
	@rm -rf $(OBJECTS)
	@echo "Removing *.o from $(APPDIR)"
	@rm -rf $(APPSOBJ)
	@echo "Removing all application from $(APPDIR)"	
	@rm -rf $(APPS)
	@echo "Removing all application from $(BINDIR)"	
	@rm -rf bin/*


