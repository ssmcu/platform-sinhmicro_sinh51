# Copyright 2014-present PlatformIO <contact@platformio.org>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import sys
from os.path import join

from SCons.Script import ARGUMENTS, AlwaysBuild, Default, DefaultEnvironment


def __getSize(size_type, env):
    # FIXME: i don't really know how to do this right. see:
    #        https://community.platformio.org/t/missing-integers-in-board-extra-flags-in-board-json/821
    return str(env.BoardConfig().get("build", {
        # defaults
        "size_heap": 1024,
        "size_iram": 256,
        "size_xram": 65536,
        "size_code": 65536,
    })[size_type])


def _parseSdccFlags(flags):
    assert flags
    if isinstance(flags, list):
        flags = " ".join(flags)
    flags = str(flags)
    parsed_flags = []
    unparsed_flags = []
    prev_token = ""
    for token in flags.split(" "):
        if prev_token.startswith("--") and not token.startswith("-"):
            parsed_flags.extend([prev_token, token])
            prev_token = ""
            continue
        if prev_token:
            unparsed_flags.append(prev_token)
        prev_token = token
    unparsed_flags.append(prev_token)
    return (parsed_flags, unparsed_flags)


env = DefaultEnvironment()
board_config = env.BoardConfig()

env.Replace(
    AR="sdar",
    AS="sdas8051",
    CC="sdcc",
    LD="sdld",
    RANLIB="sdranlib",
    OBJCOPY="sdobjcopy",
    MAKEBIN="makebin",
    OBJSUFFIX=".rel",
    LIBSUFFIX=".lib",
    SIZETOOL=join(env.PioPlatform().get_dir(), "builder", "size.py"),

    SIZECHECKCMD='$PYTHONEXE $SIZETOOL $SOURCES',
    SIZEPRINTCMD='"$PYTHONEXE" $SIZETOOL $SOURCES',
    SIZEPROGREGEXP=r"^ROM/EPROM/FLASH\s+[a-fx\d]+\s+[a-fx\d]+\s+(\d+).*",

    PROGNAME="firmware",
    PROGSUFFIX=".hex"
)

env.Append(
    ASFLAGS=env.get("CCFLAGS", [])[:],

    CFLAGS=[
        "--std-sdcc11"
    ],

    CCFLAGS=[
        "--opt-code-size",  # optimize for size
        "--peep-return",    # peephole optimization for return instructions
        "-m%s" % board_config.get("build.cpu")
    ],

    CPPDEFINES=[
        "F_CPU=$BOARD_F_CPU",
        #"HEAP_SIZE=" + __getSize("size_heap", env)
    ],

    LINKFLAGS=[
        "-m%s" % board_config.get("build.cpu"),
        "--iram-size", __getSize("size_iram", env),
        "--xram-size", __getSize("size_xram", env),
        "--code-size", __getSize("size_code", env),
        "--out-fmt-ihx"
    ],
	
    BUILDERS=dict(
        HexToBin=Builder(
            action=" ".join([
                "$MAKEBIN",
                "-p",
                "$SOURCES",
                "$TARGET"]),
            suffix=".bin"
        )
    )
)

if int(ARGUMENTS.get("PIOVERBOSE", 0)):
    env.Prepend(UPLOADERFLAGS=["-v"])

# parse manually SDCC flags
if env.get("BUILD_FLAGS"):
    _parsed, _unparsed = _parseSdccFlags(env.get("BUILD_FLAGS"))
    env.Append(CCFLAGS=_parsed)
    env['BUILD_FLAGS'] = _unparsed

project_sdcc_flags = None
if env.get("SRC_BUILD_FLAGS"):
    project_sdcc_flags, _unparsed = _parseSdccFlags(env.get("SRC_BUILD_FLAGS"))
    env['SRC_BUILD_FLAGS'] = _unparsed

#
# Target: Build executable and linkable firmware
#

target_firm = env.BuildProgram()

# Target: Build the .bin file
target_bin = env.HexToBin(join("$BUILD_DIR", "firmware"), target_firm)

if project_sdcc_flags:
    env.Import("projenv")
    projenv.Append(CCFLAGS=project_sdcc_flags)

AlwaysBuild(env.Alias("nobuild", target_bin))
target_buildprog = env.Alias("buildprog", target_bin, target_bin)

#
# Target: Print binary size
#

target_size = env.Alias(
    "size", target_bin,
    env.VerboseAction("$SIZEPRINTCMD", "Calculating size $SOURCE"))
AlwaysBuild(target_size)

#
# Setup default targets
#

Default([target_buildprog, target_size])
