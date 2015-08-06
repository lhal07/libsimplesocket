CC=gcc -O3
OBJ_LINK= -fPIC -Wall -c
SHR_LINK = -shared
LINK= ln -s
LIB=simplesocket
LIBNAME=lib$(LIB)
SRC_DIR=src
LIB_DIR=lib
BIN_DIR=bin
INC_DIR=include
RM=rm -f
CP=cp -rf
APP=socket_cli
TARGET=/usr

default: lib $(APP)

all: lib $(APP) install

install:
	$(CP) $(LIB_DIR)/$(LIBNAME).so.0.0 $(TARGET)/lib/
	$(CP) $(LIB_DIR)/$(LIBNAME).so.0 $(TARGET)/lib/
	$(CP) $(LIB_DIR)/$(LIBNAME).so $(TARGET)/lib/
	$(CP) $(BIN_DIR)/$(APP) $(TARGET)/bin/

lib_dir:
	mkdir -p $(LIB_DIR)

bin_dir:
	mkdir -p $(BIN_DIR)

lib: $(LIB_DIR)/$(LIBNAME).so 

$(APP): $(BIN_DIR)/$(APP)

$(LIB_DIR)/$(LIBNAME).so: $(SRC_DIR)/$(LIBNAME).o lib_dir
	$(CC) -fPIC -shared -Wl,-soname,$(LIB_DIR)/$(LIBNAME).so.0 -I$(INC_DIR) -o $(LIB_DIR)/$(LIBNAME).so.0.0 $(SRC_DIR)/$(LIBNAME).o
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so
	$(LINK) $(LIBNAME).so.0.0 $(LIB_DIR)/$(LIBNAME).so.0
	$(LINK) $(LIBNAME).so.0 $(LIB_DIR)/$(LIBNAME).so

$(SRC_DIR)/$(LIBNAME).o: $(INC_DIR)/$(LIB).h $(SRC_DIR)/$(LIBNAME).c
	$(CC) $(OBJ_LINK) -I$(INC_DIR) $(SRC_DIR)/$(LIBNAME).c -o $(SRC_DIR)/$(LIBNAME).o


$(BIN_DIR)/$(APP): $(SRC_DIR)/$(APP).c bin_dir
	$(CC) -I$(INC_DIR) -L$(LIB_DIR) $(SRC_DIR)/$(APP).c -o $(BIN_DIR)/$(APP) -l$(LIB)

clean:
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so.0
	$(RM) $(LIB_DIR)/$(LIBNAME).so
	$(RM) $(SRC_DIR)/$(LIBNAME).o
	$(RM) $(BIN_DIR)/$(APP)
