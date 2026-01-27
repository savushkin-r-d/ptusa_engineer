#include <gtest/gtest.h>
#include "techobject/action.h"
#include "editor/draw_info.h"
#include <memory>

using namespace TechObject;
using namespace Editor;

// Mock device class for testing
class MockDevice : public IDevice {
public:
    MockDevice(const std::string& name) : name_(name) {}
    
    std::string GetName() const override {
        return name_;
    }
    
private:
    std::string name_;
};

// Test fixture for Action tests
class ActionTest : public ::testing::Test {
protected:
    void SetUp() override {
        action_ = std::make_unique<Action>("TestAction", "test_action");
        device1_ = std::make_shared<MockDevice>("DEVICE1");
        device2_ = std::make_shared<MockDevice>("DEVICE2");
    }

    std::unique_ptr<Action> action_;
    std::shared_ptr<IDevice> device1_;
    std::shared_ptr<IDevice> device2_;
};

// Test basic Action creation
TEST_F(ActionTest, BasicCreation) {
    EXPECT_EQ(action_->GetName(), "TestAction");
    EXPECT_EQ(action_->GetLuaName(), "test_action");
    EXPECT_TRUE(action_->IsEmpty());
    EXPECT_TRUE(action_->IsEditable());
}

// Test default style and action type
TEST_F(ActionTest, DefaultStyleAndType) {
    EXPECT_EQ(action_->GetDrawStyle(), DrawInfo::Style::GREEN_BOX);
    EXPECT_EQ(action_->GetActionType(), DrawInfo::ActionType::OTHER);
}

// Test setting style and action type
TEST_F(ActionTest, SetStyleAndType) {
    action_->SetDrawStyle(DrawInfo::Style::RED_BOX);
    EXPECT_EQ(action_->GetDrawStyle(), DrawInfo::Style::RED_BOX);
    
    action_->SetActionType(DrawInfo::ActionType::ON_DEVICE);
    EXPECT_EQ(action_->GetActionType(), DrawInfo::ActionType::ON_DEVICE);
}

// Test adding devices
TEST_F(ActionTest, AddDevice) {
    action_->AddDevice(device1_);
    EXPECT_FALSE(action_->IsEmpty());
    EXPECT_EQ(action_->GetDevices().size(), 1);
    
    action_->AddDevice(device2_);
    EXPECT_EQ(action_->GetDevices().size(), 2);
}

// Test clearing devices
TEST_F(ActionTest, Clear) {
    action_->AddDevice(device1_);
    action_->AddDevice(device2_);
    
    EXPECT_FALSE(action_->IsEmpty());
    
    action_->Clear();
    
    EXPECT_TRUE(action_->IsEmpty());
    EXPECT_EQ(action_->GetDevices().size(), 0);
}

// Test IsDrawOnEplanPage
TEST_F(ActionTest, IsDrawOnEplanPage) {
    EXPECT_FALSE(action_->IsDrawOnEplanPage());
    
    action_->AddDevice(device1_);
    
    EXPECT_TRUE(action_->IsDrawOnEplanPage());
}

// Test GetObjectToDrawOnEplanPage
TEST_F(ActionTest, GetObjectToDrawOnEplanPage) {
    action_->AddDevice(device1_);
    action_->AddDevice(device2_);
    action_->SetDrawStyle(DrawInfo::Style::GREEN_BOX);
    action_->SetActionType(DrawInfo::ActionType::ON_DEVICE);
    
    auto drawInfos = action_->GetObjectToDrawOnEplanPage();
    
    EXPECT_EQ(drawInfos.size(), 2);
    EXPECT_EQ(drawInfos[0].GetDrawingStyle(), DrawInfo::Style::GREEN_BOX);
    EXPECT_EQ(drawInfos[0].GetAction(), DrawInfo::ActionType::ON_DEVICE);
    EXPECT_EQ(drawInfos[1].GetDrawingStyle(), DrawInfo::Style::GREEN_BOX);
    EXPECT_EQ(drawInfos[1].GetAction(), DrawInfo::ActionType::ON_DEVICE);
}

// Test GetObjectToDrawOnEplanPage with empty action
TEST_F(ActionTest, GetObjectToDrawOnEplanPageEmpty) {
    auto drawInfos = action_->GetObjectToDrawOnEplanPage();
    
    EXPECT_EQ(drawInfos.size(), 0);
}

// Test display text
TEST_F(ActionTest, GetDisplayText) {
    auto text = action_->GetDisplayText();
    
    EXPECT_EQ(text.first, "TestAction");
    EXPECT_EQ(text.second, "");
}

// Test adding device by index
TEST_F(ActionTest, AddDeviceByIndex) {
    action_->AddDevice(1, 0, "sub_action");
    
    auto indexes = action_->GetDevicesIndex();
    EXPECT_EQ(indexes.size(), 1);
    EXPECT_EQ(indexes[0], 1);
}
