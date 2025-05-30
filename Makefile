# Libraries
GLFW := -lglfw3 -lopengl32 -lgdi32
GLEW := -lglew32
LIBS := -lm

# Source directory
SRC_DIR := src
APP_DIR := app
BUILD_DIR := build

# Debug and release flags
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O3

CXXFLAGS := -std=c++20 -I include 
CXX := clang++

# Default target
all: release

debug: BUILD_DIR := $(BUILD_DIR)/debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(BUILD_DIR)/program

release: BUILD_DIR +=/release
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(BUILD_DIR)/program

profile: debug
profile: CXXFLAGS += -pg


# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(APP_DIR)/*.cpp)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

# Target for the executable
$(BUILD_DIR)/program: $(OBJS)
	$(CXX) $(CXXFLAGS) -L lib $^ -o $@ $(GLFW) $(GLEW) $(LIBS)

# Target for object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(APP_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Clean target
clean:
	del build\*.o
	del build\*.exe


.PHONY: all debug release clean
