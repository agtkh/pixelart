CC		= g++
CFLAGS	= -Wall -O3 -std=c++11
PROG	= pixelart
SRCDIR 	= ./src
SRCEXT = cpp
OBJDIR = ./obj
SRCS 	= $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJS 	= $(SRCS:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.o)
DEPS 	= $(SRCS:$(SRCDIR)/%.$(SRCEXT)=$(OBJDIR)/%.d)
INCDIR 	=
LIBSDIR =
LIBS 	= 



# Create executable file
$(PROG): $(OBJS)
	$(CC) $(LIBS) $^ -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Create object files
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(OBJDIR)/%.d
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

# Create dependency files.
$(DEPS): $(OBJDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	@$(CC) $(CFLAGS) $(INCDIR) $< -MM -MP -MF $@

# Only include dependency files that exist.
include $(shell ls ${DEPS} 2>/dev/null)

all: clean $(PROG)

clean:
	-rm -rf $(PROG) $(OBJDIR) 
	
do: $(PROG)
	./$(PROG)

