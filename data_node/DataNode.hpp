#pragma once

#include <memory>
#include <time.h>
#include <vector>

template <typename T> class DataNode;

typedef std::variant<std::shared_ptr<DataNode<int>>, std::shared_ptr<DataNode<double>>,
                     std::shared_ptr<DataNode<std::string>>>
    DataShrPtr;
typedef std::variant<std::weak_ptr<DataNode<int>>, std::weak_ptr<DataNode<double>>,
                     std::weak_ptr<DataNode<std::string>>>
    DataWeakPtr;

template <typename T> class DataNode {
  std::vector<T> _data;
  std::vector<DataShrPtr> _pull_data;
  std::vector<DataWeakPtr> _push_data;

public:
  DataNode() {}
  std::vector<DataShrPtr> get_pull_data() { return _pull_data; }
  std::vector<DataWeakPtr> get_push_data() { return _push_data; }
  void add_pull_data(DataShrPtr data) { _pull_data.push_back(data); }
  void add_push_data(DataShrPtr data) { _push_data.push_back(data); }
  virtual std::vector<T> get_data() { return _data; };
};
