ROOT_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

.PHONY: test

CC       := gcc
CWARN    := all extra error

INCLUDES := $(ROOT_DIR)/unity
INCLUDES += $(ROOT_DIR)/utils

LDLIBS   := -lbsd

CFLAGS   := $(addprefix -W, $(CWARN))
CFLAGS   += $(addprefix -I, $(INCLUDES))
CFLAGS   += -std=gnu11 -g

UNITY_DIR := $(ROOT_DIR)/unity
UTILS_DIR := $(ROOT_DIR)/utils

UTILS_OBJ := $(UTILS_DIR)/utils.o
UNITY_OBJ := $(UNITY_DIR)/unity.o

DEPS := $(UNITY_OBJ) $(UTILS_OBJ)
