#include "NativePlatformPath.h"

namespace Platform
{
	class PathPrivate
	{
	public:
		PathPrivate()
		{

		}

		PathPrivate(tchar* pstr, uint32 size) :
			_str(pstr, size)
		{
			
		}

		PathPrivate(const std::wstring& str) : 
			_str(str)
		{

		}

		uint32 Size() const
		{
			return (uint32)_str.size();
		}

		const tchar* Data() const
		{
			return _str.data();
		}

		operator std::wstring&()
		{
			return _str;
		}

	private:
		std::wstring _str;
	};

	//-------------------------------------------------------------------------

	Path::Path() :
		_p(new PathPrivate())
	{
		
	}

	Path::Path(const Path& other) :
		_p(new PathPrivate(*other._p))
	{

	}

	Path::Path(PathPrivate& p) :
		_p(new PathPrivate(p))
	{

	}

	Path::~Path()
	{
		delete _p;
	}
	
	void Path::Append(const tchar* pstr, uint32 size)
	{
		std::wstring& sPath = *_p;

		if (sPath.size() > 1 && sPath[sPath.size() - 2] != L'/' && sPath[sPath.size() - 2] != L'\\')
			sPath += L"/";

		sPath += std::wstring(pstr, size);
	}

	Path Path::GetDirectory() const
	{
		std::wstring sDir = *_p;

		const size_t found = sDir.find_last_of(L"\\/");
		if (std::string::npos != found)
		{
			sDir.substr(0, found);
		}
		
		return Path(PathPrivate(sDir));
	}

	Path Path::GetFileName() const
	{
		std::wstring sName = *_p;
		
		const size_t found = sName.find_last_of(L"\\/");
		if (std::string::npos != found)
		{
			sName.substr(found + 1, sName.size() - found);
		}
		
		return Path(PathPrivate(sName));
	}

	const tchar* Path::GetCharData() const
	{
		return _p->Data();
	}

	int Path::GetSize() const
	{
		return _p->Size();
	}
}
