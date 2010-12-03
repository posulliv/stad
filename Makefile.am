
ACLOCAL_AMFLAGS = -I m4 --force
VERSION=$(PANDORA_RELEASE_VERSION)

pkgplugindir=$(libdir)/drizzle7
EXTRA_DIST = plugin.ini

noinst_HEADERS=
nobase_include_HEADERS=
check_PROGRAMS=
noinst_LTLIBRARIES=
bin_PROGRAMS=


EXTRA_DIST += tests

pkgplugin_LTLIBRARIES=libstad_plugin.la
libstad_plugin_la_LDFLAGS=-avoid-version -rpath $(pkgplugindir) $(AM_LDFLAGS)  $(GCOV_LIBS)
libstad_plugin_la_LIBADD=libcommon.la
libstad_plugin_la_DEPENDENCIES=libcommon.la
libstad_plugin_la_CPPFLAGS=$(AM_CPPFLAGS) -DPANDORA_DYNAMIC_PLUGIN -DPANDORA_MODULE_NAME=stad -DPANDORA_MODULE_AUTHOR='"Padraig O Sullivan"' -DPANDORA_MODULE_TITLE='"SQL Injection Preventor"' -DPANDORA_MODULE_VERSION='"0.2"' -DPANDORA_MODULE_LICENSE=PLUGIN_LICENSE_GPL  
libstad_plugin_la_CXXFLAGS=$(AM_CXXFLAGS)  -DBUILDING_DRIZZLED
libstad_plugin_la_CFLAGS=$(AM_CFLAGS)  
libstad_plugin_la_SOURCES=injection_prevention.cpp
check_PROGRAMS += 
include ./plugin.am
