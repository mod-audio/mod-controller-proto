#!/usr/bin/make -f
# Makefile for mod-controller-proto #
# --------------------------------- #
# Created by falkTX
#

# ---------------------------------------------------------------------------------------------------------------------

all: build python/__init__.py

build:
	$(MAKE) build -C tests

clean:
	$(MAKE) clean -C tests

# ---------------------------------------------------------------------------------------------------------------------

python/__init__.py: mod-protocol.h ./scripts/generate-mod-protocol.py
	./scripts/generate-mod-protocol.py $(CURDIR)/$< $(CURDIR)/$@

# ---------------------------------------------------------------------------------------------------------------------
