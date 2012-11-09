CFLAGS=-Iinclude/klibc/ -Wall -I.. -I. -Iinclude -Iinclude/klibc/cxx -Wno-write-strings -nostdlib -nostartfiles -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -nodefaultlibs -fno-exceptions -m32
CXXFLAGS=-lang=c++ -fno-rtti $(CFLAGS)
LDFLAGS=-Tarch/x86/link.ld -melf_i386
ASFLAGS=-felf 

OBJS=arch/x86/syscall.o arch/x86/cpu.o arch/x86/boot.o arch/x86/dt.o arch/x86/clock.o arch/x86/timer.o arch/x86/io.o arch/x86/arch.o arch/x86/kvideo.o arch/x86/kkeyb.o arch/x86/calls.o
KERNEL=arch/x86/kernel

TCC=gcc
TCP=g++
TAS=as
TLD=ld
TASM=nasm


include Makefile.com

SOURCES=$(OBJS)  Shell.o Elf.o bus/pci/PciBus.o ../Drivers/Vesa/Vesa.o ../Drivers/Framebuffer/Framebuffer.o ../Drivers/Smbios/Smbios.o ../Drivers/Rs232/Rs232.o ../Drivers/Pcspk/Pcspk.o ../Drivers/Rtl8139/Rtl8139.o ui/UiManager.o ui/Window.o ui/Rendering.o ui/widgets/Widget.o ui/widgets/Box.o ui/widgets/Label.o ui/widgets/Button.o ui/widgets/ProgressBar.o media/MediaManager.o security/SecurityManager.o print/PrintManager.o network/NetworkManager.o network/NetworkIface.o network/Packet.o network/netlink/Loopback.o network/netproto/Ipv4.o vfs/VFSManager.o vfs/File.o vfs/Filesystem.o vfs/DevFs.o ../Drivers/Ramdisk/Ramdisk.o vfs/Fat16.o vfs/Iso9660.o vfs/Tarfs.o $(COM_O)

MODULES= Test.o ../Drivers/Random/Random.o mm/paging.o ../Drivers/Mouse/Mouse.o ../Drivers/Keyboard/Keyboard.o

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
	$(RM) $(SOURCES)
drivers: $(MODULES)
	cp $(MODULES) ../drivers/
