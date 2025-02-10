#pragma once

#include <memory>
#include <time.h>
#include <vector>

template <typename T> class DataNode;

typedef std::variant<std::shared_ptr<DataNode<int>>, std::shared_ptr<DataNode<double>>,
                     std::shared_ptr<DataNode<std::string>>>
    DataNodeShrPtr;
typedef std::variant<std::weak_ptr<DataNode<int>>, std::weak_ptr<DataNode<double>>,
                     std::weak_ptr<DataNode<std::string>>>
    DataNodeWeakPtr;

template <typename T> class DataNode {
  std::vector<T> _data;
  std::vector<DataNodeShrPtr> _pull_data;
  std::vector<DataNodeWeakPtr> _push_data;

public:
  DataNode() : _data(), _pull_data(), _push_data() {}
  std::vector<DataNodeShrPtr> get_pull_data() { return _pull_data; }
  std::vector<DataNodeWeakPtr> get_push_data() { return _push_data; }
  void add_pull_node(DataNodeShrPtr data) { _pull_data.push_back(data); }
  void add_push_node(DataNodeWeakPtr data) { _push_data.push_back(data); }
  virtual std::vector<T> get_data() { return _data; };
};
