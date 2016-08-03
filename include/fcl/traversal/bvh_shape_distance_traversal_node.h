/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011-2014, Willow Garage, Inc.
 *  Copyright (c) 2014-2016, Open Source Robotics Foundation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Open Source Robotics Foundation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/** \author Jia Pan */

#ifndef FCL_TRAVERSAL_BVHSHAPEDISTANCETRAVERSALNODE_H
#define FCL_TRAVERSAL_BVHSHAPEDISTANCETRAVERSALNODE_H

#include "fcl/traversal/distance_traversal_node_base.h"
#include "fcl/BVH/BVH_model.h"

namespace fcl
{

/// @brief Traversal node for distance computation between BVH and shape
template<typename BV, typename S>
class BVHShapeDistanceTraversalNode
    : public DistanceTraversalNodeBase<typename BV::Scalar>
{
public:

  using Scalar = typename BV::Scalar;

  BVHShapeDistanceTraversalNode();

  /// @brief Whether the BV node in the first BVH tree is leaf
  bool isFirstNodeLeaf(int b) const;

  /// @brief Obtain the left child of BV node in the first BVH
  int getFirstLeftChild(int b) const;

  /// @brief Obtain the right child of BV node in the first BVH
  int getFirstRightChild(int b) const;

  /// @brief BV culling test in one BVTT node
  Scalar BVTesting(int b1, int b2) const;

  const BVHModel<BV>* model1;
  const S* model2;
  BV model2_bv;

  mutable int num_bv_tests;
  mutable int num_leaf_tests;
  mutable Scalar query_time_seconds;
};

//============================================================================//
//                                                                            //
//                              Implementations                               //
//                                                                            //
//============================================================================//

//==============================================================================
template<typename BV, typename S>
BVHShapeDistanceTraversalNode<BV, S>::BVHShapeDistanceTraversalNode()
  : DistanceTraversalNodeBase<typename BV::Scalar>()
{
  model1 = NULL;
  model2 = NULL;

  num_bv_tests = 0;
  num_leaf_tests = 0;
  query_time_seconds = 0.0;
}

//==============================================================================
template<typename BV, typename S>
bool BVHShapeDistanceTraversalNode<BV, S>::isFirstNodeLeaf(int b) const
{
  return model1->getBV(b).isLeaf();
}

//==============================================================================
template<typename BV, typename S>
int BVHShapeDistanceTraversalNode<BV, S>::getFirstLeftChild(int b) const
{
  return model1->getBV(b).leftChild();
}

//==============================================================================
template<typename BV, typename S>
int BVHShapeDistanceTraversalNode<BV, S>::getFirstRightChild(int b) const
{
  return model1->getBV(b).rightChild();
}

//==============================================================================
template<typename BV, typename S>
typename BV::Scalar BVHShapeDistanceTraversalNode<BV, S>::BVTesting(
    int b1, int b2) const
{
  return model1->getBV(b1).bv.distance(model2_bv);
}

} // namespace fcl

#endif