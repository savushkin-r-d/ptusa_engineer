#include "action.h"

namespace TechObject {

Action::Action(const std::string& name, const std::string& luaName)
    : name_(name),
      luaName_(luaName),
      drawStyle_(Editor::DrawInfo::Style::GREEN_BOX),
      actionType_(Editor::DrawInfo::ActionType::OTHER) {
}

std::string Action::GetLuaName() const {
    return luaName_;
}

std::string Action::GetName() const {
    return name_;
}

bool Action::IsEmpty() const {
    return devices_.empty();
}

std::vector<int> Action::GetDevicesIndex() const {
    return deviceIndexes_;
}

void Action::AddDevice(int index, int groupNumber, const std::string& subActionLuaName) {
    deviceIndexes_.push_back(index);
}

void Action::Clear() {
    deviceIndexes_.clear();
    devices_.clear();
}

Editor::DrawInfo::Style Action::GetDrawStyle() const {
    return drawStyle_;
}

void Action::SetDrawStyle(Editor::DrawInfo::Style style) {
    drawStyle_ = style;
}

Editor::DrawInfo::ActionType Action::GetActionType() const {
    return actionType_;
}

void Action::SetActionType(Editor::DrawInfo::ActionType actionType) {
    actionType_ = actionType;
}

bool Action::IsDrawOnEplanPage() const {
    return !IsEmpty();
}

std::vector<Editor::DrawInfo> Action::GetObjectToDrawOnEplanPage() const {
    std::vector<Editor::DrawInfo> devToDraw;
    
    for (const auto& device : devices_) {
        Editor::DrawInfo drawInfo(drawStyle_, device);
        drawInfo.SetAction(actionType_);
        devToDraw.push_back(drawInfo);
    }
    
    return devToDraw;
}

std::pair<std::string, std::string> Action::GetDisplayText() const {
    return std::make_pair(name_, "");
}

bool Action::IsEditable() const {
    return true;
}

const std::vector<std::shared_ptr<Editor::IDevice>>& Action::GetDevices() const {
    return devices_;
}

void Action::AddDevice(std::shared_ptr<Editor::IDevice> device) {
    devices_.push_back(device);
}

} // namespace TechObject
