/*
 * SpiderpigOS
 * Copyright (C) 2009 - 2010 Davide Gessa
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef __PCI_LIST_H
#define __PCI_LIST_H



/* class table def */
typedef struct
{
	uint8_t class_base;		///< Classe base
	uint8_t class_sub;		///< Sotto classe
	uint8_t prog_if;		///< Info aggiuntive
	char *desc_base;		///< Descrizione base
	char *desc_sub;			///< Descrizione avanzata
	char *desc_prog;		///< Descrizione info aggiuntive
} pci_classtable_t;


/* class table */
pci_classtable_t pci_class_code_table [] =
{
	{ 0x00, 0x00, 0x00, "Pre2.0 PCI Specification Device", "Non-VGA",""  } ,
	{ 0x00, 0x01, 0x00, "Pre2.0 PCI Specification Device", "VGA Compatible", ""  } ,

	{ 0x01, 0x00, 0x00, "Mass Storage Controller", "SCSI", "" } ,
	{ 0x01, 0x01, 0x00, "Mass Storage Controller", "IDE", ""  } ,
	{ 0x01, 0x02, 0x00, "Mass Storage Controller", "Floppy", "" } ,
	{ 0x01, 0x03, 0x00, "Mass Storage Controller", "IPI", ""  } ,
	{ 0x01, 0x04, 0x00, "Mass Storage Controller", "RAID", "" } ,
	{ 0x01, 0x80, 0x00, "Mass Storage Controller", "Other", ""  } ,

	{ 0x02, 0x00, 0x00, "Network Controller", "Ethernet", ""  } ,
	{ 0x02, 0x01, 0x00, "Network Controller", "Token Ring", ""  } ,
	{ 0x02, 0x02, 0x00, "Network Controller", "FDDI", ""  } ,
	{ 0x02, 0x03, 0x00, "Network Controller", "ATM", ""  } ,
	{ 0x02, 0x80, 0x00, "Network Controller", "Other", ""  } ,

	{ 0x03, 0x00, 0x00, "Display Controller", "PC Compatible", "VGA"  } ,
	{ 0x03, 0x00, 0x01, "Display Controller", "PC Compatible", "8514"  } ,
	{ 0x03, 0x01, 0x00, "Display Controller", "XGA", "" } ,
	{ 0x03, 0x80, 0x00, "Display Controller", "Other", ""  } ,

	{ 0x04, 0x00, 0x00, "Multimedia Device", "Video", ""  } ,
	{ 0x04, 0x01, 0x00, "Multimedia Device", "Audio", ""  } ,
	{ 0x04, 0x80, 0x00, "Multimedia Device", "Other", ""  } ,

	{ 0x05, 0x00, 0x00, "Memory Controller", "RAM", ""  } ,
	{ 0x05, 0x01, 0x00, "Memory Controller", "Flash", ""  } ,
	{ 0x05, 0x80, 0x00, "Memory Controller", "Other", ""  } ,

	{ 0x06, 0x00, 0x00, "Bridge Device", "Host/PCI", ""  } ,
	{ 0x06, 0x01, 0x00, "Bridge Device", "PCI/ISA", ""  } ,
	{ 0x06, 0x02, 0x00, "Bridge Device", "PCI/EISA", "" } ,
	{ 0x06, 0x03, 0x00, "Bridge Device", "PCI/Micro Channel", ""  } ,
	{ 0x06, 0x04, 0x00, "Bridge Device", "PCI/PCI", ""  } ,
	{ 0x06, 0x05, 0x00, "Bridge Device", "PCI/PCMCIA", ""  } ,
	{ 0x06, 0x06, 0x00, "Bridge Device", "PCI/NuBus", ""  } ,
	{ 0x06, 0x07, 0x00, "Bridge Device", "PCI/CardBus", ""  } ,
	{ 0x06, 0x80, 0x00, "Bridge Device", "Other", ""  } ,

	{ 0x07, 0x00, 0x00, "Simple Communications Controller", "Serial", "Generic XT Compatible"  } ,
	{ 0x07, 0x00, 0x01, "Simple Communications Controller", "Serial", "16450 Compatible"  } ,
	{ 0x07, 0x00, 0x02, "Simple Communications Controller", "Serial", "16550 Compatible"  } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Standard"  } ,
	{ 0x07, 0x01, 0x00, "Simple Communications Controller", "Parallel", "Bidirectional"  } ,
	{ 0x07, 0x01, 0x01, "Simple Communications Controller", "Parallel", "ECP 1.X Compliant" } ,
	{ 0x07, 0x80, 0x02, "Simple Communications Controller", "Other", ""  } ,

	{ 0x08, 0x00, 0x00, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "Generic 8259"  } ,
	{ 0x08, 0x00, 0x01, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "ISA"  } ,
	{ 0x08, 0x00, 0x02, "Base Systems Peripheral", "PIC (Programmable Interrupt Controller)", "PCI"  } ,
	{ 0x08, 0x01, 0x00, "Base Systems Peripheral", "DMA (Direct Memory Access)", "Generic 8259"  } ,
	{ 0x08, 0x01, 0x01, "Base Systems Peripheral", "DMA (Direct Memory Access)", "ISA"  } ,
	{ 0x08, 0x01, 0x02, "Base Systems Peripheral", "DMA (Direct Memory Access)", "EISA"  } ,
	{ 0x08, 0x02, 0x00, "Base Systems Peripheral", "System Timer", "Generic 8259"  } ,
	{ 0x08, 0x02, 0x01, "Base Systems Peripheral", "System Timer", "ISA"  } ,
	{ 0x08, 0x02, 0x02, "Base Systems Peripheral", "System Timer", "EISA"  } ,
	{ 0x08, 0x03, 0x00, "Base Systems Peripheral", "RTC (Real Time Clock)", "Generic"  } ,
	{ 0x08, 0x03, 0x01, "Base Systems Peripheral", "RTC (Real Time Clock)", "ISA"  } ,
	{ 0x08, 0x80, 0x00, "Base Systems Peripheral", "Other" } ,

	{ 0x09, 0x00, 0x00, "Input Device", "Keyboard", ""  } ,
	{ 0x09, 0x01, 0x00, "Input Device", "Digitizer (Pen)", ""  } ,
	{ 0x09, 0x02, 0x00, "Input Device", "Mouse", ""  } ,
	{ 0x09, 0x80, 0x00, "Input Device", "Other", ""  } ,

	{ 0x0A, 0x00, 0x00, "Docking Station", "Generic", ""  } ,
	{ 0x0A, 0x80, 0x00, "Docking Station", "Other", ""  } ,

	{ 0x0B, 0x00, 0x00, "Processor", "i386", ""  } ,
	{ 0x0B, 0x01, 0x00, "Processor", "i486", ""  } ,
	{ 0x0B, 0x02, 0x00, "Processor", "Pentium", ""  } ,
	{ 0x0B, 0x10, 0x00, "Processor", "Alpha", ""  } ,
	{ 0x0B, 0x20, 0x00, "Processor", "Power PC", ""  } ,
	{ 0x0B, 0x80, 0x00, "Processor", "Co-processor", "" } ,

	{ 0x0C, 0x00, 0x00, "Serial Bus Controller", "Firewire (IEEE 1394)", ""  } ,
	{ 0x0C, 0x01, 0x00, "Serial Bus Controller", "ACCESS.bus", ""  } ,
	{ 0x0C, 0x02, 0x00, "Serial Bus Controller", "SSA (Serial Storage Archetecture)", ""  } ,
	{ 0x0C, 0x03, 0x00, "Serial Bus Controller", "USB (Universal Serial Bus)", ""} ,
	{ 0x0C, 0x04, 0x00, "Serial Bus Controller", "Fibre Channel", "" } ,

	{ 0xFF, 0x00, 0x00, "Unknown", "Device Does Not Fit In Class Codes", "UDF" } ,
};

/* lenght of class_table */
#define	PCI_CLASS_CODE_TABLE_LEN (sizeof(pci_class_code_table)/sizeof(pci_classtable_t))


#endif
