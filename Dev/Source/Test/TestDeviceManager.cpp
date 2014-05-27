#include "gtest/gtest.h"
#include "DeviceManager.h"
#include "DeviceInterfaces.h"

using namespace FRE;

TEST(Test_DeviceManager, LoadRenderDevice)
{
	DeviceManager deviceMgr;
	IRenderDevice * device = deviceMgr.LoadDevice("GLRenderDevice");
	ASSERT_EQ(device != nullptr && device->GetName() == "GLRenderDevice", true);
	ASSERT_EQ(device, deviceMgr.GetDevice("GLRenderDevice"));
}