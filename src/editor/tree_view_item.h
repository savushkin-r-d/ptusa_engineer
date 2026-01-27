#ifndef TREE_VIEW_ITEM_H
#define TREE_VIEW_ITEM_H

#include <vector>
#include <string>
#include <memory>
#include "draw_info.h"

namespace Editor {

/**
 * @brief Интерфейс элемента дерева
 * 
 * Tree view item interface
 */
class ITreeViewItem {
public:
    virtual ~ITreeViewItem() = default;

    /**
     * @brief Проверка, нужно ли отображать на странице EPLAN
     * 
     * @return true если нужно отображать
     */
    virtual bool IsDrawOnEplanPage() const = 0;

    /**
     * @brief Получить объекты для отрисовки на странице EPLAN
     * 
     * @return Список информации для отрисовки
     */
    virtual std::vector<DrawInfo> GetObjectToDrawOnEplanPage() const = 0;

    /**
     * @brief Получить отображаемый текст
     * 
     * @return Пара строк для отображения
     */
    virtual std::pair<std::string, std::string> GetDisplayText() const = 0;

    /**
     * @brief Проверка возможности редактирования
     * 
     * @return true если элемент можно редактировать
     */
    virtual bool IsEditable() const = 0;
};

/**
 * @brief Базовый класс элемента дерева
 * 
 * Base tree view item class
 */
class TreeViewItem : public ITreeViewItem {
public:
    TreeViewItem() = default;
    virtual ~TreeViewItem() = default;

    /**
     * @brief Проверка, нужно ли отображать на странице EPLAN
     * 
     * @return false по умолчанию
     */
    bool IsDrawOnEplanPage() const override {
        return false;
    }

    /**
     * @brief Получить объекты для отрисовки на странице EPLAN
     * 
     * @return Пустой список по умолчанию
     */
    std::vector<DrawInfo> GetObjectToDrawOnEplanPage() const override {
        return std::vector<DrawInfo>();
    }

    /**
     * @brief Получить отображаемый текст
     * 
     * @return Пустые строки по умолчанию
     */
    std::pair<std::string, std::string> GetDisplayText() const override {
        return std::make_pair("", "");
    }

    /**
     * @brief Проверка возможности редактирования
     * 
     * @return false по умолчанию
     */
    bool IsEditable() const override {
        return false;
    }

protected:
    std::shared_ptr<ITreeViewItem> parent_;  ///< Родительский элемент
};

} // namespace Editor

#endif // TREE_VIEW_ITEM_H
