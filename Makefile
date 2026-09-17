CC = clang++

FLAGS = -DDEBUG -D_DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align \
		-Wcast-qual -Wchar-subscripts -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral \
		-Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual -Wpacked \
		-Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 \
		-Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef -Wunreachable-code -Wunused -Wvariadic-macros \
		-Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new \
		-fsized-deallocation -fstack-protector -fstrict-overflow -fno-omit-frame-pointer -Wlarger-than=8192 -fPIE \
		-Werror=vla -fsanitize=address,undefined,float-divide-by-zero,integer-divide-by-zero,vptr

LDFLAGS = -isystem /opt/homebrew/include -L/opt/homebrew/lib -lraylib \
          -framework OpenGL -framework Cocoa -framework IOKit

COMMON_INCLUDES = -I./include

COMMON_FILES = src/Colors.cpp src/Adapter.cpp src/Scene.cpp src/LightManager.cpp src/Camera2D.cpp src/Sphere.cpp src/Button.cpp

WORK_DIR = ./work
BUILD_DIR = ./work/build
RUN_DIR = ./work/run
TARGET = $(RUN_DIR)/vec_program

all: vec

vec: main.cpp $(COMMON_FILES)
	@mkdir -p $(WORK_DIR)
	@mkdir -p $(BUILD_DIR) $(RUN_DIR)
	@echo "-----------------------------------------------------------------------------------------"
	$(CC) -o $(BUILD_DIR)/vec_program $(FLAGS) $(LDFLAGS) main.cpp $(COMMON_INCLUDES) $(COMMON_FILES)
	
	@mv $(BUILD_DIR)/vec_program $(TARGET)
	@echo "-----------------------------------------------------------------------------------------"


run-vec: vec
	$(TARGET)

run: run-vec

clean:
	rm -rf $(WORK_DIR)

help:
	@echo "Available commands:"
	@echo ""
	@echo "  make vec                     - compile a vec"
	@echo "  make run-vec                 - compile and run vec"
	@echo "  make run                     - compile and run vec"
	@echo ""
	@echo "  make clean                   - remove compiled programs"

.PHONY: vec run-vec run clean help
