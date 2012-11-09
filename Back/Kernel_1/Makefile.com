KLIBC = klibc/assert.o klibc/malloc.o klibc/math.o klibc/stdio.o klibc/string.o \
        klibc/time.o klibc/typeconv.o
KLIBCPP = klibc/cxx/iostream.o
MEM	  = mm/phys.o mm/mm.o
COM_O = arch/arch.o Main.o Driver.o Term.o Device.o DeviceManager.o DriverManager.o Task.o TaskManager.o $(KLIBC) $(KLIBCPP) $(MEM)


PROMPT = " -> "
AR = @echo "   " $(PROMPT) AR "    " $ && ar
CD = @echo  $(PROMPT) CD "        " && cd
LD = @echo "   " $(PROMPT) LD "    " $ && $(TLD)
CC = @echo "   " $(PROMPT) CC "    " $< && $(TCC)
CPP = @echo "   " $(PROMPT) CPP "   " $< && $(TCP)
ASM = @echo "   " $(PROMPT) ASM "   " $< && $(TASM)
AS = @echo "   " $(PROMPT) AS "   " $< && $(TAS)

