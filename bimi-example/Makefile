# Makefile for make.lib v3
#-----------------------------------------------------------------------------------------
TOPDIR := ../../../HEAD

MEXNAME = mexlib
INSTDIR = matlab/private

LIBS += $(TOPDIR)/pdglib/libs/pdgbase/containers

OBJDIR = build/$(PDG_COMPILER_TYPE)_$(BUILDVARIANT)/$(TARGET_TYPE)

DFTARGET = install

# =====  MEXPLUS  =====
EXT_INCLUDES += ../include

# C4244 --> 'argument' : conversion from 'type1' to 'type2', possible loss of data
# C4267 --> 'var' : conversion from 'size_t' to 'type', possible loss of data
# C4800 --> 'type' : forcing value to bool 'true' or 'false' (performance warning)
CPPFLAGS += -wd4244 -wd4267 -wd4800
# =====  END MEXPLUS  =====

# =====  MATLAB  =====
MEXLIBROOT = ../_matlab_/R2014b
MEX_LIBS = libmx.lib libmex.lib

ifeq ($(PDG_ADDRESS_MODEL),amd64)
  MEXEXT = .mexw64
  MEXLIBSPATH = $(MEXLIBROOT)/lib/win64/microsoft
else
  MEXEXT := .mexw32
  MEXLIBSPATH = $(MEXLIBROOT)/lib/win32/microsoft
endif

DEFINES += -DMX_COMPAT_32 -DMATLAB_MEX_FILE
MEX_ENTRYPOINT=mexFunction

EXT_INCLUDES += $(MEXLIBROOT)/include
EXT_LIBS += $(addprefix $(MEXLIBSPATH)/,$(MEX_LIBS))
# =====  END MATLAB  =====

MKLIBDIR = $(TOPDIR)/Makefiles
include $(MKLIBDIR)/make.lib

LNKFLAGS += -export:$(MEX_ENTRYPOINT)

manifest: baredynamic
	@if $(TEST) -f $(TARGET.SO).manifest ; then                                            \
    cd $(WORKDIR) && mt -nologo -manifest $(notdir $(TARGET.SO)).manifest -outputresource:$(notdir $(TARGET.SO))\;2 ; \
   fi

MEXFILE = $(INSTDIR)/$(MEXNAME)$(MEXEXT)
install: baredynamic manifest
	@if $(TEST) $(TARGET.SO) -nt $(MEXFILE) ; then                       \
     echo "Copying $(notdir $(TARGET.SO)) to $(notdir $(MEXFILE))" ;   \
     $(MD) $(INSTDIR) ;                                                \
     $(CP) $(TARGET.SO) $(MEXFILE) ;                                   \
   fi
