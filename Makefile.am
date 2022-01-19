AUTOMAKE_OPTIONS = foreign

AM_CPPFLAGS = \
  -I$(includedir) \
  -I$(OFFLINE_MAIN)/include \
  -I$(ROOTSYS)/include

lib_LTLIBRARIES = \
   libanalysis.la

AM_CXXFLAGS = -Wall -Werror -msse2

AM_LDFLAGS = \
  -L$(libdir) \
  -L$(OFFLINE_MAIN)/lib

libanalysis_la_LIBADD = \
  -lfun4all \
  -lg4dst \
  -lPrototype4

pkginclude_HEADERS = \
  analysis.h


# I/O dictionaries have to exist for root5 and root6. For ROOT6 we need
# pcm files in addition. If someone can figure out how to make a list
# so this list of dictionaries is transformed into a list of pcm files
# following a simple naming convention, please change this accordingly and
# let me know
ROOTDICTS = \
  analysis_Dict.C 
# for root6 we need pcm and dictionaries but only for
# i/o classes. For root5 we need only dictionaries but
# those for i/o and classes available on the cmd line
# MAKEROOT6 is set in the configure.ac, true for root6
if MAKEROOT6
# this is a tweak to install files in $(libdir), automake refuses
# to install other files in libdir, this construct gets around this
pcmdir = $(libdir)
nobase_dist_pcm_DATA = \
  analysis_Dict_rdict.pcm 
else
  ROOT5_DICTS = \
    analysis_Dict.C
endif

libanalysis_la_SOURCES = \
  $(ROOTDICTS) \
  $(ROOT5_DICTS) \
  analysis.C

# Rule for generating table CINT dictionaries.
%_Dict.C: %.h %LinkDef.h
	rootcint -f $@ @CINTDEFS@ -c $(DEFAULT_INCLUDES) $(AM_CPPFLAGS) $^

# just to get the dependency                                                                                     
%_Dict_rdict.pcm: %_Dict.C ;

################################################
# linking tests

#noinst_PROGRAMS = testexternals

#BUILT_SOURCES = \
  testexternals.C

#testexternals_LDADD = \
  libanalysis.la

#testexternals.C:
#	echo "//*** this is a generated file. Do not commit, do not edit" > $@
#	echo "int main()" >> $@
#	echo "{" >> $@
#	echo "  return 0;" >> $@
#	echo "}" >> $@



noinst_PROGRAMS = testexternals

BUILT_SOURCES = \
  testexternals.C

testexternals_LDADD = \
  libanalysis.la

testexternals.C:
	echo "//*** this is a generated file. Do not commit, do not edit" > $@
	echo "int main()" >> $@
	echo "{" >> $@
	echo "  return 0;" >> $@
	echo "}" >> $@






clean-local:
	rm -f *Dict* $(BUILT_SOURCES) *.pcm
