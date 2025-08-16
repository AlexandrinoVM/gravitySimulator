CXX = g++
CXXFLAGS = -Wall -std=c++17
LIBS = -lSDL2 -lGL -lGLEW
SRC_DIR = src
BUILD_DIR = build
TARGET = $(BUILD_DIR)/main
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

