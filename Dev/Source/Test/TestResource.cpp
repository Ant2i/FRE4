#include "gtest/gtest.h"
#include "RenderTarget.h"

TEST(Resource, ResourceType)
{
	FRE::WindowRenderTarget windowRender;

	auto numTypes = FRE::ResourceType::NumTypes();

	ASSERT_EQ(FRE::WindowRenderTarget::Type.IsA(windowRender.Type), true);
	ASSERT_EQ(windowRender.Type.IsA(FRE::Resource::Type), true);
}