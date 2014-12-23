#include "gtest/gtest.h"
#include "FreEngine.h"
#include "RDMethods.h"

class Test_EngineData : public ::testing::Test
{
protected:
	void SetUp()
	{
		FRE::Engine::CreateParams params;
		params.renderDeviceName = "GLRenderDevice";
		FRE::Engine::Create(params);
	}

	void TearDown()
	{
		FRE::Engine::Destroy();
	}
};

TEST_F(Test_EngineData, RDVertexBuffer)
{
	int data[] = { 9, 34, 726, 0 };

	FRE::RDVertexBufferRef buffer = FRE::RDCreateVertexBuffer(sizeof(data), 0, data);
	ASSERT_EQ(buffer.Get() != nullptr, true);
	ASSERT_EQ(buffer->Size, sizeof(data));
	ASSERT_EQ(buffer->Usage, 0);
	
	int * bufferData = (int *)FRE::RDLockBuffer(buffer, 0, buffer->Size, FRE::ELockMode::Read);
	ASSERT_EQ(bufferData != nullptr, true);
	if (bufferData)
	{
		ASSERT_EQ(bufferData[0], data[0]);
		ASSERT_EQ(bufferData[1], data[1]);
		ASSERT_EQ(bufferData[2], data[2]);
		ASSERT_EQ(bufferData[3], data[3]);
	}
	FRE::RDUnlockBuffer(buffer);
}
