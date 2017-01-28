import numpy as np

y = np.arange(10)

pool = np.arange(-10,9+6)

_ = 10

template = '''\
    SECTION(" {slice_} ")
    {{
        s = {slice_};
        a = axis_iterator(10, s);
        gold = {gold};

        CHECK( a.indices() == gold );
    }}
'''

i = 0

while i < 1000:

    np.random.shuffle(pool)

    start, stop, step = pool[:3]

    if step == 0: continue

    # :b
    if start >= _ and stop < _ and step >= _:
        gold = y[:stop]
        slice_ = "_ | %d" % stop

    # 5:
    elif start < _ and stop >= _ and step >= _:
        gold = y[start:]
        slice_ = "%d | _" % start

    # ::c
    elif start >= _ and stop >= _ and step < _:
        gold = y[::step]
        slice_ = "_ | _ | %d" % step

    # a:b
    elif start < _ and stop < _ and step >= _:
        gold = y[start:stop]
        slice_ = "%d_s | %d" % (start, stop)

    # a:b:c
    elif start < _ and stop < _ and step < _:
        gold = y[start:stop:step]
        slice_ = "%d_s | %d | %d" % (start, stop, step)

    # a::c
    elif start < _ and stop >= _ and step < _:
        gold = y[start::step]
        slice_ = "%d | _ | %d" % (start, step)

    # :b:c
    elif start >= _ and stop < _ and step < _:
        gold = y[:stop:step]
        slice_ = "_ | %d | %d" % (stop, step)

    # ::
    elif start >= _ and stop >= _ and step >= _:
        continue

    else:
        print("start = %s" % repr(start))
        print("stop = %s" % repr(stop))
        print("step = %s" % repr(step))

        xxxxxxxxxx

        continue

    i += 1

    if len(gold) > 0:
        g = '{%d' % gold[0]
        for x in gold[1:]:
            g += ', %d' % x
        g += '}'

        gold = g

    else:
        gold = "{}"

    if start >= _: start = '_'
    if stop  >= _: stop = '_'
    if step  >= _: step = '_'

    code = template.format(**locals())

    print(code)
