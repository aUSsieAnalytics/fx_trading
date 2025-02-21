#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) {
  IDataNode::clear_registry();
  auto source = DataNode<>::create("DataNode", DataNode<>::type_id);
  auto hi_node = DataNode<>::create("DataNode", DataNode<>::type_id, "hi");
  for (int i = 0; i < 100; i++) {
    hi_node = DataNode<>::create("DataNode", DataNode<>::type_id, std::to_string(i), "hi");
  }
  string hash = source->get_hash();
  ASSERT_EQ(hash, DataNode<>::create("DataNode", DataNode<>::type_id)->get_hash());
  ASSERT_EQ(hash, sha256("DataNode(" + DataNode<>::type_id + "): "));
  ASSERT_NE(hash, hi_node->get_hash());
  ASSERT_EQ(DataNode<>::create("DataNode", DataNode<>::type_id, "hi")->get_hash(),
            sha256("DataNode(" + DataNode<>::type_id + "): hi"));
  {
    // test scoping
    auto x = IDataNode::ScopeLock("local");
    ASSERT_NE(DataNode<>::create("DataNode", DataNode<>::type_id, "hi")->get_hash(),
              sha256("DataNode(" + DataNode<>::type_id + "): hi"));
    ASSERT_EQ(DataNode<>::create("DataNode", DataNode<>::type_id, "hi")->get_hash(),
              sha256("local: DataNode(" + DataNode<>::type_id + "): hi"));
    ASSERT_EQ(DataNode<>::create("DataNode", DataNode<>::type_id, "hi")->get_scope(), "local");
  }
  // check that scope was cleared
  ASSERT_EQ(DataNode<>::create("DataNode", DataNode<>::type_id, "hi")->get_hash(),
            sha256("DataNode(" + DataNode<>::type_id + "): hi"));
}

TEST(DataTest, AddSource) {
  IDataNode::clear_registry();
  auto root = DataNode<>::create("DataNode", DataNode<>::type_id);
  auto second = DataNode<IDataNode, int>::create("DataNode", DataNode<IDataNode, int>::type_id);
  ASSERT_EQ(root->get_upstream_nodes().size(), 0);
  root->add_upstream_node(second);
  ASSERT_EQ(root->get_upstream_nodes().size(), 1);
  ASSERT_EQ(root->get_downstream_nodes().size(), 0);
  ASSERT_EQ(second->get_downstream_nodes().size(), 1);
}

TEST(DataTest, CollectLeafNodes) {
  IDataNode::clear_registry();
  auto root = DataNode<>::create("DataNode", DataNode<>::type_id);
  auto leaf1 =
      DataNode<IDataNode, double>::create("DataNode", DataNode<IDataNode, double>::type_id);
  auto second = DataNode<>::create("DataNode", DataNode<>::type_id, "hi");
  root->add_upstream_node(second);
  auto leaves = get_leaf_nodes(root);
  ASSERT_EQ(leaves->size(), 1);
  ASSERT_EQ(get_leaf_nodes(leaf1)->size(), 1);
}
