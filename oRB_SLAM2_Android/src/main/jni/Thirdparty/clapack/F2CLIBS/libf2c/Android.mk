LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(LOCAL_PATH)/Config.mk

LOCAL_MODULE:= libf2c
LOCAL_SRC_FILES:= $(OFILES)
LOCAL_CFLAGS:= -O3 -DSkip_f2c_Undefs -DNO_LONG_LONG
LOCAL_COPY_HEADERS:= f2c.h
LOCAL_ARM_MODE:= arm

include $(BUILD_STATIC_LIBRARY)

MISC:=
POW:=
CX:=
DCX:=
REAL:=
DBL:=
INT:=
HALF:=
CMP:=
EFL:=
CHAR:=
I77:=
QINT:=
TIME:=
OFILES:=

