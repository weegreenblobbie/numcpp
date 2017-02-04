"""

Copyright 2015
The Intellisis Corporation

All rights reserved.

"""

#-----------------------------------------------------------------------------
# globals & constants

WARNING = """\
-----------------------------------------------------------------------------

                         CCCCC   OOOOO   GGGGG
                         C       O   O   G
                         C       O   O   G  GG
                         C       O   0   G   G
                         CCCCC   OOOOO   GGGGG

   WARNING! This file is generated!!
   WARNING! This file is generated!!
   WARNING! This file is generated!!

   To make changes, edit: {filename}

-----------------------------------------------------------------------------"""


def warn(cog, filename, prefix = ''):

    template = WARNING.format(filename = filename)

    for l in template.split('\n'):
        cog.outl('//' + l)
