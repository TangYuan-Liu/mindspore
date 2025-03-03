/**
 * Copyright 2022 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_CCSRC_BACKEND_OPTIMIZER_ASCEND_DYNAMIC_SHAPE_ASCEND_DYNAMIC_SHAPE_HELPER_H
#define MINDSPORE_CCSRC_BACKEND_OPTIMIZER_ASCEND_DYNAMIC_SHAPE_ASCEND_DYNAMIC_SHAPE_HELPER_H

#include <string>
#include "ir/anf.h"
#include "utils/ms_utils.h"
#include "backend/optimizer/common/optimizer.h"

namespace mindspore::opt::dynamic_shape {
bool IsGeneralOp(const BaseRef &n);
bool IsDynamicOp(const BaseRef &n);
bool IsInheritedDynamicOp(const BaseRef &n);
AnfNodePtr GenInferNode(const AnfNodePtr &node, bool fake_flag = false);
AnfNodePtr GenInitNode(const AnfNodePtr &node);
AnfNodePtr GenUpdateNode(const AnfNodePtr &node, bool just_sync_flag = false);
bool IsDynUpdate(const AnfNodePtr &node);

struct RelatedCustomActorNode {
  AnfNodePtr infer_node;
  AnfNodePtr init_node;
  AnfNodePtr update_node;
};

class CustomActorNodeManager {
 public:
  static CustomActorNodeManager &Instance();
  void Reset() { custom_nodes_map_.clear(); }
  void Register(const AnfNodePtr &node, const RelatedCustomActorNode &custom_nodes) {
    custom_nodes_map_.emplace(node, custom_nodes);
  }
  bool IsRegistered(const AnfNodePtr &node) const { return custom_nodes_map_.find(node) != custom_nodes_map_.end(); }
  const RelatedCustomActorNode &GetCustomActorNodes(const AnfNodePtr &node) const {
    if (auto iter = custom_nodes_map_.find(node); iter != custom_nodes_map_.end()) {
      return iter->second;
    }

    MS_LOG(EXCEPTION) << "Not registered node!";
  }

 private:
  CustomActorNodeManager() = default;
  ~CustomActorNodeManager() = default;
  DISABLE_COPY_AND_ASSIGN(CustomActorNodeManager)
  OrderedMap<AnfNodePtr, RelatedCustomActorNode> custom_nodes_map_;
};
}  // namespace mindspore::opt::dynamic_shape
#endif  // MINDSPORE_CCSRC_BACKEND_OPTIMIZER_ASCEND_DYNAMIC_SHAPE_ASCEND_DYNAMIC_SHAPE_HELPER_H
