package tirtproject.Profilers;

import tirtproject.Generators.*;


network LeakyBucketNetwork
{
    submodules:
        gen: PoissonGenerator;
        bucket: LeakyBucket;
        sink: Node;
    connections:
        gen.out --> bucket.in;
        bucket.out --> sink.in;
}

simple LeakyBucket
{
    parameters:
        volatile double serviceTime @unit(s);
        volatile int buffer;
        @display("i=block/bucket,#0080C0");
    gates:
        input in;
        output out;
}

