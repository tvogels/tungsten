// ======================================================================== //
// Copyright 2009-2013 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "bvh4_intersector4_single.h"
#include "bvh4_intersector1.h"
#include "../geometry/triangles.h"

namespace embree
{
  template<typename TriangleIntersector1>
  void BVH4Intersector4Single<TriangleIntersector1>::intersect(const BVH4Intersector4Single* This, Ray4& ray, const __m128 valid_i)
  {
    AVX_ZERO_UPPER();

    /* iterate over all active rays */
    const BVH4* bvh = This->bvh;
    sseb valid = valid_i;
    size_t bits = movemask(valid);
    const sse3f rdir = rcp_safe(ray.dir);
    for (size_t i=__bsf(bits); bits!=0; bits=__btc(bits,i), i=__bsf(bits)) {
      BVH4Intersector1<TriangleIntersector1>::intersect1(bvh,bvh->root,i,ray,rdir);
    }

    AVX_ZERO_UPPER();
  }

  template<typename TriangleIntersector1>
  __m128 BVH4Intersector4Single<TriangleIntersector1>::occluded(const BVH4Intersector4Single* This, Ray4& ray, const __m128 valid_i)
  {
    AVX_ZERO_UPPER();

    /* iterate over all active rays */
    const BVH4* bvh = This->bvh;
    sseb valid = valid_i;
    ssei not_occluded = -1;
    size_t bits = movemask(valid);
    const sse3f rdir = rcp_safe(ray.dir);
    for (size_t i=__bsf(bits); bits!=0; bits=__btc(bits,i), i=__bsf(bits)) {
      if (BVH4Intersector1<TriangleIntersector1>::occluded1(bvh,bvh->root,i,ray,rdir))
        not_occluded[i] = 0;
    }
    AVX_ZERO_UPPER();

    return valid & (not_occluded == ssei(0));
  }

  void BVH4Intersector4SingleRegister () 
  {
    //TriangleMesh::intersectors4.add("bvh4","triangle1i","single","moeller" ,false,BVH4Intersector4Single<Triangle1iIntersector1<Intersector1MoellerTrumbore> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle1i","single","pluecker",true ,BVH4Intersector4Single<Triangle1iIntersector1<Intersector1Pluecker> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle1v","single","moeller" ,false,BVH4Intersector4Single<Triangle1vIntersector1<Intersector1MoellerTrumbore> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle1v","single","pluecker",true ,BVH4Intersector4Single<Triangle1vIntersector1<Intersector1Pluecker> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle4i","single","moeller" ,false,BVH4Intersector4Single<Triangle4iIntersector1<Intersector1MoellerTrumbore> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle4i","single","pluecker",true ,BVH4Intersector4Single<Triangle4iIntersector1<Intersector1Pluecker> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle4v","single","moeller" ,false,BVH4Intersector4Single<Triangle4vIntersector1<Intersector1MoellerTrumbore> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle4v","single","pluecker",true ,BVH4Intersector4Single<Triangle4vIntersector1<Intersector1Pluecker> >::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle1" ,"single","moeller" ,true ,BVH4Intersector4Single<Triangle1Intersector1MoellerTrumbore>::create);
    TriangleMesh::intersectors4.add("bvh4","triangle4" ,"single","moeller" ,true ,BVH4Intersector4Single<Triangle4Intersector1MoellerTrumbore>::create);
    //TriangleMesh::intersectors4.add("bvh4","triangle8" ,"single","moeller" ,true ,BVH4Intersector4Single<Triangle8Intersector1MoellerTrumbore>::create);
    //VirtualScene::intersectors4.add("bvh4","virtual"   ,"single","virtual" ,true ,BVH4Intersector4Single<VirtualObjectIntersector1>::create);
  }
}
