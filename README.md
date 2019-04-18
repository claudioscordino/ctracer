Simple C tracer
===============

Preparatory investigation for developing a software tracer
for [http://www.erika-enterprise.com](ERIKA Enterprise).

The tracer is roughly based on the ftrace approach (i.e. mcount function of
gcc, enabled through the `-pg` option).

The simple `run.py` script converts the trace to the
[https://www.eclipse.org/app4mc/docu/standards/TA_BTF_Specification_2.1.5.pdf](BTF format),
that can be viewed through [https://www.eclipse.org/tracecompass/](Eclipse Trace Compass).
