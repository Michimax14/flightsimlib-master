


#ifndef FLIGHTSIMLIB_IO_BGLCOMPRESSOR_H
#define FLIGHTSIMLIB_IO_BGLCOMPRESSOR_H


#include <cstdint>


namespace flightsimlib
{
	namespace io
	{
		class CBglCompressor
		{
			static int CompressDelta(
				uint8_t* p_compressed, 
				int compressed_size, 
				const uint8_t* p_uncompressed, 
				int uncompressed_size);
		};
	}
}

#endif