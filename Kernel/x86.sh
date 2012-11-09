mkdir isofiles
mkdir isofiles/boot/
mkdir isofiles/drivers
mkdir isofiles/boot/grub/
cp arch/x86/stage2_eltorito isofiles/boot/grub
cp arch/x86/kernel isofiles/kernel
cp arch/x86/menu.lst isofiles/boot/grub
cp ../ramtest_tar.img isofiles/mtest
mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o arch/x86/image.iso isofiles
rm -r isofiles

sleep 1
qemu-system-i386 --no-kvm -cdrom arch/x86/image.iso -m 700
#qemu -cdrom arch/x86/image.iso -usb -m 128 -net nic,model=rtl8139,macaddr=52:54:00:12:34:57 -net user  -soundhw pcspk
#-drive file=arch/x86/menu.lst,if=ide,index=1,media=cdrom
#-serial stdio -net nic,model=ne2k_pci -net user
#-drive file=file,if=ide,index=1,media=cdrom
