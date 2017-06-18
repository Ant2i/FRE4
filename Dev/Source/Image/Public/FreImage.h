#pragma once

#include "FreImageDecl.h"
#include "FrePixels.h"

#include <string>

namespace Image
{
	/// Интерфейс сериализации изображения
	class IStream
	{
	public:
		
		/// Читает buffer из потока и возвращает зармер прочитанных данных. Размер buffer должен быть не меньше size байт.
		virtual size_t Read(void * buffer, size_t size) = 0;
		/// Записывает buffer размером size в поток.
		virtual void Write(const void * buffer, size_t size) = 0;
		/// Пропустить данные размером в size байт.
		virtual void Skip(int size) = 0;
		/// Проверка конца потока. Возвращает true если достигнут конец потока, иначе false. 
		virtual bool AtEnd() const = 0;
	};
	
	struct Color
	{
		unsigned char R, G, B, A;
	};

	struct ColorF
	{
		float R, G, B, A;
	};

	/// 2D изображение
	class IMAGE_API Image2D
	{
	public:
		/// Конструктор
		Image2D();
		/// Конструктор
		Image2D(size_t width, size_t height, PixelFormat format);
		/// Конструктор копирования.
		Image2D(const Image2D & image);
		/// Конструктор переноса.
		Image2D(Image2D && image);
		/// Деструктор
		~Image2D();

		/// Загрузить изображение
		void Load(IStream & stream, const char * type, int flags = 0);
		/// Сохранить изображение
		void Save(IStream & stream, const char * type, int flags = 0);

		/// Высота изображения
		size_t Height() const;
		/// Ширина изображения
		size_t Width() const;

		/// Формат изображения
		PixelFormat Format() const;

		/// Изображение в памяти
		unsigned char * Bits();
		const unsigned char * Bits() const;

		void SetPixel(size_t x, size_t y, const Color & c);
		void GetPixel(size_t x, size_t y, Color & c) const;

		void SetPixel(size_t x, size_t y, const ColorF & c);
		void GetPixel(size_t x, size_t y, ColorF & c) const;

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
