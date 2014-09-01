#include "gtest/gtest.h"
#include "FreDeviceManager.h"
#include "FreRDInterfaces.h"

using namespace FRE;

TEST(Test_DeviceManager, LoadRenderDevice)
{
	DeviceManager deviceMgr;
	IRenderDevice * device = deviceMgr.LoadDevice("GLRenderDevice");
	ASSERT_EQ(device != nullptr && strcmp(device->GetName(), "GLRenderDevice") == 0, true);
	ASSERT_EQ(device, deviceMgr.GetDevice("GLRenderDevice"));
}