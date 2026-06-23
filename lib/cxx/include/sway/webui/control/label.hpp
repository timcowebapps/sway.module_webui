#ifndef _SWAY_WEBUI_CONTROL_LABEL_H
#define _SWAY_WEBUI_CONTROL_LABEL_H

#include <sway/webcore/mvc/view.hpp>
#include <sway/webcore/prereqs.hpp>
#include <sway/webcore/treenodeelement.hpp>

namespace sway::webui {

typedef std::shared_ptr<class Label> LabelSmartPtr_t;

class Label : public webcore::mvc::AView {
  DECLARE_EMSCRIPTEN_BINDING()

public:
#pragma region "Static methods"

  static LabelSmartPtr_t create(core::NodePtr_t parent, const std::string &nodeId,
      const webcore::TreeNodeElementDescriptor &createInfo, emscripten::val styleSheet, const std::string &content);

#pragma endregion

#pragma region "Constructor / Destructor"

  /**
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   */
  Label(core::NodePtr_t parent, const std::string &nodeId, const webcore::TreeNodeElementDescriptor &createInfo);

  /**
   * @brief Виртуальный деструктор класса.
   */
  virtual ~Label() = default;

#pragma endregion

#pragma region "IVisitable > HierarchyNode > TreeNodeElement implementation"

  // virtual void accept(webcore::ITreeVisitor *visitor);
  virtual auto traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t override;

#pragma endregion

#pragma region "Getters / Setters"

  void setFontFamily(const std::string &fontFamily);

  void setColor(const std::string &color);

  std::string getText() const;

  void setText(const std::string &text);

#pragma endregion

private:
  std::string _fontFamily;
  std::string _color;
};

}  // namespace sway::webui

#endif  // _SWAY_WEBUI_CONTROL_LABEL_H
