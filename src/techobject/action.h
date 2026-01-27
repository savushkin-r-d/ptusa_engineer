#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <string>
#include <memory>
#include "../editor/tree_view_item.h"
#include "../editor/draw_info.h"

namespace TechObject {

/**
 * @brief Интерфейс действия
 * 
 * Action interface
 */
class IAction {
public:
    virtual ~IAction() = default;

    /**
     * @brief Получить Lua-имя действия
     * 
     * @return Lua-имя
     */
    virtual std::string GetLuaName() const = 0;

    /**
     * @brief Получить имя действия
     * 
     * @return Имя действия
     */
    virtual std::string GetName() const = 0;

    /**
     * @brief Проверка, пустое ли действие
     * 
     * @return true если действие пустое
     */
    virtual bool IsEmpty() const = 0;

    /**
     * @brief Получить индексы устройств
     * 
     * @return Список индексов
     */
    virtual std::vector<int> GetDevicesIndex() const = 0;

    /**
     * @brief Добавить устройство к действию
     * 
     * @param index Индекс устройства
     * @param groupNumber Номер группы
     * @param subActionLuaName Lua-имя поддействия
     */
    virtual void AddDevice(int index, int groupNumber, const std::string& subActionLuaName) = 0;

    /**
     * @brief Очистить список устройств
     */
    virtual void Clear() = 0;

    /**
     * @brief Получить стиль отрисовки
     * 
     * @return Стиль отрисовки
     */
    virtual Editor::DrawInfo::Style GetDrawStyle() const = 0;

    /**
     * @brief Установить стиль отрисовки
     * 
     * @param style Стиль отрисовки
     */
    virtual void SetDrawStyle(Editor::DrawInfo::Style style) = 0;

    /**
     * @brief Получить тип действия
     * 
     * @return Тип действия
     */
    virtual Editor::DrawInfo::ActionType GetActionType() const = 0;

    /**
     * @brief Установить тип действия
     * 
     * @param actionType Тип действия
     */
    virtual void SetActionType(Editor::DrawInfo::ActionType actionType) = 0;
};

/**
 * @brief Действие над устройствами (включение, выключение и т.д.)
 * 
 * Action on devices (turning on, turning off, etc.)
 */
class Action : public Editor::TreeViewItem, public IAction {
public:
    /**
     * @brief Конструктор
     * 
     * @param name Имя действия
     * @param luaName Lua-имя действия
     */
    Action(const std::string& name, const std::string& luaName);

    /**
     * @brief Деструктор
     */
    virtual ~Action() = default;

    // Реализация IAction
    std::string GetLuaName() const override;
    std::string GetName() const override;
    bool IsEmpty() const override;
    std::vector<int> GetDevicesIndex() const override;
    void AddDevice(int index, int groupNumber, const std::string& subActionLuaName) override;
    void Clear() override;
    Editor::DrawInfo::Style GetDrawStyle() const override;
    void SetDrawStyle(Editor::DrawInfo::Style style) override;
    Editor::DrawInfo::ActionType GetActionType() const override;
    void SetActionType(Editor::DrawInfo::ActionType actionType) override;

    // Переопределение TreeViewItem
    bool IsDrawOnEplanPage() const override;
    std::vector<Editor::DrawInfo> GetObjectToDrawOnEplanPage() const override;
    std::pair<std::string, std::string> GetDisplayText() const override;
    bool IsEditable() const override;

    /**
     * @brief Получить список устройств
     * 
     * @return Список устройств
     */
    const std::vector<std::shared_ptr<Editor::IDevice>>& GetDevices() const;

    /**
     * @brief Добавить устройство к действию
     * 
     * @param device Устройство
     */
    void AddDevice(std::shared_ptr<Editor::IDevice> device);

private:
    std::string name_;                                        ///< Имя действия
    std::string luaName_;                                     ///< Lua-имя действия
    std::vector<int> deviceIndexes_;                          ///< Индексы устройств
    std::vector<std::shared_ptr<Editor::IDevice>> devices_;   ///< Устройства
    Editor::DrawInfo::Style drawStyle_;                       ///< Стиль отрисовки
    Editor::DrawInfo::ActionType actionType_;                 ///< Тип действия
};

} // namespace TechObject

#endif // ACTION_H
