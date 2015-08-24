#pragma once

#include "Decl.h"
#include "Pixels.h"

#include <string>

namespace Image
{
	/// ��������� ������������ �����������
	class IStream
	{
	public:
		/// ����������
		virtual ~IStream(){}

		/// ������ buffer �� ������ � ���������� ������ ����������� ������. ������ buffer ������ ���� �� ������ size ����.
		virtual size_t Read(void * buffer, size_t size) = 0;
		/// ���������� buffer �������� size � �����.
		virtual void Write(const void * buffer, size_t size) = 0;

		/// ���������� ������ �������� � size ����.
		virtual void Skip(size_t size) = 0;
		/// �������� ����� ������. ���������� true ���� ��������� ����� ������, ����� false. 
		virtual bool AtEnd() const = 0;
	};

	struct Color
	{
		unsigned char R, G, B, A;
	};

	/// 2D �����������
	class IMAGE_API Image2D
	{
	public:
		/// �����������
		Image2D();
		/// �����������
		Image2D(size_t width, size_t height, PixelFormat format);
		/// ����������� �����������.
		Image2D(const Image2D & image);
		/// ����������� ��������.
		Image2D(Image2D && image);
		/// ����������
		~Image2D();

		/// ��������� �����������
		void Load(IStream & stream, const std::string & type, int flags = 0);
		/// ��������� �����������
		void Save(IStream & stream, const std::string & type, int flags = 0);

		/// ������ �����������
		size_t Height() const;
		/// ������ �����������
		size_t Width() const;

		/// ������ �����������
		PixelFormat Format() const;

		/// ����������� � ������
		unsigned char * Bits();
		const unsigned char * Bits() const;

		void SetPixel(size_t x, size_t y, const Color & c);
		void GetPixel(size_t x, size_t y, Color & c) const;

		inline bool IsEmpty() const { return _p == nullptr; }

//DOM-IGNORE-BEGIN
	private:
		void ResetP(class ImageData *);
		void * GetPixelPtr(size_t x, size_t y) const;

	private:
		class ImageData * _p;
//DOM-IGNORE-END
	};

//DOM-IGNORE-BEGIN
	IMAGE_API_F void Startup();
	IMAGE_API_F void Shutdown();
//DOM-IGNORE-END
}