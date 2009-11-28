SUBDIRS = src man

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = xi.pc

MAINTAINERCLEANFILES = ChangeLog INSTALL
EXTRA_DIST = xi.pc.in 


.PHONY: ChangeLog INSTALL

INSTALL:
	$(INSTALL_CMD)

ChangeLog:
	$(CHANGELOG_CMD)

dist-hook: ChangeLog INSTALL
