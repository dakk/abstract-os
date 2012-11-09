#ifndef PCIBUS_HPP
#define PCIBUS_HPP

#include <types.h>
#include <list.hpp>

class PciBus
{
	public:
		static const unsigned VENDOR_ID      = 0x00; /* (2 byte) vendor id */
		static const unsigned DEVICE_ID      = 0x02; /* (2 byte) device id */
		static const unsigned COMMAND        = 0x04; /* (2 byte) command */
		static const unsigned STATUS         = 0x06; /* (2 byte) status */
		static const unsigned REVISION_ID    = 0x08; /* (1 byte) revision id */
		static const unsigned CLASS_API      = 0x09; /* (1 byte) specific register interface type */
		static const unsigned CLASS_SUB      = 0x0A; /* (1 byte) specific device function */
		static const unsigned CLASS_BASE     = 0x0B; /* (1 byte) device type (display vs network, etc) */
		static const unsigned LINE_SIZE      = 0x0C; /* (1 byte) cache line size in 32 bit words */
		static const unsigned LATENCY        = 0x0D; /* (1 byte) latency timer */
		static const unsigned HEADER_TYPE    = 0x0E; /* (1 byte) header type */
		static const unsigned BIST           = 0x0F; /* (1 byte) built-in self-test */
		static const unsigned BASE_REGISTERS = 0x10; /* base registers (size varies) */
		static const unsigned SUBSYS_VEND_ID = 0x2C; /* (2 byte) subsystem vendor id */
		static const unsigned SUBSYS_DEV_ID  = 0x2E; /* (2 byte) subsystem id */
		static const unsigned INTERRUPT_LINE = 0x3C; /* (1 byte) interrupt line */
		static const unsigned INTERRUPT_PIN  = 0x3D;

		/** Pci bus data */
		typedef struct Device
		{
			uint32_t Bus;					///< Bus del device
			uint32_t Function;
			uint32_t Device;
	
			uint32_t Command;
			uint32_t Status;
			uint32_t RevId;
			uint32_t Iface;
	
			uint32_t VendorId;				///< Id del costruttore
			uint32_t DeviceId;				///< Id del device
			uint32_t ClassId;				///< Classe base id
			uint32_t SubclassId;			///< Sotto classe id	

			uint32_t Bar[6];
			uint32_t IntLine;
			uint32_t IntPin;

			char Class[128];
			char ClassDesc[128];

			struct Device *Next;
		} Device;


		/* entry */
		typedef struct
		{
			uint32_t VendorId;				///< Id del costruttore
			uint32_t DeviceId;				///< Id del device	
		} Entry;

		PciBus();
		~PciBus();

		uint32_t Read(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint8_t size);
		Device *getBusDevice(uint32_t bus, uint32_t device, uint32_t func);
		bool Probe();
		uint32_t Update();
		Device *getDevice(Entry *m);
		Device *getDevice(Entry **m, unsigned size);

	protected:
		list<Device> *m_PciDeviceList;
};

#endif


