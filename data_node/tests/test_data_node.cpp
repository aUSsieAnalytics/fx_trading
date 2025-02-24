#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace DataNodes;

TEST(DataTest, Initialization) {
  IDataNode::clear_registry();
  auto source = DataNode<>::create();
  auto hi_node = DataNode<>::create("hi");
  for (int i = 0; i < 100; i++) {
    hi_node = DataNode<>::create(std::to_string(i), "hi");
  }
  string hash = source->get_hash();
  ASSERT_EQ(hash, DataNode<>::create()->get_hash());
  string blah = "(" + string(typeid(IDataNode).name()) + ")" + "{" + DataNode<>::type_id + "}: ";
  ASSERT_EQ(hash, sha256("(" + string(typeid(IDataNode).name()) + ")" + "{" + DataNode<>::type_id +
                         "}: "));
  ASSERT_NE(hash, hi_node->get_hash());
  ASSERT_EQ(
      DataNode<>::create("hi")->get_hash(),
      sha256("(" + string(typeid(IDataNode).name()) + ")" + "{" + DataNode<>::type_id + "}: hi"));
  {
    // test scoping
    auto x = IDataNode::ScopeLock("local");
    ASSERT_NE(
        DataNode<>::create("hi")->get_hash(),
        sha256("(" + string(typeid(IDataNode).name()) + ")" + "{" + DataNode<>::type_id + "}: hi"));
    ASSERT_EQ(DataNode<>::create("hi")->get_hash(),
              sha256("local: (" + string(typeid(IDataNode).name()) + ")" + "{" +
                     DataNode<>::type_id + "}: hi"));
    ASSERT_EQ(DataNode<>::create("hi")->get_scope(), "local");
  }
  // check that scope was cleared
  ASSERT_EQ(
      DataNode<>::create("hi")->get_hash(),
      sha256("(" + string(typeid(IDataNode).name()) + ")" + "{" + DataNode<>::type_id + "}: hi"));
}

TEST(DataTest, AddSource) {
  IDataNode::clear_registry();
  auto root = DataNode<>::create();
  auto second = DataNode<IDataNode, int>::create();
  ASSERT_EQ(root->get_upstream_nodes().size(), 0);
  root->add_upstream_node(second);
  ASSERT_EQ(root->get_upstream_nodes().size(), 1);
  ASSERT_EQ(root->get_downstream_nodes().size(), 0);
  ASSERT_EQ(second->get_downstream_nodes().size(), 1);
}

TEST(DataTest, CollectLeafNodes) {
  IDataNode::clear_registry();
  auto root = DataNode<>::create();
  auto leaf1 = DataNode<IDataNode, int>::create();
  auto second = DataNode<>::create("hi");
  root->add_upstream_node(second);
  auto leaves = get_leaf_nodes(root);
  ASSERT_EQ(leaves->size(), 1);
  ASSERT_EQ(get_leaf_nodes(leaf1)->size(), 1);
}
