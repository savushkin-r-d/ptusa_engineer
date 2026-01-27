#include <gtest/gtest.h>
#include "editor/draw_info.h"
#include <memory>
#include <vector>
#include <random>

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

// Test fixture for DrawInfo tests
class DrawInfoTest : public ::testing::Test {
protected:
    void SetUp() override {
        device1_ = std::make_shared<MockDevice>("DEVICE1");
        device2_ = std::make_shared<MockDevice>("DEVICE2");
        device3_ = std::make_shared<MockDevice>("DEVICE3");
    }

    std::shared_ptr<IDevice> device1_;
    std::shared_ptr<IDevice> device2_;
    std::shared_ptr<IDevice> device3_;
};

// Test basic DrawInfo creation
TEST_F(DrawInfoTest, BasicCreation) {
    DrawInfo drawInfo(DrawInfo::Style::GREEN_BOX, device1_);
    
    EXPECT_EQ(drawInfo.GetDrawingStyle(), DrawInfo::Style::GREEN_BOX);
    EXPECT_EQ(drawInfo.GetDrawingDevice(), device1_);
    EXPECT_EQ(drawInfo.GetAction(), DrawInfo::ActionType::OTHER);
}

// Test DrawInfo setters
TEST_F(DrawInfoTest, Setters) {
    DrawInfo drawInfo(DrawInfo::Style::GREEN_BOX, device1_);
    
    drawInfo.SetDrawingStyle(DrawInfo::Style::RED_BOX);
    EXPECT_EQ(drawInfo.GetDrawingStyle(), DrawInfo::Style::RED_BOX);
    
    drawInfo.SetDrawingDevice(device2_);
    EXPECT_EQ(drawInfo.GetDrawingDevice(), device2_);
    
    drawInfo.SetAction(DrawInfo::ActionType::ON_DEVICE);
    EXPECT_EQ(drawInfo.GetAction(), DrawInfo::ActionType::ON_DEVICE);
}

// Test Filter with RED_BOX priority
TEST_F(DrawInfoTest, FilterRedBoxPriority) {
    std::vector<DrawInfo> input;
    input.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, device1_));
    input.push_back(DrawInfo(DrawInfo::Style::RED_BOX, device1_));
    
    auto result = DrawInfo::Filter(input);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].GetDrawingStyle(), DrawInfo::Style::RED_BOX);
}

// Test Filter with multiple styles
TEST_F(DrawInfoTest, FilterMultipleStyles) {
    std::vector<DrawInfo> input;
    input.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, device1_));
    input.push_back(DrawInfo(DrawInfo::Style::GRAY_BOX, device1_));
    
    auto result = DrawInfo::Filter(input);
    
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].GetDrawingStyle(), DrawInfo::Style::GREEN_GRAY_BOX);
}

// Test Filter with NO_DRAW exclusion
TEST_F(DrawInfoTest, FilterNoDrawExclusion) {
    std::vector<DrawInfo> input;
    input.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, device1_));
    input.push_back(DrawInfo(DrawInfo::Style::NO_DRAW, device1_));
    
    auto result = DrawInfo::Filter(input);
    
    EXPECT_EQ(result.size(), 1);
    // Should not create GREEN_GRAY_BOX since NO_DRAW is excluded
    EXPECT_EQ(result[0].GetDrawingStyle(), DrawInfo::Style::GREEN_BOX);
}

// Test FilterByActions with conflicting actions
TEST_F(DrawInfoTest, FilterByActionsConflict) {
    std::vector<DrawInfo> input;
    
    DrawInfo info1(DrawInfo::Style::GREEN_BOX, device1_);
    info1.SetAction(DrawInfo::ActionType::ON_DEVICE);
    
    DrawInfo info2(DrawInfo::Style::GREEN_BOX, device1_);
    info2.SetAction(DrawInfo::ActionType::OFF_DEVICE);
    
    input.push_back(info1);
    input.push_back(info2);
    
    auto result = DrawInfo::FilterByActions(input);
    
    EXPECT_EQ(result.size(), 1);
    // Conflicting actions should result in RED_BOX
    EXPECT_EQ(result[0].GetDrawingStyle(), DrawInfo::Style::RED_BOX);
}

// Test FilterByActions with compatible actions
TEST_F(DrawInfoTest, FilterByActionsCompatible) {
    std::vector<DrawInfo> input;
    
    DrawInfo info1(DrawInfo::Style::GREEN_BOX, device1_);
    info1.SetAction(DrawInfo::ActionType::DELAYED_ON_DEVICE);
    
    DrawInfo info2(DrawInfo::Style::GREEN_BOX, device1_);
    info2.SetAction(DrawInfo::ActionType::DELAYED_ON_DEVICE);
    
    input.push_back(info1);
    input.push_back(info2);
    
    auto result = DrawInfo::FilterByActions(input);
    
    EXPECT_EQ(result.size(), 1);
    // Compatible actions should keep the original style
    EXPECT_EQ(result[0].GetDrawingStyle(), DrawInfo::Style::GREEN_BOX);
}

// Test action type bitwise operations (as in the original C# test)
TEST_F(DrawInfoTest, ActionTypeAggregate) {
    // Test conflicting combinations
    {
        int result = static_cast<int>(DrawInfo::ActionType::ON_DEVICE) &
                    static_cast<int>(DrawInfo::ActionType::OFF_DEVICE);
        EXPECT_EQ(result, 0); // Conflict
    }
    
    {
        int result = static_cast<int>(DrawInfo::ActionType::ON_DEVICE) &
                    static_cast<int>(DrawInfo::ActionType::DELAYED_ON_DEVICE);
        EXPECT_EQ(result, 0); // Conflict
    }
    
    {
        int result = static_cast<int>(DrawInfo::ActionType::OFF_DEVICE) &
                    static_cast<int>(DrawInfo::ActionType::DELAYED_OFF_DEVICE);
        EXPECT_EQ(result, 0); // Conflict
    }
    
    // Test compatible combinations
    {
        int result = static_cast<int>(DrawInfo::ActionType::OTHER) &
                    static_cast<int>(DrawInfo::ActionType::ON_DEVICE);
        EXPECT_NE(result, 0); // Compatible
    }
    
    {
        int result = static_cast<int>(DrawInfo::ActionType::DELAYED_ON_DEVICE) &
                    static_cast<int>(DrawInfo::ActionType::DELAYED_OFF_DEVICE);
        EXPECT_NE(result, 0); // Compatible
    }
}

// Test Filter with multiple devices
TEST_F(DrawInfoTest, FilterMultipleDevices) {
    std::vector<DrawInfo> input;
    input.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, device1_));
    input.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, device2_));
    input.push_back(DrawInfo(DrawInfo::Style::RED_BOX, device3_));
    
    auto result = DrawInfo::Filter(input);
    
    // Should have 3 devices (one for each unique device)
    EXPECT_EQ(result.size(), 3);
}
