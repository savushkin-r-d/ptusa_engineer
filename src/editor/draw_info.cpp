#include "draw_info.h"
#include <unordered_map>
#include <set>

namespace Editor {

DrawInfo::DrawInfo(Style style, std::shared_ptr<IDevice> dev)
    : style_(style), device_(dev), action_(ActionType::OTHER) {
}

std::shared_ptr<IDevice> DrawInfo::GetDrawingDevice() const {
    return device_;
}

void DrawInfo::SetDrawingDevice(std::shared_ptr<IDevice> dev) {
    device_ = dev;
}

DrawInfo::Style DrawInfo::GetDrawingStyle() const {
    return style_;
}

void DrawInfo::SetDrawingStyle(DrawInfo::Style style) {
    style_ = style;
}

DrawInfo::ActionType DrawInfo::GetAction() const {
    return action_;
}

void DrawInfo::SetAction(ActionType action) {
    action_ = action;
}

std::vector<DrawInfo> DrawInfo::Filter(const std::vector<DrawInfo>& draw) {
    // Группировка по имени устройства
    std::unordered_map<std::string, std::vector<DrawInfo>> groups;
    
    for (const auto& drawInfo : draw) {
        if (drawInfo.device_) {
            std::string deviceName = drawInfo.device_->GetName();
            groups[deviceName].push_back(drawInfo);
        }
    }

    // Обработка каждой группы
    std::vector<DrawInfo> result;
    for (const auto& pair : groups) {
        const auto& group = pair.second;
        
        // Собираем все стили в группе
        std::vector<Style> styles;
        for (const auto& item : group) {
            styles.push_back(item.GetDrawingStyle());
        }

        // Проверяем наличие RED_BOX
        bool hasRedBox = false;
        for (const auto& style : styles) {
            if (style == Style::RED_BOX) {
                hasRedBox = true;
                break;
            }
        }

        if (hasRedBox) {
            result.push_back(DrawInfo(Style::RED_BOX, group[0].device_));
            continue;
        }

        // Проверяем количество различных стилей (исключая NO_DRAW)
        std::set<Style> uniqueStyles;
        for (const auto& style : styles) {
            if (style != Style::NO_DRAW) {
                uniqueStyles.insert(style);
            }
        }

        if (uniqueStyles.size() > 1) {
            result.push_back(DrawInfo(Style::GREEN_GRAY_BOX, group[0].device_));
        } else {
            result.push_back(group[0]);
        }
    }

    return result;
}

std::vector<DrawInfo> DrawInfo::FilterByActions(const std::vector<DrawInfo>& draw) {
    // Группировка по имени устройства
    std::unordered_map<std::string, std::vector<DrawInfo>> groups;
    
    for (const auto& drawInfo : draw) {
        if (drawInfo.device_) {
            std::string deviceName = drawInfo.device_->GetName();
            groups[deviceName].push_back(drawInfo);
        }
    }

    // Обработка каждой группы
    std::vector<DrawInfo> result;
    for (const auto& pair : groups) {
        const auto& group = pair.second;
        
        // Пропускаем пустые группы
        if (group.empty()) {
            continue;
        }
        
        // Собираем все стили и действия в группе
        std::vector<Style> styles;
        std::vector<ActionType> actions;
        for (const auto& item : group) {
            styles.push_back(item.GetDrawingStyle());
            actions.push_back(item.GetAction());
        }

        // Проверяем конфликты действий через побитовое И
        int aggregated = static_cast<int>(actions[0]);
        for (size_t i = 1; i < actions.size(); ++i) {
            aggregated &= static_cast<int>(actions[i]);
        }

        if (aggregated == 0) {
            result.push_back(DrawInfo(Style::RED_BOX, group[0].device_));
            continue;
        }

        // Проверяем количество различных стилей (исключая NO_DRAW)
        std::set<Style> uniqueStyles;
        for (const auto& style : styles) {
            if (style != Style::NO_DRAW) {
                uniqueStyles.insert(style);
            }
        }

        if (uniqueStyles.size() > 1) {
            result.push_back(DrawInfo(Style::GREEN_GRAY_BOX, group[0].device_));
        } else {
            result.push_back(group[0]);
        }
    }

    return result;
}

} // namespace Editor
