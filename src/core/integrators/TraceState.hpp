#ifndef TRACESTATE_HPP_
#define TRACESTATE_HPP_

#include "volume/Medium.hpp"

#include "math/Ray.hpp"

namespace Tungsten {

class SampleGenerator;

// TODO: Modify TraceBase to primarily take/return TraceState as parameter
struct TraceState
{
    SampleGenerator &sampler;
    SampleGenerator &supplementalSampler;
    Medium::MediumState mediumState;
    const Medium *medium;
    bool wasSpecular;
    Ray ray;
    int bounce;

    TraceState(SampleGenerator &sampler_, SampleGenerator &supplementalSampler_)
    : sampler(sampler_),
      supplementalSampler(supplementalSampler_),
      medium(nullptr),
      wasSpecular(true),
      ray(Vec3f(0.0f), Vec3f(0.0f)),
      bounce(0)
    {
        mediumState.reset();
    }
};

}

#endif /* TRACESTATE_HPP_ */