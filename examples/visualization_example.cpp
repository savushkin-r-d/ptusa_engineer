#include "editor/draw_info.h"
#include "techobject/action.h"
#include <iostream>
#include <iomanip>

using namespace Editor;
using namespace TechObject;

// Простое устройство для примера
class SimpleDevice : public IDevice {
public:
    SimpleDevice(const std::string& name) : name_(name) {}
    
    std::string GetName() const override {
        return name_;
    }
    
private:
    std::string name_;
};

// Функция для вывода информации о стиле
std::string StyleToString(DrawInfo::Style style) {
    switch(style) {
        case DrawInfo::Style::NO_DRAW: return "NO_DRAW";
        case DrawInfo::Style::GRAY_BOX: return "GRAY_BOX";
        case DrawInfo::Style::GREEN_BOX: return "GREEN_BOX";
        case DrawInfo::Style::GREEN_UPPER_BOX: return "GREEN_UPPER_BOX";
        case DrawInfo::Style::GREEN_LOWER_BOX: return "GREEN_LOWER_BOX";
        case DrawInfo::Style::GREEN_GRAY_BOX: return "GREEN_GRAY_BOX";
        case DrawInfo::Style::RED_BOX: return "RED_BOX";
        default: return "UNKNOWN";
    }
}

// Функция для вывода информации о типе действия
std::string ActionTypeToString(DrawInfo::ActionType type) {
    switch(type) {
        case DrawInfo::ActionType::OTHER: return "OTHER";
        case DrawInfo::ActionType::ON_DEVICE: return "ON_DEVICE";
        case DrawInfo::ActionType::OFF_DEVICE: return "OFF_DEVICE";
        case DrawInfo::ActionType::DELAYED_ON_DEVICE: return "DELAYED_ON_DEVICE";
        case DrawInfo::ActionType::DELAYED_OFF_DEVICE: return "DELAYED_OFF_DEVICE";
        default: return "UNKNOWN";
    }
}

void PrintDrawInfo(const std::vector<DrawInfo>& infos, const std::string& title) {
    std::cout << "\n" << title << ":\n";
    std::cout << std::string(60, '-') << "\n";
    
    for (const auto& info : infos) {
        auto device = info.GetDrawingDevice();
        if (device) {
            std::cout << "  Устройство: " << std::setw(15) << std::left 
                      << device->GetName();
            std::cout << " Стиль: " << std::setw(20) << std::left 
                      << StyleToString(info.GetDrawingStyle());
            std::cout << " Действие: " << ActionTypeToString(info.GetAction()) << "\n";
        }
    }
}

int main() {
    std::cout << "=== Пример использования системы визуализации ===\n";
    
    // Создание устройств
    auto valve1 = std::make_shared<SimpleDevice>("V101");
    auto valve2 = std::make_shared<SimpleDevice>("V102");
    auto pump1 = std::make_shared<SimpleDevice>("P101");
    
    // Пример 1: Создание действия и добавление устройств
    std::cout << "\n1. Создание действия 'Открыть клапаны':\n";
    auto openValvesAction = std::make_unique<Action>("Открыть клапаны", "open_valves");
    openValvesAction->SetDrawStyle(DrawInfo::Style::GREEN_BOX);
    openValvesAction->SetActionType(DrawInfo::ActionType::ON_DEVICE);
    openValvesAction->AddDevice(valve1);
    openValvesAction->AddDevice(valve2);
    
    std::cout << "  Имя: " << openValvesAction->GetName() << "\n";
    std::cout << "  Lua имя: " << openValvesAction->GetLuaName() << "\n";
    std::cout << "  Количество устройств: " << openValvesAction->GetDevices().size() << "\n";
    std::cout << "  Отображать на странице: " 
              << (openValvesAction->IsDrawOnEplanPage() ? "Да" : "Нет") << "\n";
    
    auto drawInfos = openValvesAction->GetObjectToDrawOnEplanPage();
    PrintDrawInfo(drawInfos, "Информация для отрисовки");
    
    // Пример 2: Фильтрация с конфликтом стилей
    std::cout << "\n2. Пример фильтрации с разными стилями:\n";
    std::vector<DrawInfo> mixedStyles;
    mixedStyles.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, valve1));
    mixedStyles.push_back(DrawInfo(DrawInfo::Style::GRAY_BOX, valve1));
    
    auto filtered = DrawInfo::Filter(mixedStyles);
    PrintDrawInfo(filtered, "Результат фильтрации");
    
    // Пример 3: Фильтрация с приоритетом RED_BOX
    std::cout << "\n3. Пример фильтрации с RED_BOX:\n";
    std::vector<DrawInfo> withRedBox;
    withRedBox.push_back(DrawInfo(DrawInfo::Style::GREEN_BOX, pump1));
    withRedBox.push_back(DrawInfo(DrawInfo::Style::RED_BOX, pump1));
    
    filtered = DrawInfo::Filter(withRedBox);
    PrintDrawInfo(filtered, "Результат фильтрации (приоритет RED_BOX)");
    
    // Пример 4: Фильтрация с конфликтом действий
    std::cout << "\n4. Пример фильтрации с конфликтом действий:\n";
    std::vector<DrawInfo> conflictingActions;
    
    DrawInfo info1(DrawInfo::Style::GREEN_BOX, valve2);
    info1.SetAction(DrawInfo::ActionType::ON_DEVICE);
    
    DrawInfo info2(DrawInfo::Style::GREEN_BOX, valve2);
    info2.SetAction(DrawInfo::ActionType::OFF_DEVICE);
    
    conflictingActions.push_back(info1);
    conflictingActions.push_back(info2);
    
    PrintDrawInfo(conflictingActions, "До фильтрации");
    
    filtered = DrawInfo::FilterByActions(conflictingActions);
    PrintDrawInfo(filtered, "После фильтрации (обнаружен конфликт)");
    
    // Пример 5: Совместимые действия
    std::cout << "\n5. Пример фильтрации с совместимыми действиями:\n";
    std::vector<DrawInfo> compatibleActions;
    
    DrawInfo info3(DrawInfo::Style::GREEN_BOX, pump1);
    info3.SetAction(DrawInfo::ActionType::DELAYED_ON_DEVICE);
    
    DrawInfo info4(DrawInfo::Style::GREEN_BOX, pump1);
    info4.SetAction(DrawInfo::ActionType::DELAYED_OFF_DEVICE);
    
    compatibleActions.push_back(info3);
    compatibleActions.push_back(info4);
    
    filtered = DrawInfo::FilterByActions(compatibleActions);
    PrintDrawInfo(filtered, "После фильтрации (действия совместимы)");
    
    std::cout << "\n=== Завершение примера ===\n";
    
    return 0;
}
