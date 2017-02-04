"""

Copyright 2014
The Intellisis Corporation

All rights reserved.

"""

import datetime
import fnmatch
import glob
import os
import shlex
import sys

import SCons

from SCons.Action import Action
from SCons.Script import AddOption
from SCons.Script import Exit
from SCons.Script import File
from SCons.Script import GetLaunchDir
from SCons.Script import GetOption
from SCons.Script import Glob


#--------------------------------------------------------------------------
# Globals & constants

TOOLS_DIR = os.path.abspath(os.path.dirname(__file__))
VERBOSE = GetOption("verbose")


def recursive_glob(path, pattern):
    '''
    Recursively walks the directory tree globbing for pattern.
    '''

    sources = []

    for root, dirnames, filenames in os.walk(path):
        for filename in fnmatch.filter(filenames, pattern):
            sources.extend(glob.glob(os.path.join(root, filename)))

    return sources


def rebuild_cog(env, *args, **kwargs):
    '''
    forces a rebuild of all .cog files.
    '''

    # Glob for all .cog files

    filelist = recursive_glob(GetLaunchDir(), "*.cog")

    # remove .cog targets

    targets = []

    for f in filelist:

        target, _ = os.path.splitext(f)

        # Remove target

        if os.path.isfile(target):
            os.remove(target)

        targets.append(target)

    # Rebuild targets

    prefix = GetLaunchDir()

    os.chdir(prefix)

    cmd = sys.argv

    PYTHON = sys.executable

    cmd.insert(0, PYTHON)
    cmd.remove('--cog')
    cmd.append('-Q')
    cmd.append('--no-cache')

    for t in targets:
        cmd.append(t)

    ecode = os.system(" ".join(cmd))

    if ecode != 0:
        raise RuntimeError("Failed to execute: %s" % " ".join(cmd))

    Exit(0)


def _get_target(target, source, env):
    """
    Utility to create the File() node for the target fhex file.
    """

    target, _ = os.path.splitext(str(source[0]))

    return [target]


def emitter(target, source, env):

    src = source[0].get_abspath()

    if not src.endswith('.cog'):
        raise SCons.Errors.UserError(
            "Source '%s' must end with extension '.cog'" % source[0])

    target = _get_target(target, source, env)

    tool = str(File(__file__))

    if tool.endswith(".pyc"):
        tool = tool[:-1]

    env.Depends(target, tool)

    return target, source


def generate(env):

    env['COG'] = exists(env)

    python = File(sys.executable).get_abspath()

    # windows fixes
    python = python.replace("\\", "\\\\")

    env['PYTHON'] = python

    # default cog flags

    env['COGFLAGS'] = ''.join([
        '-d ',  # deletes the generator code from the output
        '-e ',  # warns if the input file has no cog code in it.
        '-I submods/xgen_ws ', # includes in python path
        '-I "%s" ' % TOOLS_DIR, # include the tools dir so cog_warnign can be imported
        '-D __COGFILE__="$SOURCE" ', # defines a global string for cog program
    ])

    cmd = '$PYTHON -m cogapp -o $TARGET $COGFLAGS $SOURCE'

    env['COGCOM'] = cmd

    action = Action('$COGCOM', '$COGCOMSTR')

    bld = env.Builder(
        action = [action],
        emitter = emitter,
        )

    env['BUILDERS']['Cog'] = bld
    env['BUILDERS']['rebuild_cog'] = rebuild_cog

    if not VERBOSE:
        env['COGCOMSTR'] = 'Processing $SOURCE --> $TARGET'

    AddOption(
        "--cog",
        dest = "cog",
        action = "store_true",
        default = False,
        help = "Forces .cog files to be rebuilt")


def exists(env):

    try:
        import cogapp
        return True

    except ImportError:

        sys.stderr.write("""
The python mdoule 'cogapp' wasn't detected!  You should be able to install
it with:

    pip install cogapp

""")

    return False