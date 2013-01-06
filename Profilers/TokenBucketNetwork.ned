package tirtproject.Profilers;

import tirtproject.Generators.*;


network TokenBucketNetwork
{
    submodules:
        gen: PoissonGenerator;
        bucket: TokenBucket;
        sink: Node;
    connections:
        gen.out --> bucket.in;
        bucket.out --> sink.in;
}

simple TokenBucket
{
    parameters:
        volatile double tokenArrivalInterval @unit(s);
        volatile int tokenCount;
        @display("i=block/bucket,#0080C0");
    gates:
        input in;
        output out;
}

