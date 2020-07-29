#!/usr/bin/make -f
# Makefile for mod-controller-proto #
# --------------------------------- #
# Created by falkTX
#

# ---------------------------------------------------------------------------------------------------------------------

all: build mod-protocol.py

build:
	$(MAKE) build -C tests

clean:
	$(MAKE) clean -C tests

# ---------------------------------------------------------------------------------------------------------------------

mod-protocol.py: mod-protocol.h ./scripts/generate-mod-protocol.py
	./scripts/generate-mod-protocol.py $(CURDIR)/$< $(CURDIR)/$@

# ---------------------------------------------------------------------------------------------------------------------
