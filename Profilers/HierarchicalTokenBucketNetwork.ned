package tirtproject.Profilers;

import tirtproject.Generators.*;


network HierarchicalTokenBucketNetwork
{
    submodules:
        gen: PoissonGenerator;
        bucket: HierarchicalTokenBucket;
        sink: Node;
    connections:
        gen.out --> bucket.in;
        bucket.out --> sink.in;
}

simple HierarchicalTokenBucket
{
    parameters:
        volatile double tokenArrivalInterval1 @unit(s);
        volatile double tokenArrivalInterval2 @unit(s);
        volatile double tokenArrivalInterval3 @unit(s);
        volatile double tokenArrivalInterval4 @unit(s);
        volatile int tokenCount;
        @display("i=block/bucket,#0080C0");
    gates:
        input in;
        output out;
}

