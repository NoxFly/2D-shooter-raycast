CC 			= clang++
ifeq ($(CXX), g++) # detect if compiler is gcc instead of clang. Not viewing for other compiler
	$(CC) = $(g++)
endif
CFLAGS 		:= -std=c++17 -Wno-unused-command-line-argument #-Wall -Wextra

EXECUTABLE 	:= raycast
EXT 		:= exe
TARGETDIR_1 := ./bin

ifneq ($(RELEASE), 1)
	TARGETDIR = $(TARGETDIR_1)/debug
else
	TARGETDIR = $(TARGETDIR_1)/release
	CFLAGS = -o
endif

TARGET 		:= $(TARGETDIR)/$(EXECUTABLE).$(EXT)


BUILDDIR 	:= ./build

SRCDIR 		:= ./src
INCDIR 		:= ./include

SRCEXT 		:= cpp


SOURCES 	:= $(shell find $(SRCDIR)/** -type f -name *.$(SRCEXT))
OBJECTS 	:= $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))


INCDIRS 	:= $(shell find $(INCDIR)/** -name '*.h' -exec dirname {} \; | sort | uniq)
INCLIST 	:= $(patsubst $(INCDIR)/%, -I $(INCDIR)/%, $(INCDIRS))
BUILDLIST 	:= $(patsubst $(INCDIR)/%, $(BUILDDIR)/%, $(INCDIRS))

INC 		:= -I $(INCDIR) $(INCLIST)
LIBS 		:= -lsfml-graphics -lsfml-window -lsfml-system


$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"; $(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDLIST)
	@echo "Compiling $<..."; $(CC) $(CFLAGS) -c $(INC) -o $@ $<

clean:
	rm -f -r $(BUILDDIR)/** $(TARGETDIR_1)/release/* $(TARGETDIR_1)/debug/*
	@echo "All objects removed"

.PHONY: clean