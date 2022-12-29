export POK_PATH=$(CURDIR)/../..
export ARCH=x86
export BSP=x86-qemu

include $(POK_PATH)/misc/mk/config.mk
include $(POK_PATH)/misc/mk/common-$(ARCH).mk

TARGET=$(CURDIR)/pok.elf
ARCHIVE=$(CURDIR)/partitions.cpio
PARTITIONS=src/src.elf
KERNEL=kernel/kernel.lo
PARTDIRS=src
SUBDIRS=kernel $(PARTDIRS)

all: build-regular

build-regular: build-kernel partitions $(TARGET)

compiletest: all

build-kernel:
	$(CD) kernel && $(MAKE)

partitions:
	for d in $(PARTDIRS); do $(MAKE) -C $$d clean all || exit 1; done

clean: common-clean
	$(RM) node_impl
	for d in $(SUBDIRS); do $(MAKE) -C $$d clean || exit 1; done

distclean: clean
	for d in $(SUBDIRS); do $(MAKE) -C $$d distclean || exit 1; done

include $(POK_PATH)/misc/mk/rules-common.mk
include $(POK_PATH)/misc/mk/rules-main.mk
include $(POK_PATH)/misc/mk/install-rules.mk