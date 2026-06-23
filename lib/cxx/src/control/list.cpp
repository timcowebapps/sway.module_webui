#include <sway/webcore/css/stylesheet.hpp>
#include <sway/webcore/nodeelementupdater.hpp>
#include <sway/webui/control/list.hpp>

namespace sway::webui {

EMSCRIPTEN_BINDING_BEGIN(List) {
  emscripten::class_<List, emscripten::base<webcore::mvc::AView>>("List")
      .constructor<core::NodePtr_t, std::string, webcore::TreeNodeElementDescriptor>()
      //.smart_ptr<ListSmartPtr_t>("ListSmartPtr_t")
      .class_function("create", &List::create, emscripten::allow_raw_pointers())
      .function("makeItem", &List::makeItem, emscripten::allow_raw_pointers());
}
EMSCRIPTEN_BINDING_END()

ListSmartPtr_t List::create(core::NodePtr_t parent, const std::string &nodeId,
    const webcore::TreeNodeElementDescriptor &createInfo, emscripten::val styleSheet) {

  auto instance = std::make_shared<List>(parent, nodeId, createInfo);
  instance->setStyleSheet(styleSheet);
  parent->addChildNode(instance);
  return instance;
}

List::List(core::NodePtr_t parent, const std::string &nodeId, const webcore::TreeNodeElementDescriptor &createInfo)
    : webcore::mvc::AView(parent, core::NodeIndex(), nodeId, createInfo) {
  // Empty
}

// void List::accept(webcore::ITreeVisitor *visitor) {
//   visitor->visitOnEnter(this);

//   for (core::NodePtr_t node : getChildren())
//     static_cast<List *>(node)->accept(visitor);
// }

auto List::traverse(core::typedefs::TraverserSharedPtr_t traverser) -> u32_t {
  return core::toBase(core::TraverserAction::Enum::NONE);
}

void List::update() {
  // Empty
}

void List::makeItem(u32_t index, std::shared_ptr<webcore::mvc::AView> item) {
  // auto collection = static_cast<webcore::ACollectionModel *>(getModel());
  // item->setNodeId(core::format("%s_%i", item->getNodeId().c_str(), index));
  // item->setModel(collection->getItem(index));
  item->initialize();
  addChildNode(item);
}

}  // namespace sway::webui
