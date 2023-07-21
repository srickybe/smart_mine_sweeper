CXX = g++
CXXFLAGS = -g -O3 -pg -Wall
LDFLAGS = -lGL -lGLU -lSDL -pthread
INCDIR = .
SRCDIR = .
OBJDIR = .

# Define a list of object files derived from a list of .cpp source files
OBJECTS = $(addprefix $(OBJDIR)/,$(patsubst %.cpp,%.o,$(wildcard $(SRCDIR)/*.cpp)))

# Provide an implicit dependency rule for building the objects.
$(OBJDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.h
	$(CXX) -c $(CXXFLAGS) -o $(OBJDIR)/$(SRCDIR)/$*.o $<

# Provide an explicit rule for building the application from the objects.
main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJECTS) -o main

clean:
	rm -f $(OBJDIR)/$(SRCDIR)/*.o main