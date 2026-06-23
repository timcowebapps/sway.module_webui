#include <sway/webcore/css/stylesheet.hpp>
#include <sway/webcore/nodeelementupdater.hpp>
#include <sway/webui/control/label.hpp>

namespace sway::webui {

EMSCRIPTEN_BINDING_BEGIN(Label) {
  emscripten::class_<Label, emscripten::base<webcore::mvc::AView>>("Label")
      .constructor<core::NodePtr_t, std::string, webcore::TreeNodeElementDescriptor>()
      .smart_ptr<LabelSmartPtr_t>("LabelSmartPtr_t")
      .class_function("create", &Label::create, emscripten::allow_raw_pointers())
      .function("setFontFamily", &Label::setFontFamily)
      .function("setColor", &Label::setColor)
      .function("getText", &Label::getText)
      .function("setText", &Label::setText);
}
EMSCRIPTEN_BINDING_END()

LabelSmartPtr_t Label::create(core::NodePtr_t parent, const std::string &nodeId,
    const webcore::TreeNodeElementDescriptor &createInfo, emscripten::val styleSheet, const std::string &content) {

  auto instance = std::make_shared<Label>(parent, nodeId, createInfo);
  instance->setStyleSheet(styleSheet);
  instance->setHtmlContent(content);
  parent->addChildNode(instance);
  return instance;
}

Label::Label(core::NodePtr_t parent, const std::string &nodeId, const webcore::TreeNodeElementDescriptor &createInfo)
    : webcore::mvc::AView(parent, core::NodeIndex(), nodeId, createInfo) {
  // Empty
}

// void Label::accept(webcore::ITreeVisitor *visitor) {
//   visitor->visitOnEnter(this);

//   for (core::NodePtr_t node : getChildren())
//     static_cast<Label *>(node)->accept(visitor);
// }

auto Label::traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t {
  return core::toBase(core::TraverserAction::Enum::NONE);
}

void Label::setFontFamily(const std::string &fontFamily) { _fontFamily = fontFamily; }

void Label::setColor(const std::string &color) { _color = color; }

std::string Label::getText() const { return getHtmlContent(); }

void Label::setText(const std::string &text) {
  if (text == getHtmlContent())
    return;

  setHtmlContent(text);
  // for (core::HierarchyListener *listener : getHostTree()->getListeners()) {
  //   listener->onNodeUpdated(getNodeIndex());
  // }
}

}  // namespace sway::webui
