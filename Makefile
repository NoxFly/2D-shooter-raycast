# modify these 3 lines depending of what you want
CFLAGS 		:= -std=c++17 -Wno-unused-command-line-argument# -Werror -Wall -Wextra
LIBS 		:= -lsfml-graphics -lsfml-window -lsfml-system
# type of source files
# c or cpp (make sure to not have space after)
SRCEXT 		:= cpp


# detect if compiler is gcc instead of clang. Not viewing for other compiler
# C
ifeq ($(SRCEXT), c)
	ifeq ($(CXX), gcc)
		CC := gcc
	else
		CC := clang
	endif # C : clang or gcc
# C++
else
	ifeq ($(CXX), g++)
		CC := g++
	else
		CC := clang++
	endif # C++ : clang++ or g++
endif

# executable name
ifdef PGNAME
	EXECUTABLE = $(PGNAME)
else
	EXECUTABLE 	:= program
endif # pgname

# program name location
ifdef OUT
	TARGETDIR_1 := $(OUT)
else
	TARGETDIR_1 := ./bin
endif # out

# compilation mode
ifdef DEBUG
	TARGETDIR = $(TARGETDIR_1)/debug
else
	TARGETDIR = $(TARGETDIR_1)/release
endif # debug

# final full executable location
TARGET 		:= $(TARGETDIR)/$(EXECUTABLE)

# .o location
BUILDDIR 	:= ./build

# source files location
SRCDIR 		:= ./src
# header files location
INCDIR 		:= ./include


SOURCES 	:= $(shell find $(SRCDIR)/** -type f -name *.$(SRCEXT))

INCDIRS		:=
INCLIST		:=
BUILDLIST	:=
INC			:= -I $(INCDIR)

ifneq ("$(ls -A "$(INCDIR)" 2> /dev/null)", "")
	INCDIRS 	:= $(shell find $(INCDIR)/** -name '*.h' -exec dirname {} \; | sort | uniq)
	INCLIST 	:= $(patsubst $(INCDIR)/%, -I $(INCDIR)/%, $(INCDIRS))
	BUILDLIST 	:= $(patsubst $(INCDIR)/%, $(BUILDDIR)/%, $(INCDIRS))
	INC 		:= -I $(INCDIR) $(INCLIST)
endif # incdir


ifdef DEBUG
OBJECTS 	:= $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"
	$(CC) -o $(TARGET) $^ $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
ifdef BUILDLIST
	@mkdir -p $(BUILDLIST)
endif
	@echo "Compiling $<...";
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

else # RELEASE

$(TARGET):
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	@echo "  Linking $(TARGET)"
	$(CC) $(INC) -o $(TARGET) $(SOURCES) $(LIBS)

endif #debug / release targets


clean:
	rm -f -r $(BUILDDIR)/** $(TARGETDIR_1)/**
	@echo "All objects removed"

.PHONY: clean