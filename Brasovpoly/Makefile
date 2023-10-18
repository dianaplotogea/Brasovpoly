CXX = g++
CXXFLAGS = -I"C:\Users\Robi\Documents\libraries\SFML-2.6.0\include" -DSFML_STATIC
LDFLAGS = -L"C:\Users\Robi\Documents\libraries\SFML-2.6.0\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main
SOURCES = $(wildcard *.cpp) $(wildcard UI/*.cpp) $(wildcard Gameplay/*.cpp) $(wildcard Menu/*.cpp) # All the directories in which there is code, have to be included here
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)