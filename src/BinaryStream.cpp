
//******************************************************************************
//
// File:     BinaryStream.cpp
//
// Summary:  Utility class for reading a streambuf as binary
//           Allows stream extract operator to be used on arbitrary byte array
//
// Author:   Tilen
//
//******************************************************************************       


#include "BinaryStream.h"

#include <cassert>


namespace flightsimlib
{

namespace io
{

CByteArrayStreambuf::CByteArrayStreambuf(const uint8_t* begin, const size_t size) :
	m_begin(begin),
	m_end(begin + size),
	m_current(m_begin)
{
	assert(std::less_equal<const uint8_t*>()(m_begin, m_end));
}

	
CByteArrayStreambuf::int_type CByteArrayStreambuf::underflow()
{
	if (m_current == m_end)
		return traits_type::eof();

	return traits_type::to_int_type(*m_current);
}

	
CByteArrayStreambuf::int_type CByteArrayStreambuf::uflow()
{
	if (m_current == m_end)
		return traits_type::eof();

	return traits_type::to_int_type(*m_current++);
}

	
CByteArrayStreambuf::int_type CByteArrayStreambuf::pbackfail(int_type ch)
{
	if (m_current == m_begin || (ch != traits_type::eof() && ch != m_current[-1]))
		return traits_type::eof();

	return traits_type::to_int_type(*--m_current);
}

	
std::streamsize CByteArrayStreambuf::showmanyc()
{
	assert(std::less_equal<const uint8_t*>()(m_current, m_end));
	return m_end - m_current;
}

	
std::streampos CByteArrayStreambuf::seekoff(std::streamoff off, std::ios_base::seekdir way,
	std::ios_base::openmode which)
{
	if (way == std::ios_base::beg)
	{
		m_current = m_begin + off;
	}
	else if (way == std::ios_base::cur)
	{
		m_current += off;
	}
	else if (way == std::ios_base::end)
	{
		m_current = m_end;
	}

	if (m_current < m_begin || m_current > m_end)
		return -1;


	return m_current - m_begin;
}

	
std::streampos CByteArrayStreambuf::seekpos(std::streampos sp,
	std::ios_base::openmode which)
{
	m_current = m_begin + sp;

	if (m_current < m_begin || m_current > m_end)
		return -1;

	return m_current - m_begin;
}

}

}