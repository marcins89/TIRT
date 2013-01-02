package tirtproject.Profilers;

import tirtproject.Generators.*;


network DoubleTokenBucketNetwork
{
    submodules:
        gen: PoissonGenerator;
        bucket: DoubleTokenBucket;
        sink: Node;
    connections:
        gen.out --> bucket.in;
        bucket.out --> sink.in;
}

simple DoubleTokenBucket
{
    parameters:
        volatile double tokenArrivalInterval @unit(s);
        volatile int tokenCount;
        volatile double serviceTime @unit(s);
        volatile int buffer;
        @display("i=block/bucket,#0080C0");
    gates:
        input in;
        output out;
}

