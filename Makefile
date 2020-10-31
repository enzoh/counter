SYSROOT ?= /opt/wasi-libc/sysroot
TOMMATH ?= /opt/libtommath-wasm-v1.2.0

WASM_CC ?= clang-10
WASM_LD ?= wasm-ld-10

SOURCE = src
TARGET = build

FILES = counter leb128 message util

WASM_CFLAGS = \
	--compile \
	--optimize=s \
	--sysroot=$(SYSROOT) \
	--target=wasm32-wasi \
	-I$(TOMMATH)/include

WASM_LDFLAGS = \
	--allow-undefined \
	--export-dynamic \
	--no-entry \
	-L$(SYSROOT)/lib/wasm32-wasi \
	-L$(TOMMATH)/lib \
	-lc \
	-ltommath

.PHONY: all
all: $(TARGET)/counter.wasm

$(TARGET)/counter.wasm: $(FILES:%=$(TARGET)/%.o)
	$(WASM_LD) $(WASM_LDFLAGS) -o $@ $+

$(TARGET)/%.o: $(SOURCE)/%.c | $(TARGET)
	$(WASM_CC) $(WASM_CFLAGS) -o $@ $<

$(TARGET):
	mkdir $@

.PHONY: clean
clean:
	rm -f -r $(TARGET)
