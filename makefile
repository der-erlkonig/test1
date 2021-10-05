ARCH=x86_64
VERSION=0.0.2
CC=$(ARCH)-gcc
INC_FLAGS=-Ionvif -IC/include -Ijson-c/include/cjson
LIB_FLAGS=-fPIC --shared
LDFLAGS=-lssl -lcrypto -ldl -lpthread -Ljson-c/lib -lcjson -lcjson_utils
CFLAGS=-O3 -Wall -Wmissing-prototypes
MACRO=-DWITH_OPENSSL -DWITH_DOM
OBJECTS=C/src/manage/manage.o C/src/device/camera_pool.o C/src/discovery/discovery.o C/src/device/device.o C/src/ptz/ptz.o C/src/snap/media.o C/src/utils/soap.o onvif/plugins/wsseapi.o onvif/plugins/wsaapi.o onvif/plugins/threads.o onvif/plugins/smdevp.o onvif/plugins/mecevp.o onvif/dom.o onvif/custom/struct_timeval.o onvif/soapC.o onvif/soapClient.o onvif/stdsoap2.o
TARGET=libonvif.so
AR=$(ARCH)-ar
TAG=$(ARCH)-$(VERSION)

.PHONY: all clean manual dist clean-manual clean-obj prepare onvif

all: prepare $(TARGET) onvif
	cp -pr C/include/* build_$(TAG)/C/include
	-mv *.a build_$(TAG)/C/lib
	-mv *.so build_$(TAG)/C/lib
	cp onvif/custom/*.h build_$(TAG)/C/include/onvif/custom
	cp onvif/extras/*.h build_$(TAG)/C/include/onvif/extras
	cp onvif/plugins/*.h build_$(TAG)/C/include/onvif/plugins
	cp -pr json-c/include/cjson/* build_$(TAG)/C/include/cjson
	cp -pr json-c/lib/* build_$(TAG)/C/lib/cjson

$(TARGET):$(OBJECTS)
	$(CC) $(LIB_FLAGS) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJECTS):%.o:%.c
	$(CC) $(MACRO) $(INC_FLAGS) -c $< -fPIC -o $@

prepare:
	mkdir -p build_$(TAG)/C/include/onvif/custom
	mkdir -p build_$(TAG)/C/include/onvif/extras
	mkdir -p build_$(TAG)/C/include/onvif/plugins
	mkdir -p build_$(TAG)/C/lib
	mkdir -p build_$(TAG)/C/include/cjson
	mkdir -p build_$(TAG)/C/lib/cjson

dist: manual
	mkdir libonvif_$(TAG)
	cp -pr build_$(TAG) libonvif_$(TAG)
	cp -pr manual libonvif_$(TAG)
	cp -pr README.* libonvif_$(TAG)
	cp -pr version.* libonvif_$(TAG)
	tar -czvf libonvif_$(TAG).tar.gz libonvif_$(TAG)
	rm -rf libonvif_$(TAG)

manual:
	mkdir -p manual/C
	mkdir -p doc
	doxygen doxygen/onvif_C
	cd doc/C/latex && $(MAKE)
	cp doc/C/latex/refman.pdf manual/C/manual.pdf
	rm -r doc

clean: clean-manual clean-obj
	-rm *.tar.gz
	-rm nohup.out

clean-manual:
	-rm -r manual

clean-obj:
	-rm $(OBJECTS)
	-rm -r build_$(TAG)
