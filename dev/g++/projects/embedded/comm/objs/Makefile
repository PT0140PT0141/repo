
########################################################################
#
#       Makefile for embedded framework - Comm library
#
#       ident  "$Id$"
#
#############################################################################

include $(PATH_DEV)/Makefile.inc

#############################################################################
# Override CC, CCP and LD in case of cross compiler

ifneq ($(CROSS_COMPILER_PATH), )
CC=$(CROSS_CC)
CCP=$(CROSS_CCP)
LD=$(CROSS_LD)

GLOBAL_DEF_STD_GLD=$(CROSS_GLOBAL_DEF_STD_GLD)

GLOBAL_DEF_GCC_DEBUG=$(CROSS_GLOBAL_DEF_GCC_DEBUG)
GLOBAL_DEF_GCC=$(CROSS_GLOBAL_DEF_GCC)

PTHREAD_INC=$(CROSS_PTHREAD_INC)
PTHREAD_LD=$(CROSS_PTHREAD_LD)
endif

#############################################################################
# Shared library version

ifneq (,$(wildcard $(SHARED_LIBRARY_VERSIONING)))
DYN_VERS_MAJ=0
DYN_VERS_MIN=1
VERSION=.$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
endif

#############################################################################
# Libraries and options.

CC_INS=$(PTHREAD_INC)
LD_INS=$(PTHREAD_LD)

# Compiler flags
CC_DEBUG_OPTIONS=$(GLOBAL_DEF_GCC_DEBUG) $(CC_INS) -I$(GLOBAL_INC_CPP_PATH)
CC_RELEASE_OPTIONS=$(GLOBAL_DEF_GCC) $(CC_INS) -I$(GLOBAL_INC_CPP_PATH)

# Linker flags
LD_DEBUG_OPTIONS=-shared -Wall $(GLOBAL_DEF_STD_GLD)
LD_RELEASE_OPTIONS=-shared -Wall $(GLOBAL_DEF_STD_GLD)

# Define Include paths + definition flags
#DEFS_CC=-I$(GLOBAL_INC_CPP_PATH) -I$(INCDIRS) -I$(GLOBAL_INC_BOOST_PATH) $(DEFS_CC_RELEASE)
#DEFS_BOOST_LD=$(GLOBAL_DEF_BOOST_GLD)
DEFS_CC=
DEFS_BOOST_LD=

#############################################################################
# Module variables.

# Paths
LIBDIR=../lib
LIBDIRS=../lib/
OBJSDIR=../objs
OBJSDIRS=../objs/
SRCDIRS=../src/
INCDIR=../include
INCDIRS=../include/
TESTDIRS = ../test/
DOCDIR=../docs
DOCDIRS=../docs
DOCCONF=$(DOCDIR)/o2.cfg

# Needed to build application.
LIBRARY=libcomm

# Targets
TARGET=$(LIBRARY)$(SHARED_LIBRARY_EXT_NAME)$(VERSION)
TARGET_D=$(LIBRARY)_d$(SHARED_LIBRARY_EXT_NAME)$(VERSION)
LIB=$(LIBDIR)/$(TARGET)
LIB_D=$(LIBDIR)/$(TARGET_D)
TEST_TARGET=testlib
BIN=$(TESTDIRS)$(TEST_TARGET)

MODULE_LIBS=$(LIB) 
MODULE_LIBS_D=$(LIB_D) 
MODULE_TEST=$(BIN)

# Object app
OBJS=$(TEST_OBJS)
LIB_OBJS=\
	$(CHANNEL_MANAGER_OBJ) \
	$(SOCKET_ADDRESS_OBJ) \
	$(IPV4_ADDRESS_OBJ) \
	$(IPV6_ADDRESS_OBJ) \
	$(SOCKET_OBJ) \
	$(IPV4_SOCKET_OBJ) \
	$(IPV6_SOCKET_OBJ) \
	$(RAW_CHANNEL_OBJ) \
	$(UDP_CHANNEL_OBJ) \
	$(TCP_CHANNEL_OBJ)

# Objects
TEST_OBJ=testlib.o
CHANNEL_MANAGER_OBJ=channel_manager.o
SOCKET_ADDRESS_OBJ=socket_address.o
IPV4_ADDRESS_OBJ=ipv4_address.o
IPV6_ADDRESS_OBJ=ipv6_address.o
SOCKET_OBJ=socket.o
IPV4_SOCKET_OBJ=ipv4_socket.o
IPV6_SOCKET_OBJ=ipv6_socket.o
RAW_CHANNEL_OBJ=raw_channel.o
UDP_CHANNEL_OBJ=udp_channel.o
TCP_CHANNEL_OBJ=tcp_channel.o

# Headears
ABSTRACT_CHANNEL_INC=abstract_channel.h
CHANNEL_TYPE_INC=channel_type.h
CHANNEL_MANAGER_INC=channel_manager.h
IPVX_ADDRESS_INC=ipvx_address.h
SOCKET_ADDRESS_INC=socket_address.h
IPV4_ADDRESS_INC=ipv4_address.h
IPV6_ADDRESS_INC=ipv6_address.h
IPVX_SOCKET_INC=ipvx_socket.h
SOCKET_INC=socket.h
IPV4_SOCKET_INC=ipv4_socket.h
IPV6_SOCKET_INC=ipv6_socket.h
RAW_CHANNEL_INC=raw_channel.h
UDP_CHANNEL_INC=udp_channel.h
TCP_CHANNEL_INC=tcp_channel.h

INC_MODULES=$(ABSTRACT_CHANNEL_INC) $(CHANNEL_TYPE_INC) $(CHANNEL_MANAGER_INC) $(IPVX_ADDRESS_INC) $(SOCKET_ADDRESS_INC) $(IPV4_ADDRESS_INC) $(IPV6_ADDRESS_INC) $(IPVX_SOCKET_INC) $(SOCKET_INC) $(IPV4_SOCKET_INC) $(IPV6_SOCKET_INC) $(RAW_CHANNEL_INC) $(UDP_CHANNEL_INC) $(TCP_CHANNEL_INC)

#############################################################################
# Real compilation sections.

all: directories $(MODULE_LIBS) links
	@echo "*** $@ done ***"

all_d: directories $(MODULE_LIBS_D) links
	@echo "*** $@ done ***"

$(LIB): $(LIB_OBJS)
	$(LD) $(LD_OPTION) -o $(LIB) $(LIB_OBJS)
	@echo "*** $@ done ***"

$(LIB_D): $(LIB_OBJS)
	$(LD) $(LD_OPTION) -o $(LIB_D) $(LIB_OBJS)
	@echo "*** $@ done ***"

$(TEST_TARGET): $(TEST_OBJ)
	$(LD) $(TEST_OBJ) -o $(BIN) $(LD_OPTION)
	@echo "*** $@ done ***"

$(TEST_OBJ): $(TESTDIRS)$(TEST_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(TEST_OBJ)

$(CHANNEL_MANAGER_OBJ): $(SRCDIRS)$(CHANNEL_MANAGER_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(CHANNEL_MANAGER_OBJ)

$(SOCKET_ADDRESS_OBJ): $(SRCDIRS)$(SOCKET_ADDRESS_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(SOCKET_ADDRESS_OBJ)

$(IPV4_ADDRESS_OBJ): $(SRCDIRS)$(IPV4_ADDRESS_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(IPV4_ADDRESS_OBJ)

$(IPV6_ADDRESS_OBJ): $(SRCDIRS)$(IPV6_ADDRESS_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(IPV6_ADDRESS_OBJ)

$(SOCKET_OBJ): $(SRCDIRS)$(SOCKET_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(SOCKET_OBJ)

$(IPV4_SOCKET_OBJ): $(SRCDIRS)$(IPV4_SOCKET_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(IPV4_SOCKET_OBJ)

$(IPV6_SOCKET_OBJ): $(SRCDIRS)$(IPV6_SOCKET_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(IPV6_SOCKET_OBJ)

$(RAW_CHANNEL_OBJ): $(SRCDIRS)$(RAW_CHANNEL_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(RAW_CHANNEL_OBJ)

$(UDP_CHANNEL_OBJ): $(SRCDIRS)$(UDP_CHANNEL_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(UDP_CHANNEL_OBJ)

$(TCP_CHANNEL_OBJ): $(SRCDIRS)$(TCP_CHANNEL_OBJ:.o=.cpp)
	$(CCP) $(CC_OPTION) -I$(INCDIR) -c $? -o $(OBJSDIRS)$(TCP_CHANNEL_OBJ)

compile :
	${MAKE} -f Makefile \
		CC_OPTION="$(CC_RELEASE_OPTIONS)" \
		LD_OPTION="$(LD_RELEASE_OPTIONS) -L$(HOME_LIB) -lconverter" \
		all

recompile :
	${MAKE} -f Makefile clean
	${MAKE} -f Makefile \
		CC_OPTION="$(CC_RELEASE_OPTIONS)" \
		LD_OPTION="$(LD_RELEASE_OPTIONS) -L$(HOME_LIB) -lconverter" \
		all

debug :
	${MAKE} -f Makefile \
		CC_OPTION="$(CC_DEBUG_OPTIONS)" \
		LD_OPTION="$(LD_DEBUG_OPTIONS) -L$(HOME_LIB) -lconverter" \
		all

test : compile
	${MAKE} -f Makefile \
		CC_OPTION="$(GLOBAL_DEF_GCC) $(CC_INS) $(CPP_TEST_INC) -I$(HOME_INC)" \
		LD_OPTION="$(GLOBAL_DEF_STD_GLD) $(LD_INS) -L$(HOME_LIB) -lcomm -lhelper -lconverter $(CPP_TEST_LIB)" \
		directories $(TEST_TARGET)

test_d : debug
	${MAKE} -f Makefile \
		CC_OPTION="$(GLOBAL_DEF_GCC_DEBUG) $(CC_INS) $(CPP_TEST_INC) -I$(HOME_INC)" \
		LD_OPTION="$(GLOBAL_DEF_STD_GLD) $(LD_INS) -L$(HOME_LIB) -lcomm -lhelper -lconverter $(CPP_TEST_LIB)" \
		directories $(TEST_TARGET)

run : test
	@$(SUDO) LD_LIBRARY_PATH=$(HOME_LIB):$(USR_LOCAL_LIB) $(TESTDIRS)$(TEST_TARGET)

run_d : test_d
	@$(SUDO) LD_LIBRARY_PATH=$(HOME_LIB):$(USR_LOCAL_LIB) gdb $(TESTDIRS)$(TEST_TARGET)

clean: cleanlinks
	@$(RM) -f $(BIN) $(LIBDIRS)$(TARGET) $(LIBDIRS)$(TARGET_D) ./../$(LIBRARY).tar.gz $(TARGET) *.lst *.o *.d *~  $(SRCDIRS)*.o $(SRCDIRS)*~ $(SRCDIRS)*.err $(INCDIR)/*~ $(TESTDIRS)*.o $(TESTDIRS)*~ $(DOCDIRS)*~
	@$(RM) -fr $(DOCDIRS)html $(DOCDIRS)latex $(DOCDIRS)man
	@echo "*** $@ done ***"

cleanlinks:
	@$(RM) $(HOME_LIB)/$(LIBRARY)$(SHARED_LIBRARY_EXT_NAME)
	@for header in $(INC_MODULES); do \
		$(RM) $(HOME_INC)/$$header; \
	done
	@echo "*** $@ done ***"

links:
ifeq (,$(wildcard $(HOME_LIB)/$(LIBRARY)$(SHARED_LIBRARY_EXT_NAME)))
	ln -s $(PWD)/$(LIBDIRS)$(TARGET) $(HOME_LIB)/$(LIBRARY)$(SHARED_LIBRARY_EXT_NAME)
endif
ifeq (,$(wildcard $(HOME_INC)/$(ABSTRACT_CHANNEL_INC)))
	ln -s $(PWD)/$(INCDIRS)$(ABSTRACT_CHANNEL_INC) $(HOME_INC)/$(ABSTRACT_CHANNEL_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(CHANNEL_MANAGER_INC)))
	ln -s $(PWD)/$(INCDIRS)$(CHANNEL_MANAGER_INC) $(HOME_INC)/$(CHANNEL_MANAGER_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(CHANNEL_TYPE_INC)))
	ln -s $(PWD)/$(INCDIRS)$(CHANNEL_TYPE_INC) $(HOME_INC)/$(CHANNEL_TYPE_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPVX_ADDRESS_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPVX_ADDRESS_INC) $(HOME_INC)/$(IPVX_ADDRESS_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(SOCKET_ADDRESS_INC)))
	ln -s $(PWD)/$(INCDIRS)$(SOCKET_ADDRESS_INC) $(HOME_INC)/$(SOCKET_ADDRESS_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPV4_ADDRESS_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPV4_ADDRESS_INC) $(HOME_INC)/$(IPV4_ADDRESS_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPV6_ADDRESS_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPV6_ADDRESS_INC) $(HOME_INC)/$(IPV6_ADDRESS_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPVX_SOCKET_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPVX_SOCKET_INC) $(HOME_INC)/$(IPVX_SOCKET_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(SOCKET_INC)))
	ln -s $(PWD)/$(INCDIRS)$(SOCKET_INC) $(HOME_INC)/$(SOCKET_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPV4_SOCKET_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPV4_SOCKET_INC) $(HOME_INC)/$(IPV4_SOCKET_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(IPV6_SOCKET_INC)))
	ln -s $(PWD)/$(INCDIRS)$(IPV6_SOCKET_INC) $(HOME_INC)/$(IPV6_SOCKET_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(RAW_CHANNEL_INC)))
	ln -s $(PWD)/$(INCDIRS)$(RAW_CHANNEL_INC) $(HOME_INC)/$(RAW_CHANNEL_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(UDP_CHANNEL_INC)))
	ln -s $(PWD)/$(INCDIRS)$(UDP_CHANNEL_INC) $(HOME_INC)/$(UDP_CHANNEL_INC)
endif
ifeq (,$(wildcard $(HOME_INC)/$(TCP_CHANNEL_INC)))
	ln -s $(PWD)/$(INCDIRS)$(TCP_CHANNEL_INC) $(HOME_INC)/$(TCP_CHANNEL_INC)
endif
	@echo "*** $@ done ***"

directories :
	@if [ ! -d $(LIBDIR) ] ; then mkdir -p $(LIBDIR) ; fi ;
	@echo "*** $@ done ***"

dist: clean
	@$(RM) ../../$(LIBRARY).tar.gz
	@cd ../.. ; \
	$(TAR) - $(LIBRARY) | $(GZIP) > $(LIBRARY).tar.gz ; \
	cd -
	@echo "*** $@ done ***"

install: compile cleanlinks
	@$(CP) $(LIBDIRS)$(TARGET) $(PATH_INSTALL_LIB)/$(LIBRARY)$(SHARED_LIBRARY_EXT_NAME)
	@echo "*** $@ done ***"

install-devel: install
	@$(CP) $(INCDIRS)$(ABSTRACT_CHANNEL_INC) $(PATH_INSTALL_INC)/$(ABSTRACT_CHANNEL_INC)
	@echo "*** $@ done ***"

depend :
	makedepend -m $(CC_OPTIONS) $(SRCDIR)/*.cpp -f$(MAKEFILE)
	@echo "*** $@ done ***"

gendoc: $(DOCCONF)
	@$(O2) $(DOCCONF)
	@echo "$(SUDO) mandb $(DOCDIRS)man"

help:
	@clear
	@echo
	@echo "make options are:"
	@echo
	@echo "   help         : This menu."
	@echo "   clean        : Erase objects, binaries and temporary files."
	@echo "   debug        : Build a debug version."
	@echo "   compile      : Build the application in release mode."
	@echo "   recompile    : Rebuild the application in release mode."
	@echo "   rel          : Clean and rebuild the application in release mode."
	@echo "   test         : Build the test application."
	@echo "   dist         : Build a compressed archive of the application."
	@echo "   install      : Install binaries, libraries and configuration files into final directory $(PATH_INSTALL)/xxx."
	@echo "   install-devel: Same as 'install' plus include files."
	@echo "   depend       : Build the file dependencies for $(MAKE)."
	@echo "   gendoc       : Build the Doxygen documantation."
	@echo
	@echo "Without option it compilates in optimized mode."
	@echo
	@echo "*** $@ done ***"

#############################################################################
# Dependencies sections.

# DO NOT DELETE





