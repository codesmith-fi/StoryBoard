#include "Tag.h"

namespace codesmith
{
	bool Tag::operator==(const Tag& rhs) const
	{
		return m_name == rhs.m_name;
	}

	bool Tag::operator!=(const Tag& rhs) const
	{
		return m_name != rhs.m_name;
	}
} // namespace codesmith