#include "PciBus.hpp"
#include <arch.h>
#include "PciList.h"
#include <stdio.h>


PciBus::PciBus()
{
	m_PciDeviceList = new list<PciBus::Device>();
}


PciBus::~PciBus()
{
	delete m_PciDeviceList;
}

bool
PciBus::Probe()
{
	return true;
}


list<PciBus::Device> *
PciBus::getDeviceList()
{
	return m_PciDeviceList;
}



uint32_t 
PciBus::Read(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint8_t size)
{
	uint32_t value;
	io_outd(0xCF8,  0x80000000 | (bus << 16) | (device << 11) | (function << 8) | (offset & ~3));

	switch (size)
	{
		case 1: 
			value = io_inb(0xCFC + (offset & 3)); 
			break;

		case 2: 
			value = io_inw(0xCFC + (offset & 2)); 
			break;

		case 4: 
			value = io_ind(0xCFC); 
			break;

		default:
			return 0xFF;
	}
	return value;
}



/** Get the device from the bus*/
PciBus::Device *
PciBus::getBusDevice(uint32_t bus, uint32_t device, uint32_t func)
{
	unsigned i;

	uint32_t tmp = Read(bus, device, func, VENDOR_ID, 2);
	if ((tmp == 0xFFFF) || (tmp == 0x0000)) 
		return NULL;

	PciBus::Device *pci_dev = (PciBus::Device *) malloc(sizeof(PciBus::Device));

	pci_dev->Bus = bus;
	pci_dev->Device = device;
	pci_dev->Function = func;

	pci_dev->VendorId = Read(bus, device, func, VENDOR_ID, 2);
	pci_dev->DeviceId = Read(bus, device, func, DEVICE_ID, 2);

	pci_dev->Command = Read(bus, device, func, COMMAND, 2);
	pci_dev->Status = Read(bus, device, func, STATUS, 2);
	//pci_dev->RevId = Read(bus, device, func, REVISION, 2);
	//pci_dev->Iface = Read(bus, device, func, PCI_INTERFACE, 1);

	pci_dev->ClassId = Read(bus, device, func, CLASS_BASE, 1);
	pci_dev->SubclassId = Read(bus, device, func, CLASS_SUB, 1);

	for(i = 0; i < 6; i++)
		pci_dev->Bar[i] = Read(bus, device, func, BASE_REGISTERS + (i * 4), 4);

	pci_dev->IntLine = Read(bus, device, func, INTERRUPT_LINE, 1);
	pci_dev->IntPin = Read(bus, device, func, INTERRUPT_PIN, 1);
	
	for(i = 0; i < PCI_CLASS_CODE_TABLE_LEN; i++)
		if(	(pci_class_code_table[i].class_base == pci_dev->ClassId) &&
			(pci_class_code_table[i].class_sub == pci_dev->SubclassId))
		{
			strcpy(pci_dev->Class, pci_class_code_table[i].desc_base);
			strcpy(pci_dev->ClassDesc, pci_class_code_table[i].desc_sub);
			
			//printf("%s %s\n", pci_dev->Class, pci_dev->ClassDesc);
			break;
		}

	return pci_dev;
}



/** Update the pci device list */
uint32_t 
PciBus::Update()
{
	unsigned n = 0;
	unsigned int bus, device, func;
	
	m_PciDeviceList->Clear();

	for(bus = 0; bus < 16; bus++)
		for(device = 0; device < 12; device++)
			for(func = 0; func < 12; func++)
			{
				PciBus::Device *newdev = getBusDevice(bus, device, func);

				if(newdev != NULL)
				{
					m_PciDeviceList->addNode(newdev);
					n++;
				}
			}
	return n;
}






PciBus::Device *
PciBus::getDevice(Entry **m, unsigned size)
{
	unsigned i;
	PciBus::Device *d;

	for(i = 0; i < size; i++)
	{
		d = getDevice(m[i]);
		if(d != NULL)
			return d;
	}
	return NULL;
}


/** Get the device with passed Vendor and Device, getting it from the pcidevlist */
PciBus::Device *
PciBus::getDevice(PciBus::Entry *m)
{
	PciBus::Device *d = m_PciDeviceList->getNode(0);


	while(d != NULL)
	{
		if((m->DeviceId == d->DeviceId) && (m->VendorId == d->VendorId))	
			return d;

		d = d->Next;
	}

	return NULL;
}

