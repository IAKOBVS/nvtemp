ARCH   := $(shell getconf LONG_BIT)

ifeq (${ARCH},$(filter ${ARCH},32 64))
   NVML_LIB := ../lib/
else
   $(error Unknown architecture!)
endif

CFLAGS  := -I ../include -I /opt/cuda/include
LDFLAGS := -lnvidia-ml -L $(NVML_LIB)

nvtemp: nvtemp.o
	$(CC) $< $(LDFLAGS) -o $@

clean:
	-@rm -f nvtemp.o
	-@rm -f nvtemp
