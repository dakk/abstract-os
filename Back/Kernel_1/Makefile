include Makefile.com

CFLAGS=-Iinclude/klibc/ -Wall -I.. -I. -Iinclude -Iinclude/klibc/cxx -Wno-write-strings -nostdlib -nostartfiles -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -nodefaultlibs -fno-exceptions
CXXFLAGS=-lang=c++ -fno-rtti $(CFLAGS)
LDFLAGS=-Tarch/x86/link.ld
ASFLAGS=-felf

OBJS=arch/x86/boot.o arch/x86/dt.o arch/x86/clock.o arch/x86/timer.o arch/x86/io.o arch/x86/arch.o arch/x86/kvideo.o arch/x86/kkeyb.o arch/x86/calls.o
KERNEL=arch/x86/kernel

TCC=gcc
TCP=g++
TAS=as
TLD=ld
TASM=nasm


SOURCES=$(OBJS)  Elf.o ../Drivers/Random/Random.o bus/pci/PciBus.o ../Drivers/Vesa/Vesa.o ../Drivers/Mouse/Mouse.o ../Drivers/Keyboard/Keyboard.o ../Drivers/Framebuffer/Framebuffer.o ../Drivers/Smbios/Smbios.o ../Drivers/Rs232/Rs232.o ../Drivers/Pcspk/Pcspk.o ../Drivers/Rtl8139/Rtl8139.o network/NetworkManager.o network/NetworkIface.o network/Packet.o network/netlink/Loopback.o network/netproto/Ipv4.o vfs/VFSManager.o vfs/File.o vfs/Filesystem.o vfs/DevFs.o ../Drivers/Ramdisk/Ramdisk.o vfs/Fat16.o vfs/Iso9660.o abgui/abButton.o abgui/abText.o abgui/abLabel.o abgui/abImage.o abgui/abTheme.o abgui/abGuiManager.o abgui/abWidget.o abgui/abWindow.o abgui/abLoader.o $(COM_O)

MODULES=

all: $(SOURCES) link
.s.o:
	$(ASM) $(ASFLAGS) $<
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
.cpp.o:
	$(CPP) $(CXXFLAGS) -c $< -o $@
link:
	$(LD) $(LDFLAGS) -o arch/x86/kernel $(SOURCES)

clean:
	rm $(SOURCES)
drivers: $(MODULES)
