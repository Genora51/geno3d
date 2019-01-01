CXX=clang++
SRCDIR=src
BUILDDIR=build
RESDIR=res
TARGETDIR=bin
TARGET=geno3d

SRCEXT=cpp
SOURCES = $(wildcard $(SRCDIR)/*.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CXXFLAGS = -std=c++17 -Wall -pedantic
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system
# LDFLAGS = -L lib

$(TARGETDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo "Linking..."
	$(CXX) $^ -o $(TARGETDIR)/$(TARGET) $(LDFLAGS) $(LDLIBS)
	@echo "Copying resources..."
	@cp -a $(RESDIR) $(TARGETDIR)/

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning..."
	$(RM) -r $(BUILDDIR) $(TARGETDIR)

debug: CXXFLAGS += -DDEBUG -g
debug: $(TARGETDIR)/$(TARGET)

fast: CXXFLAGS += -O2
fast: $(TARGETDIR)/$(TARGET)


.PHONY: clean debug
