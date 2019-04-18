Simple C tracer
===============

Preparatory investigation for developing a software tracer
for [ERIKA Enterprise](http://www.erika-enterprise.com).

The tracer is roughly based on the ftrace approach (i.e. mcount function of
gcc, enabled through the `-pg` option).

The simple `run.py` script converts the trace to the
[BTF format](https://www.eclipse.org/app4mc/docu/standards/TA_BTF_Specification_2.1.5.pdf),
that can be viewed through [Eclipse Trace Compass](https://www.eclipse.org/tracecompass/).

TODO
====
* Simplify trampoline
* Restore pointer to enable/disable tracing
* Data structure for saving information at the end of execution
* Get and save function arguments
* Hijack trampoline to be called when the function ends execution
* Port to ERIKA Enterprise
