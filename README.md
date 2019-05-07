Simple C tracer
===============

Preparatory investigation for developing a software tracer
for [ERIKA Enterprise](http://www.erika-enterprise.com).

The tracer is roughly based on the ftrace approach (i.e. `__fentry__` or
`mcount` functions of gcc, enabled through the `-pg` option).

Example of usage
================

Once compiled (type `make`) the `./main` executable writes a `trace.dat` file
containing symbols and timestamps:

    ./main

Then, the `create_trace.py` script can convert the trace to the
[BTF format](https://www.eclipse.org/app4mc/docu/standards/TA_BTF_Specification_2.1.5.pdf),
that can be viewed through [Eclipse Trace Compass](https://www.eclipse.org/tracecompass/):

    ./create_trace.py ./main trace.dat

TODO
====
* Hijack trampoline to be called when the function ends execution
* Port to aarch64
* Port to ERIKA Enterprise
