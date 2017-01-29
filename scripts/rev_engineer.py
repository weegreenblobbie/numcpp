import sys

import numpy as np


def addr(array):
    return array.__array_interface__['data'][0]


def strides_(array):
    return array.__array_interface__['strides']


def debug_print(ref, array):

    offset = addr(array) - addr(ref)
    offset /= array.itemsize

    strides = strides_(array)

    if strides is not None:
        strides = [x/array.itemsize for x in strides]

    print("offset = %s" % repr(offset))
    print("strides = %s" % repr(strides))

    # compute elment display width
    width = len(str(array.max()))

    fmt0 = " %{}s ".format(width)
    fmt1 = " " + "x" * width + " "
    fmt2 = "[%{}s]".format(width)

    if array.ndim == 1:

        step = 1

        if strides is not None:
            step = strides[0]

        if step < 0:
            array = array[::-1]

        a = iter(ref)
        b = iter(array)

        bb = b.next()

        for i in range(ref.size):

            aa = a.next()

            if i == offset:
                sys.stdout.write(fmt2 % aa)

                if aa == bb:
                    try:
                        bb = b.next()
                    except:
                        pass

            elif aa == bb:
                sys.stdout.write(fmt0 % aa)
                try:
                    bb = b.next()
                except:
                    pass

            else:
                sys.stdout.write(fmt1)

        print("")

    elif array.ndim == 2:

        step0 = 1
        step1 = 1

        if strides is not None:
            step0 = strides[0]

            if len(strides) == 2:
                step1 = strides[1]

        if step0 < 0:
            array = array[::-1, :]

        if step1 < 0:
            array = array[:, ::-1]

        a = iter(ref.reshape((ref.size)))
        b = iter(array.reshape((array.size)))

        bb = b.next()

        for m in range(ref.shape[0]):
            for n in range(ref.shape[1]):

                aa = a.next()

                idx = m * ref.shape[1] + n

                if idx == offset:

                    sys.stdout.write(fmt2 % aa)

                    if aa == bb:
                        try:
                            bb = b.next()
                        except:
                            pass

                elif aa == bb:
                    sys.stdout.write(fmt0 % aa)
                    try:
                        bb = b.next()
                    except:
                        pass

                else:
                    sys.stdout.write(fmt1)

            print("")

    elif array.ndim == 3:

        print("array[0,0,0] = %s" % array[0,0,0])

        i,j,k = 1,1,1

        if array.shape[0] == 1: i = 0
        if array.shape[1] == 1: j = 0
        if array.shape[2] == 1: k = 0

        print("array[%d,%d,%d] = %s" % (i,j,k,array[i,j,k]))

        step0 = 1
        step1 = 1
        step2 = 1

        if strides is not None:
            step0 = strides[0]

            if len(strides) >= 2:
                step1 = strides[1]

            if len(strides) >= 3:
                step2 = strides[2]

        if step0 < 0:
            array = array[::-1, :, :]

        if step1 < 0:
            array = array[:, ::-1, :]

        if step2 < 0:
            array = array[:, :, ::-1]

        a = iter(ref.reshape((ref.size)))
        b = iter(array.reshape((array.size)))

        bb = b.next()

        for i in range(ref.shape[0]):
            for j in range(ref.shape[1]):
                for k in range(ref.shape[2]):

                    aa = a.next()

                    idx = i * ref.shape[1] * ref.shape[2] + j * ref.shape[2] + k

                    if idx == offset:

                        sys.stdout.write(fmt2 % aa)

                        if aa == bb:
                            try:
                                bb = b.next()
                            except:
                                pass

                    elif aa == bb:
                        sys.stdout.write(fmt0 % aa)
                        try:
                            bb = b.next()
                        except:
                            pass

                    else:
                        sys.stdout.write(fmt1)

                print("")

            print("")

        print("")

    print("")


def main():

    a = np.arange(17).astype(np.int32)

    print("-" * 60)
    print("a = arange(17)")
    debug_print(a, a)

    print("a[5:]")
    debug_print(a, a[5:])

    print("a[2:-2]")
    debug_print(a, a[2:-2])

    print("a[::-2]")
    debug_print(a, a[::-2])

    print("a[3:13:3]")
    debug_print(a, a[3:13:3])


    a = np.arange(100).reshape(10,10)

    print("-" * 60)
    print("a = arange(100).reshape(10,10)")
    debug_print(a, a)

    print("a[0:-1]")
    debug_print(a, a[0:-1])

    print("a[1:-1]")
    debug_print(a, a[1:-1])

    print("a[:, 1:-1]")
    debug_print(a, a[:, 1:-1])

    print("a[1:-1, 1:-1]")
    debug_print(a, a[1:-1, 1:-1])

    print("a[::2, :]")
    debug_print(a, a[::2, :])

    print("a[:, ::2]")
    debug_print(a, a[:, ::2])

    print("a[:, ::-2]")
    debug_print(a, a[:, ::-2])

    print("a[::-2, :]")
    debug_print(a, a[::-2, :])

    print("a[::-2, ::-2]")
    debug_print(a, a[::-2, ::-2])

    print("a[-2:1:-2, -2:1:-2]")
    debug_print(a, a[-2:1:-2, -2:1:-2])


    a = np.arange(3*4*4).reshape(3, 4, 4)

    print("-" * 60)
    print("a = np.arange(60).reshape(3, 5,4)")
    debug_print(a, a)

    print("a[0:-1]")
    debug_print(a, a[0:-1])

    print("a[1:-1]")
    debug_print(a, a[1:-1])

    print("a[:, 1:-1]")
    debug_print(a, a[:, 1:-1])

    print("a[1:-1, 1:-1]")
    debug_print(a, a[1:-1, 1:-1])

    print("a[::2, :]")
    debug_print(a, a[::2, :])

    print("a[:, ::2]")
    debug_print(a, a[:, ::2])

    print("a[:, ::-2]")
    debug_print(a, a[:, ::-2])

    print("a[::-2, :]")
    debug_print(a, a[::-2, :])

    print("a[::-2, ::-2]")
    debug_print(a, a[::-2, ::-2])

    print("a[:,-2:1:-2, -1:1:-2]")
    debug_print(a, a[:, -2:1:-2, -2:1:-2])


if __name__ == "__main__": main()