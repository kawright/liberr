# ----- PROJECT INFO -----

PROJ_NAME := liberr
VER := 1.1

# ----- COMPILER CONFIGURATION -----

CC := gcc
CC_OPTS := \
	-Wall \
	-Werror \
	-fpic

# ----- REAL TARGETS -----

build/lib/liberr.so: build/obj/err.o
	@mkdir -p build/lib
	@${CC} -shared -o $@ $<
	@echo "Built target $@"

build/obj/err.o: err.c err.h
	@mkdir -p build/obj
	@${CC} ${CC_OPTS} -c -o $@ $<
	@echo "Built target $@"

# ----- PHONY TARGETS -----

.PHONY: \
	all \
	clean \
	install \
	uninstall

all: build/lib/liberr.so
	@echo "Built ${PROJ_NAME} version ${VER}"

clean:
	@rm -rf build
	@echo "All build artifacts removed"

install: build/lib/liberr.so
	@cp err.h /usr/local/include/err.h
	@echo "Copied err.h"
	@cp build/lib/liberr.so /usr/local/lib/liberr.so
	@echo "Copied liberr.so"
	@echo "${PROJ_NAME} version ${VER} successfully installed"

uninstall:
	@rm /usr/local/include/err.h
	@echo "Deleted err.h"
	@rm /usr/local/lib/liberr.so
	@echo "Deleted liberr.so"
	@echo "${PROJ_NAME} successfully uninstalled"
