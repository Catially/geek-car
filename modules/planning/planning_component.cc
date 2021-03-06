/******************************************************************************
 * MIT License

 * Copyright (c) 2019 Geekstyle

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
******************************************************************************/
#include "modules/planning/planning_component.h"
#include "modules/common/global_gflags.h"

namespace apollo {
namespace planning {

using apollo::planning::Point;

bool PlanningComponent::Init() {
  writer_ = node_->CreateWriter<Trajectory>(FLAGS_planning_channel);

  reader_ = node_->CreateReader<PlanningInfo>(
      FLAGS_routing_channel,
      [this](const std::shared_ptr<PlanningInfo>& routing) {
        // this->Plan(routing);
        routing_ = routing;
      });

  Plan();

  return true;
}

void PlanningComponent::Plan() {
  if (routing_.empty()) {
    AERROR << "routing message is empty";
  }

  endPoint.x = routing_.x();
  endPoint.y = routing_.y();
}

}  // namespace planning
}  // namespace apollo
