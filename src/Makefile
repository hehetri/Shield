# =========================
# CONFIG
# =========================

TARGET   := EvoShield.dll
OUTDIR   := .
SRCDIR   := src
OBJDIR   := obj

CC       := gcc

CFLAGS   := -O0 -pipe -Wno-int-conversion -fno-omit-frame-pointer -DDEBUG \
            -ffreestanding -fno-builtin

INCDIRS  := -I$(SRCDIR)

LFLAGS   := -shared \
            -nostdlib \
            -Wl,--entry=DllMainCRTStartup@12 \
            -Wl,--enable-stdcall-fixup \
            -lmsvcrt \
            -lpsapi -lkernel32 -luser32 -lwinmm -lws2_32 -ld3d9

# =========================
# SOURCES
# =========================

SRC := $(shell find $(SRCDIR) -name "*.c")
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# =========================
# RULES
# =========================

all: build

build: $(OBJ)
	$(CC) -o $(OUTDIR)/$(TARGET) $(OBJ) $(LFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all build clean
