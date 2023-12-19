# Compiler
CC = g++

# Compiler flags
CFLAGS = -std=c++11 -w

SRCDIR = Source
INCDIR = Headers
BINDIR = Bin

# Source files
SRCS = $(wildcard $(SRCDIR)/*.cpp)
# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))

# Executable name
EXEC = ECMS

# Main target
all: $(BINDIR)/$(EXEC)

# Linking the executable
$(BINDIR)/$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compiling source files
$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INCDIR)  -c $< -o $@


clean:
	rm -rf $(BINDIR)/*.o $(BINDIR)/$(EXEC)	