#include "gtest/gtest.h"
#include "FreEngine.h"
#include "RDInterfaces.h"

using namespace FRE;

TEST(Test_Engine, InitEngine)
{
	FRE::Engine::CreateParams params;
	params.renderDeviceName = "GLRenderDevice";
	FRE::Engine::Create(params);

	IRenderDevice & device = FRE::Engine::GetActiveRenderDevice();

	ASSERT_EQ(strcmp(device.GetName(), "GLRenderDevice") == 0, true);

	FRE::Engine::Destroy();
}
