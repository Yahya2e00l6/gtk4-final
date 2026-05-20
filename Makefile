CC = gcc
PKG_CONFIG_CFLAGS := $(shell pkg-config --cflags gtk4)
PKG_CONFIG_LIBS := $(shell pkg-config --libs gtk4)
CFLAGS = $(PKG_CONFIG_CFLAGS) -Iinclude -I. -MMD -MP -O2
DEBUG_FLAGS = -g
LIBS = $(PKG_CONFIG_LIBS)
MAKEFLAGS += -j$(shell nproc)

BUILD_DIR = build
TARGET = $(BUILD_DIR)/gtk-app
SRC = main.c src/demo_app.c \
	src/widgets/common.c \
	src/widgets/window.c \
	src/widgets/container.c \
	src/widgets/button.c \
	src/widgets/input.c \
	src/widgets/toggle.c \
	src/widgets/display.c \
	src/widgets/date.c \
	src/widgets/separator.c \
	src/widgets/dialog.c \
	src/widgets/menu.c \
	src/widgets/theme.c \
	src/pages/icons_page.c \
	src/pages/toolbar_page.c \
	src/pages/inputs_page.c \
	src/pages/buttons_page.c \
	src/pages/toggles_page.c \
	src/pages/displays_page.c \
	src/pages/dialogs_page.c

OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRC))
DEP = $(OBJ:.o=.d)

# XML demo target
XML_TARGET = $(BUILD_DIR)/xml-demo
XML_DIR = examples/xml
XML ?= $(XML_DIR)/demo_app.xml
XML_SRC = xml_demo_main.c \
	src/widgets/xml_parser.c \
	src/widgets/common.c \
	src/widgets/window.c \
	src/widgets/container.c \
	src/widgets/button.c \
	src/widgets/input.c \
	src/widgets/toggle.c \
	src/widgets/display.c \
	src/widgets/date.c \
	src/widgets/separator.c \
	src/widgets/dialog.c \
	src/widgets/menu.c \
	src/widgets/theme.c
XML_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(XML_SRC))
XML_DEP = $(XML_OBJ:.o=.d)

# Assignment demo built with wrapper C APIs
ASSIGNMENT_TARGET = $(BUILD_DIR)/assignment-api
ASSIGNMENT_SRC = examples/c/assignment_api_main.c \
	src/widgets/common.c \
	src/widgets/window.c \
	src/widgets/container.c \
	src/widgets/button.c \
	src/widgets/input.c \
	src/widgets/toggle.c \
	src/widgets/display.c \
	src/widgets/dialog.c \
	src/widgets/menu.c \
	src/widgets/theme.c
ASSIGNMENT_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(ASSIGNMENT_SRC))
ASSIGNMENT_DEP = $(ASSIGNMENT_OBJ:.o=.d)

# Layout stress demo built with wrapper C APIs
LAYOUT_STRESS_TARGET = $(BUILD_DIR)/layout-stress-api
LAYOUT_STRESS_SRC = examples/c/layout_stress_api_main.c \
	src/widgets/common.c \
	src/widgets/window.c \
	src/widgets/container.c \
	src/widgets/button.c \
	src/widgets/input.c \
	src/widgets/toggle.c \
	src/widgets/display.c \
	src/widgets/theme.c
LAYOUT_STRESS_OBJ = $(patsubst %.c,$(BUILD_DIR)/%.o,$(LAYOUT_STRESS_SRC))
LAYOUT_STRESS_DEP = $(LAYOUT_STRESS_OBJ:.o=.d)

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

$(XML_TARGET): $(XML_OBJ)
	$(CC) $(CFLAGS) -o $(XML_TARGET) $(XML_OBJ) $(LIBS)

$(ASSIGNMENT_TARGET): $(ASSIGNMENT_OBJ)
	$(CC) $(CFLAGS) -o $(ASSIGNMENT_TARGET) $(ASSIGNMENT_OBJ) $(LIBS)

$(LAYOUT_STRESS_TARGET): $(LAYOUT_STRESS_OBJ)
	$(CC) $(CFLAGS) -o $(LAYOUT_STRESS_TARGET) $(LAYOUT_STRESS_OBJ) $(LIBS)

$(BUILD_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

clean:
	rm -rf $(BUILD_DIR)

run: $(TARGET)
	$(TARGET)

xml-demo: $(XML_TARGET)
	$(XML_TARGET) $(XML)

assignment-api: $(ASSIGNMENT_TARGET)
	$(ASSIGNMENT_TARGET)

layout-stress-api: $(LAYOUT_STRESS_TARGET)
	$(LAYOUT_STRESS_TARGET)

.PHONY: all clean debug run xml-demo assignment-api layout-stress-api

-include $(DEP) $(XML_DEP) $(ASSIGNMENT_DEP) $(LAYOUT_STRESS_DEP)
