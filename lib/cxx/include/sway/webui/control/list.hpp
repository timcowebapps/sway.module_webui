#ifndef _SWAY_WEBUI_CONTROL_LIST_H
#define _SWAY_WEBUI_CONTROL_LIST_H

#include <sway/webcore/mvc/view.hpp>
#include <sway/webcore/prereqs.hpp>
#include <sway/webcore/treenodeelement.hpp>

namespace sway::webui {

typedef std::shared_ptr<class List> ListSmartPtr_t;
// typedef class List *ListSmartPtr_t;

class List : public webcore::mvc::AView {
  DECLARE_EMSCRIPTEN_BINDING()

public:
#pragma region "Static methods"

  static ListSmartPtr_t create(core::NodePtr_t parent, const std::string &nodeId,
      const webcore::TreeNodeElementDescriptor &createInfo, emscripten::val styleSheet);

#pragma endregion

#pragma region "Constructor / Destructor"

  /**
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   */
  List(core::NodePtr_t parent, const std::string &nodeId, const webcore::TreeNodeElementDescriptor &createInfo);

  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~List() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement > AView implementation"

  // virtual void accept(webcore::ITreeVisitor *visitor);
  virtual auto traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t override;

#pragma endregion

#pragma region "IObserver > AView implementation"

  /**
   * @brief Обновляет состояние наблюдателя.
   */
  virtual void update() override;

#pragma endregion

  void makeItem(u32_t index, std::shared_ptr<webcore::mvc::AView> item);
};

}  // namespace sway::webui

#endif  // _SWAY_WEBUI_CONTROL_LIST_H
