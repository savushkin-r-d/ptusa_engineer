#ifndef DRAW_INFO_H
#define DRAW_INFO_H

#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>

namespace Editor {

// Forward declaration
class IDevice;

/**
 * @brief Класс для настройки цвета отображения на странице
 * 
 * Class for configuring the color display on the page.
 */
class DrawInfo {
public:
    /**
     * @brief Стиль отрисовки
     * 
     * Drawing style enumeration
     */
    enum class Style {
        NO_DRAW,           ///< Не отображать
        GRAY_BOX,          ///< Серая рамка
        GREEN_BOX,         ///< Зеленая рамка
        GREEN_UPPER_BOX,   ///< Зеленая верхняя рамка
        GREEN_LOWER_BOX,   ///< Зеленая нижняя рамка
        GREEN_GRAY_BOX,    ///< Зелено-серая рамка
        RED_BOX            ///< Красная рамка (неверное связывание)
    };

    /**
     * @brief Тип действия
     * 
     * Указаны битовые флаги пересечений, если сумма побитового "и" 
     * равна 0, тогда пересечение действий неверно
     * 
     * Bitwise flags for intersections. If the bitwise AND result is 0,
     * then the action intersection is invalid.
     */
    enum class ActionType {
        OTHER = 0b1111,              ///< Другое действие
        ON_DEVICE = 0b0001,          ///< Включение устройства
        OFF_DEVICE = 0b0010,         ///< Выключение устройства
        DELAYED_ON_DEVICE = 0b0110,  ///< Отложенное включение
        DELAYED_OFF_DEVICE = 0b0101  ///< Отложенное выключение
    };

    /**
     * @brief Конструктор
     * 
     * @param style Стиль отображения
     * @param dev Устройство для отображения
     */
    DrawInfo(Style style, std::shared_ptr<IDevice> dev);

    /**
     * @brief Деструктор
     */
    ~DrawInfo() = default;

    /**
     * @brief Получить устройство для отрисовки
     * 
     * @return Указатель на устройство
     */
    std::shared_ptr<IDevice> GetDrawingDevice() const;

    /**
     * @brief Установить устройство для отрисовки
     * 
     * @param dev Указатель на устройство
     */
    void SetDrawingDevice(std::shared_ptr<IDevice> dev);

    /**
     * @brief Получить стиль отрисовки
     * 
     * @return Стиль отрисовки
     */
    Style GetDrawingStyle() const;

    /**
     * @brief Установить стиль отрисовки
     * 
     * @param style Стиль отрисовки
     */
    void SetDrawingStyle(Style style);

    /**
     * @brief Получить тип действия
     * 
     * @return Тип действия
     */
    ActionType GetAction() const;

    /**
     * @brief Установить тип действия
     * 
     * @param action Тип действия
     */
    void SetAction(ActionType action);

    /**
     * @brief Фильтр устройств для подсветки
     * 
     * @param draw Список информации для отрисовки
     * @return Отфильтрованный список
     */
    static std::vector<DrawInfo> Filter(const std::vector<DrawInfo>& draw);

    /**
     * @brief Фильтр устройств для подсветки с проверкой конфликтов действий
     * 
     * @param draw Список информации для отрисовки
     * @return Отфильтрованный список
     */
    static std::vector<DrawInfo> FilterByActions(const std::vector<DrawInfo>& draw);

private:
    Style style_;                      ///< Стиль отрисовки
    std::shared_ptr<IDevice> device_;  ///< Устройство для отрисовки
    ActionType action_;                ///< Тип действия
};

/**
 * @brief Интерфейс устройства
 * 
 * Device interface
 */
class IDevice {
public:
    virtual ~IDevice() = default;

    /**
     * @brief Получить имя устройства
     * 
     * @return Имя устройства
     */
    virtual std::string GetName() const = 0;
};

} // namespace Editor

#endif // DRAW_INFO_H
