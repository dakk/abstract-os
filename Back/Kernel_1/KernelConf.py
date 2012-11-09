# AbastractOS
# Copyright (C) 2011 Davide Gessa
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.


contents_arch = [ ["ARCH_X86", "-Wall -I.. -I. -Iinclude -Iinclude/klibc/cxx -Wno-write-strings -nostdlib -nostartfiles -ffreestanding -fno-stack-protector -nostdlib -nostdinc -fno-builtin -nodefaultlibs -fno-exceptions", "-Tarch/x86/link.ld", "-felf", "arch/x86/boot.o arch/x86/dt.o arch/x86/clock.o arch/x86/timer.o arch/x86/io.o arch/x86/arch.o arch/x86/kvideo.o arch/x86/kkeyb.o arch/x86/calls.o", "arch/x86/kernel", "gcc", "as", "ld", "nasm", ["BIT32", "ARCH \"x86\"", "X86"]] ]
#--fast-math -mmmx -msse -msse2 -msse3 -m3dnow 
contents =  [ 	
				["VESA", ["VESA"], "../Drivers/Vesa/Vesa.o", []],
				["MOUSE", ["MOUSE"], "../Drivers/Mouse/Mouse.o", []],
				["KEYBOARD", ["KEYBOARD"], "../Drivers/Keyboard/Keyboard.o", []],
				["FRAMEBUFFER", ["FRAMEBUFFER"], "../Drivers/Framebuffer/Framebuffer.o", []],
				["NETWORK", ["NETWORK"], "network/NetworkManager.o network/NetworkIface.o network/Packet.o", []],
				["NETWORK_LO", ["NETWORK_LO"], "network/netlink/Loopback.o", []],
				["NETWORK_IPV4", ["NETWORK_IPV4"], "network/netproto/Ipv4.o", []],
				["VFS", ["VFS"], "vfs/VFSManager.o vfs/File.o vfs/Filesystem.o vfs/DevFs.o", []],
				["FAT16", ["FAT16"], "vfs/Fat16.o", []],
				["ISO9660", ["ISO9660"], "vfs/Iso9660.o", []],
				["RAMDISK", ["RAMDISK"], "../Drivers/Ramdisk/Ramdisk.o", []],
				["SMBIOS", ["SMBIOS"], "../Drivers/Smbios/Smbios.o", []],
				["RS232", ["RS232"], "../Drivers/Rs232/Rs232.o", []],
				["PCSPK", ["PCSPK"], "../Drivers/Pcspk/Pcspk.o", []],
				["ELF", ["ELF"], "Elf.o", []],
				["RANDOM", ["RANDOM"], "../Drivers/Random/Random.o", []],
				["PCIBUS", ["PCIBUS"], "bus/pci/PciBus.o", []],
				["RTL8139", ["RTL8139"], "../Drivers/Rtl8139/Rtl8139.o", []],
				["ABGUI", ["ABGUI"], "abgui/abButton.o abgui/abText.o abgui/abLabel.o abgui/abImage.o abgui/abTheme.o abgui/abGuiManager.o abgui/abWidget.o abgui/abWindow.o", []],
				["ABGUI_LOADER", ["ABGUI_LOADER"], "abgui/abLoader.o", []]
			]


ls = open("Config", "r").read().split("\n")
makefile = "include Makefile.com\n\n"
config = "#ifndef __CONFIG_H\n#define __CONFIG_H\n\n"
sources = "SOURCES=$(OBJS) "
modules = "MODULES="
with_c = '#define CONTENTS "'

for x in ls:
	if len(x) > 0 and x[0] == "#": 
		continue
	
	# Arch?
	for i in contents_arch:
		if i[0] == x:
			makefile += "CFLAGS=-Iinclude/klibc/ "+i[1]+"\n"
			makefile += "CXXFLAGS=-lang=c++ -fno-rtti $(CFLAGS)\n"
			makefile += "LDFLAGS="+i[2]+"\n"
			makefile += "ASFLAGS="+i[3]+"\n\n"
			makefile += "OBJS="+i[4]+"\n"
			makefile += "KERNEL="+i[5]+"\n\n"
			makefile += "TCC="+i[6]+"\n"
			makefile += "TCP=g++\n"
			makefile += "TAS="+i[7]+"\n"
			makefile += "TLD="+i[8]+"\n"
			makefile += "TASM="+i[9]+"\n\n\n"
			config += "#define "+i[0]+"\n"
			for j in i[10]:
				config += "#define "+j+"\n"
			
	for i in contents:
		if i[0] == x.split("=")[0]:
			print x
			if x.split("=")[1] == "y":
				for j in i[1]:
					config += "#define "+j+"\n"
					with_c += j+" "
				sources += " " + i[2]
			else:# x.split("=")[1] == "m":
				modules += " " + i[2]
			
			
makefile += sources+" $(COM_O)\n\n"
makefile += modules+"\n\n"

makefile += "all: $(SOURCES) link\n"
makefile += ".s.o:\n"
makefile += "\t$(ASM) $(ASFLAGS) $<\n"
makefile += ".c.o:\n"
makefile += "\t$(CC) $(CFLAGS) -c $< -o $@\n"
makefile += ".cpp.o:\n"
makefile += "\t$(CPP) $(CXXFLAGS) -c $< -o $@\n"
makefile += "link:\n"
makefile += "\t$(LD) $(LDFLAGS) -o arch/x86/kernel $(SOURCES)\n\n"
makefile += "clean:\n\trm $(SOURCES)\n"
makefile += "drivers: $(MODULES)\n"
#makefile += "link_mod:\n"
#makefile += "\t$(LD) -Tarch/x86/link.ld  -o $<.ko $<\n\n"
if modules != "MODULES=":
	makefile += "\tcp $(MODULES) ../drivers/\n"
	#makefile += "\tcd ../drivers/\n"
	#makefile += '\tfor i in *.o; do mv $i ${i/.o}.ko; done\n'

with_c += '"\n\n'
config += "\n\n"+with_c+"#endif\n"

f = open("include/config.h", "w")
f.write(config)
f.close()

f = open("Makefile", "w")
f.write(makefile)
f.close()
