#include "gtest/gtest.h"

#include "FrePixels.h"
#include "FreImageMemoryStream.h"

TEST(Test_Image, PackUnpack_Int_RGBA8)
{
	char data[256];

	unsigned packColorInt[4] = { 20, 46, 72, 233 };
	Image::Pixels::PackI(packColorInt[0], packColorInt[1], packColorInt[2], packColorInt[3], Image::PixelFormat::RGBA8, data);
	unsigned unpackColorInt[4];
	Image::Pixels::UnpackI(unpackColorInt[0], unpackColorInt[1], unpackColorInt[2], unpackColorInt[3], Image::PixelFormat::RGBA8, data);

	for (auto i = 0; i < 4; ++i)
		EXPECT_EQ(packColorInt[i], unpackColorInt[i]);
}

TEST(Test_Image, PackUnpack_Float_RGBA8)
{
	char data[256];

	float packColorFloat[4] = { 0.5f, 0.2f, 0.3f, 0.1f };
	Image::Pixels::PackF(packColorFloat[0], packColorFloat[1], packColorFloat[2], packColorFloat[3], Image::PixelFormat::RGBA8, data);
	float unpackColorFloat[4];
	Image::Pixels::UnpackF(unpackColorFloat[0], unpackColorFloat[1], unpackColorFloat[2], unpackColorFloat[3], Image::PixelFormat::RGBA8, data);

	for (auto i = 0; i < 4; ++i)
		EXPECT_EQ(fabs(packColorFloat[i] - unpackColorFloat[i]) < 0.01, true);
}

TEST(Test_Image, PackUnpack_Any_RGBA8)
{
	char data[256];

	unsigned packColorInt[4] = { 123, 22, 44, 1 };
	Image::Pixels::PackI(packColorInt[0], packColorInt[1], packColorInt[2], packColorInt[3], Image::PixelFormat::BGRA8, data);

	float colorFloat[4];
	Image::Pixels::UnpackF(colorFloat[0], colorFloat[1], colorFloat[2], colorFloat[3], Image::PixelFormat::BGRA8, data);
	Image::Pixels::PackF(colorFloat[0], colorFloat[1], colorFloat[2], colorFloat[3], Image::PixelFormat::BGRA8, data);

	unsigned unpackColorInt[4];
	Image::Pixels::UnpackI(unpackColorInt[0], unpackColorInt[1], unpackColorInt[2], unpackColorInt[3], Image::PixelFormat::BGRA8, data);

	for (auto i = 0; i < 4; ++i)
		EXPECT_EQ(packColorInt[i], unpackColorInt[i]);
}

TEST(Test_Image, Raed_Write_MemoryStream)
{
	Image::MemoryStream memoryStream(2);

	int data[4] = { 102, 304, 238, 4 };

	memoryStream.Write(data, sizeof(data));
	memoryStream.Reset();
	int result[4] = { 0, 0, 0, 0 };
	auto readSize = memoryStream.Read(result, sizeof(result));
	EXPECT_EQ(readSize, sizeof(result));

	for (auto i = 0; i < 4; ++i)
		EXPECT_EQ(data[i], result[i]);

	memoryStream.Reset();
	int result2[100];
	auto readSize2 = memoryStream.Read(result2, sizeof(result2));
	EXPECT_EQ(readSize2, sizeof(data));
}
